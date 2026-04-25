#pragma once

struct sRoleta
{
	BYTE                    _Quantity;
	BYTE			        _Type;
	BYTE				    _Index;
	BYTE				    _Level;
	BYTE				    _Skill;
	BYTE				    _Luck;
	BYTE				    _Option;
	BYTE				    _Excelente;
	char                    _Name[255];
};

class cRoleta
{
public:
	cRoleta();

public:
	bool Load();
	void Command(int aIndex);

public:
	bool				    _Active;
	int                     _Count;
	int						_Reward;
	int						_Amount;
	char                    _Name[255];
	char                    _Syntax[25];

private:
	sRoleta                 RoletaStruct[1000];
};

extern cRoleta Roleta;