#pragma once

struct sReset
{
	int                     _VipCount;
	int					    _ResetsMin;
	int					    _ResetsMax;
	int                     _Level;
	int                     _Money;
	int					    _Points;
};

class cReset
{
public:
	cReset();

public:
	bool Load();
	void Run(int aIndex);

public:
	bool					_Active;
	BYTE					_Type;
	int                     _Teleport[4];
	int                     _Remove[4];
	int                     _Count;
	char					_Syntax[25];

	sReset                  ResetStruct[255];
};

extern cReset Reset;