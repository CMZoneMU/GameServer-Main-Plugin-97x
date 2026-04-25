#include "StdAfx.h"

bool cDisconnect::Check(int aIndex)
{
	if (!this->DisconnectStruct[aIndex]._Send)
	{
		return false;
	}

	if (this->DisconnectStruct[aIndex]._Timer <= 0)
	{
		this->DisconnectStruct[aIndex]._Timer = GetTickCount();
	}

	if (this->DisconnectStruct[aIndex]._Count >= 500)
	{
		DWORD Timer = (GetTickCount() - this->DisconnectStruct[aIndex]._Timer) / 1000;

		if (Timer <= 1)
		{
			this->DisconnectStruct[aIndex]._Send = false;

			gObjCloseSet(aIndex, 0);
		}
		else
		{
			this->DisconnectStruct[aIndex]._Count = 0;
			this->DisconnectStruct[aIndex]._Timer = GetTickCount();
		}
	}

	this->DisconnectStruct[aIndex]._Count++;

	return true;
}

cDisconnect Disconnect;