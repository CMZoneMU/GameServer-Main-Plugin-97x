#pragma once

#define MAX_SHOP 12

class CShop
{
public:
	CShop();
	virtual ~CShop();

public:
	void Init();
	bool LoadShopItem(char* Filename);
	int InsertItem(int Type, int Index, int Level, int Dur, BYTE Opt1, BYTE Opt2, BYTE Opt3, BYTE ExcOpt);
	int InventoryMapCheck(int iX, int iY, int Width, int Height);
	int FindFreeSlot(int Width, int Height);

public:
	int Type;
	int Index;
	int Level;
	int Durability;
	BYTE Option[4];
	BYTE ShopInventoryMap[120];
	int ItemCount;
	CItem Item[120];
	BYTE SendItemData[600];
	int SendItemDataLen;
};

extern CShop ShopC[MAX_SHOP];
