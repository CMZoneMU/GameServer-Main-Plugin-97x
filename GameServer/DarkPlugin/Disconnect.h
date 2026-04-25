#pragma once

struct sDisconnect
{
	bool				_Send;
	DWORD				_Timer;
	DWORD				_Count;
};

class cDisconnect
{
public:
	bool                Check(int aIndex);

public:
	sDisconnect			DisconnectStruct[1000];
};

extern cDisconnect Disconnect;