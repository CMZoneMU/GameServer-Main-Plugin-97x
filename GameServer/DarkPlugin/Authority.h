#pragma once

struct sAuthority
{
	char Name[11];
	int  Type[16];
};

class cAuthority
{
public:
	bool Load();
	bool Check(LPOBJ lpObj, unsigned Value);

private:
	int  Count;

private:
	sAuthority		AuthorityStruct[1000];
};

extern cAuthority Authority;