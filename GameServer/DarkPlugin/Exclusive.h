#pragma once

struct sBoxExclusive
{
	int				    _Type;
	int				    _Index;
	int				    _Level;
	int				    _Skill;
	int				    _Luck;
	int				    _Option;
	int				    _Excelente;
};

class cBoxExclusive
{
public:
	bool Load();
	bool Item(int aIndex);

public:
	int	_Count;

private:
	sBoxExclusive	ExclusiveStruct[255];
};

extern cBoxExclusive BoxExclusive;