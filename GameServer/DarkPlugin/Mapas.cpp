#include "StdAfx.h"

bool cMaps::Load()
{
	memset((DWORD*)0x0048A6B6, 0x90, 10);
	memset((DWORD*)0x0048A6B6, 0xE8, 1);

	*(DWORD*)(0x0048A6B6 + 1) = (DWORD)&cMaps::LoadAtt - (0x48A6B6 + 5);

	if (!cMaps::LoadLimit())
	{
		return false;
	}

	return true;
}

pMapItemInit	MapItemInit = (pMapItemInit)0x402225;
pLoadMapAttr	LoadMapAttr = (pLoadMapAttr)0x401FC3;
pGetNewPath		GetNewPath = (pGetNewPath)0x401A7D;

bool cMaps::LoadLimit()
{
	memset((BYTE*)0x489424, 25, 1);	
	memset((BYTE*)0x48948F, 25, 1);
	memset((BYTE*)0x47C7D4, 25, 1);
	memset((BYTE*)0x47C7FE, 25, 1);
	memset((BYTE*)0x47334E, 25, 1);
	memset((BYTE*)0x47C499, 25, 1);
	memset((BYTE*)0x4122FC, 25, 1);
	memset((BYTE*)0x443782, 24, 1);
	memset((BYTE*)0x45C620, 24, 1);
	memset((BYTE*)0x45BA63, 24, 1);
	memset((BYTE*)0x406B47, 24, 1);
	memset((BYTE*)0x463FF1, 24, 1);
	memset((BYTE*)0x4188DD, 24, 1);
	memset((BYTE*)0x497B30, 24, 1);	
	memset((BYTE*)0x497C00, 24, 1);

	return true;
}

bool cMaps::LoadAtt()
{
	if (Setting._Mapas == 1)
	{
		cMaps::LoadMapAtt(17, "Terrain18.att");
		cMaps::LoadMapAtt(18, "Terrain19.att");
		cMaps::LoadMapAtt(19, "Terrain20.att");
		cMaps::LoadMapAtt(20, "Terrain21.att");
		cMaps::LoadMapAtt(21, "Terrain22.att");
		cMaps::LoadMapAtt(22, "Terrain23.att");
		cMaps::LoadMapAtt(23, "Terrain24.att");
		cMaps::LoadMapAtt(24, "Terrain25.att");
	}

	_asm
	{
		MOV ECX, 06342BC0h;
		MOV EDI, 00401145h;
		CALL EDI;
	}

	return true;
}

void cMaps::LoadMapAtt(unsigned int index, const char *name)
{
	unsigned int thismap = (index * 0x4DB68) + 0x6354C78;

	__asm
	{
		XOR ECX, ECX;
		MOV ECX, thismap;
		CALL MapItemInit;

		PUSH index;
		PUSH name;
		XOR ECX, ECX;
		MOV ECX, 0687DE60h;
		CALL GetNewPath;

		PUSH EAX;
		MOV ECX, thismap;
		CALL LoadMapAttr;
	}
}

cMaps Maps;