#pragma once

struct sPairEvent
{
	int Day;
	int Hours;
	int Minutes;
};

struct PairPlayer
{
	bool Die;
	bool Quit;
	bool Select;
	short Move;
	LPOBJ lpObj;

};

struct PairTeam
{
	PairPlayer Player[2];
	BYTE Score;
};

class cPairEvent
{
public:
	cPairEvent();
	~cPairEvent();

public:
	bool Load();
	bool Check(LPOBJ lpObj, const char* Text);
	void Start(int Time, int Class);
	void Run();
	bool Attack(LPOBJ lpObj, LPOBJ Target);
	void Die(LPOBJ lpObj);
	void Move();
	void Quit(LPOBJ lpObj);

public:
	bool					_Active;
	bool                    _Sended;
	char					_Syntax[2][25];
	char                    _Notice[60];
	char                    _Buffer[3][255];
	BYTE					_MapNumber[2];
	BYTE					_X[2];
	BYTE					_Y[2];
	BYTE					_State;
	BYTE					_Type;
	int                     _List;
	int						_Count;
	std::vector<LPOBJ>		_Registered;
	std::vector<PairTeam>   _Teams[2];
	PairTeam				_Selected[2];

public:
	sPairEvent			    EventStruct[1000];

public:
	enum State
	{
		Empty, Register, Select, Progress, Died, NextStage, WO, Final
	};
};

extern cPairEvent PairEvent;