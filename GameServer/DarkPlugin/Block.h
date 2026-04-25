#pragma once

struct sBlock
{
	int                     _Active;
	char                    _Password[50];
};

class cBlock
{
public:
	bool Load();
	void Run(int aIndex, char* msg);

public:
	bool                    _Active;
	char                    _Password[5];
	char                    _Name[255];
	char                    _Syntax[25];

public:
	sBlock                  BlockStruct[OBJECT_MAX];
};

extern cBlock Block;