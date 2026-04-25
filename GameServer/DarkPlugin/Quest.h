#pragma once

struct sQuest
{
	int                 _Monster;
	int                 _Quantity[2];
	int                 _Amount;
	int                 _Reward;
	BYTE				_Type;
	BYTE				_Index;
	BYTE				_Level;
	BYTE				_Skill;
	BYTE				_Luck;
	BYTE				_Option;
	BYTE				_Excelente;
	char                _Message[255];
	char                _Name[2][255];
	char                _Column[255];
	char                _Coin[255];
};

struct sQuestPlayer
{
	int                 _Index;
	int                 _Kills;
	int                 _Start;
};

class cQuest
{
public:
	bool Load();
	void Connect(int aIndex);
	void Talk(OBJECTSTRUCT* Npc, OBJECTSTRUCT* lpObj);
	void Kill(int aIndex);
	void Reward(int aIndex);
	void Quit(LPOBJ lpObj);

public:
	bool                _Active;
	int                 _Count[2];

public:
	sQuest              QuestStruct[1000];

	sQuestPlayer	    PlayerStruct[OBJECT_MAX];
};

extern cQuest Quest;