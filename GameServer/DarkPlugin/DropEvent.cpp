#include "StdAfx.h"

bool cDropEvent::Load()
{
	for (int i = 0; i < 2; i++)
	{
		this->_Count[i] = 0;
	}

	memset(this->EventStruct, 0, sizeof(this->EventStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/DropEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active[0] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[2], sizeof(this->_Syntax[2]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Syntax[3], sizeof(this->_Syntax[3]), (Section.Rows[0].GetStringPtr(2)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->EventStruct[this->_Count[0]]._Day = Section.Rows[i].GetInt(0);
			this->EventStruct[this->_Count[0]]._Hours = Section.Rows[i].GetInt(1);
			this->EventStruct[this->_Count[0]]._Minutes = Section.Rows[i].GetInt(2);
			this->EventStruct[this->_Count[0]]._Duration = Section.Rows[i].GetInt(3) * 60 * 1000;
			this->EventStruct[this->_Count[1]]._MapNumber[0] = Section.Rows[i].GetInt(4);
			this->_Count[0]++;
		}
	}

	if (Group.GetSection(2, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->EventStruct[this->_Count[1]]._MapNumber[1] = Section.Rows[i].GetInt(0);
			this->EventStruct[this->_Count[1]]._X = Section.Rows[i].GetInt(1);
			this->EventStruct[this->_Count[1]]._Y = Section.Rows[i].GetInt(2);
			this->EventStruct[this->_Count[1]]._Type = Section.Rows[i].GetInt(3);
			this->EventStruct[this->_Count[1]]._Index = Section.Rows[i].GetInt(4);
			this->EventStruct[this->_Count[1]]._Level = Section.Rows[i].GetInt(5);
			this->EventStruct[this->_Count[1]]._Luck = Section.Rows[i].GetInt(6);
			this->EventStruct[this->_Count[1]]._Skill = Section.Rows[i].GetInt(7);
			this->EventStruct[this->_Count[1]]._Option = Section.Rows[i].GetInt(8);
			this->EventStruct[this->_Count[1]]._Excelente = Section.Rows[i].GetInt(9);
			this->_Count[1]++;
		}
	}

	return true;
}

void cDropEvent::Run()
{
	if (this->_Active[0] == true)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		for (int i = 0; i < this->_Count[0]; i++)
		{
			if (Now.wDayOfWeek == this->EventStruct[i]._Day && Now.wHour == this->EventStruct[i]._Hours && Now.wMinute == this->EventStruct[i]._Minutes && Now.wSecond == 0)
			{
				this->_Active[1] = false;

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   DROP EVENT   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 5 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   DROP EVENT   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 4 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   DROP EVENT   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 3 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   DROP EVENT   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 2 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   DROP EVENT   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 1 Minuto(s)");
					}
				}

				Sleep(60000);

				this->_MapNumber = this->EventStruct[i]._MapNumber[0];

				this->Mapa(this->_MapNumber);

				int Value = 0;

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   DROP EVENT   ]");
						Func.MsgOutput(Index, 0, "Evento iniciado em %s", this->_MapName);

						Value = Index;
					}
				}

				if (Value > 0)
				{
					for (int x = 0; x < this->_Count[1]; x++)
					{
						if (gObj[Value].MapNumber == this->_MapNumber && this->EventStruct[x]._MapNumber[1] == this->_MapNumber)
						{
							ItemSerialCreateSend(Value, this->EventStruct[x]._MapNumber[1], this->EventStruct[x]._X - 4 + rand() % 8, this->EventStruct[x]._Y - 4 + rand() % 8, ITEMGET(this->EventStruct[x]._Type, this->EventStruct[x]._Index), this->EventStruct[x]._Level, 0, this->EventStruct[x]._Skill, this->EventStruct[x]._Luck, this->EventStruct[x]._Option, -1, this->EventStruct[x]._Excelente);
						}
					}
				}

				_beginthread(cDropEvent::Repeat, 0, NULL);

				Sleep(this->EventStruct[i]._Duration);

				this->_Active[1] = true;
			}
		}
	}
}

void cDropEvent::Repeat(void* lpParam)
{
	while (true)
	{
		Sleep(18000);

		int Index = 0;

		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[Index].Connected == 3)
			{
				Index = i;
			}
		}

		if (Index > 0)
		{
			for (int x = 0; x < DropEvent._Count[1]; x++)
			{
				if (gObj[Index].MapNumber == DropEvent._MapNumber && DropEvent.EventStruct[x]._MapNumber[1] == DropEvent._MapNumber)
				{
					ItemSerialCreateSend(Index, DropEvent.EventStruct[x]._MapNumber[1], DropEvent.EventStruct[x]._X - 4 + rand() % 8, DropEvent.EventStruct[x]._Y - 4 + rand() % 8, ITEMGET(DropEvent.EventStruct[x]._Type, DropEvent.EventStruct[x]._Index), DropEvent.EventStruct[x]._Level, 0, DropEvent.EventStruct[x]._Skill, DropEvent.EventStruct[x]._Luck, DropEvent.EventStruct[x]._Option, -1, DropEvent.EventStruct[x]._Excelente);
				}
			}
		}

		if (DropEvent._Active[1] == true)
		{
			for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
			{
				if (gObj[Index].Connected == 3)
				{
					Func.MsgOutput(Index, 0, "[   DROP EVENT   ]");
					Func.MsgOutput(Index, 0, "Evento encerrado.");
				}
			}

			_endthread();
		}
	}

	_endthread();
}

void cDropEvent::Mapa(int MapNumber)
{
	switch (MapNumber)
	{
	case 0:
		this->_MapName = "Lorencia";
		break;
	case 1:
		this->_MapName = "Dungeon";
		break;
	case 2:
		this->_MapName = "Devias";
		break;
	case 3:
		this->_MapName = "Noria";
		break;
	case 4:
		this->_MapName = "LostTower";
		break;
	case 7:
		this->_MapName = "Atlans";
		break;
	case 8:
		this->_MapName = "Tarkan";
		break;
	case 10:
		this->_MapName = "Icarus";
		break;
	}
}


void cDropEvent::StartManual()
{
	srand(time(NULL));

	if (this->_Count[0] <= 0) return;

	int Sortear = rand() % this->_Count[0];

	this->_MapNumber = this->EventStruct[Sortear]._MapNumber[0];
	this->Mapa(this->_MapNumber);

	for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
	{
		if (gObj[Index].Connected == 3)
		{
			Func.MsgOutput(Index, 0, "[ TESTE ] O DROP EVENT comecou em %s!", this->_MapName);
		}
	}

	_beginthread(cDropEvent::Repeat, 0, &this->EventStruct[Sortear]);
}
cDropEvent DropEvent;


