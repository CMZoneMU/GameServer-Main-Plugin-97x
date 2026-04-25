#include "StdAfx.h"

CManager Manager = CManager();

CManager::CManager(void)
{
}

CManager::~CManager(void)
{
}

bool CManager::Initialize()
{
	if (!this->InitDatabase())
	{
		return false;
	}

	return true;
}

bool CManager::InitDatabase()
{
	bool Return = false;

	Manager.Load();

	if (this->Connect(this->Host, this->Database, this->User, this->Senha) == true)
	{
		Return = true;
	}
	else
	{
		MessageBox(NULL, "Conexão com SQL Server falhou!\n Por favor verifique o arquivo 'Settings.txt", "Fire Plugin", MB_OK | MB_ICONERROR);
		ExitProcess(0);

		this->DiagnosticConn();
	}

	return Return;
}

bool CManager::Load()
{
	GetPrivateProfileString("MSSQL", "Usuário do sql server", "sa", this->User, sizeof(this->User), "./Data/Settings.txt");
	GetPrivateProfileString("MSSQL", "Senha do sql server", "123456", this->Senha, sizeof(this->Senha), "./Data/Settings.txt");
	GetPrivateProfileString("MSSQL", "Banco de dados do servidor", "MuOnline", this->Database, sizeof(this->Database), "./Data/Settings.txt");
	GetPrivateProfileString("MSSQL", "Host do sql server", "127.0.0.1", this->Host, sizeof(this->Host), "./Data/Settings.txt");

	return true;
}

void CManager::OnError(const char * Message, ...)
{
	Log((char*)Message);
}

void CManager::OnMessage(const char * Message, ...)
{
	Log((char*)Message);
}

void CManager::OnQuery(const char * Message, ...)
{
	Log((char*)Message);
}

int CManager::VipCount(char* Account)
{
	this->ExecFormat(
		"SELECT CASE " "WHEN AccountExpireDate IS NULL OR AccountExpireDate <= GETDATE() THEN 0 " "ELSE AccountLevel " "END AS VipLevel " "FROM MEMB_INFO WHERE memb___id = '%s'",Account);

	this->Fetch();

	int Vip = this->GetInt("VipLevel");

	this->Clear();

	if (Vip == 0)
	{
		this->ExecFormat("UPDATE MEMB_INFO SET AccountLevel = 0 WHERE memb___id = '%s' AND AccountLevel > 0",Account);
	}

	return Vip;
}

int CManager::VipDays(char* Account)
{
	this->ExecFormat("SELECT ISNULL(DATEDIFF(DAY, GETDATE(), AccountExpireDate), 0) AS VipDays " "FROM MEMB_INFO WHERE memb___id = '%s'", Account);

	this->Fetch();

	int Days = this->GetInt("VipDays");

	this->Clear();

	return (Days < 0 ? 0 : Days);
}


int CManager::CountResets(char* Character)
{
	this->ExecFormat("SELECT Resets FROM Character WHERE Name = '%s'", Character);

	this->Fetch();

	int Reset = this->GetInt("Resets");

	this->Clear();

	return Reset;
}

int CManager::CountDay(char* Character)
{
	this->ExecFormat("SELECT ResetsDay FROM Character WHERE Name = '%s'", Character);

	this->Fetch();

	int Day = this->GetInt("ResetsDay");

	this->Clear();

	return Day;
}

int CManager::CountMasters(char* Character)
{
	this->ExecFormat("SELECT MResets FROM Character WHERE Name = '%s'", Character);

	this->Fetch();

	int Master = this->GetInt("MResets");

	this->Clear();

	return Master;
}

int CManager::MasterPoint(char* Character)
{
	this->ExecFormat("SELECT MasterPoint FROM Character WHERE Name = '%s'", Character);

	this->Fetch();

	int Master = this->GetInt("MasterPoint");

	this->Clear();

	return Master;
}

int CManager::Contador(int aIndex, char* Character)
{
	bool Select = this->ExecFormat("SELECT Sword01, Sword02, Sword03, Sword04, Sword05, Sword06, Sword07, Sword08, Sword09, Sword10, Sword11, Sword12 FROM Character WHERE Name = '%s'", Character);

	this->Fetch();

	Custom[aIndex].Count[0] = this->GetInt("Sword01");
	Custom[aIndex].Count[1] = this->GetInt("Sword02");
	Custom[aIndex].Count[2] = this->GetInt("Sword03");
	Custom[aIndex].Count[3] = this->GetInt("Sword04");
	Custom[aIndex].Count[4] = this->GetInt("Sword05");
	Custom[aIndex].Count[5] = this->GetInt("Sword06");
	Custom[aIndex].Count[6] = this->GetInt("Sword07");
	Custom[aIndex].Count[7] = this->GetInt("Sword08");
	Custom[aIndex].Count[8] = this->GetInt("Sword09");
	Custom[aIndex].Count[9] = this->GetInt("Sword10");
	Custom[aIndex].Count[10] = this->GetInt("Sword11");
	Custom[aIndex].Count[11] = this->GetInt("Sword12");

	this->Clear();

	return Select;
}

