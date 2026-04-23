#pragma once

#define AUTOCLICK_LEFT		70001
#define AUTOCLICK_RIGHT		70002

// Mimimizer Tray Icon
#define WM_TRAYICON (WM_USER + 1001)
void Tray_Update(HWND hWnd);
void Tray_Create(HWND hWnd);
void Tray_Remove(HWND hWnd);
void Tray_Message(HWND hWnd, LPARAM lParam);

extern HWND         Window;
extern HHOOK        m_Keyboard1;
extern HHOOK        m_Keyboard2;
extern HHOOK        m_Mouse;
extern bool			Treasure;
extern bool         m_Monster[2];
extern bool         m_Patent[2];
extern bool         AutoClick[3];
extern bool         Active[5];

typedef SHORT(WINAPI* pGetAsyncKeyState_t)(int vKey);
typedef SHORT(WINAPI* pGetKeyState_t)(int nVirtKey);

extern pGetAsyncKeyState_t pGetAsyncKeyStateReal;
extern pGetKeyState_t      pGetKeyStateReal;

void Initialize();
void Finalize();
void LevelUp();
char* MapName(int MapNumber);
void CalcFPS();
void WindowText();
void MainThread(void* lpParam);
const char* GetVipName(int vip);

SHORT WINAPI hkGetAsyncKeyState(int vKey);
SHORT WINAPI hkGetKeyState(int nVirtKey);

LRESULT CALLBACK KeyboardProc(int Code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LL_KeyboardProc(int Code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Mouse(int Code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcEx(HWND Window, UINT Message, WPARAM W, LPARAM L);
HICON WINAPI IconProc(HINSTANCE hInstance, LPCSTR lpIconName);