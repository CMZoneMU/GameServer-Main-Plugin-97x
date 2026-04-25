#include "StdAfx.h"

bool cBoxWings::Load()
{
	this->_Count = 0;

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Box's/01 - Box Of Wings.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			WingsStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			WingsStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			WingsStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			WingsStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			WingsStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			WingsStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			WingsStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->_Count++;
		}
	}

	return true;
}

bool cBoxWings::Item(int aIndex)
{
	if (this->_Count == 0)
	{
		return false;
	}

	srand(time(NULL));

	int Sortear = rand() % this->_Count;

	for (int i = 0; i < this->_Count; i++)
	{
		if (this->WingsStruct[i]._Index == this->WingsStruct[Sortear]._Index)
		{
			int Item = ITEMGET(this->WingsStruct[i]._Type, this->WingsStruct[i]._Index);

			ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->WingsStruct[i]._Level, 0, this->WingsStruct[i]._Skill, this->WingsStruct[i]._Luck, this->WingsStruct[i]._Option, aIndex, this->WingsStruct[i]._Excelente);
		}
	}

	return true;
}

cBoxWings BoxWings;