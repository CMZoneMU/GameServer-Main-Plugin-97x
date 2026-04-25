#pragma once

#define MonsterCount	                0x634D8E4
#define MAXMONSTER                      4200
#define OBJECT_BASE		                0x4CEE778
#define OBJECT_SIZE		                0x0D0C
#define OBJECT_MIN		                4800
#define OBJECT_MAX		                5600
#define	DIR_BASE						(0x687DE60)
#define gMerryXMasNpcEvent				(int*)(0x704E1D8)
#define gHappyNewYearNpcEvent			(int*)(0x704E1DC)
#define bCanChaosBox					(int*)(0x5135F8)
#define bCanWarehouseLock				(int*)(0x5135FC)
#define gDQChaosSuccessRateLevel1		(int*)(0x5136B4)
#define gDQChaosSuccessRateLevel2		(int*)(0x5136B8)
#define gDQChaosSuccessRateLevel3		(int*)(0x5136BC)
#define gDQChaosSuccessRateLevel4		(int*)(0x5136C0)
#define ServerMaxUser                   *(int*)0x5133E8
#define TotalUser						*(int*)0x5EC4F14
#define ITEM_SIZE		                0x0084
#define ITEMGET(t,i)	                ((t * 32) + i)
#define MSGGET(x,y)		                ((x * 256) + y)
#define REFILL_MAX		                0xFE
#define REFILL_VALUE	                0xFF
#define REFILL_UNKNOWN	                0xFD

#define GET_NUMBERH(x)				    ((BYTE)((DWORD)(x) >> (DWORD)(8)))
#define GET_NUMBERL(x)				    ((BYTE)((DWORD)(x) & 0xFF))
#define MAKE_NUMBER(X,Y)				((WORD)(((BYTE)(Y) & 0xFF) | ((BYTE)(X & 0xFF) << 8)))
#define MAKE_NUMBERD(X,Y)				((UINT)((WORD)(Y & 0xFFFF) | ((WORD)(X & 0xFFFF) << 16)))
#define BC_MAP_RANGE(i)                 (((i < MAP_INDEX_BLOODCASTLE1 ) ? FALSE : (i > MAP_INDEX_BLOODCASTLE7) ? FALSE : TRUE ))
#define OBJECT_RANGE(x)                 (((x) < 0) ? FALSE: ((x) > OBJECT_MAX -1) ? FALSE :TRUE)

