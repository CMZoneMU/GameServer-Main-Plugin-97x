#pragma once

struct sDrop
{
	int					_MapNumber;
	int					_Monster;
	int					_Type;
	int					_Index;
	int					_Level;
	int					_Skill;
	int					_Luck;
	int					_Option;
	int					_Excelente;
	int					_Min;
	int					_Max;
	int					_Percent;
};

class cDropping
{
public:
	bool Load();
	static BOOL gObjDrop(LPOBJ lpObj, LPOBJ lpTargetObj);

public:
	int					_Count;

	sDrop			    DropStruct[1000];
};

extern cDropping Drop;