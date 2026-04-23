#include "StdAfx.h"

void __declspec(naked) cJewel::Upgrade()
{
	__asm
	{
		CMP BP, ITEMGET(14, 14);
		JE Item;

		CMP BP, ITEMGET(15, 16);
		JE Item;

		CMP BP, ITEMGET(15, 17);
		JE Item;

		CMP BP, ITEMGET(15, 18);
		JE Item;

		CMP BP, ITEMGET(15, 19);
		JE Item;

		CMP BP, ITEMGET(15, 20);
		JE Item;

		CMP BP, ITEMGET(15, 22);
		JE Item;

		CMP BP, ITEMGET(15, 23);
		JE Item;

		MOV EAX, 0x4DA01D;
		JMP EAX;

	Item:
		MOV EAX, 0x4DA028;
		JMP EAX;
	}
}

void __declspec(naked) cJewel::Apply()
{
	__asm
	{
		CMP BP, ITEMGET(14, 14);
		JE Item;

		CMP BP, ITEMGET(15, 16);
		JE Item;

		CMP BP, ITEMGET(15, 17);
		JE Item;

		CMP BP, ITEMGET(15, 18);
		JE Item;

		CMP BP, ITEMGET(15, 19);
		JE Item;

		CMP BP, ITEMGET(15, 20);
		JE Item;

		CMP BP, ITEMGET(15, 22);
		JE Item;

		CMP BP, ITEMGET(15, 23);
		JE Item;

		MOV ECX, 0x4D1D39;
		JMP ECX;

	Item:
		MOV ECX, 0x4D1D51;
		JMP ECX;
	}
}

void __declspec(naked) cJewel::Color()
{
	static short Item = 0;

	_asm
	{
		MOV Item, AX
	}

	if (Item == ITEM(14, 13))
	{
		goto Return;
	}
	else if (Item == ITEM(15, 16))
	{
		goto Return;
	}
	else if (Item == ITEM(15, 17))
	{
		goto Return;
	}
	else if (Item == ITEM(15, 18))
	{
		goto Return;
	}
	else if (Item == ITEM(15, 19))
	{
		goto Return;
	}
	else if (Item == ITEM(15, 20))
	{
		goto Return;
	}
	else if (Item == ITEM(15, 22))
	{
		goto Return;
	}
	else if (Item == ITEM(15, 23))
	{
		goto Return;
	}
	else
	{
		_asm
		{
			MOV EDX, 0x4C55E6
			JMP EDX
		}
	}

Return:
	__asm
	{
		MOV EAX, 0x4C5FE9;
		JMP EAX;
	}
}

cJewel Jewel;