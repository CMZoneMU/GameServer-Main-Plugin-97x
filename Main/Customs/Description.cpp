#include "StdAfx.h"

__declspec(naked) void cDescription::Load()
{
	static WORD TEXT;
	static WORD ITEM;
	static DWORD RETURN;

	_asm
	{
		MOV TEXT, AX
		MOV AX, WORD PTR SS : [EBP]
		MOV ITEM, AX
	}

	if (ITEM == ITEMGET(12, 15))
	{
		Text("É usado para combinar item chaos.", TextColor::White, 0);
	}
	else if (ITEM == ITEMGET(14, 27))
	{
		Text("Jogue-o e você pode receber itens.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(14, 28))
	{
		Text("Jogue-o e você pode receber itens.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(14, 29))
	{
		Text("Jogue-o e você pode receber itens.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(14, 30))
	{
		Text("Jogue-o e você pode receber itens.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(14, 31))
	{
		Text("Jogue-o e você pode receber itens.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(15, 16))
	{
		Text("É usado para adicionar 10 Golds.", TextColor::Blue, 0);

		Text(" ", NULL, 0);

		Text("Atenção!", TextColor::WhiteRed, 0);
		Text("Para consumir utilize o botão direito.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(15, 17))
	{
		Text("É usado para adicionar 640 Golds.", TextColor::Blue, 0);

		Text(" ", NULL, 0);

		Text("Atenção!", TextColor::WhiteRed, 0);
		Text("Para consumir utilize o botão direito.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(15, 18))
	{
		Text("Adiciona o Opcional Luck ao Item.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(15, 19))
	{
		Text("Adiciona o Atributo Skill ao Item.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(15, 20))
	{
		Text("Aumenta o level do item para +12, +13, +14 e +15", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(15, 22))
	{
		Text("Pena Especial!", TextColor::WhiteRed, 0);

		Text(" ", NULL, 0);

		Text("Transforma sua asa em uma asa nível 2.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(15, 23))
	{
		Text("Aumenta o Opcional Excelente do Item.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(0, 30))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[0]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(1, 12))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[1]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(1, 14))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[2]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(1, 23))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[3]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(1, 28))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[4]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(1, 31))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[5]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(2, 14))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[6]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(2, 16))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[7]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(2, 17))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[8]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(2, 24))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[9]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(2, 25))
	{
		sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[10]);
		Text(Description.Buffer, TextColor::WhiteRed, 0);
	}
	else if (ITEM == ITEMGET(2, 28))
	{
	    sprintf_s(Description.Buffer, "Contador de Mortes: %d", Protocol.Sword[11]);
	    Text(Description.Buffer, TextColor::WhiteRed, 0);
	}

	_asm
	{
		MOV AX, TEXT
		MOV RETURN, 0x4C1A72
		JMP RETURN
	}
}

void cDescription::Text(char * Text, int Color, int Weight, ...)
{
	char Buffer[1024] = { 0 };

	va_list Arguments;
	va_start(Arguments, Text);
	vsprintf(Buffer, Text, Arguments);
	va_end(Arguments);

	*(&*(DWORD*)0x8390A70 + *(DWORD*)0x83A947C) = Color;
	*(&*(DWORD*)0x83A6E78 + *(DWORD*)0x83A947C) = Weight;

	ItemText(100 * (*(DWORD*)0x83A947C) + 0x838FB00, Buffer);

	*(DWORD*)0x83A947C += 1;
}

cDescription Description;