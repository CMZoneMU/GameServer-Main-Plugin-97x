#pragma once

struct sFlood
{
	char IP[16];
	DWORD LastConnect;
};

class cFlood
{
public:
	cFlood();

public:
	int Get(char* IP);
	static short Connect(SOCKET Socket, char* Address, int aIndex);

public:
	int			    _List;

private:
	sFlood			FloodStruct[2000];
};

extern cFlood Flood;