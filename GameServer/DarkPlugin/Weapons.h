#pragma once

struct sBoxWeapons
{
	int				    _Type;
	int				    _Index;
	int				    _Level;
	int				    _Skill;
	int				    _Luck;
	int				    _Option;
	int				    _Excelente;
};

class cBoxWeapons
{
public:
	bool Load();
	bool Item(int aIndex);

public:
	int				    _Count;

private:
	sBoxWeapons			WeaponsStruct[255];
};

extern cBoxWeapons BoxWeapons;