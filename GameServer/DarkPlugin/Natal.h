#pragma once

struct sNatal
{
	int					_Day;
	int					_Hours;
	int					_Minutes;
	int					_Monster;
	int					_Duration;
	int                 _Map;
	int                 _X;
	int                 _Y;
	int                 _QNTD[2];
	BYTE				_Type;
	BYTE				_Index;
	BYTE				_Level;
	BYTE				_Skill;
	BYTE				_Luck;
	BYTE				_Option;
	BYTE				_Excelente;
	BYTE                _Quantity;
};

class cNatal
{
public:
	char _Syntax[10][25];
	cNatal();

public:
	bool Load();
	void Run();
	void Disappear();
	void Santa(int aIndex);
	void Globin(int aIndex);
	void StartManual();

public:
	bool					_Active;
	bool                    _Sended;
	int                     _Class[2];
	
	int                     _Total[2];
	int                     _Count[2];
	BYTE                    _Mapa;
	short                   _X;
	short                   _Y;
	char                    _Buffer[255];

private:
	sNatal			        NatalStruct[1000];
};

extern cNatal Natal;


