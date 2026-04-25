#pragma once

struct sTheft
{
	int                  _Day;
	int                  _Hours;
	int                  _Minutes;
	int                  _Duration;
};

struct sTheftPlayer
{
	bool                 _InEvent;
	bool                 _AttackBlock;
	int                  _Kills;
};

class cTheftEvent
{
public:
	cTheftEvent();

public:
	bool Load();
	void Run();
	bool Attack(LPOBJ lpObj, LPOBJ Target);
	void Killer(LPOBJ lpObj, LPOBJ Target);
	void Winner();
	void Finish();
	void Quit(LPOBJ lpObj);
	void Talk(OBJECTSTRUCT* Npc, OBJECTSTRUCT* lpObj);

public:
	bool                _Active;
	bool                _Portal;
	bool                _Progress;
	int                 _Level;
	int                 _Zen;
	BYTE                _MapNumber;
	BYTE                _X;
	BYTE                _Y;
	int                 _Count;
	int                 _Value;
	int                 _Players;
	char                _Notice[255];
	char                _Buffer[255];

public:
	sTheft			    TheftStruct[1000];

	sTheftPlayer	    PlayerStruct[OBJECT_MAX];
};

extern cTheftEvent TheftEvent;