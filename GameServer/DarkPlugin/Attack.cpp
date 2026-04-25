#include "StdAfx.h"

cAttack::cAttack() : _Active(false)
{
}

bool cAttack::Load()
{
	this->_Count[0] = 0; this->_Count[1] = 0;

	memset(this->AttackStruct, 0, sizeof(this->AttackStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Attack.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_VipCount = Section.Rows[0].GetInt(1);
		this->_Level = Section.Rows[0].GetInt(2);
		this->_Zen = Section.Rows[0].GetInt(3);
		this->_Time[0] = Section.Rows[0].GetInt(4);
		this->_Time[1] = Section.Rows[0].GetInt(5);

		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(6)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->AttackStruct[this->_Count[0]]._MapNumber = Section.Rows[i].GetInt(0);
			this->_Count[0]++;
		}
	}

	if (Group.GetSection(2, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->AttackStruct[this->_Count[1]]._Magic = Section.Rows[i].GetInt(0);
			this->_Count[1]++;
		}
	}

	return true;
}

void cAttack::Connect(int aIndex)
{
	this->PlayerStruct[aIndex]._Attack = false;

	this->PlayerStruct[aIndex]._OffAttack = false;

	this->PlayerStruct[aIndex]._Skill = -1;

	this->PlayerStruct[aIndex]._Time[0] = 0;

	this->PlayerStruct[aIndex]._Time[1] = 0;
}

bool cAttack::MapCheck(LPOBJ lpObj)
{
	if (BC_MAP_RANGE(lpObj->MapNumber))
	{
		return false;
	}

	for (int i = 0; i < this->_Count[0]; i++)
	{
		if (lpObj->MapNumber == this->AttackStruct[i]._MapNumber)
		{
			return false;
		}
	}

	return true;
}

bool cAttack::SkillCheck(LPOBJ lpObj, int Magic)
{
	CMagicInf * lpMagic = { 0 };
	
	lpMagic = new CMagicInf();

	lpMagic->Set(Magic, 0);

	if (lpMagic != NULL)
	{
		for (int i = 0; i < this->_Count[1]; i++)
		{
			if (Magic == this->AttackStruct[i]._Magic)
			{
				return true;
			}
		}
	}

	return false;
}

bool cAttack::Start(int aIndex, int Attack)
{
	if (Attack == 0)
	{
		this->PlayerStruct[aIndex]._Attack = true;

		this->PlayerStruct[aIndex]._Time[0] = GetTickCount();
	}
	else if (Attack == 1)
	{
		this->PlayerStruct[aIndex]._OffAttack = true;

		this->PlayerStruct[aIndex]._Time[1] = GetTickCount();
	}

	this->PlayerStruct[aIndex]._Skill = gObj[aIndex].UseMagicNumber;

	Func.MsgOutput(aIndex, 1, "O sistema foi iniciado.");

	if (Attack == 1)
	{
		gObjCloseSet(aIndex, 0);
	}

	return true;
}

void cAttack::Run(LPOBJ lpObj)
{
	if (lpObj->Connected == 3 && lpObj->Type == PLAYER && this->PlayerStruct[lpObj->m_Index]._Skill > 0)
	{
		if (this->PlayerStruct[lpObj->m_Index]._Attack == true)
		{
			if ((GetTickCount() - this->PlayerStruct[lpObj->m_Index]._Time[0]) > (this->_Time[0] * (1000 * 60)))
			{
				this->Finish(lpObj->m_Index, "Sistema finalizado.");
			}
		}
		else if (this->PlayerStruct[lpObj->m_Index]._OffAttack == true)
		{
			if ((GetTickCount() - this->PlayerStruct[lpObj->m_Index]._Time[1]) > (this->_Time[1] * (1000 * 60)))
			{
				this->Finish(lpObj->m_Index, "Sistema finalizado.");

				GJPUserClose(lpObj->AccountID);

				gObjCloseSet(lpObj->m_Index, 0);

				gObjDel(lpObj->m_Index);
			}
		}

		if (lpObj->HaveWeaponInHand == false)
		{
			this->Finish(lpObj->m_Index, "Utilize uma arma válida.");
			return;
		}
		else if (this->MapCheck(lpObj) == false)
		{
			this->Finish(lpObj->m_Index, "Sistema proibido nesse mapa.");
			return;
		}

		if (this->PlayerStruct[lpObj->m_Index]._Attack == true || this->PlayerStruct[lpObj->m_Index]._OffAttack == true)
		{
			if (((lpObj->Life * 100) / (lpObj->MaxLife + lpObj->AddLife)) < 50)
			{
				PMSG_USEITEM Result;
				Result.inventoryPos = this->Inventory(lpObj, ITEMGET(14, 3));
				Result.inventoryTarget = 0;

				if (Result.inventoryPos != 0x0)
				{
					CGUseItemRecv(&Result, lpObj->m_Index);
				}
			}
			else if (((lpObj->Mana * 100) / (lpObj->MaxMana + lpObj->AddMana)) < 50)
			{
				PMSG_USEITEM Result;
				Result.inventoryPos = this->Inventory(lpObj, ITEMGET(14, 6));
				Result.inventoryTarget = 0;

				if (Result.inventoryPos != 0x0)
				{
					CGUseItemRecv(&Result, lpObj->m_Index);
				}
			}

			CMagicInf * lpMagic = { 0 };
			lpMagic = new CMagicInf();

			this->PlayerStruct[lpObj->m_Index]._Skill = lpObj->UseMagicNumber;

			lpMagic->Set(this->PlayerStruct[lpObj->m_Index]._Skill, 0);

			if (lpMagic != NULL)
			{
				this->Check(lpObj, lpMagic, lpObj->Class == KNIGHT ? 3 : 6);
			}
		}
	}
}

