#pragma once

static DWORD m_MonsterId = 0;
static DWORD m_ModelId = 0;
//							0		4		  8			12		  16		20		  24		28		  32		36
static DWORD m_Jump[] = { 0x45E03D, 0x45E032, 0x504082, 0x504579, 0x45B7E9, 0x45DE6E, 0x45DE8A, 0x5045B9, 0x504071, 0x50456A };
static DWORD m_Call[] = { 0x501080, 0x504040 };
static DWORD m_Directory1 = 0;
static DWORD m_Directory2 = 0;
static const char* m_Filename = nullptr;
static ZMonsterAttribute* m_Attribute = nullptr;

void __declspec(naked) SetMonster()
{
	__asm
	{
		MOV m_MonsterId, EBX;
		PUSHAD;
	}

	if (!Monster.Exist(m_MonsterId))
	{
	Exit:
		__asm
		{
			POPAD;
			CMP EBX, 0xC8;
			JMP m_Jump[4];
		}
	}
	else
	{
		if (Monster.IsNPC(m_MonsterId))
		{
			__asm
			{
				POPAD;
				JMP m_Jump[0];
			}
		}
		else
		{
			goto Exit;
		}
	}
}

void __declspec(naked) LoadBmd()
{
	__asm
	{
		MOV m_ModelId, ESI;
		PUSH EBP;
		PUSHAD;
	}

	m_Attribute = Monster.GetAttribute(m_ModelId);

	if (!m_Attribute)
	{
		__asm
		{
			POPAD;
			CMP EAX, 0x29;
			JA IsJA;
			JMP m_Jump[8];

		IsJA:
			JMP m_Jump[12];
		}
	}
	else
	{
		m_Filename = m_Attribute->Filename.c_str();
		m_Directory1 = m_Attribute->Directory1;
		m_Directory2 = m_Attribute->Directory2;

		
		__asm
		{
			POPAD;
			XOR EDX, EDX;
			PUSH -1;
			PUSH m_Filename;
			PUSH m_Directory1;
			PUSH ESI;
			CALL m_Call[0];
			PUSH 0x1;
			PUSH 0x2600;
			PUSH m_Directory2;
			PUSH ESI;
			JMP m_Jump[36];
		}
	}
}

void __declspec(naked) LoadModel()
{
	__asm
	{
		MOV m_MonsterId, EAX;
		PUSH EDI;
		MOV EBX, 0x2;
		PUSHAD;
	}

	if (!Monster.Exist(m_MonsterId + 1))
	{
		__asm
		{
			POPAD;
			CMP EAX, 0xFE;
			JA IsJA;
			JMP m_Jump[16];

		IsJA:
			JMP m_Jump[20];
		}
	}
	else
	{
		m_ModelId = Monster.GetModel(m_MonsterId + 1);

		__asm
		{
			POPAD;
			PUSH m_ModelId;
			CALL m_Call[4];
			MOV ECX, DWORD PTR SS : [ESP + 0x20];
			MOV EDX, DWORD PTR SS : [ESP + 0x1C];
			MOV EAX, DWORD PTR SS : [ESP + 0x24];
			PUSH 0;
			PUSH ECX;
			PUSH EDX;
			PUSH m_ModelId;
			JMP m_Jump[24];
		}
	}
}

void __declspec(naked) ReloadModel()
{
	__asm
	{
		MOV m_ModelId, ESI;
		PUSHAD;
	}

	if (Monster.GetAttribute(m_ModelId))
	{
		__asm
		{
			POPAD;
			MOV WORD PTR DS : [EDI + 0x26], 0x0;
			JMP IsModel;
		}
	}
	
	__asm
	{
		POPAD;
	IsModel:
		CMP WORD PTR DS : [EDI + 0x26], 0x0;
		JG IsJG;
		JMP m_Jump[32];

	IsJG:
		JMP m_Jump[28];
	}
}

