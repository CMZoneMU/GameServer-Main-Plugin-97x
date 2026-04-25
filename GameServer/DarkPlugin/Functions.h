#pragma once

class Functions
{
public:
	void Hook(DWORD Function, DWORD Offset);
	void HookJump(DWORD Offset, LPVOID Function);
	void SetNop(DWORD Offset, int Size);
	void SetRRetn(DWORD Offset);
	int Get_PlayerIndex(char *Name);
	void Blue(LPCSTR Nome, LPSTR Mensagem, int aIndex);
	void Green(LPCSTR Nome, LPSTR Mensagem, int aIndex);
	void Yellow(LPCSTR Nome, LPSTR Mensagem, int aIndex);
	void Golden(int aIndex, const char* Format, ...);
	void Announce(const char *Format, ...);
	void UpdateCharacter(int aIndex, bool Effect);
	int MonsterAdd(int Monster, int MapNumber, int X, int Y);
	void FireWork(int aIndex);
	void MsgOutput(int aIndex, int Type, char * Msg, ...);
	void AllServerAnnounce(char *message, ...);
	void MsgOutputAll(char *message, ...);
	int CheckInventory(int aIndex, int Type, int Level);
	int DeleteInventory(int aIndex, int Type, int Level, int Quantity);
	int GetInventoryEmptySlotCount(LPOBJ lpObj);
	static BOOL gObjAttackEx(OBJECTSTRUCT* lpObj, OBJECTSTRUCT* lpTargetObj, class CMagicInf* lpMagic, int magicsend, unsigned char MSBFlag, int AttackDamage);
	static void gObjLifeCheckEx(LPOBJ lpTargetObj, LPOBJ lpObj, int AttackDamage, int DamageSendType, int MSBFlag, int MSBDamage, BYTE Skill);
	static void gObjPlayerKillerEx(LPOBJ lpObj, LPOBJ lpTargetObj);
	static void gObjInterfaceTimeCheckEx(LPOBJ lpObj);
	static void gObjSecondProcEx();
	static void gObjCloseSetEx(int aIndex, int flag);
	static short gObjDelEx(int aIndex);
	static void gObjUserDieEx(LPOBJ lpObj, LPOBJ lpTargetObj);
	static BYTE gObjInventoryMoveItemEx(int aIndex, unsigned char source, unsigned char target, int& durSsend, int& durTsend, unsigned char sFlag, unsigned char tFlag, unsigned char* siteminfo);
	static bool gObjLevelUpEx(LPOBJ lpObj, int addexp, int iMonsterType, int iEventType);
	BOOL GetBoxPosition(int MapNumber, int X, int Y, int W, int H, short& rX, short& rY);
	char* lMsgGet(int Number);
    BOOL gObjIsConnectedGP(int aIndex);
    void gObjFixInventoryPointer(OBJECTSTRUCT* lpObj);
	static void CGTalkRequestRecv(PMSG_TALKREQUEST* Msg, int aIndex);
	static void CGBuyRequestRecv(PMSG_BUYREQUEST* Msg, int Index);
	static BOOL ShopDataLoad();
	static BOOL gObjSetMonsterEx(int aIndex, int Class);
	static void GCWarePassSend(int aIndex, PMSG_WAREHOUSEPASSSEND *lpMsg);
	static BOOL gObjSetCharacterEx(LPBYTE lpdata, int aIndex);
	bool CheckItem(LPOBJ lpObj);
	void PlayerOut(LPOBJ lpObj);
	static BOOL gObjMoveGateEx(int aIndex, int Gate);
	float GetStatus(LPOBJ lpObj, BYTE Class, BYTE Type);
	static void GCDamageSend(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage);
	static void GCRefillSend(int aIndex, int Life, BYTE Ipos, BYTE flag);
	static void GCManaSend(int aIndex, int Mana, BYTE Ipos, unsigned char flag, WORD BP);
	static int ItemGetDurabilityEx(int aIndex, int Level, int Excellent);
	void SendMain(int aIndex);
	BYTE gObjInventoryInsertItem(int aIndex, CItem Item);
	static void ItemSerialCreateRecvEx(SDHP_ITEMCREATERECV* Result);
	int InventoryFullCheck(int aIndex, short Item);
	static BOOL CGItemDropRequestEx(PMSG_ITEMTHROW* lpMsg, int aIndex, BOOL Type);
	static void CSPJoinIdPassRequestEx(PMSG_IDPASS* lpMsg, int aIndex);
	int Rand(int Min, int Max);
	static void GCItemDurSendEx(int aIndex, BYTE pos, BYTE dur, unsigned char flag);
	static void CGUseItemRecvEx(PMSG_USEITEM* lpMsg, int aIndex);
	static BOOL NpcTalkEx(OBJECTSTRUCT* lpNpc, OBJECTSTRUCT* lpObj);
	static void PChatProcEx(PMSG_CHATDATA* Message, int aIndex);
	void GCResultSend(int aIndex, BYTE headcode, BYTE result);
	static void CGGuildRequestRecvEx(PMSG_GUILDJOINQ * lpMsg, int aIndex);
	void CGCloseWindow(int aIndex);
	static void gObjTeleportMagicUseEx(int aIndex, BYTE X, BYTE Y);
	void Refresh(int aIndex);
	void HealthBarSend(LPOBJ lpObj);
	static void gObjViewportListCreateEx(short aIndex);
	static void CGWarehouseUseEndEx(int aIndex);
	BOOL Position(int aIndex, int MapNumber, int X, int Y, int View);
	void CheckBuffs(LPOBJ lpObj);
	bool CheckString(const std::string& str);
	static void CGLiveClient(PMSG_CLIENTTIME * lpMsg, short aIndex);
	static void CGSellRequestRecvEx(PMSG_SELLREQUEST * lpMsg, int aIndex);
	static void gObjCalCharacterEx(int aIndex);
	static void CGPCharDelEx(PMSG_CHARDELETE * lpMsg, int aIndex);
	void DataSendAll(unsigned char* lpMsg, int Size);
	void PostSend(int Type, char Send[20], const char* Message, ...);
	static void Thread(void* lpParam);

	// ---------------------------
	static void ReadCommonEx();
};

extern Functions Func;
