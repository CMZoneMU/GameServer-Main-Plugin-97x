#pragma once

struct sTeleport
{
	bool					_Active;
	int                     _MapNumber;
	int                     _X;
	int                     _Y;
	int                     _Level;
	int                     _Zen;
	int                     _Vip;
	int                     _Killer;
	int                     _Wing;
	char					_Syntax[25];
};

class cTeleport
{
public:
	bool Load();
	void Run(int aIndex, int Count);

public:
	int                 _Count;

public:
	sTeleport			TeleportStruct[1000];
};

extern cTeleport Teleport;