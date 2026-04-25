#pragma once

struct sBonus
{
	int					    _Type;
	int					    _Index;
	int					    _Level;
	int					    _Skill;
	int					    _Luck;
	int					    _Option;
	int					    _Excelente;
	int                     _Class;
};

class cBonus
{
public:
	cBonus();

public:
	bool Load();
	void Command(int aIndex);

public:
	bool                    _Active;
	int                     _LevelUpPoint;
	int                     _Resets;
	int                     _Money;
	int                     _Item;
	int                     _Count;
	char                    _Syntax[25];

public:
	sBonus			        BonusStruct[1000];
};

extern cBonus Bonus;