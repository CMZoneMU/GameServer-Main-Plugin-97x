#include "StdAfx.h"

bool cAuthority::Load()
{
	this->Count = 0;

	memset(this->AuthorityStruct, 0, sizeof(this->AuthorityStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Authority.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			strcpy_s(this->AuthorityStruct[this->Count].Name, sizeof(this->AuthorityStruct[this->Count].Name), (Section.Rows[i].GetStringPtr(0)));

			this->AuthorityStruct[this->Count].Type[0] = Section.Rows[i].GetInt(1);
			this->AuthorityStruct[this->Count].Type[1] = Section.Rows[i].GetInt(2);
			this->AuthorityStruct[this->Count].Type[2] = Section.Rows[i].GetInt(3);
			this->AuthorityStruct[this->Count].Type[3] = Section.Rows[i].GetInt(4);
			this->AuthorityStruct[this->Count].Type[4] = Section.Rows[i].GetInt(5);
			this->AuthorityStruct[this->Count].Type[5] = Section.Rows[i].GetInt(6);
			this->AuthorityStruct[this->Count].Type[6] = Section.Rows[i].GetInt(7);
			this->AuthorityStruct[this->Count].Type[7] = Section.Rows[i].GetInt(8);
			this->AuthorityStruct[this->Count].Type[8] = Section.Rows[i].GetInt(9);
			this->AuthorityStruct[this->Count].Type[9] = Section.Rows[i].GetInt(10);
			this->AuthorityStruct[this->Count].Type[10] = Section.Rows[i].GetInt(11);
			this->AuthorityStruct[this->Count].Type[11] = Section.Rows[i].GetInt(12);
			this->AuthorityStruct[this->Count].Type[12] = Section.Rows[i].GetInt(13);
			this->AuthorityStruct[this->Count].Type[13] = Section.Rows[i].GetInt(14);
			this->AuthorityStruct[this->Count].Type[14] = Section.Rows[i].GetInt(15);
			this->AuthorityStruct[this->Count].Type[15] = Section.Rows[i].GetInt(16);
			this->Count++;
		}
	}

	return true;
}

bool cAuthority::Check(LPOBJ lpObj, unsigned Value)
{
	if (lpObj->AuthorityCode > 1)
	{
		for (int i = 0; i < this->Count; i++)
		{
			if (strcmp(lpObj->Name, AuthorityStruct[i].Name) == 0)
			{
				if (AuthorityStruct[i].Type[Value] == 0)
				{
					return false;
				}

				return true;
			}
		}
	}

	return false;
}

cAuthority Authority;