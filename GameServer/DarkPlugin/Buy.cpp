#include "StdAfx.h"

bool cBuy::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Buy.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(1)));

		this->_Amount[0] = Section.Rows[1].GetInt(0);
		strcpy_s(this->_Column[0], sizeof(this->_Column[0]), (Section.Rows[1].GetStringPtr(1)));
		strcpy_s(this->_Coin[0], sizeof(this->_Coin[0]), (Section.Rows[1].GetStringPtr(2)));

		this->_Amount[1] = Section.Rows[2].GetInt(0);
		strcpy_s(this->_Column[1], sizeof(this->_Column[1]), (Section.Rows[2].GetStringPtr(1)));
		strcpy_s(this->_Coin[1], sizeof(this->_Coin[1]), (Section.Rows[2].GetStringPtr(2)));
	}

	return true;
}

void cBuy::Run(int aIndex, char* msg)
{
	if (this->_Active == true && Command._Type == 1)
	{
		memset(this->_Name, 0, sizeof(this->_Name));

		this->_Count = 0;

		sscanf(msg, "%s %d", &this->_Name, &this->_Count);

		if (strlen(msg) < 2 || this->_Count < 1 || strcmpi(this->_Name, "bau") && strcmpi(this->_Name, "cash"))
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s bau ou cash <valor>.", this->_Syntax);
			return;
		}

		if (!strcmpi(this->_Name, "bau"))
		{
			if (Custom[aIndex].Coin[2] < this->_Amount[0] * this->_Count)
			{
				Func.MsgOutput(aIndex, 1, "É necessário %d %s.", this->_Amount[0] * this->_Count, this->_Coin[0]);
				return;
			}

			Custom[aIndex].Vault[1] += this->_Count;

			Custom[aIndex].Coin[2] -= this->_Amount[0] * this->_Count;

			Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s - %d WHERE memb___id = '%s'", this->_Column[0], this->_Column[0], this->_Amount[0] * this->_Count, gObj[aIndex].AccountID);

			Manager.ExecFormat("UPDATE warehouse SET Count = Count + %d WHERE AccountID = '%s'", this->_Count, gObj[aIndex].AccountID);

			Func.MsgOutput(aIndex, 1, "Você comprou %d baú com sucesso!", this->_Count);
			Func.MsgOutput(aIndex, 1, "Seu total de baús é: %d", Custom[aIndex].Vault[1]);
		}

		if (!strcmpi(this->_Name, "cash"))
		{
			Manager.CoinCount(aIndex, gObj[aIndex].AccountID);

			if (Custom[aIndex].Coin[4] < this->_Amount[1] * this->_Count)
			{
				Func.MsgOutput(aIndex, 1, "É necessário %d %s.", this->_Amount[1] * this->_Count, this->_Coin[1]);
				return;
			}

			Custom[aIndex].Coin[5] += this->_Count;

			Custom[aIndex].Coin[4] -= this->_Amount[1] * this->_Count;

			Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s - %d WHERE memb___id = '%s'", this->_Column[1], this->_Column[1], this->_Amount[1] * this->_Count, gObj[aIndex].AccountID);

			Connect.UpdateCharacterInfo(aIndex); // Manager cpp

			Func.MsgOutput(aIndex, 1, "Você comprou %d cash com sucesso!", this->_Count);
			Func.MsgOutput(aIndex, 1, "Seu total de cashs é: %d", Custom[aIndex].Coin[5]);
		}
	}
}

cBuy Buy;