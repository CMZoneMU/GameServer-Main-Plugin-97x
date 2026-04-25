#include "StdAfx.h"

bool cBlock::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Block.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(1)));
	}

	return true;
}

void cBlock::Run(int aIndex, char* msg)
{
	if (this->_Active == true)
	{
		memset(this->_Name, 0, sizeof(this->_Name));

		memset(this->_Password, 0, sizeof(this->_Password));

		sscanf(msg, "%s %s", &this->_Name, &this->_Password);

		if (strlen(msg) < 2 || this->_Name == 0 || strcmpi(this->_Name, "on") && strcmpi(this->_Name, "off"))
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s on ou off.", this->_Syntax);
			return;
		}

		if (!strcmpi(this->_Name, "on"))
		{
			if (this->BlockStruct[aIndex]._Active == 0)
			{
				if (strlen(this->_Password) < 4 || strlen(this->_Password) > 4)
				{
					Func.MsgOutput(aIndex, 1, "Use 4 caracteres na senha.");
					return;
				}

				Manager.ExecFormat("UPDATE MEMB_INFO SET Block = 1 WHERE memb___id = '%s'", gObj[aIndex].AccountID);

				Manager.ExecFormat("UPDATE MEMB_INFO SET Password = '%s' WHERE memb___id = '%s'", this->_Password, gObj[aIndex].AccountID);

				Manager.CheckBlock(aIndex, gObj[aIndex].AccountID);

				Func.MsgOutput(aIndex, 1, "Conta bloqueada com sucesso.");
			}
			else
			{
				Func.MsgOutput(aIndex, 1, "O sistema já está ativado.");
			}
		}

		if (!strcmpi(this->_Name, "off"))
		{
			if (this->BlockStruct[aIndex]._Active == 1)
			{
				if (strlen(this->_Password) < 4 || strlen(this->_Password) > 4)
				{
					Func.MsgOutput(aIndex, 1, "Use 4 caracteres na senha.");
					return;
				}

				if (!_stricmp(this->_Password, this->BlockStruct[aIndex]._Password))
				{
					Manager.ExecFormat("UPDATE MEMB_INFO SET Block = 0 WHERE memb___id = '%s'", gObj[aIndex].AccountID);

					Manager.ExecFormat("UPDATE MEMB_INFO SET Password = '%s' WHERE memb___id = '%s'", this->_Password, gObj[aIndex].AccountID);

					Manager.CheckBlock(aIndex, gObj[aIndex].AccountID);

					Func.MsgOutput(aIndex, 1, "Conta desbloqueada com sucesso.");
				}
				else
				{
					Func.MsgOutput(aIndex, 1, "Senha incorreta!");
				}
			}
			else
			{
				Func.MsgOutput(aIndex, 1, "O sistema não está ativo.");
			}
		}
	}
}

cBlock Block;