#define GCWarehouseStateSend            ((void(*)(int aIndex, char state)) 0x4233A0)
#define GCWarehouseRecivePassword       ((void(*)(int aIndex, PMSG_WAREHOUSEPASSSEND *lpMsg)) 0x423400)
#define DGGuildMemberInfoRequest        ((void(*)(int aIndex)) 0x42C460)
#define CGRequestQuestInfo              ((void(*)(int aIndex)) 0x42A7C0)
#define GCItemListSend                  ((void(*)(int aIndex)) 0x411010)
#define gObjPlayerKiller			    ((void(*)(LPOBJ, LPOBJ)) 0x4641A0)
#define GCKillPlayerExpSend             ((void(*)(int aIndex, int TargetIndex, int Exp, int AttackDamage, int MSBFlag)) 0x425A70) 
#define gObjNextExpCal	                ((void(*)(LPOBJ)) 0x402040)
#define gObjSetBP				        ((void(*)(int aIndex)) 0x45C040)
#define gObjInventorySend               ((void(*)(DWORD aIndex)) 0x411010) 
#define gObjMakePreviewCharSet          ((void(*)(DWORD aIndex)) 0x46FE30)    
#define ChatNpc                         ((void(*) (OBJECTSTRUCT * lpNpc, char * Msg, int senduser)) 0x40147E)
#define NpcTalk                         ((BOOL(*) (OBJECTSTRUCT* lpNpc, OBJECTSTRUCT* lpObj)) 0x487A50)
#define ChatTargetSend					((void(*)(LPOBJ lpObj, char* szMsg, int aIndex)) 0x415AD0)
#define TradeEx							((void(*) (LPBYTE aRecv, int aIndex)) 0x41D3B0)
#define ProtocolCore					((void(*)(BYTE, PBYTE, DWORD, DWORD, ...)) 0x414180)
#define DataSend                        ((void(*)(DWORD aIndex, PBYTE Packet, DWORD Size)) 0x440240)
#define LogAdd							((void(*)(char* Log, ...)) 0x44C7E0)
#define LogAddC							((void(*)(BYTE Color, char* Log, ...)) 0x44C8D0)
#define LogAddTD						((void(*)(char* Log, ...)) 0x44CA00)
#define GCPkLevelSend					((void(*)(DWORD aIndex,BYTE PkLevel)) 0x417E80)
#define CMAPMoneyItemDrop				((void(*)(DWORD Money,DWORD x, DWORD y))0x490560)
#define gObjDel							((short(*)(int)) 0x460640)
#define GCMoneySend						((void(*)(DWORD aIndex, DWORD Money))0x4185C0)
#define ItemSerialCreateSend			((void(*)(int aIndex, BYTE MapNumber, BYTE X, BYTE Y, int Type, BYTE Level, BYTE Dur, BYTE Op1, BYTE Op2, BYTE Op3, int LootIndex, BYTE NewOption)) 0x4121E0)
#define gObjTeleport					((void(*)(int aIndex, int MapNumber, int X, int Y)) 0x40181B)
#define ChatNpc							((void(*) (OBJECTSTRUCT * lpNpc, char * Msg, int senduser)) 0x40147E)
#define gEventMonsterItemDrop			((int(*)(OBJECTSTRUCT *,OBJECTSTRUCT *)) 0x40A670)
#define gObjMonsterTopHitDamageUser		((int(*)(LPOBJ lpObj)) 0x405180)
#define gObjCloseSet                    ((void(*)(int aIndex, int flag))  0x45AAB0) 
#define ItemGetNumberMake				((int(*)(int, int)) 0x482DE0)
#define ItemGetSize						((void(*)(int, int&, int&)) 0x482E40)
#define ItemByteConvert					((void(*)(LPBYTE, CItem)) 0x482AE0)
#define AllMonsterReload				((void(*)()) 0x48BA40)
#define ShopReload						((void(*)()) 0x484FA0)
#define MonsReload						((void(*)()) 0x4026A3)
#define gObjTradeCancel				    ((void(*)(int aIndex)) 0x41E8A0)
#define gObjTradeOkButton               ((void(*)(int aIndex)) 0x46F6C0)
#define JGCharacterCreateFailSend	    ((void(*)(DWORD, char*)) 0x410A50)
#define ConfigReload					((void(*)()) 0x48C2E0)
#define CGWarehouseUseEnd               ((void(*)(int)) 0x423250)  
#define GCMagicAttackNumberSend         ((void(*)(LPOBJ lpObj, BYTE MagicNumber, int Number, unsigned char Skill)) 0x402036)
#define GCServerMsgStringSend			((void(*)(char * Text, DWORD PlayerID, int Type)) 0x416430)
#define CloseClient						((void(*)(int)) 0x440E90)
#define gObjGameClose					((void(*)(int)) 0x4602E0)
#define gObjViewportListProtocolCreate  ((void(*)(OBJECTSTRUCT*))0x474E40)
#define gObjViewportListProtocolDestroy ((void(*)(OBJECTSTRUCT*)) 0x474D10) 
#define gObjViewportClose               ((void(*)(OBJECTSTRUCT*)) 0x470EA0) 
#define gObjViewportListCreate          ((void(*)(int index)) 0x4710D0) 
#define gObjClearViewport               ((void(*)(OBJECTSTRUCT*)) 0x45AA00)
#define gObjViewportPaint               ((void(*)(HWND hWnd, short aIndex)) 0x470710)
#define gObjSetCharacter                ((bool(*)(LPBYTE lpdata, int aIndex)) 0x45C370)
#define gObjAddMonster				    ((short(*)(int MapNumber)) 0x4013B1) 
#define gObjSetMonster				    ((BOOL(*)(int aIndex, int Mob)) 0x45E6C0)  
#define gObjAttack                      ((int(*)(LPOBJ lpObj, LPOBJ lpTargetObj, class CMagicInf* lpMagic, int magicsend, unsigned char MSBFlag, int AttackDamage))(0x4677A0))
#define GCLevelUpMsgSend		     	((void(*)(int aIndex, WORD Level, WORD LevelUpPoint, WORD MaxLife, WORD MaxMana, WORD MaxBP)) 0x4018B6)
#define gObjLifeCheck					((void(*)(LPOBJ lpTargetObj, LPOBJ lpObj, int AttackDamage, int DamageSendType, int MSBFlag, int MSBDamage, BYTE Skill)) 0x4684A0)
#define GCDiePlayerSend                 ((void(*)(OBJECTSTRUCT* lpObj, int TargetIndex, BYTE skill, int KillerIndex))  0x425BB0)
#define GCMagicListMultiSend            ((void(*)(LPOBJ lpObj)) 0x418030)
#define gObjInventoryDeleteItem         ((void(*)(int,int)) 0x402383)
#define GCInventoryItemDeleteSend       ((void(*)(int,int,unsigned char)) 0x40201D)
#define LoadItemBag	                    ((void(*)()) 0x48E9A0)
#define gObjAdd                         ((short(*)(SOCKET, char*, int)) 0x45F1E0)
#define GCSendQuestPrize                ((int(*)(int, int, int)) 0x4018D9)
#define gObjSecondProc                  ((void(*)()) 0x473800)
#define gObjInterfaceTimeCheck          ((void(*)(OBJECTSTRUCT* lpObj)) 0x4652A0)
#define PacketCheckTime					((BOOL(*)(OBJECTSTRUCT*)) 0x4140C0)
#define gObjSetInventory1Pointer		((void(*)(OBJECTSTRUCT*)) 0x461960)
#define GDGetWarehouseList				((void(*)(int, char*)) 0x411560)
#define gObjInventoryTrans				((bool(*)(int)) 0x468C40)
#define gObjItemTextSave				((void(*)(OBJECTSTRUCT*)) 0x45DCD0)
#define gObjWarehouseTextSave			((void(*)(OBJECTSTRUCT*)) 0x45DF40)
#define gObjSearchItem					((int(*)(OBJECTSTRUCT*, int, int)) 0x469F50)
#define gObjShopBuyInventoryInsertItem	((BYTE(*)(int, CItem)) 0x46A1D0)
#define CGPartyRequestRecv              ((void(*)(PMSG_PARTYREQUEST* lpMsg, int aIndex)) 0x41E970)
#define gObjUserDie						((void(*)(OBJECTSTRUCT*, OBJECTSTRUCT*)) 0x4645C0)
#define gObjInventoryMoveItem			((BYTE(*)(int, BYTE, BYTE, int&, int&, BYTE, BYTE, LPBYTE)) 0x46C3D0)
#define gObjLevelUp						((bool(*)(LPOBJ lpObj, int addexp, int iMonsterType, int iEventType))(0x462A20))
#define gObjCalcMaxLifePower			((int(*)(int aIndex)) 0x47DED0)
#define gObjCalDistance                 ((int(*)(LPOBJ, LPOBJ)) 0x461730)
#define GCItemDurSend                   ((void(*)(int aIndex, BYTE pos, BYTE dur, unsigned char flag)) 0x429210)
#define gObjMoveGate					((BOOL(*)(int aIndex, int Gate)) 0x477760)
#define CGChaosBoxUseEnd                ((void(*)(int aIndex)) 0x424330)
#define WinMain							((int(*)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)) 0x48F740)
#define NpcGuildMasterTalk				((BOOL(*)(LPOBJ lpNpc, LPOBJ lpObj)) 0x488120)
#define CGActionRecv		            ((void(*)(PMSG_ACTION* lpMsg, int aIndex)) 0x425CD0)
#define CSPJoinIdPassRequest            ((void(*)(PMSG_IDPASS* lpMsg, int aIndex)) 0x416A40)
#define ReadCommon                      ((void(*)()) 0x48C2E0)
#define GDGetWarehouseList              ((void(*)(int aIndex, char* Account)) 0x411560)
#define gObjExtItemApply	            ((void(*)(LPOBJ)) 0x453C40)
#define ItemGetDurability               ((int(*)(int Index, int Level, int Excellent)) 0x482EE0)
#define gObjWarehouseDeleteItem			((BYTE(*)(int aIndex, int Pos)) 0x469750)
#define ItemSerialCreateRecv			((void(*)(SDHP_ITEMCREATERECV* Result)) 0x4122C0)
#define GCInventoryItemOneSend          ((void(*)(int aIndex, int pos)) 0x417CB0)
#define gObjOnlyInventoryRectCheck      ((BYTE(*)(int aIndex, int sx, int sy, int Width, int Height)) 0x46AB80)
#define CGItemDropRequest				((BOOL(*)(PMSG_ITEMTHROW* lpMsg, int aIndex, BOOL Type)) 0x4191B0)
#define GJPUserClose                    ((void(*)(char* Account)) 0x413160)
#define CGUseItemRecv                   ((void(*)(PMSG_USEITEM* lpMsg, int aIndex)) 0x427A70)
#define CGMagicAttack                   ((void(*)(PMSG_MAGICATTACK* lpMsg, int aIndex)) 0x425F60)
#define GCActionSend                    ((void(*)(LPOBJ lpObj, BYTE ActionNumber, int aIndex, int TargetIndex)) 0x425C50)
#define gObjCharZeroSet				    ((void(*)(int aIndex)) 0x45AD90)
#define BuxConvert                      ((void(*)(char* Buff, int Size)) 0x44D4A0)
#define gObjGameClose				    ((BOOL(*)(int aIndex)) 0x4602E0)
#define gObjCalCharacter                ((void(*)(int aIndex)) 0x451DE0)
#define PMoveProc                       ((void(*)(PMSG_MOVE* Move, int aIndex)) 0x424470)
#define gObjInventoryItemSet			((void(*)(int aIndex, int Item, BYTE Set)) 0x469410)
#define PChatProc					    ((void(*)(PMSG_CHATDATA* Message, int aIndex)) 0x415B90)
#define CGGuildRequestRecv              ((void(*)(PMSG_GUILDJOINQ * lpMsg, int aIndex)) 0x4201C0)
#define CGPartyListAll                  ((void(*)(int Party)) 0x41FB80)
#define GCEquipmentSend                 ((void(*)(int aIndex)) 0x418200)
#define ChaosBoxInit			        ((BOOL(*)(LPOBJ lpObj)) 0x447270)
#define gObjInventoryCommit             ((BOOL(*)(int aIndex)) 0x468F10)
#define gObjTeleportMagicUse			((void(*)(int aIndex, BYTE X, BYTE Y)) 0x4775C0)
#define GDSetWarehouseMoney             ((void(*)(int aIndex)) 0x412140)
#define GCRecallMonLife                 ((void(*)(int aIndex, int Max, int Life)) 0x4182C0)
#define gObjAddCallMon				    ((short(*)()) 0x45F420)
#define gObjMonsterCallKill             ((void(*)(int aIndex)) 0x47C2C0)
#define CGPCharDel					    ((void(*)(PMSG_CHARDELETE * lpMsg, int aIndex)) 0x417680)
#define CGSellRequestRecv               ((void(*)(PMSG_SELLREQUEST * lpMsg, int aIndex)) 0x41C610)

