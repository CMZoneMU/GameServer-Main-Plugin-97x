#include "StdAfx.h"

cRaffleEvent::cRaffleEvent() : _Active(false)
{
}

bool cRaffleEvent::Load()
{
	this->_Count[0] = 0; this->_Count[1] = 0;

	memset(this->RaffleStruct, 0, sizeof(this->RaffleStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/RaffleEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->RaffleStruct[this->_Count[0]]._Day = Section.Rows[i].GetInt(0);
			this->RaffleStruct[this->_Count[0]]._Hours = Section.Rows[i].GetInt(1);
			this->RaffleStruct[this->_Count[0]]._Minutes = Section.Rows[i].GetInt(2);
			this->RaffleStruct[this->_Count[0]]._Amount = Section.Rows[i].GetInt(3);
			strcpy_s(RaffleStruct[this->_Count[0]]._NameCoin, sizeof(RaffleStruct[this->_Count[0]]._NameCoin), (Section.Rows[i].GetStringPtr(4)));
			this->_Count[0]++;
		}
	}

	return true;
}

void cRaffleEvent::Run()
{
	if (this->_Active)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		for (int i = 0; i < this->_Count[0]; i++)
		{
			if (Now.wDayOfWeek == this->RaffleStruct[i]._Day && Now.wHour == this->RaffleStruct[i]._Hours && Now.wMinute == this->RaffleStruct[i]._Minutes && Now.wSecond == 0)
			{
				this->_Count[1] = 0;

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3 && gObj[Index].AuthorityCode == 0)
					{
						this->_Received[this->_Count[1]++] = Index;
					}
				}

				if (this->_Count[1] > 0)
				{
					int Sortear = rand() % this->_Count[1];

					int Target = this->_Received[Sortear];

					for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
					{
						if (gObj[Index].Connected == 3)
						{
							Func.MsgOutput(Index, 0, "[   SORTEIO   ]");
							Func.MsgOutput(Index, 0, "%s foi sorteado(a) com %d %s!", gObj[Target].Name, this->RaffleStruct[i]._Amount, this->RaffleStruct[i]._NameCoin);
						}
					}

					Func.MsgOutput(Target, 1, "Você foi sorteado(a) com %d %s!", this->RaffleStruct[i]._Amount, this->RaffleStruct[i]._NameCoin);

					Manager.ExecFormat(Query._Query[23], gObj[Target].Name);
					Manager.ExecFormat(Query._Query[24], this->RaffleStruct[i]._Amount, gObj[Target].AccountID);
				}
			}
		}
	}
}

cRaffleEvent RaffleEvent;