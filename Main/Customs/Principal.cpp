#include "StdAfx.h"
#include "Naked.h"

void Initialize()
{
	if (gProtect.ReadMainFile("Data\\Custom\\CustomInfo\\CustomInfo.cmz") == 0)
	{
		MessageBoxA(NULL, "Leitura do arquivo incorreta ou não existe", "[ Error Custom Info] ", MB_OK);

		ExitProcess(0);
	}


	// [ Novo ]: GetMainCMZ Leitura das Dll

	gProtect.CheckClientFile();

	gProtect.CheckPluginFile();

	// [ Novo ]: GetMainCMZ Configurações Customs

	MemoryCpy(0x00553F6E, gProtect.m_MainInfo.IpAddress, sizeof(gProtect.m_MainInfo.IpAddress)); // Endreço de IP/Host 127.0.0.1

	SetWord(0x0055C53C, (gProtect.m_MainInfo.IpAddressPort)); // Porta CS 44405

	SetWord(0x005212E2, (DWORD)gProtect.m_MainInfo.ScreenShotPath); // Screenshot 

	MemoryCpy(0x00554668, gProtect.m_MainInfo.ClientSerial, sizeof(gProtect.m_MainInfo.ClientSerial)); //  ClientSerial 

	// - [ Novo ]: Fix Abrir Launcher 

	*(BYTE*)(0x0041E175) = 0xEB;
	
	// - [ Novo ]: Global Message sem ficar piscando

	*(BYTE*)(0x47DAF2 + 2) = 0; // Original 5 sombra
	*(BYTE*)(0x47DAE8 + 1) = 200; // Original 10 amarelo 
	

	// [ Novo ]: Carregar as novas texturas da interface
	mInterface.Load();


	// - New itens

	memset((DWORD*)0x5032A5, 0x50, 1);
	memset((DWORD*)0x503384, 0x50, 1);
	memset((DWORD*)0x5033AF, 0x50, 1);
	memset((DWORD*)0x503405, 0x50, 1);
	memset((DWORD*)0x503430, 0x50, 1);
	memset((DWORD*)0x5034DD, 0x50, 1);
	memset((DWORD*)0x503508, 0x50, 1);

	// - Screen

	CreateDirectory("ScreenShot", NULL);

	*(DWORD*)(0x5212E1 + 1) = (DWORD)(Screen);

	// - Remoção da gameguard

	*(BYTE*)(0x41E3FC) = 0xEB;
	*(BYTE*)(0x41E25B) = 0x74;
	*(BYTE*)(0x53853B) = 0xEB;

	// - Remoção muerror

	*(DWORD*)(0x405060) = 0xC3;

	// - Remoção muplayer

	*(DWORD*)(0x413D80) = 0xC3;

	// - Brilho em itens

	*(BYTE*)(0x5006B1 + 2) = 0x10;

	// - Cursor

	*(BYTE*)(0x43019F) = 0x90;

	for (BYTE i = 0; i < 7; i++)
	{
		*(BYTE*)(0x4301BD + i) = 0x90;

	}

	*(BYTE*)(0x432BFC) = 0x90;
	*(BYTE*)(0x432C21) = 0x90;

	for (BYTE i = 0; i < 6; i++)
	{
		*(BYTE*)(0x432C35 + i) = 0x90;
	}

	// - Optimize

	*(BYTE*)(0x521608) = 0x6A;
	*(BYTE*)(0x521609) = 0x01;
	*(BYTE*)(0x52160A) = 0xFF;
	*(BYTE*)(0x52160B) = 0x15;
	*(BYTE*)(0x52160C) = 0x24;
	*(BYTE*)(0x52160D) = 0xD1;
	*(BYTE*)(0x52160E) = 0x54;
	*(BYTE*)(0x52160F) = 0x00;

	for (BYTE i = 0; i <= 9; i++)
	{
		*(BYTE*)(0x521610 + i) = 0x90;
	}

	*(BYTE*)(0x52161A) = 0xEB;
	*(BYTE*)(0x52161B) = 0xD1;

	// - Excelente wings nível 1

	*(BYTE*)(0x4BFF9B) = 0x80;
	*(BYTE*)(0x4C0D81) = 0x80;
	*(BYTE*)(0x4796D7) = 0x80;
	*(BYTE*)(0x4798CF) = 0x80;
	*(BYTE*)(0x479A99) = 0x80;
	*(BYTE*)(0x479AFE) = 0x80;

	// - Modo janela

	*(DWORD*)(0x41D37B) = (DWORD)(&WndProcEx);
	*(DWORD*)(0x54D38C) = (DWORD)&IconProc;

	// - Novos monstros

	Monster.Load();

	// - Levelup sound

	HookCall(0x430948, LevelUp);

	// - Protocol

	HookJump(0x4384F5, nProtocolCore);
	HookJump(0x430B52, UpdateCharacterNoEffect);
	HookJump(0x4308FD, UpdateCharacterEffect);
	HookJump(0x4EA835, LevelUpPoints);

	// - Caça ao tesouro

	HookJump(0x4C0300, nPriceBuyRecv);
	HookJump(0x4C0343, nPriceBuyRecv);
	HookJump(0x4C036E, nPriceBuyRecv);
	HookJump(0x4C038F, nPriceBuyRecv);

	for (BYTE i = 0; i != 6; i++)
	{
		*(BYTE*)(0x4C0305 + i) = 0x90;
		*(BYTE*)(0x4C0348 + i) = 0x90;
		*(BYTE*)(0x4C0373 + i) = 0x90;
		*(BYTE*)(0x4C0394 + i) = 0x90;
	}

	// - Visual

	Visual.Load();

	// - Money

	memcpy((char*)0x5554CC, "%d.%03d.%03d.%03d", 17);
	memcpy((char*)0x5554E0, "%d.%03d.%03d", 12);
	memcpy((char*)0x5554F0, "%d.%03d", 6);

	// - Texture

	HookCall(0x50BCDB, cTexture::Models);
	HookCall(0x50BCE0, cTexture::Textures);

	// - Description

	SetNop(0x4C1A36, 60);
	HookJump(0x4C1A36, cDescription::Load);

	// - Title

	SetNop(0x4BFEF5, 34);
	HookJump(0x4BFEF0, cTitle::Load);

	// - Nome dos novos mapas

	HookCall(0x428240, MapName);

	// - Acentuação

	*(BYTE*)(0x553EB4) = 0xA0;

	// New Font
	gFont.Init();

	// - Resolution

	HookJump(0x41D82B, cResolution::Switch);
	HookJump(0x41E4D3, cResolution::Font);

	if (Registry("Resolution") > 2)
	{
		*(DWORD*)(0x51C296) = 0x1A0;
		*(BYTE*)(0x51C2A0) = 0x20;
	}

	// - New jewels

	SetNop(0x4DA016, 7);
	HookJump(0x4DA016, cJewel::Upgrade);
	SetNop(0x4D1D32, 7);
	HookJump(0x4D1D32, cJewel::Apply);
	SetNop(0x4C55DC, 10);
	HookJump(0x4C55DC, cJewel::Color);

	*(WORD*)(0x4D033E + 2) = 0x1F2;

	// - Effect

	Effect.Load();
	SetNop(0x520487, 5);
	SetNop(0x52048C, 5);

	// - HP bar

	HookCall(0x4B798E, cHealthBar::Draw);

	// - Global

	*(DWORD*)(0x47D934 + 2) = 0x4B0;

	// - Correção do arco archangel

	HookJnz(0x0F, 0x85, 0x4728B8, Archangel);

	// - Move item

	SetNop(0x4D13B5, 4);
	SetNop(0x4D1368, 4);
	HookCall(0x4D1388, MoveItem);

	// - Calcular FPS

	HookJump(0x43ED80, CalcFPS);

	// - Window Text

	HookCall(0x5214EF, WindowText);

	// - Exile Moviment

	BYTE Exile[7] = { 0x83, 0x3D, 0xB8, 0x57, 0x55, 0x00, 0x21 };
	memcpy((int*)0x0051F8F2, Exile, sizeof(Exile));

	// - Remove trava do jogo

	SetNop(0x50F3F1, 7);
	SetNop(0x50FB10, 7);
	SetNop(0x51020E, 7);

	// - Ping

	*(DWORD*)(0x41E649) = 1000;

	// - New Message

	Message.Load();


	// - Reflect

	SetNop(0x443D1D, 20);

	// - LoadLibrary

	LoadLibrary("./Glow.dll");
	LoadLibrary("./Weapon.dll");
	LoadLibrary("./Texture.dll");

}

