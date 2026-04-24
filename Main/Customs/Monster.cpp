#include "StdAfx.h"
#include "NakedMonster.h"

ZMonster Monster;

ZMonster::ZMonster()
{
}

ZMonster::~ZMonster()
{
}

void ZMonster::Load()
{
	// - Hooks
	// Hook CreateCharacter (0x45AA90)
	*(BYTE*)(0x45AA90) = 0xE9;
	*(DWORD*)(0x45AA91) = (DWORD)(&CreateCharacter_Hook) - 0x45AA95; // [ Novo ]: Redireciona para a função de hook
	*(BYTE*)(0x45AA95) = 0x90;



	*(BYTE*)(0x45E02C) = 0xE9;
	*(DWORD*)(0x45E02D) = (DWORD)(&SetMonster) - 0x45E031;
	*(BYTE*)(0x45E031) = 0x90;

	*(BYTE*)(0x504078) = 0xE9;
	*(DWORD*)(0x504079) = (DWORD)(&LoadBmd) - 0x50407D;
	*(BYTE*)(0x50407D) = 0x90;
	*(BYTE*)(0x50407E) = 0x90;
	*(BYTE*)(0x50407F) = 0x90;
	*(BYTE*)(0x504080) = 0x90;
	*(BYTE*)(0x504081) = 0x90;
	*(BYTE*)(0x45B7D8) = 0xE9;

	*(DWORD*)(0x45B7D9) = (DWORD)(&LoadModel) - 0x45B7DD;
	*(BYTE*)(0x45B7DD) = 0x90;
	*(BYTE*)(0x45B7DE) = 0x90;
	*(BYTE*)(0x45B7DF) = 0x90;
	*(BYTE*)(0x45B7E0) = 0x90;
	*(BYTE*)(0x45B7E1) = 0x90;
	*(BYTE*)(0x45B7E2) = 0x90;
	*(BYTE*)(0x45B7E3) = 0x90;
	*(BYTE*)(0x45B7E4) = 0x90;
	*(BYTE*)(0x45B7E5) = 0x90;
	*(BYTE*)(0x45B7E6) = 0x90;
	*(BYTE*)(0x45B7E7) = 0x90;
	*(BYTE*)(0x45B7E8) = 0x90;

	*(BYTE*)(0x504066) = 0xE9;
	*(DWORD*)(0x504067) = (DWORD)(&ReloadModel) - 0x50406B;

	// First ID - NPC starts in 201
	*(BYTE*)(0x48D276) = 201;

	// New NPC / Mobs:
	// { MonsterId | { IsNPC? | ModelId | Filename | Directory | Scale } }

	this->Insert(201, true, 1001, "Jack", NPC_DIRECTORY, 1.0f);
	this->Insert(202, true, 1002, "Murphy", NPC_DIRECTORY, 1.0f);
	this->Insert(168, false, 1003, "Medusa", MONSTER_DIRECTORY, 1.0f);
	this->Insert(169, false, 1004, "Illusion", MONSTER_DIRECTORY, 1.0f);
	this->Insert(170, false, 1005, "Santa", MONSTER_DIRECTORY, 1.0f);
	this->Insert(171, false, 1006, "Globin", MONSTER_DIRECTORY, 1.0f);
	this->Insert(172, false, 1007, "Knight", MONSTER_DIRECTORY, 1.0f);
	this->Insert(173, false, 1008, "Wizard", MONSTER_DIRECTORY, 1.0f);
	this->Insert(174, false, 1009, "Elf", MONSTER_DIRECTORY, 1.0f);
	this->Insert(175, false, 1010, "gaionkharein", MONSTER_DIRECTORY, 1.0f);
	this->Insert(176, false, 1011, "Rabbit1", MONSTER_DIRECTORY, 1.0f);
	this->Insert(177, false, 1012, "Rabbit2", MONSTER_DIRECTORY, 1.50f);

	// Kalima
	this->Insert(178, false, 1013, "Aegis", MONSTER_DIRECTORY, 1.50f);
	this->Insert(179, false, 1014, "ArcherWolf", MONSTER_DIRECTORY, 1.50f);
	this->Insert(188, false, 1015, "DareDevil", MONSTER_DIRECTORY, 2.50f);

	this->Insert(203, true, 1027, "Devin", NPC_DIRECTORY, 1.0f);
	this->Insert(204, true, 1028, "Blue", NPC_DIRECTORY, 1.0f);
	this->Insert(205, true, 1029, "Red", NPC_DIRECTORY, 1.0f);
	this->Insert(206, true, 1030, "Cherry", NPC_DIRECTORY, 1.0f);
	this->Insert(208, true, 1031, "Coletor", NPC_DIRECTORY, 1.0f);
}

void ZMonster::Insert(BYTE MonsterId, bool IsNPC, DWORD ModelId, std::string Filename, DWORD Directory1, DWORD Directory2, float Scale)
{
	ZMonsterAttribute Attribute;
	Attribute.IsNPC = IsNPC;
	Attribute.ModelId = ModelId;
	Attribute.Filename = Filename;
	Attribute.Directory1 = Directory1;
	Attribute.Directory2 = Directory2;
	Attribute.Scale = Scale; // [ Novo ]: Escala para monstros
	this->Monster.insert(std::pair<BYTE, ZMonsterAttribute>(MonsterId, Attribute));
}

bool ZMonster::Exist(BYTE MonsterId)
{
	if (this->Monster.count(MonsterId) <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool ZMonster::IsNPC(BYTE MonsterId)
{
	return this->Monster[MonsterId].IsNPC;
}

DWORD ZMonster::GetModel(BYTE MonsterId)
{
	return this->Monster[MonsterId].ModelId;
}

//  [ Novo ]: Escalas para monstros
float ZMonster::GetScale(BYTE MonsterId)
{
	if (this->Monster.count(MonsterId) <= 0)
	{
		return 1.0f;
	}

	return this->Monster[MonsterId].Scale;
}

ZMonsterAttribute* ZMonster::GetAttribute(DWORD ModelId)
{
	for (auto it = this->Monster.begin(); it != this->Monster.end(); ++it)
	{
		if (it->second.ModelId == ModelId)
		{
			return &it->second;
		}
	}

	return nullptr;
}