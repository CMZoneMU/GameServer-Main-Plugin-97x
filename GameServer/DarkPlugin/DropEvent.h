#pragma once

struct sDropEvent
{
	int					_Day;
	int					_Hours;
	int					_Minutes;
	int					_Duration;
	int                 _MapNumber[2];
	int                 _X;
	int                 _Y;
	BYTE				_Type;
	BYTE				_Index;
	BYTE				_Level;
	BYTE				_Skill;
	BYTE				_Luck;
	BYTE				_Option;
	BYTE				_Excelente;
};

class cDropEvent
{
public:
	char _Syntax[10][25];
	bool Load();
	void Run();
	static void Repeat(void* lpParam);
	void Mapa(int MapNumber);
	void StartManual();

public:
	bool                _Active[2];
	int                 _Count[2];
	int                 _MapNumber;
	const char*			_MapName;
	

private:
	sDropEvent			EventStruct[1000];
};

extern cDropEvent DropEvent;


