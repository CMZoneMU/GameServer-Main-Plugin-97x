#include "StdAfx.h"

extern "C" __declspec(dllexport) void FireTeam()
{
}

BOOL APIENTRY DllMain(HINSTANCE Instance, DWORD Reason, LPVOID Reserved)
{
	switch (Reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		DWORD OldProtect;
		if (VirtualProtect((LPVOID)(0x401000), 2834430, PAGE_EXECUTE_READWRITE, &OldProtect) == TRUE)
		{
			Optimize.Load();

			Initialize();

			_beginthread(&MainThread, 0, NULL);

			m_Keyboard1 = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, NULL, GetCurrentThreadId());
			m_Keyboard2 = SetWindowsHookEx(WH_KEYBOARD_LL, LL_KeyboardProc, Instance, 0);
			m_Mouse = SetWindowsHookEx(WH_MOUSE, Mouse, NULL, GetCurrentThreadId());

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach(&(PVOID&)pGetAsyncKeyStateReal, hkGetAsyncKeyState);
			DetourAttach(&(PVOID&)pGetKeyStateReal, hkGetKeyState);

			if (Registry("WindowMode") > 0)
			{
				DetourAttach((&(LPVOID&)(pCreateWindowExA)), dtCreateWindowExA);
				DetourAttach((&(LPVOID&)(pChangeDisplaySettingsA)), dtChangeDisplaySettingsA);
			}

			DetourTransactionCommit();
		}
	}
	break;

	case DLL_PROCESS_DETACH:
	{
		if (m_Keyboard1)
		{
			UnhookWindowsHookEx(m_Keyboard1);
		}

		if (m_Keyboard2)
		{
			UnhookWindowsHookEx(m_Keyboard2);
		}

		if (m_Mouse)
		{
			UnhookWindowsHookEx(m_Mouse);
		}

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		DetourDetach(&(PVOID&)pGetAsyncKeyStateReal, hkGetAsyncKeyState);
		DetourDetach(&(PVOID&)pGetKeyStateReal, hkGetKeyState);

		if (Registry("WindowMode") > 0)
		{
			DetourDetach((&(LPVOID&)(pCreateWindowExA)), dtCreateWindowExA);
			DetourDetach((&(LPVOID&)(pChangeDisplaySettingsA)), dtChangeDisplaySettingsA);
		}

		DetourTransactionCommit();
	}
	break;
	}

	return TRUE;
}