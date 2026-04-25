#include "StdAfx.h"

bool Create(PMSG_CHARCREATE* lpMsg, DWORD aIndex)
{
	for(int i = 0; i < sizeof(lpMsg->Name); i++)
	{
		if (!isalnum((BYTE)(lpMsg->Name[i])) && lpMsg->Name[i] != ' ' && lpMsg->Name[i] != NULL)
		{	
			return true;
		}
	}

	return false;
}