bool CManager::Patent(int aIndex, char* Character)
{
	bool Select = this->ExecFormat("SELECT PointEvent, ReiEvent FROM Character WHERE Name = '%s'", Character);

	this->Fetch();

	Custom[aIndex].Patent = this->GetInt("PointEvent");
	Custom[aIndex].Rei = this->GetInt("ReiEvent");

	this->Clear();

	return Select;
}

bool CManager::CheckVault(int aIndex, char* Account)
{
	bool Select = this->ExecFormat("SELECT VaultID, Count FROM warehouse WHERE AccountID = '%s'", Account);

	this->Fetch();

	Custom[aIndex].Vault[0] = this->GetInt("VaultID");
	Custom[aIndex].Vault[1] = this->GetInt("Count");

	this->Clear();

	return Select;
}

bool CManager::JewelsCount(int aIndex, char* Account)
{
	bool Select = this->ExecFormat("SELECT Bless, Soul, Life, Chaos, Creation, Luck, Skill, JLevel, JOption FROM MEMB_INFO WHERE memb___id = '%s'", Account);

	this->Fetch();

	Custom[aIndex].Jewels[Bank.Bless] = this->GetInt("Bless");
	Custom[aIndex].Jewels[Bank.Soul] = this->GetInt("Soul");
	Custom[aIndex].Jewels[Bank.Life] = this->GetInt("Life");
	Custom[aIndex].Jewels[Bank.Chaos] = this->GetInt("Chaos");
	Custom[aIndex].Jewels[Bank.Creation] = this->GetInt("Creation");
	Custom[aIndex].Jewels[Bank.Luck] = this->GetInt("Luck");
	Custom[aIndex].Jewels[Bank.Skill] = this->GetInt("Skill");
	Custom[aIndex].Jewels[Bank.Level] = this->GetInt("JLevel");
	Custom[aIndex].Jewels[Bank.Option] = this->GetInt("JOption");

	this->Clear();

	return Select;
}

bool CManager::CheckBonus(int aIndex, char* Account)
{
	bool Select = this->ExecFormat("SELECT Bonus, Day FROM MEMB_INFO WHERE memb___id = '%s'", Account);

	this->Fetch();

	Custom[aIndex].Bonus = this->GetInt("Bonus");
	Custom[aIndex].Day = this->GetInt("Day");

	this->Clear();

	return Select;
}

bool CManager::CoinCount(int aIndex, char* Account)
{
	bool Select = this->ExecFormat("SELECT %s, %s, %s, EventPoint, %s, Cash FROM MEMB_INFO WHERE memb___id = '%s'", Roleta._Name, Duel._Column, Buy._Column[0], Buy._Column[1], Account);

	this->Fetch();

	Custom[aIndex].Coin[0] = this->GetInt(Roleta._Name);
	Custom[aIndex].Coin[1] = this->GetInt(Duel._Column);
	Custom[aIndex].Coin[2] = this->GetInt(Buy._Column[0]);
	Custom[aIndex].Coin[3] = this->GetInt("EventPoint");
	Custom[aIndex].Coin[4] = this->GetInt(Buy._Column[1]);
	Custom[aIndex].Coin[5] = this->GetInt("Cash");

	this->Clear();

	return Select;
}

bool CManager::QuestCount(int aIndex, char* Account)
{
	bool Select = this->ExecFormat("SELECT Number, Start, Kills FROM MEMB_INFO WHERE memb___id = '%s'", Account);

	this->Fetch();

	Quest.PlayerStruct[aIndex]._Index = this->GetInt("Number");
	Quest.PlayerStruct[aIndex]._Start = this->GetInt("Start");
	Quest.PlayerStruct[aIndex]._Kills = this->GetInt("Kills");

	this->Clear();

	return Select;
}

bool CManager::CheckNick(int aIndex, const char* Character)
{
	snprintf(this->Buffer, sizeof(this->Buffer), "SELECT COUNT(*) FROM Character WHERE Name = '%s'", Character);

	if (this->Exec(this->Buffer))
	{
		this->Fetch();

		int Count = this->GetInt(0);

		if (Count > 0)
		{
			this->Clear();
			return true;
		}
	}

	return false;
}

bool CManager::CheckBlock(int aIndex, char* Account)
{
	bool Select = this->ExecFormat("SELECT Block, Password FROM MEMB_INFO WHERE memb___id = '%s'", Account);

	this->Fetch();

	Block.BlockStruct[aIndex]._Active = this->GetInt("Block");

	this->GetStr("Password", Block.BlockStruct[aIndex]._Password);

	this->Clear();

	return Select;
}