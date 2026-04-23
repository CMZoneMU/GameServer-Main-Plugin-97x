#include "StdAfx.h"

void cOptimize::Load()
{
	if (!this->Memory())
	{
		MessageBox(NULL, "Impossível iniciar a thread.", "Flame Plugin - Error", MB_OK | MB_ICONERROR);

		DWORD Exit;
		GetExitCodeProcess(GetCurrentProcess(), &Exit);
		ExitProcess(Exit);
	}
}

DWORD __stdcall MainProc(PVOID Void)
{
	while (true)
	{
		SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);

		Sleep(1000);
	}

	return true;
}

bool cOptimize::Memory()
{
	this->_Thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainProc, 0, 0, &this->_Id);

	if (this->_Thread == false)
	{
		return false;
	}

	CloseHandle(this->_Thread);

	return true;
}

cOptimize Optimize;