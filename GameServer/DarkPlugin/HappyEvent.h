#pragma once

struct sHappy
{
	int                     _Day;
	int                     _Hours;
	int                     _Minutes;
	int                     _Duration;
	int                     _Experience;
};

class cHappy
{
public:
	cHappy();

public:
	bool Load();
	void Run();
	void Finish();

public:
	bool                    _Active;
	bool                    _Event;
	int                     _Experience;
	int                     _Count;

public:
	sHappy			        HappyStruct[255];
};

extern cHappy HappyEvent;