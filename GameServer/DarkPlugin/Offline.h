#pragma once

struct sOfflinePlayer
{
public:
	sOfflinePlayer() : _Offline(false)
	{
	}

	bool                    _Offline;
};

class cOffline
{
public:
	bool Load();
	void Command(int aIndex);

public:
	bool                    _Active;
	char                    _Syntax[25];

public:
	sOfflinePlayer			PlayerStruct[OBJECT_MAX];
};

extern cOffline Offline;