#include "StdAfx.h"

cFlood::cFlood() : _List(0)
{
}

int cFlood::Get(char* IP)
{
	int Return = -1;

	for (int i = 0; i < this->_List; i++)
	{
		if (this->FloodStruct[i].IP[0] == IP[0])
		{
			if (strcmp(this->FloodStruct[i].IP, IP) == 0)
			{
				return i; break;
			}
		}
	}

	Return = this->_List;

	sprintf(this->FloodStruct[this->_List].IP, "%s", IP);

	this->_List++;

	if (this->_List >= 2000)
	{
		this->_List = 0;
	}

	return Return;
}

short cFlood::Connect(SOCKET Socket, char* Address, int aIndex)
{
	int Index = Flood.Get(Address);

	DWORD Tick = (GetTickCount() - Flood.FloodStruct[Index].LastConnect) / 1000;

	if (Tick < 3)
	{
		Flood.FloodStruct[Index].LastConnect = GetTickCount();
		return -1;
	}

	Flood.FloodStruct[Index].LastConnect = GetTickCount();

	return gObjAdd(Socket, Address, aIndex);
}

cFlood Flood;