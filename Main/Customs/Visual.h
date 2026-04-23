#pragma once

class VisualState
{
public:
	void Load();
	void Index(PMSG_JOINRESULT* Data);
	void RecvDamage(PMSG_ATTACKRESULT * Data);
	void RecvHP(PMSG_REFILL* Data);
	void RecvMP(PMSG_MANASEND* Data);
	void Respawn();
	void Killed(PMSG_DIEPLAYER* Data);
	static void DrawHP(float a1, float a2, int Value, float a4, float a5);
	static void DrawMP(float a1, float a2, int Value, float a4, float a5);
	static void DrawAG(float a1, float a2, int Value, float a4, float a5);
	static void DrawTabHP(int PosX, int PosY, LPCSTR lpString);
	static void DrawTabMP(int PosX, int PosY, LPCSTR lpString);
	static void DrawTabAG(int PosX, int PosY, LPCSTR lpString);
	static void InfoHp(int a1, int a2, LPCSTR a3, int a4, char a5, int a6);
	static void InfoMp(int a1, int a2, LPCSTR a3, int a4, char a5, int a6);

public:
	bool Kill;
	short aIndex;
	int Attack;
	int Life;
	int MaxLife;
	int Mana;
	int MaxMana;
	int Ag;
	int MaxAg;
	char Buffer[5][50];
};

extern VisualState Visual;