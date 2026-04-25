#pragma once

struct sBlood
{
	BYTE				_Type[7];
	BYTE				_Index[7];
	BYTE				_Level[7];
	BYTE				_Skill[7];
	BYTE				_Luck[7];
	BYTE				_Option[7];
	BYTE				_Excelente[7];
};

class BloodEvent
{
public:
	bool Load();
	void Item(LPOBJ lpObj, char Vector);
	static void DropChaosGem(int aIndex);

private:
	int                 _Count[6];

private:
	sBlood			    BloodStruct[1000];
};

extern BloodEvent Blood;