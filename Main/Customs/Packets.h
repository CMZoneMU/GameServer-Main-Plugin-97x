#pragma once

struct PBMSG_HEAD
{
public:
	void set(LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};

	BYTE c;
	BYTE size;
	BYTE head;
};

struct PWMSG_HEAD
{
	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE head;
};

struct PSBMSG_HEAD
{
public:
	void set(BYTE head, BYTE subh, BYTE size)
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head, BYTE subh, BYTE size)
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size;
	BYTE head;
	BYTE subh;
};

struct PMSG_TALKRESULT
{
    PBMSG_HEAD h;
    BYTE result;
    BYTE level1;
    BYTE level2;
    BYTE level3;
    BYTE level4;
    BYTE Treasure;
};

struct PMSG_CHARINFOMAIN
{
	PBMSG_HEAD h;
	BYTE Code;
	WORD Class;
	WORD Dexterity;
	WORD AttackSpeed;
	WORD MagicSpeed;
	int LevelUpPoint;
	int Sword[13];
};

struct PMSG_UPDATECHARACTER
{
	PBMSG_HEAD h;
	BYTE Code;
	DWORD Experience;
	DWORD NextExperience;
	WORD Level;
	int LevelUpPoint;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	WORD BP;
	WORD MaxBP;
};

struct PMSG_LEVELUP
{
	PBMSG_HEAD h;
	BYTE subcode;
	WORD Level;
	WORD LevelUpPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxBP;
	WORD AddPoint;
	WORD MaxAddPoint;
};

struct PMSG_LVPOINTADDRESULT
{
	PBMSG_HEAD h;
	BYTE subcode;
	BYTE ResultType;
	WORD MaxLifeAndMana;
	WORD MaxBP;
};

struct PMSG_UPDATEPOINTS
{
	PBMSG_HEAD h;
	BYTE subcode;
	int LevelUpPoint;
};

struct PMSG_JOINRESULT
{
	PBMSG_HEAD h;
	BYTE scode;
	BYTE result;
	BYTE NumberH;
	BYTE NumberL;
	BYTE CliVersion[5];
};

struct PMSG_ATTACKRESULT
{
	PBMSG_HEAD h;
	unsigned char NumberH;
	unsigned char NumberL;
	unsigned char DamageH;
	unsigned char DamageL;
	unsigned char DamageType;
	int AttackDamage;
};

struct PMSG_REFILL
{
	PBMSG_HEAD h;
	unsigned char IPos;
	unsigned char LifeH;
	unsigned char LifeL;
	unsigned char Flag;
	int Life;
};

struct PMSG_MANASEND
{
	PBMSG_HEAD h;
	unsigned char IPos;
	unsigned char ManaH;
	unsigned char ManaL;
	unsigned char BPH;
	unsigned char BPL;
	int Mana;
	int BP;
};

struct PMSG_DIEPLAYER
{
	PBMSG_HEAD h;
	unsigned char NumberH;
	unsigned char NumberL;
	unsigned char Skill;
	unsigned char KillerNumberH;
	unsigned char KillerNumberL;
};

struct PMSG_HEALTHBAR
{
	PWMSG_HEAD h;
	BYTE Code;
	BYTE Count;
};

struct PMSG_HEALTHBAR_INFO
{
	short Index;
	BYTE Rate;
};

struct CUSTOM_RANKUSER_DATA
{
	int Index;
	int ResetCount;
	int Rank;
	int Type;
};

struct PMSG_CUSTOM_RANKUSER
{
	PSBMSG_HEAD h;
	int Index;
	int ResetCount;
	int Rank;
	int Type;
};

struct PMSG_LIVE_CLIENT
{
	PBMSG_HEAD h;
	DWORD TickCount;
};

struct CHAT_WHISPER
{
	PBMSG_HEAD h;
	char Name[10];
	char Message[90];
	BYTE Type;
};

// [ Novo ]: Struct para receber informações do personagem, como resets, pontos, vip, etc.
struct PMSG_CUSTOM_CHARACTER_INFO_RECV
{
	PSBMSG_HEAD h;
	int Reset;
	int MasterReset;
	int MasterPoint;
	int Cash;
	int EventPoint;
	int Vip;
	int VipDays;
	int OnlineCount;
};