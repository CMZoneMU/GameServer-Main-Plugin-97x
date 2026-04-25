#include "StdAfx.h"

bool cOffline::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Offline.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(1)));
	}

	return true;
}

void cOffline::Command(int aIndex)
{
	if (this->_Active)
	{
		this->PlayerStruct[aIndex]._Offline = true;

		gObjCloseSet(aIndex, 0);
	}
}

cOffline Offline;