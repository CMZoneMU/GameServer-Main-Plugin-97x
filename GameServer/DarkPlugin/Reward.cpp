#include "StdAfx.h"

cReward::cReward() : _Active(false)
{
}

bool cReward::Load()
{
	this->_Count = 0;

	memset(this->RewardStruct, 0, sizeof(this->RewardStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Reward.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->RewardStruct[this->_Count]._Day = Section.Rows[i].GetInt(0);
			this->RewardStruct[this->_Count]._Amount = Section.Rows[i].GetInt(1);
			strcpy_s(this->RewardStruct[this->_Count]._Column, sizeof(this->RewardStruct[this->_Count]._Column), (Section.Rows[i].GetStringPtr(2)));
			strcpy_s(this->RewardStruct[this->_Count]._Coin, sizeof(this->RewardStruct[this->_Count]._Coin), (Section.Rows[i].GetStringPtr(3)));
			this->_Count++;
		}
	}

	return true;
}


void cReward::Connect(int aIndex)
{
	if (this->_Active == true)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		for (int i = 0; i < this->_Count; i++)
		{
			if (Now.wDayOfWeek == this->RewardStruct[i]._Day && Custom[aIndex].Day == 0)
			{
				Func.Golden(aIndex, "Esta é sua primeira conexão!");
				Func.Golden(aIndex, "Parabéns, prêmio: %d %s.", this->RewardStruct[i]._Amount, this->RewardStruct[i]._Coin);

				Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s + %d WHERE memb___id = '%s'", this->RewardStruct[i]._Column, this->RewardStruct[i]._Column, this->RewardStruct[i]._Amount, gObj[aIndex].AccountID);

				Custom[aIndex].Day = 1;

				Manager.ExecFormat("UPDATE MEMB_INFO SET Day = Day + 1 WHERE memb___id = '%s'", gObj[aIndex].AccountID);

				Manager.CoinCount(aIndex, gObj[aIndex].AccountID);
			}
		}
	}
}

void cReward::Run(LPOBJ lpObj)
{
	if (this->_Active == true)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		if (Now.wHour == 00 && Now.wMinute == 01 && Now.wSecond == 0)
		{
			Manager.ExecFormat("UPDATE MEMB_INFO SET Day = '0'");

			Custom[lpObj->m_Index].Day = 0;

			this->Connect(lpObj->m_Index);
		}
	}
}

cReward Reward;