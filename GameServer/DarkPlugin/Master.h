#pragma once

class cMaster
{
public:
	cMaster();

public:
	bool Load();
	void Run(int aIndex);

public:
	bool					_Active;
	int					    _Level[4];
	int					    _Zen[4];
	int					    _Remove[4];
	int                     _Return[4];
	int                     _Resets[4];
	int					    _NeedFor[4];
	int					    _NeedAgi[4];
	int					    _NeedVit[4];
	int					    _NeedEne[4];
	char					_Syntax[25];
};

extern cMaster Master;