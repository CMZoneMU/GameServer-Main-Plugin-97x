#pragma once

class cPet
{
public:
	bool Load();
	void Command(int aIndex, char* msg);
	int Add(int aIndex, int Monster, int X, int Y);
	static void gObjMonsterCallKillEx(int aIndex);
	void Item(int aIndex, int Type, BYTE Level, BYTE Dur, BYTE Skill, BYTE Luck, BYTE Option, BYTE NewOption, DWORD Number);
	void Quit(LPOBJ lpObj);

public:
	bool                    _Active;
	int                     _VipCount;
	int                     _ExpPercent;
	char                    _Name[255];
	char                    _Syntax[25];
};

extern cPet Pet;