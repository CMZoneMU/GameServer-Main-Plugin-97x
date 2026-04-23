#pragma once

void Hook(BYTE Head, DWORD Offset, ...);
void HookJump(DWORD Offset, LPVOID Function);
void HookCall(DWORD Offset, LPVOID Function);
void HookJnz(BYTE Type1, BYTE Type2, DWORD Offset, LPVOID Function);
void SetNop(DWORD Offset, int Size);
void SetFloat(DWORD offset, float value);
int Registry(const char* Section);

// [ Novo ]: Functions Hook na Memoria 
void SetDword(DWORD offset, DWORD value);
void SetByte(DWORD offset, BYTE value);
void SetCompleteHook(BYTE head, DWORD offset, ...);
char* ConvertModuleFileName(char* name);
void MemoryCpy(DWORD offset, void* value, DWORD size);
void SetWord(DWORD offset, WORD value);
