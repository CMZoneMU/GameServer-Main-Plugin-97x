#include "StdAfx.h"

void cGuild::Run(int x, int y, DWORD c)
{
	DWORD character = *(DWORD*)(c + 564);

	if (*(BYTE*)(character + 0x84) == 1)
	{
		if (*(short*)(character + 0x1DA) != -1)
		{
			Mark(*(WORD*)(character + 0x1DA), true);

			RenderBitmap(0x22, ((float)x - 21.0f), (float)y, 16.0f, 16.0f, 0.0f, 0.0f, 1.0f, 1.0f, true, true);
		}
	}

	RenderBoolean(x, y, c);
}

cGuild Guild;