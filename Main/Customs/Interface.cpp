#include "StdAfx.h"

void cInterface::Load()
{
	//=================================================================================================
	// OZJ - Loading  
	//=================================================================================================
	SetDword(0x0051F669 + 1, (DWORD)"Custom\\Local\\Loading01.jpg");
	SetDword(0x0051F68A + 1, (DWORD)"Custom\\Local\\Loading02.jpg");
	SetDword(0x0051F6A4 + 1, (DWORD)"Custom\\Local\\Loading03.jpg");
	
	//=================================================================================================
	// OZJ - Logo do Inicio do Cliente
	//=================================================================================================
	SetDword(0x0050E6EA + 1, (DWORD)"Custom\\Local\\WebZenLogo.jpg"); 

	//=================================================================================================
	// OZJ - Menu Interface
	//=================================================================================================
	SetDword(0x0050B329 + 1, (DWORD)"Custom\\Interface\\Menu01_new.jpg");
	SetDword(0x0050B363 + 1, (DWORD)"Custom\\Interface\\Menu03_new.jpg");
	SetDword(0x0050B3A0 + 1, (DWORD)"Custom\\Interface\\Menu_Red.jpg");
	SetDword(0x0050B3BD + 1, (DWORD)"Custom\\Interface\\Menu_Blue.jpg");
	SetDword(0x0050B525 + 1, (DWORD)"Custom\\Interface\\Menu_Green.jpg");
	//=================================================================================================
	// - Remover Dagrão Interface
	//=================================================================================================
	SetNop(0x4B8BE0, 5);
	SetNop(0x4B8C12, 5);

	//=================================================================================================
	// - Patent
	//=================================================================================================
	HookCall(0x50E802, cPatent::LoadImagesEx);
	
	//=================================================================================================
	// - Guild Logo
	//=================================================================================================
	HookCall(0x4B8B6B, cGuild::Run);
}

void cInterface::Ping()
{
	if (*(HDC*)(0x55C5044) == 0 || *(HFONT*)(0x55C5068) == 0)
	{
		return;
	}

	SelectObject(*(HDC*)(0x55C5044), *(HFONT*)(0x55C5068));

	char PingBuffer[64];

	if (Protocol.Count > 70.0f)
	{
		Protocol.Count = 70.0f;
	}

	sprintf_s(PingBuffer, "Ping: %u ms | FPS: %.0f", Protocol.Tick, Protocol.Count, Protocol.Reset);

	int PingX = 10;
	int PingY = 390;


	SetBlend(true);

	SIZE Size;
	GetTextExtentPoint(*(HDC*)(0x55C5044), PingBuffer, strlen(PingBuffer), &Size);

	Size.cx = (LONG)((float)(Size.cx) / (*(float*)(0x55C4BC0)));

	float Width = (float)Size.cx + 10.0f;

	if (Width > 120.0f)
	{
		Width = 120.0f;
	}

	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	DrawBarForm((float)PingX, (float)PingY, Width, 18.0f);

	GLSwitchBlend();

	int TextX = PingX + ((int)Width - Size.cx) / 2;
	int TextY = PingY + 3;

	if (Protocol.Tick <= 80)
	{
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else if (Protocol.Tick <= 150)
	{
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	}
	else
	{
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	}

	DrawTextOut(TextX, TextY, PingBuffer, 0, 0, 0);
}


void cInterface::EventPoint()
{
	if (*(HDC*)(0x55C5044) == 0 || *(HFONT*)(0x55C5068) == 0)
	{
		return;
	}

	SelectObject(*(HDC*)(0x55C5044), *(HFONT*)(0x55C5068));

	char EventBuffer[64];
	sprintf_s(EventBuffer, "Event Points: %d", Protocol.EventPoint);

	SetBlend(true);

	SIZE Size;
	GetTextExtentPoint(*(HDC*)(0x55C5044), EventBuffer, strlen(EventBuffer), &Size);

	float Scale = *(float*)(0x55C4BC0);

	Size.cx = (LONG)((float)Size.cx / Scale);
	Size.cy = (LONG)((float)Size.cy / Scale);

	float PaddingX = 4.0f;
	float PaddingY = 1.5f;

	float Width = (float)Size.cx + (PaddingX * 2.0f);
	float Height = (float)Size.cy + (PaddingY * 2.0f);

	float ScreenWidth = (float)(*(int*)(0x0055C4EC)) / Scale;
	float RightMargin = 12.0f;

	float EventX = ScreenWidth - Width - RightMargin;
	float EventY = 35.0f;

	glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
	DrawBarForm(EventX, EventY, Width, Height);

	GLSwitchBlend();

	float TextX = EventX + PaddingX;
	float TextY = EventY + PaddingY;

	glColor4f(0.85f, 0.25f, 1.0f, 1.0f);
	DrawTextOut((int)TextX, (int)TextY, EventBuffer, 0, 0, 0);
}

cInterface mInterface;