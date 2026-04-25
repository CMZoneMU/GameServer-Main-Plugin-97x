#pragma once

class cCollector
{
public:
	bool Load();
	void Talk(OBJECTSTRUCT* Npc, OBJECTSTRUCT* lpObj);

private:
	bool				_Active;
	int                 _Section;
	int				    _Type[6];
	int				    _Index[6];
	int				    _Level[6];
	int				    _Quantity[6];
	int                 _Value[6];
	char                _Name[6][60];
	char                _Coin[6][60];
	char                _Buffer[60];
};

extern cCollector Collector;