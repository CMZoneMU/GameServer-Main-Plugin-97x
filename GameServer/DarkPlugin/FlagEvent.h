#pragma once

struct sFlag
{
	int                     _Day;
	int                     _Hours;
	int                     _Minutes;
	int                     _Duration;
};

struct sFlagEvent
{
	bool					_Status;
	bool					_InEvent;
	short					_Team;
	short					_Move;

	LPOBJ                   lpObj;

	bool operator == (const sFlagEvent& s) const
	{
		return lpObj == s.lpObj && _Team == s._Team;
	}

	bool operator != (const sFlagEvent& s) const
	{
		return !operator==(s);
	}
};

class cFlagEvent
{
public:
	char _Syntax[10][25];
	cFlagEvent();

public:
	bool Load();
	void Run();
	int GetIndex();
	bool Teleport(LPOBJ lpObj);
	bool Attack(LPOBJ lpObj, LPOBJ Target);
	void FlagPoint(LPOBJ lpObj);
	void Killer(LPOBJ lpObj, LPOBJ Target);
	void Die(LPOBJ lpObj);
	void Move(int Team);
	void Talk(LPOBJ lpNpc, LPOBJ lpObj, BYTE Mode);
	bool CheckItem(LPOBJ lpObj);
	void Winner(int Team);
	int Diference(int v1, int v2);
	void Finish(BYTE Mode);
	void Quit(LPOBJ lpObj);
	bool Equip(LPOBJ lpObj, BYTE SourcePos, BYTE TargetPos);
	void StartManual();

public:
	bool					_Active;
	bool                    _Portal;
	bool                    _Progress;
	BYTE                    _EventState;
	BYTE					_MapNumber;
	BYTE					_X[2];
	BYTE					_Y[2];
	short					_FlagState[2];
	int                     _Level;
	int                     _Zen;
	int                     _Players[2];
	int                     _Points[2];
	int						_Amount;
	int                     _Team;
	int                     _Red;
	int                     _Blue;
	int                     _Count;
	char                    _Column[255];
	char                    _Coin[255];
	char                    _Buffer[255];
	
	std::list<sFlagEvent>   Team;

public:
	sFlag			        FlagStruct[255];

	sFlagEvent			    PlayerStruct[OBJECT_MAX];

private:
	enum State
	{
		Red, Blue
	};
};

extern cFlagEvent FlagEvent;


