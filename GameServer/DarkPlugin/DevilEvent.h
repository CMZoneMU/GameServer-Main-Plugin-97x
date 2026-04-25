#pragma once

struct sDevil
{
	BYTE                     _Type;
	BYTE                     _Index;
	BYTE                     _Level;
	BYTE                     _Skill;
	BYTE                     _Luck;
	BYTE                     _Option;
	BYTE                     _Excelente;
};

class cDevilEvent
{
public:
	bool Load();
	static void SendRanking();

public:
	int                      _Count;

public:
	sDevil			         DevilStruct[255];
};

extern cDevilEvent DevilEvent;