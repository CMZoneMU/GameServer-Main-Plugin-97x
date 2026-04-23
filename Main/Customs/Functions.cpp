#include "StdAfx.h"

void Hook(BYTE Head, DWORD Offset, ...)
{
	if (Head != 0xFF)
	{
		*(BYTE*)(Offset) = Head;
	}

	DWORD* Function = &Offset + 1;
	*(DWORD*)(Offset + 1) = (*Function) - (Offset + 5);
}

void HookJump(DWORD Offset, LPVOID Function)
{
	*(BYTE*)(Offset) = 0xE9;
	*(DWORD*)(Offset + 1) = (DWORD)Function - (Offset + 5);
}

void HookCall(DWORD Offset, LPVOID Function)
{
	*(BYTE*)(Offset) = 0xE8;
	*(DWORD*)(Offset + 1) = (DWORD)Function - (Offset + 5);
}

void HookJnz(BYTE Type1, BYTE Type2, DWORD Offset, LPVOID Function)
{
	*(BYTE*)(Offset) = Type1;
	*(BYTE*)(Offset + 1) = Type2;
	*(DWORD*)(Offset + 2) = (DWORD)Function - (Offset + 6);
}

void SetNop(DWORD Offset, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		*(BYTE*)(Offset + i) = 0x90;
	}
}

void SetFloat(DWORD offset, float value)
{
	*(float*)(offset) = value;
}

int Registry(const char* Section)
{
	HKEY Key;

	int Value = 0;

	DWORD Size = sizeof(int);

	if (RegOpenKey(HKEY_CURRENT_USER, "Software\\Webzen\\MU\\Config", &Key) == 0)
	{
		if (RegQueryValueEx(Key, Section, nullptr, nullptr, (LPBYTE)(&Value), &Size) == 0)
		{
			return Value;
		}

		RegCloseKey(Key);
	}

	return 0;
}


// [ Novo ]: Functions Hook na Memoria

void SetCompleteHook(BYTE head, DWORD offset, ...)
{
	DWORD OldProtect;

	VirtualProtect((void*)offset, 5, PAGE_EXECUTE_READWRITE, &OldProtect);

	if (head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset + 1;

	*(DWORD*)(offset + 1) = (*function) - (offset + 5);

	VirtualProtect((void*)offset, 5, OldProtect, &OldProtect);
}

void SetByte(DWORD offset, BYTE value)
{
	DWORD OldProtect;

	VirtualProtect((void*)offset, 1, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(BYTE*)(offset) = value;

	VirtualProtect((void*)offset, 1, OldProtect, &OldProtect);
}

char* ConvertModuleFileName(char* name)
{
	static char buff[MAX_PATH] = { 0 };

	for (int n = strlen(name); n > 0; n--)
	{
		if (name[n] == '\\')
		{
			strcpy_s(buff, sizeof(buff), &name[(n + 1)]);

			break;
		}
	}

	return buff;
}

void MemoryCpy(DWORD offset, void* value, DWORD size)
{
	DWORD OldProtect;

	VirtualProtect((void*)offset, size, PAGE_EXECUTE_READWRITE, &OldProtect);

	memcpy((void*)offset, value, size);

	VirtualProtect((void*)offset, size, OldProtect, &OldProtect);
}

void SetWord(DWORD offset, WORD value)
{
	DWORD OldProtect;

	VirtualProtect((void*)offset, 2, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(WORD*)(offset) = value;

	VirtualProtect((void*)offset, 2, OldProtect, &OldProtect);
}

void SetDword(DWORD offset, DWORD value)
{
	DWORD OldProtect;

	VirtualProtect((void*)offset, 4, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(DWORD*)(offset) = value;

	VirtualProtect((void*)offset, 4, OldProtect, &OldProtect);
}