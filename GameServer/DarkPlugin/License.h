#pragma once

class cLicense
{
public:
	static int WinMainEx(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	bool Check(LPCSTR ID);

private:
	BYTE  _Data[6];
	DWORD _Serial;
	char  _Buffer[60];
};

extern cLicense License;