#pragma once

struct sRoom
{
	bool                 _Invitation;
	bool                 _Live;
	bool                 _Running;
	bool                 _Waiting;
	int                  _Index;
	int                  _Target;
	int                  _Time[3];
	int                  _Total;
};

struct sDuel
{
	bool                 _Duel;
	bool                 _Attack;
	bool                 _Move;
	BYTE                 _State;
	BYTE                 _Room;
	int                  _Index;
	int                  _Score;
	int                  _Time;
	int                  _Total;
};

class cDuel
{
public:
	bool Load();
	int GetPlayer(std::string Name);
	bool Attack(LPOBJ lpObj, LPOBJ Target);
	bool CheckRoom(int aIndex, int Target);
	void DuelRoom(int aIndex, int Target, int Room);
	void InvitationSend(int aIndex, int Target);
	void InvitationCancel(int aIndex, int Target);
	void InvitationCheck(LPOBJ lpObj);
	void Invitation(int aIndex, char* msg);
	void AcceptSend(int aIndex, int Target);
	void Accept(int aIndex);
	void ClearRoom(int Room);
	void ZeroStruct(int aIndex, int Target);
	void Killer(LPOBJ lpObj, LPOBJ Target);
	void CheckWinner(int aIndex, int Target);
	void Winner(int aIndex, int Target, int Score1, int Score2);
	static void Run(int Room);
	void Quit(LPOBJ lpObj);

public:
	bool				 _Active;
	int					 _Level;
	int					 _Zen;
	int                  _MapNumber[4];
	int                  _X[4];
	int                  _Y[4];
	int                  _Score[4];
	int                  _Count;
	int                  _Total;
	DWORD                _Time[4];
	char                 _Name[255];
	char                 _Column[255];
	char                 _Coin[255];
	char				 _Syntax[2][25];

public:
	sRoom			    RoomStruct[4];

	sDuel               DuelStruct[OBJECT_MAX];
};

extern cDuel Duel;