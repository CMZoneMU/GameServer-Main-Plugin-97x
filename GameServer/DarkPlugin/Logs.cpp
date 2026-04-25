#include "StdAfx.h"

void Log(char * Text)
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	FILE * stream;

	TCHAR String[512];

	wsprintf(String, "SQL_LOG\\%02d%02d%02d_SQL.txt", t.wYear, t.wMonth, t.wDay);

	stream = fopen(String, "a+");

	fprintf(stream, "%02d:%02d:%02d - %s\n", t.wHour, t.wMinute, t.wSecond, Text);

	fclose(stream);
}

void Log2(char * Text, ...)
{
	char Buffer[250];
	va_list pArguments;

	va_start(pArguments, Text);
	vsprintf(&Buffer[0], Text, pArguments);
	va_end(pArguments);

	SYSTEMTIME t;
	GetLocalTime(&t);

	FILE * stream;

	TCHAR String[512];

	wsprintf(String, "GM_LOG\\%02d-%02d-%02d_GameMaster.txt", t.wYear, t.wMonth, t.wDay);

	stream = fopen(String, "a+");

	fprintf(stream, "%02d:%02d:%02d - %s\n", t.wHour, t.wMinute, t.wSecond, Buffer);

	fclose(stream);
}