#include "StdAfx.h"

bool cBalancer::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Balancer.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->WizardAttack[0] = Section.Rows[0].GetInt(0);
		this->WizardAttack[1] = Section.Rows[0].GetInt(1);
		this->WizardAttack[2] = Section.Rows[0].GetInt(2);
		this->WizardAttack[3] = Section.Rows[0].GetInt(3);
		this->WizardAttack[4] = Section.Rows[0].GetInt(4);
	}

	if (Group.GetSection(1, Section))
	{
		this->KnightAttack[0] = Section.Rows[0].GetInt(0);
		this->KnightAttack[1] = Section.Rows[0].GetInt(1);
		this->KnightAttack[2] = Section.Rows[0].GetInt(2);
		this->KnightAttack[3] = Section.Rows[0].GetInt(3);
		this->KnightAttack[4] = Section.Rows[0].GetInt(4);
	}

	if (Group.GetSection(2, Section))
	{
		this->ElfAttack[0] = Section.Rows[0].GetInt(0);
		this->ElfAttack[1] = Section.Rows[0].GetInt(1);
		this->ElfAttack[2] = Section.Rows[0].GetInt(2);
		this->ElfAttack[3] = Section.Rows[0].GetInt(3);
		this->ElfAttack[4] = Section.Rows[0].GetInt(4);
	}

	if (Group.GetSection(3, Section))
	{
		this->GladiatorAttack[0] = Section.Rows[0].GetInt(0);
		this->GladiatorAttack[1] = Section.Rows[0].GetInt(1);
		this->GladiatorAttack[2] = Section.Rows[0].GetInt(2);
		this->GladiatorAttack[3] = Section.Rows[0].GetInt(3);
		this->GladiatorAttack[4] = Section.Rows[0].GetInt(4);
	}

	Func.HookJump(0x4555DE, GetAttackDamage1);
	Func.HookJump(0x45566C, GetAttackDamage2);
	Func.HookJump(0x45563B, GetAttackDamageWizard);

	return true;
}

void cBalancer::Attack(LPOBJ lpObj, LPOBJ lpTarget, int &AttackDamage)
{
	if (lpObj->Type != PLAYER || lpTarget->Type != PLAYER || AttackDamage <= 0)
	{
		return;
	}
	else if (lpObj->Class == WIZARD)
	{
		switch (lpTarget->Class)
		{
		case WIZARD:
			AttackDamage = (AttackDamage * this->WizardAttack[0]) / 100; break;
		case KNIGHT:
			AttackDamage = (AttackDamage * this->WizardAttack[1]) / 100; break;
		case ELF:
			AttackDamage = (AttackDamage * this->WizardAttack[2]) / 100; break;
		case MAGIC:
			AttackDamage = (AttackDamage * this->WizardAttack[3]) / 100; break;
		default:
			break;
		}
	}
	else if (lpObj->Class == KNIGHT)
	{
		switch (lpTarget->Class)
		{
		case KNIGHT:
			AttackDamage = (AttackDamage * this->KnightAttack[0]) / 100; break;
		case WIZARD:
			AttackDamage = (AttackDamage * this->KnightAttack[1]) / 100; break;
		case ELF:
			AttackDamage = (AttackDamage * this->KnightAttack[2]) / 100; break;
		case MAGIC:
			AttackDamage = (AttackDamage * this->KnightAttack[3]) / 100; break;
		default:
			break;
		}
	}
	else if (lpObj->Class == ELF)
	{
		switch (lpTarget->Class)
		{
		case ELF:
			AttackDamage = (AttackDamage * this->ElfAttack[0]) / 100; break;
		case KNIGHT:
			AttackDamage = (AttackDamage * this->ElfAttack[1]) / 100; break;
		case WIZARD:
			AttackDamage = (AttackDamage * this->ElfAttack[2]) / 100; break;
		case MAGIC:
			AttackDamage = (AttackDamage * this->ElfAttack[3]) / 100; break;
		default:
			break;
		}
	}
	else if (lpObj->Class == MAGIC)
	{
		switch (lpTarget->Class)
		{
		case MAGIC:
			AttackDamage = (AttackDamage * this->GladiatorAttack[0]) / 100; break;
		case KNIGHT:
			AttackDamage = (AttackDamage * this->GladiatorAttack[1]) / 100; break;
		case WIZARD:
			AttackDamage = (AttackDamage * this->GladiatorAttack[2]) / 100; break;
		case ELF:
			AttackDamage = (AttackDamage * this->GladiatorAttack[3]) / 100; break;
		default:
			break;
		}
	}
}

void __declspec(naked) cBalancer::GetAttackDamage1()
{
	static DWORD Local = 0x4555E5;

	static LPOBJ lpObj;
	static LPOBJ lpTargetObj;
	static int AttackDamage;

	__asm
	{
		MOV AttackDamage, EAX;
		MOV EAX, DWORD PTR SS : [EBP + 0x8];
		MOV lpObj, EAX;
		MOV EAX, DWORD PTR SS : [EBP + 0xC];
		MOV lpTargetObj, EAX;
		PUSHAD;
	}

	Balancer.Attack(lpObj, lpTargetObj, AttackDamage);

	__asm
	{
		POPAD;
		MOV EAX, AttackDamage;
		MOV DWORD PTR SS : [EBP + 0x1C], EAX;
		CMP DWORD PTR SS : [EBP + 0x1C], 0;
		JMP Local;
	}
}

void __declspec(naked) cBalancer::GetAttackDamage2()
{
	static DWORD Local = 0x455642;

	static LPOBJ lpObj;
	static LPOBJ lpTargetObj;
	static int AttackDamage;

	__asm
	{
		MOV AttackDamage, EAX;
		MOV EAX, DWORD PTR SS : [EBP + 0x8];
		MOV lpObj, EAX;
		MOV EAX, DWORD PTR SS : [EBP + 0xC];
		MOV lpTargetObj, EAX;
		PUSHAD;
	}

	Balancer.Attack(lpObj, lpTargetObj, AttackDamage);

	__asm
	{
		POPAD;
		MOV EAX, AttackDamage;
		MOV DWORD PTR SS : [EBP + 0x1C], EAX;
		CMP DWORD PTR SS : [EBP + 0x1C], 0;
		JMP Local;
	}
}

void __declspec(naked) cBalancer::GetAttackDamageWizard()
{
	static DWORD Local = 0x455673;

	static LPOBJ lpObj;
	static LPOBJ lpTargetObj;
	static int AttackDamage;

	__asm
	{
		MOV AttackDamage, EAX;
		MOV EAX, DWORD PTR SS : [EBP + 0x8];
		MOV lpObj, EAX;
		MOV EAX, DWORD PTR SS : [EBP + 0xC];
		MOV lpTargetObj, EAX;
		PUSHAD;
	}

	Balancer.Attack(lpObj, lpTargetObj, AttackDamage);

	__asm
	{
		POPAD;
		MOV EAX, AttackDamage;
		MOV DWORD PTR SS : [EBP + 0x1C], EAX;
		CMP DWORD PTR SS : [EBP + 0x1C], 0;
		JMP Local;
	}
}

cBalancer Balancer;