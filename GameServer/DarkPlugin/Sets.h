#pragma once

struct sBoxSets
{
	int				    _Type;
	int				    _Index;
	int				    _Level;
	int				    _Skill;
	int				    _Luck;
	int				    _Option;
	int				    _Excelente;
};

class cBoxSets
{
public:
	bool Load();
	bool Item(int aIndex);

public:
	int				    _Count;

private:
	sBoxSets 		SetsStruct[255];
};

extern cBoxSets BoxSets;