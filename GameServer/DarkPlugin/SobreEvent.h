#pragma once

struct sSobreEvent
{
	int Day;
	int Hours;
	int Minutes;
};

class cSobreEvent
{
public:
	cSobreEvent();
	~cSobreEvent();

public:
	bool Load();
	bool Check(LPOBJ lpObj, const char* Text);
	void Start(int Time);
	void Run();
	bool Attack(LPOBJ lpObj, LPOBJ Target);
	void Die(LPOBJ lpObj, LPOBJ Target);
	void Quit(LPOBJ lpObj);

public:
	bool				_Active;
	char _Syntax[10][25];
	
	char                _Notice[255];
	BYTE				_MapNumber;
	BYTE				_X;
	BYTE				_Y;
	BYTE				_State;
	int                 _List;
	int			        _Count;
	std::vector<LPOBJ>	_Players;

public:
	sSobreEvent			EventStruct[1000];

public:
	enum State
	{
		Empty, Register, Progress, Fight, Final
	};
};

extern cSobreEvent SobreEvent;