// [ Novo ]: Minimizer com Icone perto do relógio
NOTIFYICONDATAA g_TrayIcon;

HWND            Window = NULL;
HHOOK           m_Keyboard1 = NULL;
HHOOK           m_Keyboard2 = NULL;
HHOOK           m_Mouse = NULL;
bool            Treasure = false;
bool            m_Monster[2] = { false, false };
bool            m_Patent[2] = { false, false };
bool            AutoClick[3] = { false, false, false };
bool			Active[5] = { false, true, false, false, false };

// [ Novo ]: Hooks para bloquear as teclas quando estiver minimizado
pGetAsyncKeyState_t pGetAsyncKeyStateReal = GetAsyncKeyState;
pGetKeyState_t      pGetKeyStateReal = GetKeyState;



void LevelUp()
{
	_asm
	{
		PUSH ECX
		MOV ECX, DWORD PTR DS:[EAX+0x34]
		MOV DWORD PTR DS:[EAX+0x10],ECX
		MOV BYTE PTR DS:[0x561616],1
		POP ECX
	}

	GCLevelUInfoSend();

	LoadWav(0x400,"Data\\Sound\\pLevelUp.wav",1,1);
	PlayWav(0x400,0,0);
}

char * MapName(int MapNumber)
{
	switch (MapNumber)
	{
	case 0:
		return "Lorencia";
	case 1:
		return "Dungeon";
	case 2:
		return "Davias";
	case 3:
		return "Noria";
	case 4:
		return "Lost Tower";
	case 5:
		return "Exile";
	case 6:
		return "Stadium";
	case 7:
		return "Atlans";
	case 8:
		return "Tarkan";
	case 9:
		return "Devil Square";
	case 10:
		return "Icarus";
	case 11:
		return "Blood Castle I";
	case 12:
		return "Blood Castle II";
	case 13:
		return "Blood Castle III";
	case 14:
		return "Blood Castle IV";
	case 15:
		return "Blood Castle V";
	case 16:
		return "Blood Castle VI";
	case 24:
		return "Kalima";
	case 18:
		return "Chaos Castle";
	case 19:
		return "Land of Trials";
	case 20:
		return "Vulcanus";
	case 21:
		return "Aida";
	case 22:
		return "Boss Room";
	case 17:
		return "Crystal";
	default:
		return "Desconhecido";
	}
}

