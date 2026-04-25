#include "StdAfx.h"

bool cTeleport::Load()
{
	this->_Count = 0;

	memset(this->TeleportStruct, 0, sizeof(this->TeleportStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Moves.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->TeleportStruct[this->_Count]._Active = Section.Rows[i].GetInt(0) > 0 ? true : false;
			this->TeleportStruct[this->_Count]._Level = Section.Rows[i].GetInt(1);
			this->TeleportStruct[this->_Count]._Zen = Section.Rows[i].GetInt(2);
			this->TeleportStruct[this->_Count]._Vip = Section.Rows[i].GetInt(3);
			this->TeleportStruct[this->_Count]._Killer = Section.Rows[i].GetInt(4);
			this->TeleportStruct[this->_Count]._MapNumber = Section.Rows[i].GetInt(5);
			this->TeleportStruct[this->_Count]._Wing = Section.Rows[i].GetInt(6);
			this->TeleportStruct[this->_Count]._X = Section.Rows[i].GetInt(7);
			this->TeleportStruct[this->_Count]._Y = Section.Rows[i].GetInt(8);
			strcpy_s(this->TeleportStruct[this->_Count]._Syntax, sizeof(this->TeleportStruct[this->_Count]._Syntax), (Section.Rows[i].GetStringPtr(9)));
			this->_Count++;
		}
	}

	return true;
}

void cTeleport::Run(int aIndex, int Count)
{
	if (this->TeleportStruct[Count]._Active == true)
	{
		if (this->TeleportStruct[Count]._Level > gObj[aIndex].Level)
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->TeleportStruct[Count]._Level);
			return;
		}
		else if (this->TeleportStruct[Count]._Zen > gObj[aIndex].Money)
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->TeleportStruct[Count]._Zen);
			return;
		}
		else if (Custom[aIndex].VipCount < this->TeleportStruct[Count]._Vip)
		{
			Func.MsgOutput(aIndex, 1, "Você não possui o plano vip necessário.");
			return;
		}
		else if (this->TeleportStruct[Count]._Killer == 1 && gObj[aIndex].m_PK_Level == 6)
		{
			Func.MsgOutput(aIndex, 1, "Pk's não podem se mover.");
			return;
		}
		else if (gObj[aIndex].m_IfState.use == 1 || gObj[aIndex].pTransaction == 1 || gObj[aIndex].WarehouseSave == 1)
		{
			Func.MsgOutput(aIndex, 1, "Feche todas as janelas para mover-se.");
			return;
		}

		if (this->TeleportStruct[Count]._Wing == 1)
		{
			if (gObj[aIndex].pInventory[7].m_Type != -1 || gObj[aIndex].pInventory[8].m_Type == ITEMGET(13, 3))
			{
				gObj[aIndex].Money -= this->TeleportStruct[Count]._Zen;

				GCMoneySend(aIndex, gObj[aIndex].Money);

				gObjTeleport(aIndex, this->TeleportStruct[Count]._MapNumber, this->TeleportStruct[Count]._X, this->TeleportStruct[Count]._Y);
			}
			else
			{
				Func.MsgOutput(aIndex, 1, "Proibido mover-se sem asas ou dinorant.");
			}
		}
		else
		{
			gObj[aIndex].Money -= this->TeleportStruct[Count]._Zen;

			GCMoneySend(aIndex, gObj[aIndex].Money);

			gObjTeleport(aIndex, this->TeleportStruct[Count]._MapNumber, this->TeleportStruct[Count]._X, this->TeleportStruct[Count]._Y);
		}
	}
}

cTeleport Teleport;