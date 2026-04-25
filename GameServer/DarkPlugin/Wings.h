#pragma once

struct sBoxWings
{
	BYTE				_Type;
	BYTE				_Index;
	BYTE				_Level;
	BYTE				_Skill;
	BYTE				_Luck;
	BYTE				_Option;
	BYTE				_Excelente;
};

class cBoxWings
{
public:
	bool Load();
	bool Item(int aIndex);

public:
	int				    _Count;

private:
	sBoxWings			WingsStruct[255];
};

extern cBoxWings BoxWings;