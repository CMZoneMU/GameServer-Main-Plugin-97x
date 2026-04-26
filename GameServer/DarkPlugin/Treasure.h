#pragma once

class TREASURE_Custom
{
public:
	char _Syntax[10][25];
	bool Load();
	void Check();
	void Talk(OBJECTSTRUCT* Npc, OBJECTSTRUCT* Player);
	BYTE ShopNumber() const;
	const char* Winner() const;
	void StartManual();
	bool				_Active;

public:
	BYTE				_State;
	DWORD				_TimeCount;
	DWORD				_TimeOpen;
	DWORD				_TimeBuy;
	DWORD				_TimeClose;
	int				    _Index;
	BYTE				_ShopNumber;
	char				_Winner[11];
	char                _Buffer[3][60];

private:
	enum TreasureState 
	{ 
		treasureOff, treasureOn 
	};
};

extern TREASURE_Custom Treasure;
