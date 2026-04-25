#pragma once

class cPotion
{
public:
	bool Load();
	int Inventory(LPOBJ lpObj, int aIndex);
	static void Thread1(void* lpParam);
	static void Thread2(void* lpParam);
	void Command(int aIndex, char* msg);
	void Quit(LPOBJ lpObj);

public:
	bool				    _Active[2];
	int                     _Delay;
	int                     _VipCount;
	char                    _Name[255];
	char                    _Syntax[255];
};

extern cPotion Potion;