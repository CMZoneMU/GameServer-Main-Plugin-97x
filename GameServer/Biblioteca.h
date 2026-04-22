#pragma once

class CItem
{
public:
	void Clear()
	{
		__asm
		{
			MOV ECX, this;
			MOV EDI, 0x47E110;
			CALL EDI;
		}
	}

	bool IsItem()
	{
		if ((int)this->m_Type == (-1))
		{
			return false;
		}

		return true;
	}

	void PlusSpecial(int* Value, int Special)
	{
		if (this->m_Type >= 0 && this->m_Durability != 0.0)
		{
			for (int i = 0; i < this->m_SpecialNum; i++)
			{
				if (this->m_Special[i] == Special)
				{
					int Option;

					switch (Special)
					{
					case 60:
					case 61:
					case 63:
						Option = 4 * this->m_Option;
						*Value += Option - (int)(Option * this->m_CurrentDurabilityState);
						break;
					case 62:
						Option = 5 * this->m_Option;
						*Value += Option - (int)(Option * this->m_CurrentDurabilityState);
						break;
					case 64:
						*Value += 4;
						break;
					case 80:
					case 81:
						*Value += 5 * this->m_Level + 50;
						break;
					case 83:
						*Value += 50;
						break;
					default:
						*Value += 4 * this->m_Option;
						break;
					}
				}
			}
		}
	}

	int ItemDefense()
	{
		if (!this->IsItem())
		{
			return 0;
		}
		else
		{
			int Defense = this->m_Defense;

			this->PlusSpecial(&Defense, 63);

			return Defense;
		}
	}

	void Convert(int iType, BYTE Option1, BYTE Option2, BYTE Option3, BYTE Attribute, BYTE DbVersion)
	{
		__asm
		{
			XOR EDX, EDX;
			MOV DL, DbVersion;
			PUSH EDX;
			XOR EDX, EDX;
			MOV DL, Attribute;
			PUSH EDX;
			XOR EDX, EDX;
			MOV DL, Option3;
			PUSH EDX;
			XOR EDX, EDX;
			MOV DL, Option2;
			PUSH EDX;
			XOR EDX, EDX;
			MOV DL, Option1;
			PUSH EDX;
			PUSH iType;
			MOV EDI, 0x47E290;
			MOV ECX, this;
			CALL EDI;
		}
	}

	char* GetName()
	{
		char* Name = "";

		__asm
		{
			MOV EDI, 0x401E9C;
			MOV ECX, this;
			CALL EDI;
			MOV Name, EAX;
		}

		return Name;
	}

	void Value()
	{
		__asm
		{
			MOV ECX, this;
			MOV EDI, 0x47FD80;
			CALL EDI;
		}
	}

public:
	DWORD	m_Number;
	char	m_Serial;
	short	m_Type;
	short	m_Level;
	BYTE	m_Part;
	BYTE	m_Class;
	BYTE	m_TwoHand;
	BYTE	m_AttackSpeed;
	BYTE	m_WalkSpeed;
	WORD	m_DamageMin;
	WORD	m_DamageMax;
	BYTE	m_SuccessfulBlocking;
	WORD	m_Defense;
	WORD	m_MagicDefense;
	BYTE	m_Speed;
	WORD	m_DamageMinOrigin;
	WORD	m_DefenseOrigin;
	WORD	m_Magic;
	float	m_Durability;
	WORD	m_DurabilitySmall;
	float	m_BaseDurability;
	BYTE	m_SpecialNum;
	BYTE	m_Special[8];
	BYTE	m_SpecialValue[8];
	WORD	m_RequireStrength;
	WORD	m_RequireDexterity;
	WORD	m_RequireEnergy;
	WORD	m_RequireLevel;
	BYTE	m_RequireClass[4];
	BYTE	m_Resistance[4];
	int		m_Value;
	DWORD	m_SellMoney;
	DWORD	m_BuyMoney;
	DWORD	m_OldSellMoney;
	DWORD	m_OldBuyMoney;
	BYTE	m_Skill;
	BYTE	m_Luck;
	BYTE	m_Option;
	BYTE	m_Excellent;
	float	m_DurabilityState[4];
	float	m_CurrentDurabilityState;
	bool	m_QuestItem;
};

