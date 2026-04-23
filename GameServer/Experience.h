#pragma once

class cExperience
{
public:
	bool Load();
	static void ExperienceSend(int aIndex, int TargetIndex, int Exp, int AttackDamage, int MSBFlag);

public:
	bool                    _Active;
	int                     _Experience[3];
};

extern cExperience Experience;