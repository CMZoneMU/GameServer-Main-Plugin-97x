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
	// { MonsterId | { IsNPC? | ModelId | Filename | Directory } }
	// { 201, { true, 1000, "NpcReset", "Data\\NPC\\" } } // example
	// O MonsterId é o ID do Monstro / NPC
	// O "IsNPC" é pra saber se é um NPC ou não, porque tem um jump naked pra identificar (como o gObjSetMonster faz no gs)
	// Filename é o arquivo.bmd no cliente, apenas o nome, não o diretorio, (ps: sem o bmd)
	// Directory é o directório onde está o arquivo, ex: Data\\NPC


	this->Insert(168, false, 1003, "Medusa", MONSTER_DIRECTORY);
	this->Insert(169, false, 1004, "Illusion", MONSTER_DIRECTORY);
	this->Insert(170, false, 1005, "Santa", MONSTER_DIRECTORY);
	this->Insert(171, false, 1006, "Globin", MONSTER_DIRECTORY);
	this->Insert(172, false, 1007, "Knight", MONSTER_DIRECTORY);
	this->Insert(173, false, 1008, "Wizard", MONSTER_DIRECTORY);
	this->Insert(174, false, 1009, "Elf", MONSTER_DIRECTORY);
	this->Insert(175, false, 1010, "Magic", MONSTER_DIRECTORY);
	this->Insert(176, false, 1011, "Rabbit1", MONSTER_DIRECTORY);
	this->Insert(177, false, 1012, "Rabbit2", MONSTER_DIRECTORY);

	this->Insert(162, false, 1013, "BlackDragon", MONSTER_DIRECTORY);
	this->Insert(163, false, 1014, "BrassWarrior", MONSTER_DIRECTORY);
	this->Insert(164, false, 1015, "GuardianElf", MONSTER_DIRECTORY);
	this->Insert(165, false, 1016, "RedDragon", MONSTER_DIRECTORY);
	this->Insert(166, false, 1017, "SoulMaster", MONSTER_DIRECTORY);
	this->Insert(195, false, 1018, "PlateWarrior", MONSTER_DIRECTORY);
	this->Insert(196, false, 1019, "SphinixWizard", MONSTER_DIRECTORY);
	this->Insert(197, false, 1032, "PhoenixKinight", MONSTER_DIRECTORY);

	// Novos Mosntros Kalima
	this->Insert(178, false, 1020, "Lobster", MONSTER_DIRECTORY);
	this->Insert(179, false, 1021, "Aegis", MONSTER_DIRECTORY);
	this->Insert(180, false, 1022, "Schriker", MONSTER_DIRECTORY);
	this->Insert(181, false, 1023, "Necron", MONSTER_DIRECTORY);
	this->Insert(182, false, 1024, "DeathCenturion", MONSTER_DIRECTORY);
	this->Insert(183, false, 1025, "DeathAngel", MONSTER_DIRECTORY);

	// Novos Monstros Land of Trials
	this->Insert(184, false, 1026, "Wolf", MONSTER_DIRECTORY);
	this->Insert(185, false, 1027, "PoisonGolem", MONSTER_DIRECTORY);
	this->Insert(186, false, 1028, "FireGolem", MONSTER_DIRECTORY);
	this->Insert(187, false, 1029, "PrincessTiara", MONSTER_DIRECTORY);


	// Novos Monstros Chaos Castle
	this->Insert(192, false, 1030, "ChaosCastleStaff", MONSTER_DIRECTORY);
	this->Insert(193, false, 1031, "ChaosCastleSword", MONSTER_DIRECTORY);

	//  NPC
	this->Insert(201, true, 1001, "Jack", NPC_DIRECTORY);
	this->Insert(202, true, 1002, "Murphy", NPC_DIRECTORY);
	this->Insert(203, true, 1038, "Devin", NPC_DIRECTORY);
	this->Insert(204, true, 1033, "Blue", NPC_DIRECTORY);
	this->Insert(205, true, 1034, "Red", NPC_DIRECTORY);
	this->Insert(206, true, 1035, "Cherry", NPC_DIRECTORY);
	this->Insert(208, true, 1036, "Zash", NPC_DIRECTORY);
}

void ZMonster::Insert(BYTE MonsterId, bool IsNPC, DWORD ModelId, std::string Filename, DWORD Directory1, DWORD Directory2)
{
	ZMonsterAttribute Attribute;
	Attribute.IsNPC = IsNPC;
	Attribute.ModelId = ModelId;
	Attribute.Filename = Filename;
	Attribute.Directory1 = Directory1;
	Attribute.Directory2 = Directory2;
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