struct _GUILD_INFO_STRUCT
{
	int				Number;
	char			Name[9];
	unsigned char	Mark[32];
	unsigned char	Count;
	unsigned char	TotalCount;
	char			Names[35][11];
	short			Index[35];
	unsigned char	Use[35];
	char			pServer[35];
	char			TargetGuildName[9];
	short			TargetIndex[35];
	struct			_GUILD_INFO_STRUCT* lpTargetGuildNode;
	unsigned char	WarDeclareState;
	unsigned char	WarState;
	unsigned char	WarType;
	unsigned char	BattleGroundIndex;
	unsigned char	BattleTeamCode;
	unsigned char	PlayScore;
	int				TotalScore;
	char			Notice[60];

	_GUILD_INFO_STRUCT *back;
	_GUILD_INFO_STRUCT *next;
};

struct tagActionState
{
	DWORD Rest : 1;
	DWORD Attack : 1;
	DWORD Move : 1;
	DWORD Escape : 1;
	DWORD Emotion : 4;
	DWORD EmotionCount : 8;
};

struct tagInterfaceState
{
	BYTE use : 2;
	BYTE state : 2;
	BYTE type : 4;
};

struct HITDAMAGE_STRUCT
{
	short number;
	int	HitDamage;
	DWORD LastHitTime;
};

struct VIEWPORT_PLAYER_STRUCT
{
	char State;
	short Number;
	unsigned char Type;
	short aIndex;
	int Distance;
};

struct VIEWPORT_STRUCT
{
	char State;
	short Number;
	unsigned char Type;
	short aIndex;
	int Distance;
};

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

struct PMSG_PARTYREQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;
};

struct PMSG_PARTYREQUESTSEND
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;
};

struct PMSG_WAREHOUSEPASSSEND
{
	PBMSG_HEAD h;
	char Type;
	short Pass;
	char LastJoominNumber[10];
};

struct PMSG_DEFAULT2
{
	PBMSG_HEAD h;
	BYTE subcode;
};

struct PMSG_CHARCREATE
{
	PBMSG_HEAD h;
	BYTE subcode;
	char Name[10];
	BYTE ClassSkin;
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

struct PMSG_UPDATEPOINTS
{
	PBMSG_HEAD h;
	BYTE subcode;
	int LevelUpPoint;
};

struct SDHP_ITEMCREATERECV
{
	PBMSG_HEAD	h;
	BYTE		x;
	BYTE		y;
	BYTE		MapNumber;
	DWORD		m_Number;
	short		Type;
	BYTE		Level;
	BYTE		Dur;
	BYTE		Op1;
	BYTE		Op2;
	BYTE		Op3;
	BYTE		NewOption;
	int			aIndex;
	short		lootindex;
};

struct PMSG_ITEMTHROW
{
	PBMSG_HEAD h;
	BYTE px;
	BYTE py;
	BYTE Ipos;
};

struct PMSG_ITEMTHROW_RESULT
{
	PBMSG_HEAD h;
	BYTE Result;
	BYTE Ipos;
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

struct PMSG_ACTION
{
	PBMSG_HEAD h;
	unsigned char Direction;
	unsigned char Action;
	unsigned char TargetH;
	unsigned char TargetL;
};

struct PMSG_IDPASS
{
	PBMSG_HEAD h;
	unsigned char Sub;
	char Id[10];
	char Pass[10];
	unsigned long Count;
	unsigned char Version[5];
	unsigned char Serial[16];
};

struct PMSG_TALKREQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;
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

struct PMSG_SELLREQUEST
{
	PBMSG_HEAD h;
	BYTE Pos;
};

struct PMSG_SELLRESULT
{
	PBMSG_HEAD h;
	BYTE Result;
	int Money;
};

struct PMSG_SHOPITEMCOUNT
{
	PWMSG_HEAD h;
	BYTE Type;
	BYTE count;
};

struct PMSG_BUYREQUEST
{
	PBMSG_HEAD h;
	BYTE Pos;
};

struct PMSG_BUYRESULT
{
	PBMSG_HEAD h;
	BYTE Result;
	BYTE ItemInfo[4];
};

struct PMSG_USEITEM
{
	PBMSG_HEAD h;
	BYTE inventoryPos;
	BYTE inventoryTarget;
	BYTE btItemUseType;
};

struct PMSG_MAGICATTACK
{
	PBMSG_HEAD h;
	BYTE MagicNumber;
	BYTE NumberH;
	BYTE NumberL;
	BYTE Dis;
};

struct PMSG_MOVE
{
	PBMSG_HEAD h;
	BYTE X;
	BYTE Y;
	BYTE Path[8];
};

struct PMSG_CHATDATA
{
	unsigned char Head;
	unsigned char Size;
	unsigned char Code;
	char Name[10];
	char Message[60];
};

struct PMSG_CHARDELETE
{
	PBMSG_HEAD h;
	BYTE subcode;
	char Name[10];
	char LastJoominNumber[10];
};

struct PMSG_RESULT
{
	PBMSG_HEAD h;
	unsigned char subcode;
	unsigned char result;
};

struct PMSG_DEFRESULT
{
	PBMSG_HEAD h;
	BYTE result;
};

struct PMSG_GUILDJOINQ
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;
};

struct PMSG_TRADE_REQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;
};

