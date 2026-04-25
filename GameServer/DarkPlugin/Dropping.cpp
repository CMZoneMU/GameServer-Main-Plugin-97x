#include "StdAfx.h"

bool cDropping::Load()
{
	this->_Count = 0;

	memset(this->DropStruct, 0, sizeof(this->DropStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Dropping.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->DropStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->DropStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->DropStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			this->DropStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			this->DropStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			this->DropStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			this->DropStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->DropStruct[this->_Count]._MapNumber = Section.Rows[i].GetInt(7);
			this->DropStruct[this->_Count]._Monster = Section.Rows[i].GetInt(8);
			this->DropStruct[this->_Count]._Min = Section.Rows[i].GetInt(9);
			this->DropStruct[this->_Count]._Max = Section.Rows[i].GetInt(10);
			this->DropStruct[this->_Count]._Percent = Section.Rows[i].GetInt(11);
			this->_Count++;
		}
	}

	return true;
}

BOOL cDropping::gObjDrop(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	int aIndex = gObjMonsterTopHitDamageUser(lpObj);

	int MapNumber, Monster, Luck, Skill, Option, Excelente;

	for (int i = 0; i < Drop._Count; i++)
	{
		if (Drop.DropStruct[i]._MapNumber == -1)
		{
			MapNumber = lpObj->MapNumber;
		}
		else
		{
			MapNumber = Drop.DropStruct[i]._MapNumber;
		}

		if (Drop.DropStruct[i]._Monster == -1)
		{
			Monster = lpObj->Class;
		}
		else
		{
			Monster = Drop.DropStruct[i]._Monster;
		}

		if (Drop.DropStruct[i]._Luck == -1)
		{
			Luck = Func.Rand(0, 2);
		}
		else
		{
			Luck = Drop.DropStruct[i]._Luck;
		}

		if (Drop.DropStruct[i]._Skill == -1)
		{
			Skill = Func.Rand(0, 2);
		}
		else
		{
			Skill = Drop.DropStruct[i]._Skill;
		}

		if (Drop.DropStruct[i]._Option == -1)
		{
			Option = Func.Rand(0, 8);
		}
		else
		{
			Option = Drop.DropStruct[i]._Option;
		}

		if (Drop.DropStruct[i]._Excelente == -1)
		{
			int  Option[] = { 1, 2, 4, 8, 16, 32, 42, 63 };

			Excelente = Option[Func.Rand(0, 9)];
		}
		else
		{
			Excelente = Drop.DropStruct[i]._Excelente;
		}

		if (lpObj->MapNumber == MapNumber)
		{
			if (lpObj->Class == Monster)
			{
				if (lpObj->Level >= Drop.DropStruct[i]._Min && lpObj->Level <= Drop.DropStruct[i]._Max)
				{
					if (rand() % 10000 <= Drop.DropStruct[i]._Percent)
					{
						int Item = ITEMGET(Drop.DropStruct[i]._Type, Drop.DropStruct[i]._Index);

						ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, lpObj->X, lpObj->Y, Item, Drop.DropStruct[i]._Level, 0, Skill, Luck, Option, aIndex, Excelente);
						return true;
					}
				}
			}
		}
	}

	return gEventMonsterItemDrop(lpObj, lpTargetObj);
}

cDropping Drop;