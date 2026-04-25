#include "StdAfx.h"

CShop::CShop()
{
}

CShop::~CShop()
{
}

void CShop::Init()
{
	this->SendItemDataLen = 0;
	this->ItemCount = 0;
	memset(this->ShopInventoryMap, 0, sizeof(this->ShopInventoryMap));

	for (int i = 0; i < 120; i++)
	{
		this->Item[i].Clear();
	}
}

bool CShop::LoadShopItem(char* Filename)
{
	this->Init();

	Tokenizer token;
	TokenizerGroup group;
	TokenizerSection Section;

	if (token.ParseFile(std::string(Filename), group) == false)
	{
		char Buffer[100];
		sprintf_s(Buffer, "Falha no carregamento do shop!\n%s", &Filename[3]);
		MessageBoxA(NULL, Buffer, "[CMZ]: - Fatal Erro", MB_OK);
		return false;
	}

	if (group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->Type = Section.Rows[i].GetInt(0);
			this->Index = Section.Rows[i].GetInt(1);
			this->Level = Section.Rows[i].GetInt(2);
			this->Durability = Section.Rows[i].GetInt(3);
			this->Option[0] = Section.Rows[i].GetInt(4);
			this->Option[1] = Section.Rows[i].GetInt(5);
			this->Option[2] = Section.Rows[i].GetInt(6);
			this->Option[3] = Section.Rows[i].GetInt(7);

			if (this->InsertItem(this->Type, this->Index, this->Level, this->Durability, this->Option[0], this->Option[1], this->Option[2], this->Option[3]) == false)
			{
				char Buffer[120];
				sprintf_s(Buffer, "Falha ao inserir item no shop!\n%s\nItem: %d %d", &Filename[3], this->Type, this->Index);
				MessageBoxA(NULL, Buffer, "[CMZ]: - Erro", MB_OK);
			}
		}
	}

	return true;
}

int CShop::InsertItem(int Type, int Index, int Level, int Dur, BYTE Opt1, BYTE Opt2, BYTE Opt3, BYTE ExcOpt)
{
	int ItemNumber = ItemGetNumberMake(Type, Index);

	if (ItemNumber < 0)
	{
		char Buffer[100];
		sprintf_s(Buffer, "Error : ItemNumber invalido - %d %d", Type, Index);
		MessageBoxA(NULL, Buffer, "[CMZ]: - Erro", MB_OK);
		return 0;
	}

	int Width = 0;
	int Height = 0;

	ItemGetSize(ItemNumber, Width, Height);

	if (Width <= 0 || Height <= 0)
	{
		char Buffer[100];
		sprintf_s(Buffer, "Error : Size invalido - W:%d H:%d Item:%d %d", Width, Height, Type, Index);
		MessageBoxA(NULL, Buffer, "[CMZ]: - Erro", MB_OK);
		return 0;
	}

	int Blank = this->FindFreeSlot(Width, Height);

	if (Blank < 0 || Blank >= 120)
	{
		char Buffer[120];
		sprintf_s(Buffer, "Sem espaco no shop para item!\nType:%d Index:%d Size:%dx%d", Type, Index, Width, Height);
		MessageBoxA(NULL, Buffer, "[CMZ]: - Plugin - Erro", MB_OK);
		return 0;
	}

	this->Item[Blank].Clear();
	this->Item[Blank].m_Level = Level;

	if (Dur == 0)
	{
		Dur = ItemGetDurability(ItemNumber, Level, ((ExcOpt != 0) ? 1 : 0));
	}

	this->Item[Blank].m_Durability = (float)(Dur);
	this->Item[Blank].Convert(ItemNumber, Opt1, Opt2, Opt3, ExcOpt, 1);
	this->Item[Blank].Value();

	this->SendItemData[this->SendItemDataLen] = (BYTE)Blank;
	this->SendItemDataLen++;

	ItemByteConvert((LPBYTE)(&this->SendItemData[this->SendItemDataLen]), this->Item[Blank]);
	this->SendItemDataLen += 4;
	this->ItemCount++;

	return 1;
}

int CShop::InventoryMapCheck(int iX, int iY, int Width, int Height)
{
	if (Width <= 0 || Height <= 0)
	{
		return -1;
	}

	if (((iX + Width) > 8) || ((iY + Height) > 15))
	{
		return -1;
	}

	for (int Y = 0; Y < Height; Y++)
	{
		for (int X = 0; X < Width; X++)
		{
			if (this->ShopInventoryMap[((Y + iY) * 8) + (X + iX)] != 0)
			{
				return -1;
			}
		}
	}

	for (int Y = 0; Y < Height; Y++)
	{
		for (int X = 0; X < Width; X++)
		{
			this->ShopInventoryMap[((Y + iY) * 8) + (X + iX)] = 1;
		}
	}

	return (iX + (iY * 8));
}

int CShop::FindFreeSlot(int Width, int Height)
{
	for (int Y = 0; Y < 15; Y++)
	{
		for (int X = 0; X < 8; X++)
		{
			int Blank = this->InventoryMapCheck(X, Y, Width, Height);

			if (Blank >= 0)
			{
				return Blank;
			}
		}
	}

	return -1;
}

CShop ShopC[MAX_SHOP];
