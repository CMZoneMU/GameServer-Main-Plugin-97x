#include "StdAfx.h"

char * TitleText[1] =
{
	"[-          Flame Team          -]"
};

cDisplay::cDisplay()
{
	this->Font = CreateFont(110, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN, "Times");
	this->Background = CreateSolidBrush(RGB(255, 0, 0));
}

cDisplay::~cDisplay()
{
	DeleteObject(this->Font);
	DeleteObject(this->Background);
}

void cDisplay::ViewPaint(HWND hWnd, short aIndex)
{
	int iMonsterCount = 0, iFreeCount = 0, iVipCount = 0, Staffers = 0, iTotalCount = 0;
	
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		if (i < OBJECT_MIN)
		{
			if (gObj[i].Type != PLAYER && gObj[i].Connected == 3)
			{
				iMonsterCount++;
			}
		}
		else
		{
			if (gObj[i].Type == PLAYER && gObj[i].Connected == 3)
			{
				if (Custom[i].VipCount == 0 && gObj[i].Authority == 1)
				{
					iFreeCount++;
				}

				if (Custom[i].VipCount > 0 && gObj[i].Authority == 1)
				{
					iVipCount++;
				}

				if (gObj[i].Authority > 1)
				{
					Staffers++;
				}

				iTotalCount++;
			}
		}
	}

	TotalUser = iTotalCount;

	wsprintf(Display.Buffer,"MONSTERS: %d       -       FREE PLAYERS: %d       -       VIP PLAYERS: %d       -       STAFFERS: %d       -       TOTAL ONLINE: %d       -       MAX DE USUÁRIOS: %d", iMonsterCount,iFreeCount,iVipCount,Staffers,iTotalCount,ServerMaxUser);
	
	RECT Rect;
	HDC Hdc = GetDC(hWnd);

	int OldBkMode = SetBkMode(Hdc, TRANSPARENT);

	GetClientRect(hWnd, &Rect);

	Rect.top = 20;
	Rect.bottom = 220;

	SetTextColor(Hdc, RGB(255, 255, 255));
	TextOut(Hdc, 200, 0, Display.Buffer, strlen(Display.Buffer));
	FillRect(Hdc, &Rect, Display.Background);

	HFONT OldFont = (HFONT)SelectObject(Hdc, Display.Font);

	SetTextColor(Hdc, RGB(255, 255, 255));
	DrawText(Hdc, TitleText[0], 34, &Rect, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

	SelectObject(Hdc, OldFont);
	SetBkMode(Hdc, OldBkMode);
	ReleaseDC(hWnd, Hdc);
}

void cDisplay::LogTextPaintProcEx(HWND hWnd)
{
	HFONT Font = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN, "Times");
	HBRUSH Background = CreateSolidBrush(RGB(31, 31, 31));

	RECT Rect;

	HDC New = GetDC(hWnd);
	HDC Hdc = GetDC(hWnd);

	GetClientRect(hWnd, &Rect);

	SelectObject(Hdc, Font);
	FillRect(Hdc, &Rect, Background);

	SetBkMode(New, TRANSPARENT);
	SetBkMode(Hdc, TRANSPARENT);

	int Total, i;

	i = Display.m_cline;

	Total = 30;

	while (Total-- != 0)
	{
		switch (Display.LogTextViewType[i])
		{
		case 2:
			SetTextColor(Hdc, RGB(207, 3, 18));
			break;
		case 3:
			SetTextColor(Hdc, RGB(0, 100, 0));
			break;
		case 4:
			SetTextColor(Hdc, RGB(0, 0, 255));
			break;
		case 5:
			SetTextColor(Hdc, RGB(155, 0, 0));
			break;
		case 6:
			SetTextColor(Hdc, RGB(0, 0, 100));
			break;
		case 7:
			SetTextColor(Hdc, RGB(210, 30, 150));
			break;
		default:
			SetTextColor(Hdc, RGB(195, 195, 195));
			break;
		}

		if (strlen(Display.LogText[i]) > 1)
		{
			SetTextColor(New, RGB((rand() % 255), (rand() % 255), (rand() % 255)));
			TextOut(New, 4, Total * 15 + 227, ":::", 3);
			TextOut(Hdc, 22, Total * 15 + 227, Display.LogText[i], strlen(Display.LogText[i]));
		}

		i--;

		if (i < 0)
		{
			i = 30 - 1;
		}
	}

	DeleteObject(Font);
	DeleteObject(Background);

	ReleaseDC(hWnd, New);
	ReleaseDC(hWnd, Hdc);
}

void cDisplay::LogTextAddEx(BYTE type, char* msg, int len)
{
	if (len > 160 -1)
	{
		len = 160 -1;
	}

	Display.m_cline++;

	if (Display.m_cline > 30 -1)
	{
		Display.m_cline = 0;
	}

	Display.LogText[Display.m_cline][0] = 0;
	memcpy(&Display.LogText[Display.m_cline],msg,len);
	Display.LogText[Display.m_cline][1+ len] = 0;
	Display.LogText[Display.m_cline][len] = 0;
	Display.LogTextLength[Display.m_cline]= len;
	Display.LogTextViewType[Display.m_cline] = type;
}

cDisplay Display;