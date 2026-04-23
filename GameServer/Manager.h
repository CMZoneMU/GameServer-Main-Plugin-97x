#pragma once

class CManager : public CDataBase
{
public:
	CManager(void);
	~CManager(void);

public:
	bool Initialize();
	bool InitDatabase();
	bool Load();
	void OnMessage(const char * Message, ...);
	void OnError(const char * Message, ...);
	void OnQuery(const char * Message, ...);
	int CountResets(char * Character);
	int CountDay(char* Character);
	int CountMasters(char * Character);
	int MasterPoint(char* Character);
	int Contador(int aIndex, char* Character);
	bool Patent(int aIndex, char* Character);
	bool CheckVault(int aIndex, char* Account);
	bool JewelsCount(int aIndex, char* Account);
	bool CheckBonus(int aIndex, char* Account);
	bool CoinCount(int aIndex, char* Account);
	bool QuestCount(int aIndex, char* Character);
	bool CheckNick(int aIndex, const char* Character);
	bool CheckBlock(int aIndex, char* Account);

	int VipCount(char* Account);
	int VipDays(char* Account);

private:
	char Host[50];
	char Database[50];
	char User[50];
	char Senha[50];
	char Buffer[255];
};

extern CManager Manager;