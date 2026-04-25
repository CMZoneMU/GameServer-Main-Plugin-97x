#include "StdAfx.h"

cCoinEvent::cCoinEvent() : _Active(false)
{
}

bool cCoinEvent::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/CoinEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Amount = Section.Rows[0].GetInt(1);
		strcpy_s(this->_NameCoin, sizeof(this->_NameCoin), (Section.Rows[0].GetStringPtr(2)));
	}

	return true;
}

void cCoinEvent::Run(LPOBJ lpObj)
{
	if (this->_Active && lpObj->Type == PLAYER)
	{
		if (this->_Time > 0 && (this->_Time % 60) == 0)
		{
			Custom[lpObj->m_Index].Hours++; this->_Time = 0;

			if (Custom[lpObj->m_Index].Hours >= 60 && (Custom[lpObj->m_Index].Hours % 60) == 0)
			{
				int Hour = Custom[lpObj->m_Index].Hours / 60;

				Func.MsgOutput(lpObj->m_Index, 1, "Você está a %d hora(s) online!", Hour);
				Func.MsgOutput(lpObj->m_Index, 1, "Prêmio: %d %s.", this->_Amount, this->_NameCoin);

				Manager.ExecFormat(Query._Query[21], lpObj->Name);

				Manager.ExecFormat(Query._Query[22], this->_Amount, lpObj->AccountID);
			}
		}
		else
		{
			this->_Time++;
		}
	}
}

void cCoinEvent::Quit(LPOBJ lpObj)
{
	if (this->_Active && lpObj->Type == PLAYER)
	{
		Custom[lpObj->m_Index].Hours = 0;
	}
}

cCoinEvent CoinEvent;