enum OBJECT_TYPE 
{
	EMPTY		= 1,
	MONSTER		= 2,
	PLAYER		= 1,
	NPC			= 3
};

enum OBJECT_STATE
{
	OFFLINE		= 0,
	CONNECTED	= 1,
	LOGGED		= 2,
	PLAYING		= 3
};

enum CLASS_NUMBER 
{
	WIZARD		= 0,
	KNIGHT		= 1,
	ELF			= 2,
	MAGIC		= 3,
};

enum MAP_INDEX
{
	MAP_INDEX_LORENCIA = 0x0,
	MAP_INDEX_DUNGEON = 0x1,
	MAP_INDEX_DEVIAS = 0x2,
	MAP_INDEX_NORIA = 0x3,
	MAP_INDEX_LOSTTOWER = 0x4,
	MAP_INDEX_RESERVED = 0x5,
	MAP_INDEX_BATTLESOCCER = 0x6,
	MAP_INDEX_ATHLANSE = 0x7,
	MAP_INDEX_TARKAN = 0x8,
	MAP_INDEX_DEVILSQUARE = 0x9,
	MAP_INDEX_ICARUS = 0xa,
	MAP_INDEX_BLOODCASTLE1 = 0xb,
	MAP_INDEX_BLOODCASTLE2 = 0xc,
	MAP_INDEX_BLOODCASTLE3 = 0xd,
	MAP_INDEX_BLOODCASTLE4 = 0xe,
	MAP_INDEX_BLOODCASTLE5 = 0xf,
	MAP_INDEX_BLOODCASTLE6 = 0x10,
	MAP_INDEX_BLOODCASTLE7 = 0x11,
};
