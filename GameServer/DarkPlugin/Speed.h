#pragma once

struct sSpeed
{
	bool                    _Sended;
	bool                    _Block;
	int                     _Attack;
	int                     _Skill;
	int                     _Moviment;
	BYTE                    _Time;
};

struct sSkill
{
	int                     _Magic;
	int                     _Velocity;
	int                     _Type;
};

class cSpeed
{
public:
	cSpeed();

public:
	bool Load();
	void Connect(int aIndex);
	void Run(LPOBJ lpObj);
	bool Attack(LPOBJ lpObj, LPOBJ Target, class CMagicInf* lpMagic);
	void Skill(LPOBJ lpObj, int Magic);
	static void PMoveProcEx(PMSG_MOVE* Move, int aIndex);
	void Log(char * Text, ...);

public:
	bool					_Active;
	int                     _Attack;
	int                     _Moviment;
	int                     _Display[3];
	int                     _Count;

public:
	sSkill			        SkillStruct[1000];

	sSpeed			        SpeedStruct[OBJECT_MAX];
};

extern cSpeed Speed;