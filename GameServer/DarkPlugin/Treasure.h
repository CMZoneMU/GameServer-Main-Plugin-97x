#pragma once

class TREASURE_Custom
{
public:
	bool Load();
	void Check();
	void Talk(OBJECTSTRUCT* Npc, OBJECTSTRUCT* Player);
	BYTE ShopNumber() const;
	const char* Winner() const;

private:
	bool				_Active;
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
