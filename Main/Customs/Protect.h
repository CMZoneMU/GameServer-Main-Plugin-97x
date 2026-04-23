#pragma once

struct MAIN_FILE_INFO
{
	char IpAddress[32];
	WORD IpAddressPort;
	char ClientSerial[17];
	char ScreenShotPath[50];
	char ClientName[32];
	DWORD ClientCRC32;
	DWORD PluginCRC32;
	char PluginName[32];
};

class CProtect
{
public:
	CProtect();
	~CProtect();

	bool ReadMainFile(char* name);

	void CheckClientFile();
	void CheckPluginFile();
	void CheckInstance();

	const char* ConvertModuleFileName(const char* path);
	void SecurityError(const char* message);

public:
	MAIN_FILE_INFO m_MainInfo;
	DWORD m_ClientFileCRC;
	HANDLE m_InstanceMutex;
};

extern CProtect gProtect;