struct PMSG_CHARMAPJOINRESULT
{
	PBMSG_HEAD h;
	unsigned char subcode;
	unsigned char MapX;
	unsigned char MapY;
	unsigned char MapNumber;
	unsigned char Dir;
	unsigned long Exp;
	unsigned long NextExp;
	unsigned short LevelUpPoint;
	unsigned short Str;
	unsigned short Dex;
	unsigned short Vit;
	unsigned short Energy;
	unsigned short Life;
	unsigned short MaxLife;
	unsigned short Mana;
	unsigned short MaxMana;
	unsigned short BP;
	unsigned short MaxBP;
	int Money;
	unsigned char PkLevel;
	unsigned char CtlCode;
	short AddPoint;
	short MaxAddPoint;
};

struct PMSG_CHARREGEN
{
	PBMSG_HEAD h;
	char subcode;
	char MapX;
	char MapY;
	char MapNumber;
	char Dir;
	unsigned short Life;
	unsigned short Mana;
	unsigned short BP;
	unsigned int Exp;
	unsigned int Money;
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

struct PMSG_CLIENTTIME
{
	PBMSG_HEAD h;
	DWORD Time;
	WORD AttackSpeed;
	WORD MagicSpeed;
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

// Packet Char Info
struct PMSG_CUSTOM_CHARACTER_INFO
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

struct PLAYERSTRUCT
{
public:
	PLAYERSTRUCT():
		ResetCount(0), MasterCount(0), VipCount(0), VipDays(0), Vault{0, 0}, Hours(0), Hero(0), Killer(0), Bonus(0), Coin{ 0, 0, 0, 0, 0, 0 }, Jewels{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, Ware(0), Day(0), Patent(0), Rei(0), MasterPoint(0), Count{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, Waiting(false), Move(false), InEvent(false), Dead(false), Start(false), Helper(false), Pet(false), Delay{ 0, 0, 0 }, Time(0)
	{
	}

	int     ResetCount;
	int     MasterCount;
	int     VipCount;
	int		VipDays; // novo 
	int     Vault[2];
	int     Hours;
	int     Hero;
	int     Killer;
	int     Bonus;
	int     Coin[10];
	int     Jewels[9];
	int     Ware;
	int     Day;
	int     Patent;
	int     Rei;
	int     MasterPoint;
	int     Count[13];
	bool    Waiting;
	bool    Move;
	bool    InEvent;
	bool    Dead;
	bool    Start;
	bool    Helper;
	bool    Pet;
	DWORD   Delay[3];
	BYTE    Time;
};

struct OBJECTSTRUCT
{
	int m_Index;
	int Connected;
	char LoginMsgSnd;
	char LoginMsgCount;
	char CloseCount;
	char CloseType;
	struct _PER_SOCKET_CONTEXT* PerSocketContext;
	unsigned int m_socket;
	char Ip_addr[16];
	int UserNumber;
	int DBNumber;
	unsigned char Magumsa;
	DWORD AutoSaveTime;
	DWORD ConnectCheckTime;
	DWORD CheckTick;
	unsigned char CheckSpeedHack;
	DWORD CheckTick2;
	unsigned char CheckTickCount;
	int iPingTime; 
	unsigned char m_TimeCount;
	DWORD m_dwPKTimer;
	short CheckSumTableNum;
	DWORD CheckSumTime;
	BYTE Type;
	BYTE Live;
	char CharacterPos;
	char AccountID[11];
	char Name[11];
	char LastJoominNumber[14];
	unsigned char Class;
	unsigned char DBClass;
	unsigned char ChangeUP;
	short Level;
	int LevelUpPoint;
	unsigned long Experience;
	unsigned long NextExp;
	int Money;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	float Life;
	float MaxLife;
	float FillLife;
	float FillLifeMax;
	float Mana;
	float MaxMana;
	int BP;
	int MaxBP;
	int AddBP;
	float VitalityToLife;
	float EnergyToMana;
	char m_PK_Count;
	char m_PK_Level;
	int m_PK_Time;
	short X;
	short Y;
	unsigned char Dir;
	unsigned char MapNumber;
	short AddLife;
	short AddMana;
	unsigned char DamageMinus;
	unsigned char DamageReflect;
	short MonsterDieGetMoney;
	unsigned char MonsterDieGetLife;
	unsigned char MonsterDieGetMana;
	unsigned char StartX;
	unsigned char StartY;
	short m_OldX;
	short m_OldY;
	short TX;
	short TY;
	short MTX;
	short MTY;
	int PathCount;
	int PathCur;
	char PathStartEnd;
	short PathOri[15];
	short PathX[15];
	short PathY[15];
	char PathDir[16];
	unsigned long PathTime;
	char m_MoveGateNumber;
	DWORD Authority;
	unsigned long AuthorityCode;
	unsigned long Penalty;
	BYTE m_cAccountItemBlock;
	tagActionState m_ActState;
	BYTE m_ActionNumber;
	DWORD m_State;
	char m_StateSub;
	unsigned char m_Rest;
	char m_ViewState;
	BYTE m_ViewSkillState;
	DWORD m_LastMoveTime;
	DWORD m_LastAttackTime;
	int m_DetectSpeedHackTime;
	unsigned long m_SumLastAttackTime;
	unsigned long m_DetectCount;
	int m_DetectedHackKickCount;
	int m_SpeedHackPenalty;
	unsigned char m_AttackSpeedHackDetectedCount;
	unsigned long m_PacketCheckTime;
	unsigned char m_ShopTime;
	unsigned long m_TotalAttackTime;
	int m_TotalAttackCount;
	unsigned long TeleportTime;
	char Teleport;
	char KillerType;
	char DieRegen;
	char RegenOk;
	BYTE RegenMapNumber;
	BYTE RegenMapX;
	BYTE RegenMapY;
	DWORD RegenTime;
	DWORD MaxRegenTime;
	short m_PosNum;
	DWORD LifeRefillTimer;
	DWORD CurActionTime;
	DWORD NextActionTime;
	DWORD DelayActionTime;
	char DelayLevel;
	char m_PoisonBeattackCount;
	char m_ColdBeattackCount;
	OBJECTSTRUCT * lpAttackObj;
	short m_SkillNumber;
	DWORD m_SkillTime;
	char m_ManaFillCount;
	char m_LifeFillCount;
	int SelfDefense[5];
	DWORD SelfDefenseTime[5];
	DWORD MySelfDefenseTime;
	char m_Drink;
	int m_SkillDefense;
	char m_SkillDefenseTime;
	int m_SkillAttack;
	char m_SkillAttackTime;
	int m_SkillAttack2;
	char m_SkillAttackTime2;
	int m_SkillAddLife;
	int m_SkillAddLifeTime;
	int m_SkillHarden;
	int m_SkillHardenTime;
	int m_SkillMagumReduceDefense;
	int m_SkillMagumReduceDefenseTime;
	int PartyNumber;
	int PartyTargetUser;
	int GuildNumber;
	struct _GUILD_INFO_STRUCT* lpGuild;
	char GuildName[11];
	int m_RecallMon;
	int m_Change;
	short TargetNumber;
	short TargetShopNumber;
	short ShopNumber;
	short LastAttackerID;
	int m_AttackDamageMin;
	int m_AttackDamageMax;
	int m_MagicDamageMin;
	int m_MagicDamageMax;
	int m_AttackDamageLeft;
	int m_AttackDamageRight;
	int m_AttackDamageMaxLeft;
	int m_AttackDamageMinLeft;
	int m_AttackDamageMaxRight;
	int m_AttackDamageMinRight;
	int m_AttackRating;
	int m_AttackSpeed;
	int m_MagicSpeed;
	int m_Defense;
	int m_MagicDefense;
	int m_SuccessfulBlocking;
	short m_MoveSpeed;
	short m_MoveRange;
	short m_AttackRange;
	short m_AttackType;
	short m_ViewRange;
	short m_Attribute;
	short m_ItemRate;
	short m_MoneyRate;
	int m_CriticalDamage;
	int m_ExcelentDamage;
	class CMagicInf* m_lpMagicBack;
	class CMagicInf* Magic;
	char MagicCount;
	unsigned char UseMagicNumber;
	unsigned long UseMagicTime;
	char UseMagicCount;
	short OSAttackSerial;
	unsigned char SASCount;
	unsigned long SkillAttackTime;
	unsigned char CharSet[11];
	unsigned char m_Resistance[4];
	int FrustrumX[4];
	int FrustrumY[4];
	struct VIEWPORT_STRUCT VpPlayer[75];
	struct VIEWPORT_PLAYER_STRUCT VpPlayer2[75];
	int VPCount;
	int VPCount2;
	struct HITDAMAGE_STRUCT sHD[40];
	short sHDCount;
	struct tagInterfaceState m_IfState;
	unsigned long m_InterfaceTime;
	CItem *pInventory;
	unsigned char * pInventoryMap;
	char * pInventoryCount;
	char pTransaction;
	CItem * Inventory1;
	unsigned char * InventoryMap1;
	char InventoryCount1;
	CItem * Inventory2;
	unsigned char * InventoryMap2;
	char InventoryCount2;
	CItem * Trade;
	LPBYTE TradeMap;
	int TradeMoney;
	unsigned char TradeOk;
	CItem * pWarehouse;
	unsigned char * pWarehouseMap;
	char WarehouseCount;
	short WarehousePW;
	unsigned char WarehouseLock;
	unsigned char WarehouseUnfailLock;
	int WarehouseMoney;
	int WarehouseSave;
	CItem * pChaosBox;
	unsigned char* pChaosBoxMap;
	int ChaosMoney;
	int ChaosSuccessRate;
	int ChaosLock;
	unsigned long m_Option;
	int m_nEventScore;
	int m_nEventExp;
	int m_nEventMoney;
	unsigned char m_bDevilSquareIndex;
	unsigned char m_bDevilSquareAuth;
	char m_cBloodCastleIndex;
	char m_cBloodCastleSubIndex;
	int m_iBloodCastleEXP;
	unsigned char IsInBattleGround;
	unsigned char HaveWeaponInHand;
	short EventChipCount;
	int MutoNumber;
	int UseEventServer;
	unsigned char LoadWareHouseInfo;
	unsigned char m_Quest[50];
	unsigned char m_SendQuestInfo;
	int m_SkyBossMonSheildLinkIndex;
	int m_SkyBossMonSheild;
	int m_SkyBossMonSheildTime;
	int m_MaxLifePower;
	int m_WizardSkillDefense;
	int m_WizardSkillDefenseTime;
	int m_PacketChecksumTime;
	int m_CheckLifeTime;
	unsigned char m_MoveOtherServer;
	char m_BossGoldDerconMapNumber;
	unsigned char m_InWebzen;
	char m_LastTeleportTime;
	BYTE m_ClientHackLogCount;
	unsigned char m_ReqWarehouseOpen;
	int NotAttackAreaCount;
};

typedef OBJECTSTRUCT*		LPOBJ;
extern	OBJECTSTRUCT*		gObj;

extern PLAYERSTRUCT Custom[5600];