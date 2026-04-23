#include "StdAfx.h"

__declspec(naked) void cTitle::Load()
{
	static DWORD Local[2] = { 0x4BFF29, 0x4BFF94 };

	__asm
	{
		CMP SI, ITEMGET(12, 15);
		MOV DWORD PTR DS : [0x83A947C], EAX;
		MOV DWORD PTR SS : [ESP + 0x24], EDI;

		MOV EDX, 0x3;
		JE Success;

		CMP SI, ITEMGET(14, 13);
		JE Success;

		CMP SI, ITEMGET(14, 14);
		JE Success;

		CMP SI, ITEMGET(14, 16);
		JE Success;

		CMP SI, ITEMGET(14, 22);
		JE Success;

		CMP SI, ITEMGET(14, 27);
		JE Success;

		CMP SI, ITEMGET(14, 28);
		JE Success;

		CMP SI, ITEMGET(14, 29);
		JE Success;

		CMP SI, ITEMGET(14, 30);
		JE Success;

		CMP SI, ITEMGET(14, 31);
		JE Success;

		CMP SI, ITEMGET(15, 16);
		JE Success;

		CMP SI, ITEMGET(15, 17);
		JE Success;

		CMP SI, ITEMGET(15, 18);
		JE Success;

		CMP SI, ITEMGET(15, 19);
		JE Success;

		CMP SI, ITEMGET(15, 20);
		JE Success;

		CMP SI, ITEMGET(15, 22);
		JE Success;

		CMP SI, ITEMGET(15, 23);
		JE Success;

		JMP Local[0];

	    Success:
	    JMP Local[4];
	}
}

cTitle Title;