#pragma once

struct sBoss
{
	int					_Day;
	int					_Hours;
	int					_Minutes;
	int					_Monster[2];
	int					_Duration;
	int                 _MapNumber;
	int                 _X;
	int                 _Y;
	int                 _Quantity;
	BYTE				_Type;
	BYTE				_Index;
	BYTE				_Level;
	BYTE				_Skill;
	BYTE				_Luck;
	BYTE				_Option;
	BYTE				_Excelente;
	char				_Name[255];
};

class cBossEvent
{
public:
	cBossEvent();

public:
	bool Load();
	void Run();
	void Disappear();
	void Mapa(int MapNumber);
	void Finish(int aIndex);

public:
	bool					_Active;
	bool                    _Alive;
	int                     _Index;
	int                     _Monster;
	int                     _Count[2];
	short                   _X;
	short                   _Y;
	const char*				_BossName;
	const char*				_MapName;
	char                    _Buffer[255];

private:
	sBoss			        BossStruct[1000];
};

extern cBossEvent BossEvent;