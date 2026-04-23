#include "StdAfx.h"

bool MoveItem(DWORD a1, DWORD a2, int a3, int Fila, int Column)
{
	((unsigned int(__thiscall*)(DWORD a1, DWORD a2)) 0x43C8B0)(0x55C4C20, 0x83A9443);

	int trade = *(BYTE*)0x83A9443;

	((unsigned int(__thiscall*)(DWORD a1, DWORD a2)) 0x4228A0)(0x55C4C20, 0x83A9443);

	if (trade) //Trade
	{
		return ((bool(*)(DWORD a1, DWORD a2, int a3, int Fila, int Columna))0x004D1710)(*(DWORD*)0x83A45F8 + 15, *(DWORD*)0x83A45F4 + 270, 0x083A6EF0, 8, 4);
	}
	else if (*(BYTE*)0x083A9442 && *(DWORD*)0x083A9468 != 1) //Chaos Mix
	{
		return ((bool(*)(DWORD a1, DWORD a2, int a3, int Fila, int Column))0x004D1710)(*(DWORD*)0x83A93F0 + 15, *(DWORD*)0x83A93F4 + 110, 0x083A8B70, 8, 4);
	}
	else if (*(BYTE*)0x083A9441) //Warehouse
	{
		return ((bool(*)(DWORD a1, DWORD a2, int a3, int Fila, int Column))0x004D1710)(a1, a2, a3, Fila, Column);
	}

	return FALSE;
}