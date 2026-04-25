#include "StdAfx.h"

int cLicense::WinMainEx(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GetVolumeInformation("C:\\", NULL, 0, &License._Serial, NULL, NULL, NULL, 0);

	UUID ID; UuidCreateSequential(&ID);

	for (int i = 2; i < 8; i++)
	{
		License._Data[i - 2] = ID.Data4[i];
	}

	sprintf(License._Buffer, "%02X-%02X-%02X-%02X-%02X-%02X", License._Data[0], License._Data[1], License._Data[2], License._Data[3], License._Data[4], License._Data[5]);

	if (/*License.Check(License._Buffer) && */License._Serial == 0x6CBD94F9)
	{
		return WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}
	else
	{
		MessageBox(NULL, "Infelizmente sua licença não foi encontrada!\n Por favor, entre em contato.\n\n www.flameteam.com.br", "Flame Plugin", MB_OK | MB_ICONINFORMATION);
		ExitProcess(0);
	}
}

bool cLicense::Check(LPCSTR ID)
{
	char CheckList[13][18] =
	{
		"00-50-56-BE-4C-FA",
	};

	for (int i = 0; i < 13; i++)
	{
		if (!strcmp(ID, CheckList[i]))
		{
			return true;
		}
	}

	return false;
}

cLicense License;