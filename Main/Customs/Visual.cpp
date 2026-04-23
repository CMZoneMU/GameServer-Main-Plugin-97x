#include "StdAfx.h"

void VisualState::Load()
{
	this->Kill = TRUE;
	this->Attack = 0;
	this->aIndex = 0;
	this->Life = 0;
	this->MaxLife = 0;
	this->Mana = 0;
	this->MaxMana = 0;
	this->Ag = 0;
	this->MaxAg = 0;

	HookCall(0x4B9BA5, DrawHP);
	HookCall(0x4B9BCC, DrawMP);
	HookCall(0x4B88EC, DrawAG);
	HookCall(0x4B92D8, DrawTabHP);
	HookCall(0x4B93A2, DrawTabMP);
	HookCall(0x4B8949, DrawTabAG);
	HookCall(0x4EA2EF, InfoHp);
	HookCall(0x4EA3DF, InfoMp);
}

void VisualState::Index(PMSG_JOINRESULT* Data)
{
	this->aIndex = MAKE_NUMBERW(Data->NumberH, Data->NumberL);
	this->Kill = FALSE;
}

void VisualState::RecvDamage(PMSG_ATTACKRESULT * Data)
{
	this->Attack = Data->AttackDamage;

	if (this->aIndex == MAKE_NUMBERW(Data->NumberH, Data->NumberL))
	{
		this->Life -= this->Attack;

		if (this->Life < 0)
		{
			this->Life = 0;
		}
	}
}

void VisualState::RecvHP(PMSG_REFILL* Data)
{
	if (Data->IPos == 0xFF)
	{
		this->Life = Data->Life;
	}

	else if (Data->IPos == 0xFE)
	{
		this->MaxLife = Data->Life;
	}

	if (this->Life > this->MaxLife)
	{
		this->Life = this->MaxLife;
	}

	if (this->Kill == TRUE)
	{
		this->Life = 0;
	}
}

void VisualState::RecvMP(PMSG_MANASEND* Data)
{
	if (Data->IPos == 0xFF)
	{
		this->Mana = Data->Mana;
		this->Ag = Data->BP;
	}

	else if (Data->IPos == 0xFE)
	{
		this->MaxMana = Data->Mana;
		this->MaxAg = Data->BP;
	}

	if (this->Mana > this->MaxMana)
	{
		this->Mana = this->MaxMana;
	}
}

void VisualState::Respawn()
{
	this->Kill = FALSE;

	this->Life = this->MaxLife;
	this->Mana = this->MaxMana;
	this->Ag = this->MaxAg;
}

void VisualState::Killed(PMSG_DIEPLAYER* Data)
{
	short tIndex = MAKE_NUMBERW(Data->NumberH, Data->NumberL);

	if (this->aIndex == tIndex)
	{
		this->Life = 0;
		this->Kill = TRUE;
	}
}

void VisualState::DrawHP(float PosX, float PosY, int Value, float ScaleX, float ScaleY)
{
	DrawBar(PosX + 25.0f, PosY, Visual.Life, ScaleX, ScaleY);
}

void VisualState::DrawMP(float PosX, float PosY, int Value, float ScaleX, float ScaleY)
{
	DrawBar(PosX - 18.0f, PosY, Visual.Mana, ScaleX, ScaleY);
}

void VisualState::DrawAG(float PosX, float PosY, int Value, float ScaleX, float ScaleY)
{
	DrawBar(PosX - 10.0f, PosY, Visual.Ag, ScaleX, ScaleY);
}

void VisualState::DrawTabHP(int PosX, int PosY, LPCSTR lpString)
{
	sprintf_s(Visual.Buffer[0], "Life: %d/%d", Visual.Life, Visual.MaxLife);

	DrawTab(PosX, PosY, Visual.Buffer[0]);
}

void VisualState::DrawTabMP(int PosX, int PosY, LPCSTR lpString)
{
	sprintf_s(Visual.Buffer[1], "Mana: %d/%d", Visual.Mana, Visual.MaxMana);

	DrawTab(PosX, PosY, Visual.Buffer[1]);
}

void VisualState::DrawTabAG(int PosX, int PosY, LPCSTR lpString)
{
	sprintf_s(Visual.Buffer[2], "AG: %d/%d", Visual.Ag, Visual.MaxAg);

	DrawTab(PosX, PosY, Visual.Buffer[2]);
}

void VisualState::InfoHp(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)
{
	sprintf_s(Visual.Buffer[3], "Life: %d/%d", Visual.Life, Visual.MaxLife);

	DrawInfo(a1, a2, Visual.Buffer[3], a4, a5, a6);
}

void VisualState::InfoMp(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)
{
	sprintf_s(Visual.Buffer[4], "Mana: %d/%d", Visual.Mana, Visual.MaxMana);

	DrawInfo(a1, a2, Visual.Buffer[4], a4, a5, a6);
}

VisualState Visual;