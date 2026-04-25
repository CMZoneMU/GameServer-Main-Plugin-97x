#include "StdAfx.h"

cRank::cRank() : _Active(false), _Success(false), _List(0)
{
}

bool cRank::Load()
{
	this->_Count = 0;

	memset(this->RankStruct, 0, sizeof(this->RankStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Rank.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			strcpy_s(this->RankStruct[this->_Count]._Name, sizeof(this->RankStruct[this->_Count]._Name), (Section.Rows[i].GetStringPtr(0)));
			strcpy_s(this->RankStruct[this->_Count]._Column[0], sizeof(this->RankStruct[this->_Count]._Column[0]), (Section.Rows[i].GetStringPtr(1)));
			strcpy_s(this->RankStruct[this->_Count]._Column[1], sizeof(this->RankStruct[this->_Count]._Column[1]), (Section.Rows[i].GetStringPtr(2)));
			strcpy_s(this->RankStruct[this->_Count]._Column[2], sizeof(this->RankStruct[this->_Count]._Column[2]), (Section.Rows[i].GetStringPtr(3)));
			strcpy_s(this->RankStruct[this->_Count]._Column[3], sizeof(this->RankStruct[this->_Count]._Column[3]), (Section.Rows[i].GetStringPtr(4)));
			this->_Count++;
		}
	}

	return true;
}

void cRank::Command(int aIndex, char* msg)
{
	if (this->_Active)
	{
		if (gObj[aIndex].AuthorityCode > 1)
		{
			memset(this->_Name[0], 0, sizeof(this->_Name[0]));

			memset(this->_Name[1], 0, sizeof(this->_Name[1]));

			this->_Number = NULL;

			sscanf(msg, "%s %s %d", this->_Name[0], this->_Name[1], &this->_Number);

			int Index = Func.Get_PlayerIndex(this->_Name[0]);

			if (strlen(msg) < 3)
			{
				Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
				Func.MsgOutput(aIndex, 1, "Digite: %s <Nome> <Evento> <Número>", this->_Syntax);
				return;
			}
			else if (gObj[Index].Connected < 3)
			{
				Func.MsgOutput(aIndex, 1, "O jogador não está online!");
				return;
			}

			for (int i = 0; i < this->_Count; i++)
			{
				if (strcmp(this->_Name[1], this->RankStruct[i]._Name) == 0)
				{
					this->_Success = true;

					this->_List = i;
				}
			}

			if (this->_Success == true)
			{
				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						Func.MsgOutput(i, 0, "[   RANKING   ]");
						Func.MsgOutput(i, 0, "%s recebeu %d pontos no %s!", gObj[Index].Name, this->_Number, this->RankStruct[this->_List]._Name);
					}
				}

				Manager.ExecFormat("UPDATE Character SET %s = %s + %d, %s = %s + %d, %s = %s + %d, %s = %s + %d WHERE Name = '%s'", this->RankStruct[this->_List]._Column[0], this->RankStruct[this->_List]._Column[0], this->_Number, this->RankStruct[this->_List]._Column[1], this->RankStruct[this->_List]._Column[1], this->_Number, this->RankStruct[this->_List]._Column[2], this->RankStruct[this->_List]._Column[2], this->_Number, this->RankStruct[this->_List]._Column[3], this->RankStruct[this->_List]._Column[3], this->_Number, gObj[Index].Name);

				this->_Success = false;

				this->_List = NULL;
			}
			else
			{
				Func.MsgOutput(aIndex, 1, "Nome do evento incorreto ou não existe.");
			}
		}
	}
}

cRank Rank;