#pragma once

class cBalancer
{
public:
	bool Load();
	void Attack(LPOBJ lpObj, LPOBJ lpTarget, int &AttackDamage);

public:
	static void GetAttackDamage1();
	static void GetAttackDamage2();
	static void GetAttackDamageWizard();

public:
	WORD WizardAttack[4];
	WORD KnightAttack[4];
	WORD ElfAttack[4];
	WORD GladiatorAttack[4];
};

extern cBalancer Balancer;