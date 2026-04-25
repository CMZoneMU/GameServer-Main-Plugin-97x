#pragma once

struct sRoletaPlayer
{
	bool                _InEvent;
	int                 _Index;
};

class cRoletaEvent
{
public:
	cRoletaEvent();
	~cRoletaEvent();

public:
	bool Load();
	bool Check(LPOBJ lpObj, const char* Text);
	void Start(int Time);
	void Run();
	bool Attack(LPOBJ lpObj, LPOBJ lpTargetObj);
	bool Trade(PMSG_TRADE_REQUEST * Result, int aIndex);
	static void Fire(int aIndex);
	void Die(LPOBJ Target);
	void Quit(LPOBJ lpObj);

public:
	bool				_Active;
	char				_Syntax[2][25];
	char                _Notice[255];
	BYTE				_MapNumber;
	BYTE				_X;
	BYTE				_Y;
	BYTE				_State;
	BYTE				_Type;
	int			        _Count;
	int                 _Time;
	std::vector<LPOBJ>	_Players;

public:
	sRoletaPlayer	    PlayerStruct[OBJECT_MAX];

public:
	enum State
	{
		Empty, Register, Progress, Waiting, Final
	};
};
extern cRoletaEvent RoletaEvent;