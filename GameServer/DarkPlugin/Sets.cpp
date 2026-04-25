#include "StdAfx.h"

bool cBoxSets::Load()
{
	this->_Count = 0;

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Box's/05 - Box Of Sets.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			SetsStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			SetsStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			SetsStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			SetsStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			SetsStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			SetsStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			SetsStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->_Count++;
		}
	}

	return true;
}

bool cBoxSets::Item(int aIndex)
{
	if (this->_Count == 0)
	{
		return false;
	}

	int Level, Luck, Skill, Option, Excelente;

	srand(time(NULL));

	int Sortear = rand() % this->_Count;

	if (this->SetsStruct[Sortear]._Level == -1)
	{
		Level = Func.Rand(0, 16);
	}
	else
	{
		Level = this->SetsStruct[Sortear]._Level;
	}

	if (this->SetsStruct[Sortear]._Skill == -1)
	{
		Skill = Func.Rand(0, 2);
	}
	else
	{
		Skill = this->SetsStruct[Sortear]._Skill;
	}

	if (this->SetsStruct[Sortear]._Luck == -1)
	{
		Luck = Func.Rand(0, 2);
	}
	else
	{
		Luck = this->SetsStruct[Sortear]._Luck;
	}

	if (this->SetsStruct[Sortear]._Option == -1)
	{
		Option = Func.Rand(0, 8);
	}
	else
	{
		Option = this->SetsStruct[Sortear]._Option;
	}

	if (this->SetsStruct[Sortear]._Excelente == -1)
	{
		int  Option[] = { 1, 2, 4, 8, 16, 32, 42, 63 };

		Excelente = Option[Func.Rand(0, 9)];
	}
	else
	{
		Excelente = this->SetsStruct[Sortear]._Excelente;
	}

	int Item = ITEMGET(SetsStruct[Sortear]._Type, SetsStruct[Sortear]._Index);

	ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, Level, 0, Skill, Luck, Option, aIndex, Excelente);

	return true;
}

cBoxSets BoxSets;