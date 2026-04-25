#pragma once

class cBuy
{
public:
	bool Load();
	void Run(int aIndex, char* msg);

public:
	bool					_Active;
	int                     _Count;
	int                     _Amount[2];
	char                    _Column[2][255];
	char                    _Coin[2][255];
	char                    _Name[255];
	char                    _Syntax[25];
};

extern cBuy Buy;