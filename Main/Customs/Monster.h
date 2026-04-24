#pragma once

#define NPC_DIRECTORY		0x5579D4, 0x55799C
#define MONSTER_DIRECTORY	0x558D70, 0x558D64

struct ZMonsterAttribute
{
	bool IsNPC;
	DWORD ModelId;
	std::string Filename;
	DWORD Directory1;
	DWORD Directory2;
	float Scale;
};

class ZMonster
{
public:
	ZMonster();
	~ZMonster();

public:
	void Load();
	void Insert(BYTE MonsterId, bool IsNPC, DWORD ModelId, std::string Filename, DWORD Directory1, DWORD Directory2, float Scale = 1.0f);
	bool Exist(BYTE MonsterId);
	bool IsNPC(BYTE MonsterId);
	DWORD GetModel(BYTE MonsterId);
	float GetScale(BYTE MonsterId); // [ Novo ]: Escala para monstros
	ZMonsterAttribute* GetAttribute(DWORD ModelId);

private:
	std::map<BYTE, ZMonsterAttribute> Monster;
};

extern ZMonster Monster;