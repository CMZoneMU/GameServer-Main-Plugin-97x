#include "StdAfx.h"

bool cBoxWeapons::Load()
{
	this->_Count = 0;

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Box's/03 - Box Of Weapons"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			WeaponsStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			WeaponsStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			WeaponsStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			WeaponsStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			WeaponsStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			WeaponsStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			WeaponsStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->_Count++;
		}
	}

	return true;
}

bool cBoxWeapons::Item(int aIndex)
{
	if (this->_Count == 0)
	{
		return false;
	}

	int Level, Luck, Skill, Option, Excelente;

	srand(time(NULL));

	int Sortear = rand() % this->_Count;

	if (this->WeaponsStruct[Sortear]._Level == -1)
	{
		Level = Func.Rand(0, 16);
	}
	else
	{
		Level = this->WeaponsStruct[Sortear]._Level;
	}

	if (this->WeaponsStruct[Sortear]._Skill == -1)
	{
		Skill = Func.Rand(0, 2);
	}
	else
	{
		Skill = this->WeaponsStruct[Sortear]._Skill;
	}

	if (this->WeaponsStruct[Sortear]._Luck == -1)
	{
		Luck = Func.Rand(0, 2);
	}
	else
	{
		Luck = this->WeaponsStruct[Sortear]._Luck;
	}

	if (this->WeaponsStruct[Sortear]._Option == -1)
	{
		Option = Func.Rand(0, 8);
	}
	else
	{
		Option = this->WeaponsStruct[Sortear]._Option;
	}

	if (this->WeaponsStruct[Sortear]._Excelente == -1)
	{
		int  Option[] = { 1, 2, 4, 8, 16, 32, 42, 63 };

		Excelente = Option[Func.Rand(0, 9)];
	}
	else
	{
		Excelente = this->WeaponsStruct[Sortear]._Excelente;
	}

	int Item = ITEMGET(WeaponsStruct[Sortear]._Type, WeaponsStruct[Sortear]._Index);

	ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, Level, 0, Skill, Luck, Option, aIndex, Excelente);

	return true;
}

cBoxWeapons BoxWeapons;