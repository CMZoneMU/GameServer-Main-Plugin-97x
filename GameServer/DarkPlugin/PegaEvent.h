#pragma once

class cPegaEvent
{
public:
	cPegaEvent();
	~cPegaEvent();

public:
	bool Load();
	bool Check(LPOBJ lpObj, const char* Text);
	void Start(int Time);
	void Run();
	bool CheckItem(LPOBJ lpObj);
	bool Attack(LPOBJ lpObj, LPOBJ Target);
	void Quit(LPOBJ lpObj);
	bool Equip(LPOBJ lpObj, BYTE SourcePos, BYTE TargetPos);
	bool Teleport(LPOBJ lpObj);

public:
	bool				_Active;
	bool                _Capturar;
	char _Syntax[10][25];
	
	char                _Notice[3][60];
	BYTE				_MapNumber;
	BYTE				_X;
	BYTE				_Y;
	BYTE				_State;
	int			        _Count;
	std::vector<LPOBJ>	_Players;
	char				_Account[3][11];
	char				_Name[3][11];

public:
	enum State
	{
		Empty, Register, Capture, Progress, Final
	};
};

extern cPegaEvent PegaEvent;
