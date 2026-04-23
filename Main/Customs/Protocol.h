#pragma once

class cProtocol
{
public:
	static void ProtocolCore(LPBYTE aRecv);
	void Message(CHAT_WHISPER* lpMsg);
	void GCLiveClient(PMSG_LIVE_CLIENT* lpMsg);
	void Agility();
	void MainCheck();

	// novo
	void GCCharacterInfo(PMSG_CUSTOM_CHARACTER_INFO_RECV* lpMsg);

public:
	bool Update;
	WORD Level;
	WORD LevelUpPoint;
	WORD Class;
	DWORD Experience;
	DWORD NextExperience;
	DWORD Tick;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	WORD BP;
	WORD MaxBP;
	WORD AttackSpeed;
	WORD MagicSpeed;
	int Cash;        // novo
	int Reset;       // novo
    int EventPoint;   // novo
	int AccountLevel; // novo
	int AccountExpireDays; // novo
	int OnlineCount; // novo
	int RealLevelUpPoint;
	int Sword[13];
	float Count;
	char Buffer[11];
    
};

extern cProtocol Protocol;