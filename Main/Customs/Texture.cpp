#include "StdAfx.h"

void cTexture::Models()
{
	((void(*)())0x502920)();

	for (int i = 0; i < 32; i++)
	{
		if (i >= 27 && i <= 32)
		{
			sprintf_s(Texture.Buffer, "Box%d", i + 1);
			((void(*)(int, char*, char*, int))0x501080)((14 * 32) + i + 0x190, "Data\\Item\\", Texture.Buffer, -1);
		}

		if (i >= 16 && i <= 26)
		{
			sprintf_s(Texture.Buffer, "Jewel%d", i + 1);
			((void(*)(int, char*, char*, int))0x501080)((15 * 32) + i + 0x190, "Data\\Item\\", Texture.Buffer, -1);
		}
	}
}

void cTexture::Textures()
{
	((void(*)())0x503BF0)();

	for (int i = 0; i < 32; i++)
	{
		if (i >= 27 && i <= 32)
		{
			((void(*)(int, char*, int, int, int))0x500C50)((14 * 32) + i + 0x190, "Item\\", GL_NEAREST, GL_FALSE, GL_TRUE);
		}

		if (i >= 16 && i <= 26)
		{
			((void(*)(int, char*, int, int, int))0x500C50)((15 * 32) + i + 0x190, "Item\\", GL_NEAREST, GL_FALSE, GL_TRUE);
		}
	}
}

cTexture Texture;
