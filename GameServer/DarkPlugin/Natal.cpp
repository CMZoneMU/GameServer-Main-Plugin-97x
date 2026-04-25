#include "StdAfx.h"

cNatal::cNatal() : _Active(false), _Sended(false)
{
}

char iMapName[][15] = { "Lorencia", "Dungeon", "Davias", "Noria" };
BYTE iMapNumber[]   = { 0,			 1,			 2,        3 };

bool cNatal::Load()
{
	this->_Count[0] = 0; this->_Count[1] = 0;

	memset(this->NatalStruct, 0, sizeof(this->NatalStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Natal.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false; 
		this->_Class[0] = Section.Rows[0].GetInt(1); 
		this->_Class[1] = Section.Rows[0].GetInt(2);
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->NatalStruct[this->_Count[0]]._Day = Section.Rows[i].GetInt(0);
			this->NatalStruct[this->_Count[0]]._Hours = Section.Rows[i].GetInt(1);
			this->NatalStruct[this->_Count[0]]._Minutes = Section.Rows[i].GetInt(2);
			this->NatalStruct[this->_Count[0]]._Duration = Section.Rows[i].GetInt(3) * 60 * 1000;
			this->_Count[0]++;
		}
	}

	if (Group.GetSection(2, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->NatalStruct[this->_Count[1]]._Type = Section.Rows[i].GetInt(0);
			this->NatalStruct[this->_Count[1]]._Index = Section.Rows[i].GetInt(1);
			this->NatalStruct[this->_Count[1]]._Level = Section.Rows[i].GetInt(2);
			this->NatalStruct[this->_Count[1]]._Luck = Section.Rows[i].GetInt(3);
			this->NatalStruct[this->_Count[1]]._Skill = Section.Rows[i].GetInt(4);
			this->NatalStruct[this->_Count[1]]._Option = Section.Rows[i].GetInt(5);
			this->NatalStruct[this->_Count[1]]._Excelente = Section.Rows[i].GetInt(6);
			this->NatalStruct[this->_Count[1]]._Quantity = Section.Rows[i].GetInt(7);
			this->NatalStruct[this->_Count[1]]._Monster = Section.Rows[i].GetInt(8);
			this->_Count[1]++;
		}
	}

	return true;
}

void cNatal::Run()
{
	if (this->_Active)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		for (int i = 0; i < this->_Count[0]; i++)
		{
			if (Now.wDayOfWeek == this->NatalStruct[i]._Day && Now.wHour == this->NatalStruct[i]._Hours && Now.wMinute == this->NatalStruct[i]._Minutes && Now.wSecond == 0)
			{
				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "A invasão de Natal inicia em 5 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "A invasão de Natal inicia em 4 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "A invasão de Natal inicia em 3 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "A invasão de Natal inicia em 2 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "A invasão de Natal inicia em 1 Minuto(s)");
					}
				}

				Sleep(60000);

				srand(time(NULL));

				BYTE Sortear = (BYTE)(rand() % sizeof(iMapNumber));
				this->_Mapa = iMapNumber[Sortear];

				this->_Total[0] = 0;

				for (int x = 0; x < 3; x++)
				{
					while (Func.GetBoxPosition(this->_Mapa, 10, 10, 240, 240, this->_X, this->_Y) == 0) {}

					Func.MonsterAdd(this->_Class[0], this->_Mapa, this->_X, this->_Y);

					this->_Total[0]++;
				}

				this->_Total[1] = 0;

				for (int x = 0; x < 15; x++)
				{
					while (Func.GetBoxPosition(this->_Mapa, 10, 10, 240, 240, this->_X, this->_Y) == 0) {}

					Func.MonsterAdd(this->_Class[1], this->_Mapa, this->_X, this->_Y);

					this->_Total[1]++;
				}

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "A invasão de Natal começou em %s", iMapName[this->_Mapa]);
						Func.MsgOutput(Index, 0, "Mate-os para ser recompensado!");
					}
				}

				Sleep(this->NatalStruct[i]._Duration);

				this->_Sended = true;

				this->Disappear();
			}
		}
	}
}

void cNatal::Disappear()
{
	if (this->_Sended == true)
	{
		Func.AllServerAnnounce("A invasão de Natal acabou!");

		for (int i = 0; i < MAXMONSTER; i++)
		{
			if (gObj[i].Class == this->_Class[0] || gObj[i].Class == this->_Class[1])
			{
				gObj[i].Live = FALSE;

				gObjDel(i);
			}
		}

		this->_Sended = false;
	}

	this->_Class[0] = -1;
	this->_Class[1] = -1;

	this->_Total[0] = 0;
	this->_Total[1] = 0;
}

void cNatal::Santa(int aIndex)
{
	if (this->_Class[0])
	{
		this->_Total[0]--;

		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3)
			{
				Func.MsgOutput(Index, 0, "%s matou um Santa!", gObj[aIndex].Name);
				Func.MsgOutput(Index, 0, "Localização: %s %02d/%02d", iMapName[this->_Mapa], gObj[aIndex].X, gObj[aIndex].Y);
				Func.MsgOutput(Index, 0, "Restam: %d %s", this->_Total[0], (this->_Total[0] == 1) ? "Santa." : "Santas.");
			}
		}
	}

	for (int i = 0; i < this->_Count[1]; i++)
	{
		if (this->NatalStruct[i]._Monster == this->_Class[0])
		{
			for (int x = 0; x < this->NatalStruct[i]._Quantity; x++)
			{
				int Item = ITEMGET(this->NatalStruct[i]._Type, this->NatalStruct[i]._Index);

				ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->NatalStruct[i]._Level, 0, this->NatalStruct[i]._Skill, this->NatalStruct[i]._Luck, this->NatalStruct[i]._Option, aIndex, this->NatalStruct[i]._Excelente);
			}
		}
	}

	Func.FireWork(aIndex);
}

void cNatal::Globin(int aIndex)
{
	if (this->_Class[1])
	{
		this->_Total[1]--;

		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3)
			{
				Func.MsgOutput(Index, 0, "%s matou um Globin!", gObj[aIndex].Name);
				Func.MsgOutput(Index, 0, "Localização: %s %02d/%02d", iMapName[this->_Mapa], gObj[aIndex].X, gObj[aIndex].Y);
				Func.MsgOutput(Index, 0, "Restam: %d %s", this->_Total[1], (this->_Total[1] == 1) ? "Globin." : "Globins.");
			}
		}
	}

	for (int i = 0; i < this->_Count[1]; i++)
	{
		if (this->NatalStruct[i]._Monster == this->_Class[1])
		{
			for (int x = 0; x < this->NatalStruct[i]._Quantity; x++)
			{
				int Item = ITEMGET(this->NatalStruct[i]._Type, this->NatalStruct[i]._Index);

				ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->NatalStruct[i]._Level, 0, this->NatalStruct[i]._Skill, this->NatalStruct[i]._Luck, this->NatalStruct[i]._Option, aIndex, this->NatalStruct[i]._Excelente);
			}
		}
	}

	Func.FireWork(aIndex);
}

cNatal Natal;