void CalcFPS()
{
	float dif = (float)clock() - WorldTime;

	DeltaT = ((dif) ? dif : 0.1f) / CLOCKS_PER_SEC;

	FPS = (1.0f / dif) * CLOCKS_PER_SEC;

	WorldTime = (float)clock();
}

const char* GetVipName(int vip)
{
	switch (vip)
	{
	case 0: return "Free";
	case 1: return "Bonus";
	case 2: return "Premium";
	case 3: return "Super Vip";
	default: return "Desconhecido";
	}
}

void WindowText()
{
	if (MAIN_STATE == 5)
	{
		if (Protocol.Count > 70.0f)
		{
			Protocol.Count = 70.0f;
		}

		char Buffer[256];

		char VipText[256];

		if (Protocol.AccountLevel > 0 && Protocol.AccountExpireDays > 0)
		{
			sprintf_s(VipText, sizeof(VipText),	"%s (Expira em %d dias)",GetVipName(Protocol.AccountLevel),Protocol.AccountExpireDays);
		}
		else
		{
			sprintf_s(VipText, sizeof(VipText), "Free");
		}

		sprintf_s(Buffer, sizeof(Buffer),"Mu Lost - Ping: %u ms | FPS: %.0f | Resets: %d | Cash: %d | Vip: %s",
			Protocol.Tick,Protocol.Count,Protocol.Reset,Protocol.Cash,VipText);
		
		SetWindowText(GameWindow, Buffer);
	}

	((void(__cdecl*)()) 0x520530)();
}

