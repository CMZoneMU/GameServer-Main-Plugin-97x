#include "StdAfx.h"

std::vector<HEALTH_BAR> HealthBar;

void cHealthBar::Clear()
{
	HealthBar.clear();
}

void cHealthBar::Insert(short Index, BYTE Rate)
{
	HEALTH_BAR Bar;

	Bar.Index = Index;
	Bar.Rate = Rate;

	HealthBar.push_back(Bar);
}

HEALTH_BAR* cHealthBar::Get(short Index)
{
	for (std::vector<HEALTH_BAR>::iterator it = HealthBar.begin(); it != HealthBar.end(); ++it)
	{
		if (it->Index == Index)
		{
			return &(*it);
		}
	}

	return NULL;
}


void cHealthBar::Draw()
{
	SelectObject(*(HDC*)(0x55C5044), *(HFONT*)(0x55C5068));

	Patent.Run();

	mInterface.EventPoint(); // [ Novo ]: Chamada do Event Point

	int X = 0, Y = 0, Width = 80;
	VAngle Angle;
	SIZE Size;
	HEALTH_BAR* NewHealthBar;

	for (int i = 0; i < 390; i++)
	{
		DWORD ViewPort = *(DWORD*)(0x08033C38) + (i * 916);

		if ((*(BYTE*)ViewPort != 0x0) && (*(BYTE*)(ViewPort + 132) == 2))
		{
			NewHealthBar = HPBar.Get(*(WORD*)(ViewPort + 476));

			if (NewHealthBar == 0)
			{
				continue;
			}

			if (m_Monster[0] == false)
			{
				continue;
			}

			Angle.X = *(float*)(ViewPort + 16);
			Angle.Y = *(float*)(ViewPort + 20);
			Angle.Z = *(float*)(ViewPort + 300) + *(float*)(ViewPort + 24) + 100.0f;

			GetPosFromAngle(&Angle, &X, &Y);

			X -= (int)(floor(Width / 2.f));

			SetBlend(true);

			glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
			DrawBarForm((float)(X - 1), (float)(Y - 12), 2.f + (float)(Width), 17.f);

			if (NewHealthBar->Rate >= 70 && NewHealthBar->Rate <= 100)
			{
				glColor3f(0.01039216f, 0.939215688f, 0.0);
			}
			else if (NewHealthBar->Rate >= 30 && NewHealthBar->Rate <= 70)
			{
				glColor3f(0.58039216f, 0.539215688f, 0.0);
			}
			else if (NewHealthBar->Rate <= 30)
			{
				glColor3f(0.98039216f, 0.039215688f, 0.0);
			}

			DrawBarForm((float)(X), 1.f + Y, (float)((NewHealthBar->Rate * Width) / 100.0f), 3.0f);

			GLSwitchBlend();

			GetTextExtentPoint(*(HDC*)(0x55C5044), (char*)(ViewPort + 449), strlen((char*)(ViewPort + 449)), &Size);
			Size.cx = 80 - (LONG)((float)(Size.cx) / (*(float*)(0x55C4BC0)));

			if (Size.cx < 0)
			{
				Size.cx = 0;
			}
			else
			{
				Size.cx /= 2;
			}

			glColor4f(1.f, 1.f, 1.f, 1.f);

			X += Size.cx;
			Y -= 9;

			if ((X >= 0 && X <= (600 - (Size.cx / 2))) && (Y >= 0 && Y <= 480))
			{
				wsprintf(HPBar._Buffer, "%s", (char*)(ViewPort + 449));
				DrawTextOut(X, Y, HPBar._Buffer, 0, 0, 0);
			}

			GLSwitch();
		}

		GLSwitch();

		glColor3f(1.0f, 1.0f, 1.0f);
	}


	((void(*)())0x4B8300)();
}

cHealthBar HPBar;