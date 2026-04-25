#include "StdAfx.h"

bool cRing::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Ring.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
	}

	return true;
}

void cRing::Killer(LPOBJ lpObj, LPOBJ Target)
{
	if (lpObj->Type == PLAYER && Target->Type == PLAYER)
	{
		if (lpObj->X >= 139 && lpObj->X <= 148 && lpObj->Y >= 123 && lpObj->Y <= 132)
		{
			if (lpObj->m_PK_Level < 3 || lpObj->m_PK_Level > 3)
			{
				this->RingStruct[lpObj->m_Index]._Killer++;
			}
		}
	}
}

void cRing::Quit(LPOBJ lpObj)
{
	if (this->RingStruct[lpObj->m_Index]._Killer > 0 && lpObj->Type == PLAYER)
	{
		Manager.ExecFormat(Query._Query[31], this->RingStruct[lpObj->m_Index]._Killer, lpObj->Name);

		this->RingStruct[lpObj->m_Index]._Killer = 0;
	}
}

cRing Ring;