// [ Novo ]: Alteração da thread principal para atualizar o ícone do 
// tray com o número de resets quando estiver minimizado.
void MainThread(void* lpParam)
{
	static int LastReset = -1; // guarda o último valor exibido

	while (true)
	{
		Protocol.Count = FPS;

		if (Active[1] == false && Window != NULL) // só quando estiver oculto
		{
			if (Protocol.Reset != LastReset)
			{
				LastReset = Protocol.Reset;
				Tray_Update(Window);
			}
		}

		Sleep(500); // pode usar 500~1000ms
	}

	_endthread();
}

// [ Novo ]: Hooks para bloquear as teclas quando estiver minimizado
SHORT WINAPI hkGetAsyncKeyState(int vKey)
{
	if (Active[1] == false)
	{
		// Permite apenas F9 para restaurar
		if (vKey != VK_F9)
		{
			return 0;
		}
	}

	return pGetAsyncKeyStateReal(vKey);
}

// [ Novo ]: Hooks para bloquear as teclas quando estiver minimizado
SHORT WINAPI hkGetKeyState(int nVirtKey)
{
	if (Active[1] == false)
	{
		// Permite apenas F9 para restaurar
		if (nVirtKey != VK_F9)
		{
			return 0;
		}
	}

	return pGetKeyStateReal(nVirtKey);
}

// [ Novo ]: Alteração do KeyboardProc para bloquear as hotkeys do jogo
// quando estiver minimizado, permitindo apenas a tecla F9 para restaurar a janela.
LRESULT CALLBACK KeyboardProc(int Code, WPARAM wParam, LPARAM lParam)
{
	if (Code != HC_ACTION)
	{
		return CallNextHookEx(m_Keyboard1, Code, wParam, lParam);
	}

	// Se estiver escondido, não processa hotkeys do jogo
	// O restore será feito pelo LL_KeyboardProc no F9
	if (Active[1] == false)
	{
		return CallNextHookEx(m_Keyboard1, Code, wParam, lParam);
	}

	if ((lParam >> 31) & 1) // key up
	{
		if (wParam == VK_F9)
		{
			if (Window != NULL && IsWindow(Window))
			{
				Active[1] = false;

				Tray_Create(Window);
				ShowWindow(Window, SW_HIDE);

				return 1;
			}
		}

		if (wParam == VK_F5)
		{
			if (m_Patent[0] == false)
			{
				m_Patent[1] = !m_Patent[1];
				m_Patent[0] = true;
			}
			else
			{
				m_Patent[1] = !m_Patent[1];
				m_Patent[0] = false;
			}
		}

		if (wParam == VK_F6)
		{
			if (!Active[4])
			{
				Active[4] = !Active[4];
				*(BYTE*)(0x4FF9C0) = 0xC3;
			}
			else
			{
				Active[4] = !Active[4];
				*(BYTE*)(0x4FF9C0) = 0x53;
			}
		}

		if (wParam == VK_F7)
		{
			if (Active[2] == false)
			{
				Active[3] = !Active[3];
				Active[2] = true;
				Camera.Toggle();
			}
			else
			{
				Active[3] = !Active[3];
				Active[2] = false;
				Camera.Restore();
			}
		}

		if (wParam == VK_F8)
		{
			if (!Active[0])
			{
				Active[0] = !Active[0];
				*(BYTE*)(0x5006B1 + 2) = 0x0C;
			}
			else
			{
				Active[0] = !Active[0];
				*(BYTE*)(0x5006B1 + 2) = 0x10;
			}
		}

		if (wParam == VK_F10)
		{
			if (AutoClick[1] == false)
			{
				AutoClick[0] = !AutoClick[0];
				AutoClick[2] = false;

				if (AutoClick[0] == false)
				{
					KillTimer(Window, AUTOCLICK_LEFT);
					SendMessage(Window, WM_LBUTTONUP, NULL, NULL);
				}
				else
				{
					SetTimer(Window, AUTOCLICK_LEFT, 10, NULL);
				}
			}
		}

		if (wParam == VK_F11)
		{
			if (AutoClick[0] == false)
			{
				AutoClick[1] = !AutoClick[1];
				AutoClick[2] = false;

				if (AutoClick[1] == false)
				{
					KillTimer(Window, AUTOCLICK_RIGHT);
					SendMessage(Window, WM_RBUTTONUP, NULL, NULL);
				}
				else
				{
					SetTimer(Window, AUTOCLICK_RIGHT, 10, NULL);
				}
			}
		}

		if (wParam == VK_F12)
		{
			if (m_Monster[0] == false)
			{
				m_Monster[1] = !m_Monster[1];
				m_Monster[0] = true;
				SetNop(0x4C7082, 5);
			}
			else
			{
				m_Monster[1] = !m_Monster[1];
				m_Monster[0] = false;
				Hook(0xE8, 0x4C7082, 0x50F120);
			}
		}
	}

	return CallNextHookEx(m_Keyboard1, Code, wParam, lParam);
}

