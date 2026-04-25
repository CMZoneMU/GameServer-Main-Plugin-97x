#pragma once

struct sRing
{
	int				     _Killer;
};

class cRing
{
public:
	bool Load();
	void Killer(LPOBJ lpObj, LPOBJ Target);
	void Quit(LPOBJ lpObj);

public:
	bool				 _Active;

public:
	sRing		         RingStruct[OBJECT_MAX];
};

extern cRing Ring;