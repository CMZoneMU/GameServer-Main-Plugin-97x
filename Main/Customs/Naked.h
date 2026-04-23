#pragma once

LPBYTE nProtocolCoreData = nullptr;

void __declspec(naked) nProtocolCore()
{
	static DWORD nProtocolCoreBack = 0x4384FB;

	__asm MOV nProtocolCoreData, EBP;

	cProtocol::ProtocolCore(nProtocolCoreData);

	__asm MOV EDX, DWORD PTR DS : [0x8311134];
	__asm JMP nProtocolCoreBack;
}

char* nItsFree    = "Gratuito!";
char* nItsFree2   = "%s";
char* nIsntFree   = (char*)(0x822D934);

void __declspec(naked) nPriceBuyRecv()
{
	static DWORD nPriceBuyRecvBack = 0x4C0476;

	__asm PUSHAD;
    
	if (Treasure)
    {
        __asm
        {
			POPAD;
            PUSH nItsFree;
            PUSH nItsFree2;
			JMP nPriceBuyRecvBack;
        }
    }
	
	__asm
    {
		POPAD;
		PUSH EAX;
		PUSH nIsntFree;
		JMP nPriceBuyRecvBack;
    }
}

void __declspec(naked) UpdateCharacterNoEffect()
{
	static DWORD UpdateCharacterNoEffectBack = 0x430B57;

	__asm PUSHAD;

	if (Protocol.Update == true)
	{
		__asm
		{
			POPAD;

			MOV EAX, DWORD PTR DS:[0x81F135C];

			MOV CX, Protocol.Strength;
			MOV WORD PTR DS:[EAX+0x14], CX;

			MOV CX, Protocol.Dexterity;
			MOV WORD PTR DS:[EAX+0x16], CX;

			MOV CX, Protocol.Vitality;
			MOV WORD PTR DS:[EAX+0x18], CX;

			MOV CX, Protocol.Energy;
			MOV WORD PTR DS:[EAX+0x1A], CX;

			MOV CX, Protocol.Life;
			MOV WORD PTR DS:[EAX+0x1C], CX;

			MOV CX, Protocol.MaxLife;
			MOV WORD PTR DS:[EAX+0x20], CX;

			MOV CX, Protocol.Mana;
			MOV WORD PTR DS:[EAX+0x1E], CX;

			MOV CX, Protocol.MaxMana;
			MOV WORD PTR DS:[EAX+0x22], CX;

			MOV CX, Protocol.BP;
			MOV WORD PTR DS:[EAX+0x24], CX;

			MOV CX, Protocol.MaxBP;
			MOV WORD PTR DS:[EAX+0x26], CX;

			MOV WORD PTR DS:[EAX+0x2E], 0;		// StatPoint
			MOV WORD PTR DS:[EAX+0x30], 0;		// MaxStatPoint

			MOV CX, Protocol.LevelUpPoint;
			MOV WORD PTR DS:[EAX+0x54], CX;

			JMP UpdateCharacterNoEffectBack;
		}
	}

	__asm
	{
		POPAD;
		MOV EAX, DWORD PTR DS:[0x81F135C];
		JMP UpdateCharacterNoEffectBack;
	}
} 

void __declspec(naked) UpdateCharacterEffect()
{
	static DWORD UpdateCharacterEffectBack[2] = { 0x430942, 0x430902 };

	__asm PUSHAD;

	if (Protocol.Update == true)
	{
		__asm
		{
			POPAD;

			MOV EAX, DWORD PTR DS:[0x81F135C];

			MOV CX, Protocol.Level;
			MOV WORD PTR DS:[EAX+0x0E], CX; 

			MOV ECX, Protocol.Experience;
			MOV DWORD PTR DS:[EAX+0x10], ECX;

			MOV ECX, Protocol.NextExperience;
			MOV DWORD PTR DS:[EAX+0x34], ECX;

			MOV CX, Protocol.Strength;
			MOV WORD PTR DS:[EAX+0x14], CX;

			MOV CX, Protocol.Dexterity;
			MOV WORD PTR DS:[EAX+0x16], CX;

			MOV CX, Protocol.Vitality;
			MOV WORD PTR DS:[EAX+0x18], CX;

			MOV CX, Protocol.Energy;
			MOV WORD PTR DS:[EAX+0x1A], CX;

			MOV CX, Protocol.Life;
			MOV WORD PTR DS:[EAX+0x1C], CX;

			MOV CX, Protocol.MaxLife;
			MOV WORD PTR DS:[EAX+0x20], CX;

			MOV CX, Protocol.Mana;
			MOV WORD PTR DS:[EAX+0x1E], CX;

			MOV CX, Protocol.MaxMana;
			MOV WORD PTR DS:[EAX+0x22], CX;

			MOV CX, Protocol.BP;
			MOV WORD PTR DS:[EAX+0x24], CX;

			MOV CX, Protocol.MaxBP;
			MOV WORD PTR DS:[EAX+0x26], CX;

			MOV WORD PTR DS:[EAX+0x2E], 0;		// StatPoint
			MOV WORD PTR DS:[EAX+0x30], 0;		// MaxStatPoint

			MOV CX, Protocol.LevelUpPoint;
			MOV WORD PTR DS:[EAX+0x54], CX;

			JMP UpdateCharacterEffectBack[0];   
		}
	}

	__asm
	{		
		POPAD;
		MOV EAX, DWORD PTR DS:[0x81F135C];
		JMP UpdateCharacterEffectBack[4];
	}
}

__declspec(naked) void LevelUpPoints()
{
	static DWORD Local = 0x4EA83A;

	__asm
	{
		MOV ECX, Protocol.RealLevelUpPoint;
		PUSH ECX;
		JMP Local;
	}
}

__declspec(naked) void Archangel()
{
	static DWORD Return1 = 0x472A5B;
	static DWORD Return2 = 0x4728BE;

	__asm
	{
		CMP EAX, 0x0A;
		JE JMP_ABSO;

		CMP EAX, 0;
		JE JMP_CROSSBOW;
		CMP EAX, 1;
		JE JMP_GREAT;
		CMP EAX, 2;
		JE JMP_ARQUEBUS;
		CMP EAX, 3;
		JE JMP_LIGHT;
		CMP EAX, 5;
		JE JMP_LEGEND;
		CMP EAX, 4;
		JE JMP_SERPENT;
		CMP EAX, 6;
		JE JMP_GOLD;

		CMP EAX, 18;
		JL JMP_TRUE;
		CMP EAX, 24;
		JG JMP_TRUE;

	JMP_TRUE:
		JMP Return1;

	JMP_ABSO:
		MOV EAX, 8;
		JMP Return2;

	JMP_CROSSBOW:
		MOV EAX, 1;
		JMP Return2;

	JMP_GREAT:
		MOV EAX, 1;
		JMP Return2;

	JMP_ARQUEBUS:
		MOV EAX, 2;
		JMP Return2;

	JMP_LIGHT:
		MOV EAX, 3;
		JMP Return2;

	JMP_LEGEND:
		MOV EAX, 5;
		JMP Return2;

	JMP_SERPENT:
		MOV EAX, 4;
		JMP Return2;

	JMP_GOLD:
		MOV EAX, 6;
		JMP Return2;
	}
}