// [ Novo ]: Alteração do LL_KeyboardProc para restaurar a janela quando o usuário pressionar F9
// mesmo que a janela esteja minimizada e sem foco.
LRESULT CALLBACK LL_KeyboardProc(int Code, WPARAM wParam, LPARAM lParam)
{
	if (Code >= 0 && Active[1] == false)
	{
		KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;

		if ((wParam == WM_KEYUP || wParam == WM_SYSKEYUP) && kb->vkCode == VK_F9)
		{
			if (Window != NULL && IsWindow(Window))
			{
				Active[1] = true;

				Tray_Remove(Window);

				ShowWindow(Window, SW_SHOW);
				ShowWindow(Window, SW_RESTORE);
				SetForegroundWindow(Window);
				SetActiveWindow(Window);
			}

			return 1;
		}
	}

	return CallNextHookEx(m_Keyboard2, Code, wParam, lParam);
}

LRESULT CALLBACK Mouse(int Code, WPARAM wParam, LPARAM lParam)
{
	if (Code == HC_ACTION)
	{
		MOUSEHOOKSTRUCTEX* HookStruct = (MOUSEHOOKSTRUCTEX*)lParam;

		switch (wParam)
		{
		case WM_MOUSEMOVE:
			if (GetForegroundWindow() == GameWindow)
			{
				Camera.Move(HookStruct);
			}
			break;
		case WM_MBUTTONDOWN:
			if (GetForegroundWindow() == GameWindow)
			{
				Camera.SetIsMove(1);
				Camera.SetCursorX(HookStruct->pt.x);
				Camera.SetCursorY(HookStruct->pt.y);
			}
			break;
		case WM_MBUTTONUP:
			if (GetForegroundWindow() == GameWindow)
			{
				Camera.SetIsMove(0);
			}
			break;
		case WM_MOUSEWHEEL:
			if (GetForegroundWindow() == GameWindow)
			{
				Camera.Zoom(HookStruct);
			}
			break;
		}
	}

	return CallNextHookEx(m_Mouse, Code, wParam, lParam);
}

// [ Novo ]: Alteração do WndProc para implementar a funcionalidade de minimizar para a
// bandeja do sistema (system tray) e restaurar ao clicar no ícone, além de atualizar
// o ícone com o número de resets quando estiver minimizado.
LRESULT CALLBACK WndProcEx(HWND Window, UINT Message, WPARAM W, LPARAM L)
{
	if (::Window == NULL)
	{
		::Window = Window;
	}


	switch (Message)
	{
	case WM_NCACTIVATE:
	{
		return 0;
	}
	break;
	case WM_TRAYICON:// Minimizer Tray Icon
	{
		Tray_Message(Window, L);
	}
	break;
	case WM_TIMER:
	{
		switch (W)
		{
		case AUTOCLICK_LEFT:
		{
			if (AutoClick[0] == true)
			{
				SendMessage(Window, (AutoClick[2] == true) ? WM_LBUTTONUP : WM_LBUTTONDOWN, NULL, NULL);
				AutoClick[2] = !AutoClick[2];
			}
		}
		break;
		case AUTOCLICK_RIGHT:
		{
			if (AutoClick[1] == true)
			{
				SendMessage(Window, (AutoClick[2] == true) ? WM_RBUTTONUP : WM_RBUTTONDOWN, NULL, NULL);
				AutoClick[2] = !AutoClick[2];
			}
		}
		break;
		}
	}
	break;
	}

	return CallWindowProc(WndProc, Window, Message, W, L);
}

