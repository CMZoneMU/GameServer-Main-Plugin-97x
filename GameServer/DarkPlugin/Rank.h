#pragma once

struct sRank
{
	char				 _Name[255];
	char                 _Column[4][512];
};

class cRank
{
public:
	cRank();

public:
	bool Load();
	void Command(int aIndex, char* msg);

public:
	bool				 _Active;
	bool                 _Success;
	int                  _Number;
	int                  _List;
	int                  _Count;
	char                 _Name[2][255];
	char                 _Syntax[25];

private:
	sRank		         RankStruct[255];
};

extern cRank Rank;