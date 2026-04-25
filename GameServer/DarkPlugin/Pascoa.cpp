#include "StdAfx.h"

cPascoa::cPascoa() : _Active(false), _Sended(false)
{
}

char PascoaMapName[][15] = { "Lorencia", "Dungeon", "Davias", "Noria" };
BYTE PascoaMapNumber[] = { 0,			 1,			 2,        3 };

bool cPascoa::Load()
{
	this->_Count[0] = 0; this->_Count[1] = 0;

	memset(this->PascoaStruct, 0, sizeof(this->PascoaStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Pascoa.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false; this->_Class[0] = Section.Rows[0].GetInt(1); this->_Class[1] = Section.Rows[0].GetInt(2);
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->PascoaStruct[this->_Count[0]]._Day = Section.Rows[i].GetInt(0);
			this->PascoaStruct[this->_Count[0]]._Hours = Section.Rows[i].GetInt(1);
			this->PascoaStruct[this->_Count[0]]._Minutes = Section.Rows[i].GetInt(2);
			this->PascoaStruct[this->_Count[0]]._Duration = Section.Rows[i].GetInt(3) * 60 * 1000;
			this->PascoaStruct[this->_Count[0]]._Map = Section.Rows[i].GetInt(4); 
			this->PascoaStruct[this->_Count[0]]._X = Section.Rows[i].GetInt(5); 
			this->PascoaStruct[this->_Count[0]]._Y = Section.Rows[i].GetInt(6); 
			this->PascoaStruct[this->_Count[0]]._QNTD[0] = Section.Rows[i].GetInt(7); 
			this->PascoaStruct[this->_Count[0]]._QNTD[1] = Section.Rows[i].GetInt(8);
			this->_Count[0]++;
		}
	}

	if (Group.GetSection(2, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->PascoaStruct[this->_Count[1]]._Type = Section.Rows[i].GetInt(0);
			this->PascoaStruct[this->_Count[1]]._Index = Section.Rows[i].GetInt(1);
			this->PascoaStruct[this->_Count[1]]._Level = Section.Rows[i].GetInt(2);
			this->PascoaStruct[this->_Count[1]]._Luck = Section.Rows[i].GetInt(3);
			this->PascoaStruct[this->_Count[1]]._Skill = Section.Rows[i].GetInt(4);
			this->PascoaStruct[this->_Count[1]]._Option = Section.Rows[i].GetInt(5);
			this->PascoaStruct[this->_Count[1]]._Excelente = Section.Rows[i].GetInt(6);
			this->PascoaStruct[this->_Count[1]]._Quantity = Section.Rows[i].GetInt(7);
			this->PascoaStruct[this->_Count[1]]._Monster = Section.Rows[i].GetInt(8);
			this->_Count[1]++;
		}
	}

	return true;
}

void cPascoa::Run()
{
	if (this->_Active)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		for (int i = 0; i < this->_Count[0]; i++)
		{
			if (Now.wDayOfWeek == this->PascoaStruct[i]._Day && Now.wHour == this->PascoaStruct[i]._Hours && Now.wMinute == this->PascoaStruct[i]._Minutes && Now.wSecond == 0)
			{
				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "A invasão de Páscoa inicia em 5 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "A invasão de Páscoa inicia em 4 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "A invasão de Páscoa inicia em 3 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "A invasão de Páscoa inicia em 2 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "A invasão de Páscoa inicia em 1 Minuto(s)");
					}
				}

				Sleep(60000);

				srand(time(NULL));

				BYTE Sortear = (BYTE)(rand() % sizeof(PascoaMapNumber));
				this->_Mapa = PascoaMapNumber[Sortear];

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
						Func.MsgOutput(Index, 0, "A invasão de Páscoa começou em %s", PascoaMapName[this->_Mapa]);
						Func.MsgOutput(Index, 0, "Mate-os para ser recompensado!");
					}
				}

				Sleep(this->PascoaStruct[i]._Duration);

				this->_Sended = true;

				this->Disappear();
			}
		}
	}
}

void cPascoa::Disappear()
{
	if (this->_Sended == true)
	{
		Func.AllServerAnnounce("A invasão de Páscoa acabou!");

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

void cPascoa::Assasin(int aIndex)
{
	if (this->_Class[0])
	{
		this->_Total[0]--;

		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3)
			{
				Func.MsgOutput(Index, 0, "%s matou um Rabbit Assasin!", gObj[aIndex].Name);
				Func.MsgOutput(Index, 0, "Localização: %s %02d/%02d", PascoaMapName[this->_Mapa], gObj[aIndex].X, gObj[aIndex].Y);
				Func.MsgOutput(Index, 0, "Restam: %d %s", this->_Total[0], (this->_Total[0] == 1) ? "Rabbit Assasin." : "Rabbit Assasins.");
			}
		}
	}

	for (int i = 0; i < this->_Count[1]; i++)
	{
		if (this->PascoaStruct[i]._Monster == this->_Class[0])
		{
			for (int x = 0; x < this->PascoaStruct[i]._Quantity; x++)
			{
				int Item = ITEMGET(this->PascoaStruct[i]._Type, this->PascoaStruct[i]._Index);

				ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->PascoaStruct[i]._Level, 0, this->PascoaStruct[i]._Skill, this->PascoaStruct[i]._Luck, this->PascoaStruct[i]._Option, aIndex, this->PascoaStruct[i]._Excelente);
			}
		}
	}

	Func.FireWork(aIndex);
}

void cPascoa::Rabbit(int aIndex)
{
	if (this->_Class[1])
	{
		this->_Total[1]--;

		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3)
			{
				Func.MsgOutput(Index, 0, "%s matou um Rabbit!", gObj[aIndex].Name);
				Func.MsgOutput(Index, 0, "Localização: %s %02d/%02d", PascoaMapName[this->_Mapa], gObj[aIndex].X, gObj[aIndex].Y);
				Func.MsgOutput(Index, 0, "Restam: %d %s", this->_Total[1], (this->_Total[1] == 1) ? "Rabbit." : "Rabbits.");
			}
		}
	}

	for (int i = 0; i < this->_Count[1]; i++)
	{
		if (this->PascoaStruct[i]._Monster == this->_Class[1])
		{
			for (int x = 0; x < this->PascoaStruct[i]._Quantity; x++)
			{
				int Item = ITEMGET(this->PascoaStruct[i]._Type, this->PascoaStruct[i]._Index);

				ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->PascoaStruct[i]._Level, 0, this->PascoaStruct[i]._Skill, this->PascoaStruct[i]._Luck, this->PascoaStruct[i]._Option, aIndex, this->PascoaStruct[i]._Excelente);
			}
		}
	}

	Func.FireWork(aIndex);
}

cPascoa Pascoa;