void cAttack::Finish(int aIndex, char* msg)
{
	this->PlayerStruct[aIndex]._Attack = false;

	this->PlayerStruct[aIndex]._OffAttack = false;

	this->PlayerStruct[aIndex]._Skill = -1;

	this->PlayerStruct[aIndex]._Time[0] = 0;

	this->PlayerStruct[aIndex]._Time[1] = 0;

	Func.MsgOutput(aIndex, 1, msg);
}

void cAttack::Command(int aIndex, char* msg)
{
	if (this->_Active)
	{
		if (Custom[aIndex].VipCount < this->_VipCount)
		{
			Func.MsgOutput(aIndex, 1, "Você não possui o plano vip necessário.");
			return;
		}
		else if (gObj[aIndex].Level < this->_Level)
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level);
			return;
		}
		else if (gObj[aIndex].Money < this->_Zen)
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen);
			return;
		}
		else if (gObj[aIndex].UseMagicNumber == 0)
		{
			Func.MsgOutput(aIndex, 1, "Utilize uma skill válida.");
			return;
		}
		else if (this->MapCheck(&gObj[aIndex]) == false)
		{
			Func.MsgOutput(aIndex, 1, "Sistema proibido nesse mapa.");
			return;
		}
		else if (this->SkillCheck(&gObj[aIndex], gObj[aIndex].UseMagicNumber) == false)
		{
			Func.MsgOutput(aIndex, 1, "Skill não permitida no sistema.");
			return;
		}

		memset(this->_Name, 0, sizeof(this->_Name));

		sscanf(msg, "%s", &this->_Name);

		if (strlen(msg) < 2 || strcmpi(this->_Name, "on") && strcmpi(this->_Name, "off") && strcmpi(this->_Name, "offline"))
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s offline ou on/off.", this->_Syntax);
			return;
		}

		if (!strcmpi(this->_Name, "off"))
		{
			this->Finish(aIndex, "Sistema finalizado.");
			return;
		}
		else if (!strcmpi(this->_Name, "on"))
		{
			if (this->PlayerStruct[aIndex]._Attack == true)
			{
				Func.MsgOutput(aIndex, 1, "O sistema já está ativo.");
				return;
			}

			if (!this->Start(aIndex, 0))
			{
				GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen);
			}
		}
		else if (!strcmpi(this->_Name, "offline"))
		{
			if (this->PlayerStruct[aIndex]._Attack == true)
			{
				this->Finish(aIndex, "");
			}

			if (!this->Start(aIndex, 1))
			{
				GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen);
			}
		}
	}
}

void cAttack::Check(LPOBJ lpObj, CMagicInf * lpMagic, short Max)
{
	for (int i = 0; i < 75; i++)
	{
		if (lpObj->VpPlayer2[i].State)
		{
			LPOBJ lpTarget = &gObj[lpObj->VpPlayer2[i].Number];

			if (lpTarget >= 0)
			{
				if (lpTarget->Live && lpTarget->Type == MONSTER)
				{
					if (gObjCalDistance(lpObj, lpTarget) < Max)
					{
						gObjUseSkill(lpObj->m_Index, lpMagic, lpTarget->X, lpTarget->Y, lpTarget->Dir, 0, lpTarget->m_Index);

						if (gObjAttack(lpObj, lpTarget, lpMagic, 1, 1, 0) == TRUE)
						{
							GCMagicAttackNumberSend(lpObj, lpMagic->m_Skill, lpTarget->m_Index, 1);
						}
					}
				}
			}
		}
	}
}

void cAttack::gObjUseSkill(int aIndex, CMagicInf *lpMagic, char x, char y, char dir, char TargetPos, int TargetIndex)
{
	_asm
	{
		PUSH TargetIndex
		PUSH TargetPos
		PUSH dir
		PUSH y
		PUSH x
		PUSH lpMagic
		PUSH aIndex
		MOV ECX, 0x4BEBB34;
		MOV EDI, 0x457970;
		CALL EDI;
	}
}

int cAttack::Inventory(LPOBJ lpObj, int aIndex)
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

cAttack Attack;

