#pragma once

struct sParty
{
public:
	sParty() :
		_Active(false)
	{
	}

	bool                _Active;
};

class cParty
{
public:
	bool Load();
	void Command(int aIndex, char* msg);
	void Quit(LPOBJ lpObj);
	int Create(int usernumber, int dbnumber, int level);
	void Paint(int party_number);
	int Add(int party_number, int usernumber, int dbnumber, int level);
	bool Accept(int Number, int aIndex);
	void GCResultSend(int aIndex, BYTE headcode, BYTE result);
	static void CGPartyRequestRecvEx(PMSG_PARTYREQUEST * lpMsg, int aIndex);

public:
	bool                _Active;
	int                 _VipCount;
	char                _Name[255];
	char                _Syntax[25];

public:
	sParty			    PlayerStruct[OBJECT_MAX];
};

extern cParty Party;