// [ Novo ]: Alteração no caminho do ícone para o tray, verificando se o arquivo 
// existe e carregando-o, caso contrário, carrega o ícone padrão do sistema.
HICON WINAPI IconProc(HINSTANCE hInstance, LPCSTR lpIconName)
{
	HICON           m_TrayIcon;
	HINSTANCE       hins;

	FILE* file;

	if (fopen_s(&file, ".\\Data\\Custom\\Window\\Main.ico", "r") != 0)
	{
		m_TrayIcon = (HICON)LoadImage(hins, MAKEINTRESOURCE(100), IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	}
	else
	{
		fclose(file);
		m_TrayIcon = (HICON)LoadImage(hins, ".\\Data\\Custom\\Window\\Main.ico", IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_LOADFROMFILE | LR_DEFAULTCOLOR);
	}

	return m_TrayIcon;
}

// [ Novo ]: Mimimizer Tray Icon
void Tray_Create(HWND hWnd)
{
	ZeroMemory(&g_TrayIcon, sizeof(g_TrayIcon));

	g_TrayIcon.cbSize = sizeof(NOTIFYICONDATA);
	g_TrayIcon.hWnd = hWnd;
	g_TrayIcon.uID = 1;
	g_TrayIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	g_TrayIcon.uCallbackMessage = WM_TRAYICON;

	HICON hIcon = NULL;

	hIcon = (HICON)LoadImageA(
		NULL,
		"Data\\Custom\\Window\\Main.ico",
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		LR_LOADFROMFILE
	);

	if (!hIcon)
	{
		hIcon = LoadIcon(NULL, IDI_APPLICATION);
	}

	g_TrayIcon.hIcon = hIcon;

	wsprintfA(g_TrayIcon.szTip, "Mu Lost 97 +99 | Online | Resets: %d", Protocol.Reset);

	Shell_NotifyIconA(NIM_ADD, &g_TrayIcon);
}

// [ Novo ]: Mimimizer Tray Icon
void Tray_Remove(HWND hWnd)
{
	Shell_NotifyIconA(NIM_DELETE, &g_TrayIcon);

	if (g_TrayIcon.hIcon)
	{
		DestroyIcon(g_TrayIcon.hIcon);
		g_TrayIcon.hIcon = NULL;
	}
}

// [ Novo ]: Mimimizer Tray Icon
void Tray_Message(HWND hWnd, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONDOWN:
	{
		// Restaurar ao clicar
		ShowWindow(hWnd, SW_SHOW);
		ShowWindow(hWnd, SW_RESTORE);
		SetForegroundWindow(hWnd);
		SetActiveWindow(hWnd);

		Active[1] = true;
		Tray_Remove(hWnd);
	}
	break;

	case WM_RBUTTONDOWN:
	{
		POINT pt;
		GetCursorPos(&pt);

		HMENU hMenu = CreatePopupMenu();

		InsertMenu(hMenu, -1, MF_BYPOSITION, 1, "Abrir");
		InsertMenu(hMenu, -1, MF_BYPOSITION, 2, "Fechar");

		SetForegroundWindow(hWnd);

		int cmd = TrackPopupMenu(
			hMenu,
			TPM_RETURNCMD | TPM_NONOTIFY,
			pt.x, pt.y,
			0,
			hWnd,
			NULL
		);

		if (cmd == 1)
		{
			ShowWindow(hWnd, SW_SHOW);
			ShowWindow(hWnd, SW_RESTORE);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);

			Active[1] = true;
			Tray_Remove(hWnd);
		}
		else if (cmd == 2)
		{
			ExitProcess(0);
		}

		DestroyMenu(hMenu);
	}
	break;
	}
}

// [ Novo ]: Mimimizer Tray Icon
void Tray_Update(HWND hWnd)
{
	g_TrayIcon.uFlags = NIF_TIP;

	wsprintfA(g_TrayIcon.szTip, "Mu Lost | Online | Resets: %d", Protocol.Reset);

	Shell_NotifyIconA(NIM_MODIFY, &g_TrayIcon);
}