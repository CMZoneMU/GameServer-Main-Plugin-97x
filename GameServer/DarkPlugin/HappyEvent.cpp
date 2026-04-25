#include "StdAfx.h"

cHappy::cHappy() : _Active(false)
{
}

bool cHappy::Load()
{
	this->_Count = 0;

	memset(this->HappyStruct, 0, sizeof(this->HappyStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/HappyEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->HappyStruct[this->_Count]._Day = Section.Rows[i].GetInt(0);
			this->HappyStruct[this->_Count]._Hours = Section.Rows[i].GetInt(1);
			this->HappyStruct[this->_Count]._Minutes = Section.Rows[i].GetInt(2);
			this->HappyStruct[this->_Count]._Experience = Section.Rows[i].GetInt(3);
			this->HappyStruct[this->_Count]._Duration = Section.Rows[i].GetInt(4) * 60 * 1000;
			this->_Count++;
		}
	}

	return true;
}

void cHappy::Run()
{
	if (this->_Active)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		for (int i = 0; i < this->_Count; i++)
		{
			if (Now.wDayOfWeek == this->HappyStruct[i]._Day && Now.wHour == this->HappyStruct[i]._Hours && Now.wMinute == this->HappyStruct[i]._Minutes && Now.wSecond == 0)
			{
				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 5 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 4 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 3 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 2 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 1 Minuto(s)");
					}
				}

				Sleep(60000);

				this->_Experience = this->HappyStruct[i]._Experience;

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Func.MsgOutput(Index, 0, "O evento começou, reset no lugar e em dobro!");
						Func.MsgOutput(Index, 0, "Experiência aumentada em %d%%", this->_Experience);
					}
				}

				this->_Event = true;

				Sleep(this->HappyStruct[i]._Duration);

				this->Finish();
			}
		}
	}
}

void cHappy::Finish()
{
	for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
	{
		if (gObj[Index].Connected == 3)
		{
			Func.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
			Func.MsgOutput(Index, 0, "Evento encerrado.");
		}
	}

	this->_Event = false;

	this->_Experience = 0;
}

cHappy HappyEvent;