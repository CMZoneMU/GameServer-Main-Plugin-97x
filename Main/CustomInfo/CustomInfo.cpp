#include "stdafx.h"
#include <direct.h>

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

static void CreateDirectoryTree()
{
	// [ Novo ]: Caminho atualizado para criar a pasta "Data" e subpastas "Custom" e "CustomInfo" 
	// dentro dela, para organizar melhor os arquivos gerados.
	CreateDirectoryA(".\\Data", 0);
	CreateDirectoryA(".\\Data\\Custom", 0);
	CreateDirectoryA(".\\Data\\Custom\\CustomInfo", 0);
}

static bool FileExists(const char* path)
{
	DWORD attr = GetFileAttributesA(path);
	return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
}

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

int main()
{
	CreateDirectoryTree();

	MAIN_FILE_INFO info;
	memset(&info, 0, sizeof(info));

	// [ Novo ]: Leitura das configurações do arquivo "CustomInfo.ini"
	// usando as funções GetPrivateProfileStringA e GetPrivateProfileIntA.
	GetPrivateProfileStringA("CustomInfo", "IpAddress", "", info.IpAddress, sizeof(info.IpAddress), ".\\CustomInfo.ini");
	info.IpAddressPort = (WORD)GetPrivateProfileIntA("CustomInfo", "IpAddressPort", 44405, ".\\CustomInfo.ini");
	GetPrivateProfileStringA("CustomInfo", "ClientSerial", "", info.ClientSerial, sizeof(info.ClientSerial), ".\\CustomInfo.ini");
	GetPrivateProfileStringA("CustomInfo", "ScreenShotPath", "", info.ScreenShotPath, sizeof(info.ScreenShotPath), ".\\CustomInfo.ini");
	GetPrivateProfileStringA("CustomInfo", "ClientName", "", info.ClientName, sizeof(info.ClientName), ".\\CustomInfo.ini");
	GetPrivateProfileStringA("CustomInfo", "PluginName", "", info.PluginName, sizeof(info.PluginName), ".\\CustomInfo.ini");

	NormalizeString(info.ClientName);
	NormalizeString(info.PluginName);

	// [ Novo ]: Verificação se o campo "ClientName" foi configurado no arquivo "CustomInfo.ini".
	if (info.ClientName[0] == 0)
	{
		std::cout << "Error: ClientName não configurado no ini!" << std::endl;
		system("pause");
		return 1;
	}

	char fullClient[MAX_PATH] = { 0 };
	char fullPlugin[MAX_PATH] = { 0 };

	wsprintfA(fullClient, ".\\%s", info.ClientName);

	// [ Novo ]: Verificação se o arquivo do cliente existe na mesma pasta do "CustomInfo.exe" usando a função FileExists.
	if (!FileExists(fullClient))
	{
		std::cout << "ERROR: Cliente nao encontrado na mesma pasta do CustomInfo.exe!" << std::endl;
		std::cout << "Path: " << fullClient << std::endl;
		system("pause");
		return 2;
	}

	CCRC32 CRC32;

	// [ Novo ]: Cálculo do CRC32 do arquivo do cliente usando a função FileCRC da classe CCRC32.
	if (CRC32.FileCRC(fullClient, &info.ClientCRC32, 1024) == 0)
	{
		std::cout << "Error: Não foi possível ler o CRC do arquivo do cliente." << std::endl;
		std::cout << "Path: " << fullClient << std::endl;
		system("pause");
		return 3;
	}

	// [ Novo ]: Opção para configurar um plugin opcional no arquivo 
	// "CustomInfo.ini". Se o campo "PluginName" estiver preenchido, 
	// o programa irá verificar se o arquivo do plugin 
	// existe e calcular seu CRC32. Caso contrário, o campo "PluginCRC32" 
	// será definido como 0 e "PluginName" será zerado.
	if (info.PluginName[0] != 0)
	{
		wsprintfA(fullPlugin, ".\\%s", info.PluginName);

		if (!FileExists(fullPlugin))
		{
			std::cout << "Error: Plugin nao encontrada na mesma pasta do CustomInfo.exe!" << std::endl;
			std::cout << "Path: " << fullPlugin << std::endl;
			system("pause");
			return 4;
		}

		// [ Novo ]: Cálculo do CRC32 do arquivo do plugin usando a função FileCRC da classe CCRC32.
		if (CRC32.FileCRC(fullPlugin, &info.PluginCRC32, 1024) == 0)
		{
			std::cout << "Error: Não foi possível ler o CRC do arquivo do plugin." << std::endl;
			std::cout << "Path: " << fullPlugin << std::endl;
			system("pause");
			return 5;
		}
	}
	else
	{
		info.PluginCRC32 = 0;
		memset(info.PluginName, 0, sizeof(info.PluginName));
	}

	BYTE XorKey[20] = {
		0x9E, 0x98, 0x12, 0x2B, 0xB6,
		0x76, 0xF6, 0x5B, 0x76, 0x4D,
		0x08, 0xF2, 0xAB, 0xDF, 0x91,
		0xB6, 0x4C, 0x1C, 0x93, 0x2F
	};

	for (int n = 0; n < (int)sizeof(MAIN_FILE_INFO); n++)
	{
		((BYTE*)&info)[n] ^= (BYTE)(XorKey[n % 20] ^ LOBYTE(n));
		((BYTE*)&info)[n] -= (BYTE)(XorKey[n % 20] ^ HIBYTE(n));
		((BYTE*)&info)[n] += (BYTE)(XorKey[n % 20] ^ HIBYTE(n));
	}

	// [ Novo ]: Definição do caminho de saída do arquivo "CustomInfo.cmz" 
	// dentro da pasta "Data\\Custom\\CustomInfo" criada anteriormente, 
	// para organizar melhor os arquivos gerados.
	const char* outputFile = ".\\Data\\Custom\\CustomInfo\\CustomInfo.cmz";

	HANDLE file = CreateFileA(outputFile,GENERIC_WRITE,FILE_SHARE_READ,0,	CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);

	// [ Novo ]: Verificação se o arquivo "CustomInfo.cmz" 
	// foi criado com sucesso usando a função CreateFileA.
	if (file == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();

		std::cout << "Error: Não foi possível criar o arquivo.." << std::endl;
		std::cout << "Path: " << outputFile << std::endl;
		std::cout << "GetLastError: " << error << std::endl;
		system("pause");
		return 6;
	}

	DWORD OutSize = 0;

	if (WriteFile(file, &info, sizeof(MAIN_FILE_INFO), &OutSize, 0) == 0)
	{
		DWORD error = GetLastError();
		CloseHandle(file);

		// [ Novo ]: Verificação se o arquivo "CustomInfo.cmz" 
		// foi gravado com sucesso usando a função WriteFile.
		std::cout << "Error: Não foi possível gravar o arquivo." << std::endl;
		std::cout << "GetLastError: " << error << std::endl;
		system("pause");
		return 7;
	}

	CloseHandle(file);

	std::cout << "=================================================================" << std::endl;
	std::cout << "===       Sistema Base GetMainInfo MuEmu para 97+99           ===" << std::endl;
	std::cout << "===           Creditos Adaptacao: NiloMaster CMZ              ===" << std::endl;
	std::cout << "=================================================================" << std::endl;
	std::cout << "Sistema: Arquivo criado com Sucesso." << std::endl;
	std::cout << "Sistema: " << outputFile << std::endl;
	std::cout << "Aviso: Agora copie somente a pasta Data para dentro do cliente." << std::endl;

	system("pause");
	return 0;
}