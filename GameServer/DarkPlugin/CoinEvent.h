#pragma once

class cCoinEvent
{
public:
	cCoinEvent();

public:
	bool Load();
	void Run(LPOBJ lpObj);
	void Quit(LPOBJ lpObj);

public:
	bool                _Active;
	int					_Time;
	int					_Amount;
	char                _NameCoin[255];
};

extern cCoinEvent CoinEvent;