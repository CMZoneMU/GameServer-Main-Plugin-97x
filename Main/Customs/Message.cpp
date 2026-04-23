#include "StdAfx.h"

void cMessage::Load()
{
	SetNop(0x40D87B, 118);
	HookJump(0x40D87B, cMessage::Color1);
	SetNop(0x40D71A, 123);
	HookJump(0x40D71A, cMessage::Color2);
	SetNop(0x40D585, 146);
	HookJump(0x40D585, cMessage::Color3);
	SetNop(0x47E7AF, 146);
	HookJump(0x47E7AF, cMessage::Color4);
	SetNop(0x47E418, 9);
	HookJump(0x47E418, cMessage::Color5);
	SetNop(0x438D37, 5);
}

void __declspec(naked) cMessage::Color1()
{
	static DWORD Offset1 = 0x40D8F1;
	static DWORD Color = 0;

	__asm
	{
		MOV Color, EAX;
	}

	*(DWORD*)0x554C9C = 0xFF000000;
	*(DWORD*)0x554CA4 = 0x9632C8FF;

	if (Color == 0)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0x9632C8FF;
	}

	if (Color == 1)
	{
		*(DWORD*)0x554C9C = 0xFFFF9664;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 2)
	{
		*(DWORD*)0x554C9C = 0xFF001EFF;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 3)
	{
		*(DWORD*)0x554C9C = 0xFFC8DCE6;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 4)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0x96FFC800;
	}

	if (Color == 5)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0xC896FF00;
	}

	if (Color == 6) // - White
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0xFFFFFFFF;
	}

	if (Color == 7) // - Prata
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(105, 114, 114, 200);
	}

	if (Color == 8) // - Gold
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(255, 166, 0, 200);
	}

	if (Color == 9) // - Diamant
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(0, 60, 255, 200);
	}

	__asm
	{
		JMP Offset1
	}
}


void __declspec(naked) cMessage::Color2()
{
	static DWORD Offset2 = 0x40D795;
	static DWORD Color = 0;

	__asm
	{
		MOV Color, EAX;
	}

	*(DWORD*)0x554C9C = 0xFF000000;
	*(DWORD*)0x554CA4 = 0x9632C8FF;

	if (Color == 0)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0x9632C8FF;
	}

	if (Color == 1)
	{
		*(DWORD*)0x554C9C = 0xFFFF9664;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 2)
	{
		*(DWORD*)0x554C9C = 0xFF001EFF;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 3)
	{
		*(DWORD*)0x554C9C = 0xFFC8DCE6;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 4)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0x96FFC800;
	}

	if (Color == 5)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0xC896FF00;
	}

	if (Color == 6) // - White
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0xFFFFFFFF;
	}

	if (Color == 7) // - Prata
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(105, 114, 114, 200);
	}

	if (Color == 8) // - Gold
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(255, 166, 0, 200);
	}

	if (Color == 9) // - Diamant
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(0, 60, 255, 200);
	}

	__asm
	{
		JMP Offset2
	}
}

void __declspec(naked) cMessage::Color3()
{
	static DWORD Offset3 = 0x40D904;
	static DWORD Color = 0;

	__asm
	{
		MOV Color, EAX;
	}

	*(DWORD*)0x554C9C = 0xFF000000;
	*(DWORD*)0x554CA4 = 0x9632C8FF;

	if (Color == 0)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0x9632C8FF;
	}

	if (Color == 1)
	{
		*(DWORD*)0x554C9C = 0xFFFF9664;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 2)
	{
		*(DWORD*)0x554C9C = 0xFF001EFF;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 3)
	{
		*(DWORD*)0x554C9C = 0xFFC8DCE6;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 4)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0x96FFC800;
	}

	if (Color == 5)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0xC896FF00;
	}

	if (Color == 6) // - White
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0xFFFFFFFF;
	}

	if (Color == 7) // - Prata
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(105, 114, 114, 200);
	}

	if (Color == 8) // - Gold
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(255, 166, 0, 200);
	}

	if (Color == 9) // - Diamant
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(0, 60, 255, 200);
	}

	__asm
	{
		JMP Offset3
	}
}

void __declspec(naked) cMessage::Color4()
{
	static DWORD Offset4 = 0x47E841;
	static DWORD Color = 0;

	__asm
	{
		MOV Color, ECX;
	}

	*(DWORD*)0x554C9C = 0xFF000000;
	*(DWORD*)0x554CA4 = 0x9632C8FF;

	if (Color == 0)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0x9632C8FF;
	}

	if (Color == 1)
	{
		*(DWORD*)0x554C9C = 0xFFFF9664;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 2)
	{
		*(DWORD*)0x554C9C = 0xFF001EFF;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 3)
	{
		*(DWORD*)0x554C9C = 0xFFC8DCE6;
		*(DWORD*)0x554CA4 = 0x96000000;
	}

	if (Color == 4)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0x96FFC800;
	}

	if (Color == 5)
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0xC896FF00;
	}

	if (Color == 6) // - White
	{
		*(DWORD*)0x554C9C = 0xFF000000;
		*(DWORD*)0x554CA4 = 0xFFFFFFFF;
	}

	if (Color == 7) // - Prata
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(105, 114, 114, 200);
	}

	if (Color == 8) // - Gold
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(255, 166, 0, 200);
	}

	if (Color == 9) // - Diamant
	{
		*(DWORD*)0x554C9C = 0xFFFFFFFF;
		*(DWORD*)0x554CA4 = RGBA(0, 60, 255, 200);
	}

	__asm
	{
		JMP Offset4
	}
}

void __declspec(naked) cMessage::Color5()
{
	static DWORD Offset1 = 0x47E6E0;
	static DWORD Offset2 = 0x47E421;

	__asm
	{
		CMP EBP, 5
		JE JMP_SUCCESS
		CMP EBP, 6
		JE JMP_SUCCESS
		JMP Offset2
		JMP_SUCCESS :
		JMP Offset1
	}
}

cMessage Message;