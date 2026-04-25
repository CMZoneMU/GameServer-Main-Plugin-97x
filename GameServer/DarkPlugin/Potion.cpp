#include "StdAfx.h"

bool cPotion::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Potion.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active[0] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Delay = Section.Rows[0].GetInt(1);
	}

	if (Group.GetSection(1, Section))
	{
		this->_Active[1] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_VipCount = Section.Rows[0].GetInt(1);
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(2)));
	}

	return true;
}

int cPotion::Inventory(LPOBJ lpObj, int aIndex)
{
	for (int i = 12; i < 76; i++)
	{
		if (lpObj->pInventory[i].m_Type == aIndex)
		{
			return i;
		}
	}

	return FALSE;
}

void cPotion::Thread1(void* lpParam)
{
	while (true)
	{
		Sleep(Potion._Delay);

		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].Connected == 3 && Custom[i].Time > 0)
			{
				--Custom[i].Time;
			}
		}
	}

	_endthread();
}

void cPotion::Thread2(void* lpParam)
{
	while (true)
	{
		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].Connected == 3 && Custom[i].Start == true)
			{
				if (Custom[i].VipCount >= Potion._VipCount)
				{
					PMSG_USEITEM Result1;
					Result1.inventoryPos = Potion.Inventory(&gObj[i], ITEMGET(14, 3));
					Result1.inventoryTarget = 0;

					if (Result1.inventoryPos != 0x0)
					{
						CGUseItemRecv(&Result1, i);
					}

					PMSG_USEITEM Result2;
					Result2.inventoryPos = Potion.Inventory(&gObj[i], ITEMGET(14, 2));
					Result2.inventoryTarget = 0;

					if (Result2.inventoryPos != 0x0)
					{
						CGUseItemRecv(&Result2, i);
					}

					PMSG_USEITEM Result3;
					Result3.inventoryPos = Potion.Inventory(&gObj[i], ITEMGET(14, 6));
					Result3.inventoryTarget = 0;

					if (Result3.inventoryPos != 0x0)
					{
						CGUseItemRecv(&Result3, i);
					}

					PMSG_USEITEM Result4;
					Result4.inventoryPos = Potion.Inventory(&gObj[i], ITEMGET(14, 5));
					Result4.inventoryTarget = 0;

					if (Result4.inventoryPos != 0x0)
					{
						CGUseItemRecv(&Result4, i);
					}

					Custom[i].Time = 1;
				}
			}
		}

		Sleep(Potion._Delay);
	}

	_endthread();
}

void cPotion::Command(int aIndex, char* msg)
{
	if (this->_Active[1] == true)
	{
		memset(this->_Name, 0, sizeof(this->_Name));

		sscanf(msg, "%s", &this->_Name);

		if (strlen(msg) < 2 || strcmpi(this->_Name, "on") && strcmpi(this->_Name, "off"))
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s on ou off.", this->_Syntax);
			return;
		}
		else if (Custom[aIndex].VipCount < this->_VipCount)
		{
			Func.MsgOutput(aIndex, 1, "Você não possui o plano vip necessário!");
			return;
		}

		if (!strcmpi(this->_Name, "on"))
		{
			Func.MsgOutput(aIndex, 1, "Auto potion ativado com sucesso.");

			Custom[aIndex].Start = true;
		}
		else if (!strcmpi(this->_Name, "off"))
		{
			Func.MsgOutput(aIndex, 1, "Auto potion desativado com sucesso.");

			Custom[aIndex].Start = false;
		}
	}
}

void cPotion::Quit(LPOBJ lpObj)
{
	if (lpObj->Type == PLAYER && Custom[lpObj->m_Index].Start == true)
	{
		Custom[lpObj->m_Index].Start = false;
	}
}

cPotion Potion;