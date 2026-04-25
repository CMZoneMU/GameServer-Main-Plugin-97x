#pragma once

struct sRaffle
{
	int                     _Day;
	int                     _Hours;
	int                     _Minutes;
	int						_Amount;
	char                    _NameCoin[255];
};

class cRaffleEvent
{
public:
	cRaffleEvent();

public:
	bool Load();
	void Run();

public:
	bool                    _Active;
	int                     _Count[2];
	int                     _Received[1000];

private:
	sRaffle			        RaffleStruct[1000];
};

extern cRaffleEvent RaffleEvent;