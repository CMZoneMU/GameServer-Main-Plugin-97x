#pragma once

struct sAutoReset
{
public:
	sAutoReset() :
		_Active(false), _Points(0), _Strength(0), _Dexterity(0), _Vitality(0), _Energy(0)
	{
	}

	bool                    _Active;
	int                     _Points;
	int                     _Strength;
	int                     _Dexterity;
	int                     _Vitality;
	int                     _Energy;
};

class cAutoReset
{
public:
	bool Load();
	void Run(LPOBJ lpObj);
	void Command(int aIndex, char* msg);
	void Quit(LPOBJ lpObj);

public:
	bool                    _Active;
	int                     _Type;
	int                     _VipCount;
	int                     _Money;
	char                    _Name[255];
	char                    _Syntax[25];

public:
	sAutoReset              AutoStruct[OBJECT_MAX];
};

extern cAutoReset AutoReset;