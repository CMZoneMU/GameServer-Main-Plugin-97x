#include "StdAfx.h"

CMagicInf::CMagicInf()
{
	this->Clear();
}

CMagicInf::~CMagicInf()
{
	this->m_DamageMin = 0;
	this->m_DamageMax = 0;
}

void CMagicInf::Clear()
{
	this->m_Skill = 0xFF;
	this->m_Level = 0;
}

BOOL CMagicInf::IsMagic()
{
	if (this->m_Skill == 0xFF)
	{
		return FALSE;
	}

	return TRUE;
}

int CMagicInf::Set(BYTE Skill, BYTE Level)
{
	_asm
	{
		PUSH Level
		PUSH Skill
		MOV EDI, 0x43BB50;
		MOV ECX, this;
		CALL EDI;
	}
}

int CMagicInf::GetDamage()
{
	int damage = 0;

	if (this->m_Skill == 0xFF)
	{
		return 0;
	}

	int subd = this->m_DamageMax - this->m_DamageMin;

	__try
	{
		damage = this->m_DamageMin + (rand() % (+1));
	}

	__except (subd = 1, EXCEPTION_EXECUTE_HANDLER)
	{
	}

	return damage;
}


