#pragma once

struct sBoxLimited
{
	int				    _Type;
	int				    _Index;
	int				    _Level;
	int				    _Skill;
	int				    _Luck;
	int				    _Option;
	int				    _Excelente;
};

class cBoxLimited
{
public:
	bool Load();
	bool Item(int aIndex);

public:
	int				    _Count;

private:
	sBoxLimited			LimitedStruct[255];
};

extern cBoxLimited BoxLimited;