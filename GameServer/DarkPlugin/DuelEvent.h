#pragma once

struct sDuelEvent
{
	int Day;
	int Hours;
	int Minutes;
};

struct DuelPlayer
{
	bool Die;
	bool Quit;
	bool Select;
	BYTE Score;
	LPOBJ lpObj;
};

class cDuelEvent
{
public:
	cDuelEvent();
	~cDuelEvent();

public:
	bool Load();
	bool Check(LPOBJ lpObj, const char* Text);
	void Start(int Time, int Class);
	void Run();
	bool Attack(LPOBJ lpObj, LPOBJ Target);
	void Die(LPOBJ lpObj);
	void Quit(LPOBJ lpObj);

public:
	bool					_Active;
	bool                    _Sended;
	char _Syntax[10][25];
	
	char                    _Notice[60];
	char                    _Buffer[3][255];
	BYTE					_MapNumber[2];
	BYTE					_X[2];
	BYTE					_Y[2];
	BYTE					_State;
	BYTE					_Type;
	int                     _List;
	int						_Count;
	std::vector<DuelPlayer> _Players[2];
	DuelPlayer				_Selected[2];

public:
	sDuelEvent			    EventStruct[1000];

public:
	enum State
	{
		Empty, Register, Select, Progress, Died, NextStage, WO, Final
	};
};

extern cDuelEvent DuelEvent;
