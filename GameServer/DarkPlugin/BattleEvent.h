#pragma once

struct EventStart
{
	int                     _Day;
	int                     _Hours;
	int                     _Minutes;
	int                     _Time;
	int                     _Class;
	BYTE                    _Type;
	int                     _Index;
	BYTE                    _Level;
	BYTE                    _Skill;
	BYTE                    _Luck;
	BYTE                    _Option;
	BYTE                    _Excelente;
};

struct sBattleEvent
{
public:
	sBattleEvent() :
		_InEvent(false), _Level(0), _Points(0), _Strength(0), _Dexterity(0), _Vitality(0), _Energy(0)
	{
	}

	int                     _InEvent;
	int                     _Level;
	int                     _Points;
	int                     _Strength;
	int                     _Dexterity;
	int                     _Vitality;
	int                     _Energy;

	class CItem             InventoryBack[76];
	class CMagicInf         MagicBack[60];
};

class cBattleEvent
{
public:
	cBattleEvent();
	~cBattleEvent();

public:
	bool Load();
	bool Check(LPOBJ lpObj, const char* Text);
	void Start(int Time, int Class);
	void Run();
	void RollBack(LPOBJ lpObj, int Value);
	bool Attack(LPOBJ lpObj, LPOBJ lpTargetObj);
	void Die(LPOBJ lpObj, LPOBJ lpTargetObj);
	void Quit(LPOBJ lpObj);
	void CheckBuffs(LPOBJ lpObj);
	static void Drop(void* lpParam);

public:
	bool					_Active;
	char					_Syntax[10][25];

private:
	bool                    _Finish;
	char                    _Notice[255];
	BYTE				    _MapNumber;
	BYTE				    _X;
	BYTE				    _Y;
	BYTE				    _State;
	BYTE				    _Type;
	int                     _Sortear;
	int                     _Points;
	int                     _List[2];
	int			            _Count;
	std::vector<LPOBJ>	    _Players;

private:
	EventStart			    EventStruct[2000];

public:
	sBattleEvent	        PlayerStruct[OBJECT_MAX];

private:
	enum State
	{
		Empty, Register, Progress, Fight, Final
	};
};

extern cBattleEvent BattleEvent;
