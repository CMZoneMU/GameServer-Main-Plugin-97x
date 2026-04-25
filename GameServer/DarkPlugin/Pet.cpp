#include "StdAfx.h"

bool cPet::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Pet.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_VipCount = Section.Rows[0].GetInt(1);
		this->_ExpPercent = Section.Rows[0].GetInt(2);

		if (this->_ExpPercent < 10)
		{
			this->_ExpPercent = 10;
		}

		if (this->_ExpPercent > 1000)
		{
			this->_ExpPercent = 1000;
		}

		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(3)));
	}

	return true;
}

void cPet::Command(int aIndex, char* msg)
{
	if (this->_Active == true)
	{
		if (Custom[aIndex].VipCount < this->_VipCount)
		{
			Func.MsgOutput(aIndex, 1, "Você não possui o plano vip necessário!");
			return;
		}

		memset(this->_Name, 0, sizeof(this->_Name));

		sscanf(msg, "%s", &this->_Name);

		if (strlen(msg) < 2 || strcmpi(this->_Name, "on") && strcmpi(this->_Name, "off"))
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s on/off.", this->_Syntax);
			return;
		}

		if (!strcmpi(this->_Name, "off"))
		{
			if (Custom[aIndex].Pet == true)
			{
				switch (gObj[aIndex].Class)
				{
				case 0:
					this->Add(aIndex, 163, gObj[aIndex].X - 1, gObj[aIndex].Y + 1);
					break;
				case 1:
					this->Add(aIndex, 164, gObj[aIndex].X - 1, gObj[aIndex].Y + 1);
					break;
				case 2:
					this->Add(aIndex, 165, gObj[aIndex].X - 1, gObj[aIndex].Y + 1);
					break;
				case 3:
					this->Add(aIndex, 166, gObj[aIndex].X - 1, gObj[aIndex].Y + 1);
					break;
				}

				Custom[aIndex].Pet = false;
			}
		}

		if (!strcmpi(this->_Name, "on"))
		{
			if (Custom[aIndex].Pet == false)
			{
				if (gObj[aIndex].m_RecallMon > 0)
				{
					GCRecallMonLife(aIndex, 60, 0);
					this->gObjMonsterCallKillEx(aIndex);
				}

				switch (gObj[aIndex].Class)
				{
				case 0:
					this->Add(aIndex, 164, gObj[aIndex].X - 1, gObj[aIndex].Y + 1);
					break;
				case 1:
					this->Add(aIndex, 163, gObj[aIndex].X - 1, gObj[aIndex].Y + 1);
					break;
				case 2:
					this->Add(aIndex, 165, gObj[aIndex].X - 1, gObj[aIndex].Y + 1);
					break;
				case 3:
					this->Add(aIndex, 166, gObj[aIndex].X - 1, gObj[aIndex].Y + 1);
					break;
				}

				if (this->_ExpPercent > 0)
				{
					int Mult = (this->_ExpPercent / 100) + 1;

					Func.MsgOutput(aIndex, 0, "Mascote invocado com Sucesso", this->_ExpPercent, Mult);
					Func.MsgOutput(aIndex, 0, "Bonus de XP: %d%% (%dx EXP)", this->_ExpPercent, Mult);
				}
				else
				{
					Func.MsgOutput(aIndex, 0, "Mascote invocado com sucesso!");
				}

				Custom[aIndex].Pet = true;
			}
		}
	}
}

int cPet::Add(int aIndex, int Monster, int X, int Y)
{
	if (gObj[aIndex].m_RecallMon >= 0)
	{
		this->gObjMonsterCallKillEx(aIndex);
		return false;
	}

	int Result = gObjAddCallMon();

	if (Result >= 0)
	{
		gObj[Result].X = X;
		gObj[Result].Y = Y;
		gObj[Result].MTX = X;
		gObj[Result].MTY = Y;
		gObj[Result].Dir = 2;
		gObj[Result].MapNumber = gObj[aIndex].MapNumber;
		gObjSetMonster(Result, Monster);
		gObj[Result].m_RecallMon = aIndex;

		gObj[Result].m_AttackDamageMin = 7000;
		gObj[Result].m_AttackDamageMax = 30000;
		gObj[Result].m_AttackRating = 120;
		gObj[Result].m_SuccessfulBlocking = 18000;
		gObj[Result].m_Defense = 9000;
		gObj[Result].m_AttackSpeed = 1500;
		gObj[Result].m_AttackRange = 1;
		gObj[Result].m_Attribute = 100;
		gObj[Result].m_MoveSpeed = 900;
		gObj[Result].TargetNumber = -1;
		gObj[Result].m_ActState.Emotion = 0;
		gObj[Result].m_ActState.Attack = 0;
		gObj[Result].m_ActState.EmotionCount = 0;
		gObj[Result].PathCount = 0;

		gObj[aIndex].m_RecallMon = Result;
		gObj[Result].m_MoveRange = 2;
		return true;
	}

	return false;
}

void cPet::gObjMonsterCallKillEx(int aIndex)
{
	if (Custom[aIndex].Pet == true)
	{
		Custom[aIndex].Pet = false;

		Func.MsgOutput(aIndex, 0, "Mascote removido!");
	}

	return gObjMonsterCallKill(aIndex);
}

void cPet::Item(int aIndex, int Type, BYTE Level, BYTE Dur, BYTE Skill, BYTE Luck, BYTE Option, BYTE NewOption, DWORD Number)
{
	CItem Item;
	Item.m_Type = Type;
	Item.m_Level = Level;
	Item.m_Durability = Dur;
	Item.m_Skill = Skill;
	Item.m_Luck = Luck;
	Item.m_Option = Option;
	Item.m_Excellent = NewOption;

	Item.Convert(Item.m_Type, Item.m_Skill, Item.m_Luck, Item.m_Option, Item.m_Excellent, 1);

	Item.m_Number = Number;

	BYTE Position = Func.gObjInventoryInsertItem(aIndex, Item);

	GCInventoryItemOneSend(aIndex, Position);
}

void cPet::Quit(LPOBJ lpObj)
{
	if (this->_Active == true)
	{
		if (Custom[lpObj->m_Index].Pet == true)
		{
			switch (lpObj->Class)
			{
			case 0:
				this->Add(lpObj->m_Index, 164, lpObj->X - 1, lpObj->Y + 1);
				break;
			case 1:
				this->Add(lpObj->m_Index, 163, lpObj->X - 1, lpObj->Y + 1);
				break;
			case 2:
				this->Add(lpObj->m_Index, 165, lpObj->X - 1, lpObj->Y + 1);
				break;
			case 3:
				this->Add(lpObj->m_Index, 166, lpObj->X - 1, lpObj->Y + 1);
				break;
			}

			Custom[lpObj->m_Index].Pet = false;
		}
	}
}

cPet Pet;