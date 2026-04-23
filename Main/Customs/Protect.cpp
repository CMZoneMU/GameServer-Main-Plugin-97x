#include "stdafx.h"
#include "Protect.h"
#include "CCRC32.h"

CProtect gProtect;

static void NormalizeString(char* text)
{
	if (text == 0)
	{
		return;
	}

	char temp[256] = { 0 };
	int j = 0;

	for (int i = 0; text[i] != 0 && j < 255; i++)
	{
		if (text[i] != '"' && text[i] != ' ' && text[i] != '\t' && text[i] != '\r' && text[i] != '\n')
		{
			temp[j++] = text[i];
		}
	}

	temp[j] = 0;
	strcpy_s(text, 256, temp);
}

CProtect::CProtect()
{
	memset(&this->m_MainInfo, 0, sizeof(this->m_MainInfo));
	this->m_ClientFileCRC = 0;
	this->m_InstanceMutex = NULL;
}

CProtect::~CProtect()
{
	if (this->m_InstanceMutex != NULL)
	{
		CloseHandle(this->m_InstanceMutex);
		this->m_InstanceMutex = NULL;
	}
}

void CProtect::SecurityError(const char* message)
{
	MessageBoxA(NULL, message, "CMZone Security", MB_OK | MB_ICONERROR);
	ExitProcess(0);
}

const char* CProtect::ConvertModuleFileName(const char* path)
{
	static char name[MAX_PATH];
	memset(name, 0, sizeof(name));

	const char* pos = strrchr(path, '\\');

	if (pos == NULL)
	{
		strcpy_s(name, path);
	}
	else
	{
		strcpy_s(name, pos + 1);
	}

	return name;
}

bool CProtect::ReadMainFile(char* name)
{
	CCRC32 CRC32;

	if (!CRC32.FileCRC(name, &this->m_ClientFileCRC, 1024))
	{
		return false;
	}

	HANDLE file = CreateFileA(name, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, 0);

	if (file == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	if (GetFileSize(file, 0) != sizeof(MAIN_FILE_INFO))
	{
		CloseHandle(file);
		return false;
	}

	DWORD OutSize = 0;

	if (ReadFile(file, &this->m_MainInfo, sizeof(MAIN_FILE_INFO), &OutSize, 0) == FALSE)
	{
		CloseHandle(file);
		return false;
	}

	BYTE XorKey[20] = {
		0x9E, 0x98, 0x12, 0x2B, 0xB6,
		0x76, 0xF6, 0x5B, 0x76, 0x4D,
		0x08, 0xF2, 0xAB, 0xDF, 0x91,
		0xB6, 0x4C, 0x1C, 0x93, 0x2F
	};

	for (int n = 0; n < (int)sizeof(MAIN_FILE_INFO); n++)
	{
		((BYTE*)&this->m_MainInfo)[n] -= (BYTE)(XorKey[n % 20] ^ HIBYTE(n));
		((BYTE*)&this->m_MainInfo)[n] += (BYTE)(XorKey[n % 20] ^ HIBYTE(n));
		((BYTE*)&this->m_MainInfo)[n] ^= (BYTE)(XorKey[n % 20] ^ LOBYTE(n));
	}

	CloseHandle(file);

	NormalizeString(this->m_MainInfo.ClientName);
	NormalizeString(this->m_MainInfo.PluginName);

	if (this->m_MainInfo.ClientName[0] == 0)
	{
		return false;
	}

	return true;
}

void CProtect::CheckInstance()
{
	this->m_InstanceMutex = CreateMutexA(0, FALSE, "Global\\CMZONE_MAIN97_MUTEX");

	if (this->m_InstanceMutex == NULL)
	{
		this->SecurityError("Falha ao criar o mutex de instancia.");
	}

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		this->SecurityError("O cliente ja esta em execucao.");
	}
}

void CProtect::CheckClientFile()
{
	if (this->m_MainInfo.ClientCRC32 == 0)
	{
		this->SecurityError("Client CRC invalido.");
	}

	char modulePath[MAX_PATH] = { 0 };

	if (GetModuleFileNameA(0, modulePath, sizeof(modulePath)) == 0)
	{
		this->SecurityError("Falha ao obter o nome do executavel.");
	}

	if (_stricmp(this->ConvertModuleFileName(modulePath), this->m_MainInfo.ClientName) != 0)
	{
		this->SecurityError("O nome do executavel nao confere com o protegido.");
	}

	CCRC32 CRC32;
	DWORD clientCRC = 0;

	if (!CRC32.FileCRC(modulePath, &clientCRC, 1024))
	{
		this->SecurityError("Falha ao calcular o CRC do cliente.");
	}

	if (this->m_MainInfo.ClientCRC32 != clientCRC)
	{
		this->SecurityError("CRC do cliente nao confere.");
	}
}

void CProtect::CheckPluginFile()
{
	// plugin opcional
	if (this->m_MainInfo.PluginName[0] == 0)
	{
		return;
	}

	if (strcmp(this->m_MainInfo.PluginName, "\"\"") == 0)
	{
		return;
	}

	if (this->m_MainInfo.PluginCRC32 == 0)
	{
		return;
	}

	CCRC32 CRC32;
	DWORD pluginCRC = 0;

	if (!CRC32.FileCRC(this->m_MainInfo.PluginName, &pluginCRC, 1024))
	{
		this->SecurityError("Falha ao calcular o CRC da plugin.");
	}

	if (this->m_MainInfo.PluginCRC32 != pluginCRC)
	{
		this->SecurityError("CRC da plugin nao confere.");
	}

	HMODULE module = GetModuleHandleA(this->m_MainInfo.PluginName);

	if (module != NULL)
	{
		this->SecurityError("A plugin ja esta carregada.");
	}

	module = LoadLibraryA(this->m_MainInfo.PluginName);

	if (module == NULL)
	{
		this->SecurityError("Falha ao carregar a plugin.");
	}

	char loadedPath[MAX_PATH] = { 0 };

	if (GetModuleFileNameA(module, loadedPath, MAX_PATH) == 0)
	{
		this->SecurityError("Falha ao obter o caminho da plugin carregada.");
	}

	pluginCRC = 0;

	if (!CRC32.FileCRC(loadedPath, &pluginCRC, 1024))
	{
		this->SecurityError("Falha ao recalcular o CRC da plugin carregada.");
	}

	if (this->m_MainInfo.PluginCRC32 != pluginCRC)
	{
		this->SecurityError("CRC da plugin carregada nao confere.");
	}

	void(*EntryProc)() = (void(*)())GetProcAddress(module, "FireTeam");

	if (EntryProc == 0)
	{
		this->SecurityError("Export FireTeam nao encontrada na plugin.");
	}

	EntryProc();
}