#include "StdAfx.h"

cRoleta::cRoleta() : _Active(false)
{
}

bool cRoleta::Load()
{
	this->_Count = 0;

	memset(this->RoletaStruct, 0, sizeof(this->RoletaStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Roleta.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Amount = Section.Rows[0].GetInt(1);

		strcpy_s(this->_Name, sizeof(this->_Name), (Section.Rows[0].GetStringPtr(2)));
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(3)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->RoletaStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->RoletaStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->RoletaStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			this->RoletaStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			this->RoletaStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			this->RoletaStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			this->RoletaStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->RoletaStruct[this->_Count]._Quantity = Section.Rows[i].GetInt(7);
			strcpy_s(this->RoletaStruct[this->_Count]._Name, sizeof(this->RoletaStruct[this->_Count]._Name), (Section.Rows[i].GetStringPtr(8)));
			this->_Count++;
		}
	}

	return true;
}

void cRoleta::Command(int aIndex)
{
	if (this->_Active && this->_Count > 0)
	{
		if (Custom[aIndex].Coin[0] < this->_Amount)
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de %s.", this->_Amount, this->_Name);
			return;
		}

		Custom[aIndex].Coin[0] -= this->_Amount;

		Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s - %d WHERE memb___id = '%s'", this->_Name, this->_Name, this->_Amount, gObj[aIndex].AccountID);

		int Sortear = rand() % this->_Count;

		for (int i = 0; i < this->RoletaStruct[Sortear]._Quantity; i++)
		{
			int Item = ITEMGET(this->RoletaStruct[Sortear]._Type, this->RoletaStruct[Sortear]._Index);

			if (!Func.InventoryFullCheck(aIndex, Item))
			{
				ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->RoletaStruct[Sortear]._Level, 0, this->RoletaStruct[Sortear]._Skill, this->RoletaStruct[Sortear]._Luck, this->RoletaStruct[Sortear]._Option, aIndex, this->RoletaStruct[Sortear]._Excelente);
			}
			else
			{
				ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, this->RoletaStruct[Sortear]._Level, 0, this->RoletaStruct[Sortear]._Skill, this->RoletaStruct[Sortear]._Luck, this->RoletaStruct[Sortear]._Option, aIndex, this->RoletaStruct[Sortear]._Excelente);
			}
		}

		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].Connected == 3)
			{
				Func.MsgOutput(i, 0, "[    ROLETA    ]");

				Func.MsgOutput(i, 0, "O jogador %s acabou de girar!", gObj[aIndex].Name);

				Func.MsgOutput(i, 0, "Prêmio: %s", this->RoletaStruct[Sortear]._Name);
			}
		}
	}
}

cRoleta Roleta;