#include "StdAfx.h"

cBossEvent::cBossEvent() : _Active(false), _Alive(false)
{
}

char MapName[][15] = { "Lorencia", "Dungeon", "Devias", "Noria", "LostTower", "Exile", "Atlans", "Tarkan", "Icarus" };
BYTE MapNumber[]   = { 0,		   1,		  2,        3,       4,           5,        7,        8,        10 };

bool cBossEvent::Load()
{
	this->_Count[0] = 0; this->_Count[1] = 0;

	memset(this->BossStruct, 0, sizeof(this->BossStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/BossEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->BossStruct[this->_Count[0]]._Day = Section.Rows[i].GetInt(0);
			this->BossStruct[this->_Count[0]]._Hours = Section.Rows[i].GetInt(1);
			this->BossStruct[this->_Count[0]]._Minutes = Section.Rows[i].GetInt(2);
			this->BossStruct[this->_Count[0]]._Monster[0] = Section.Rows[i].GetInt(3);
			this->BossStruct[this->_Count[0]]._MapNumber = Section.Rows[i].GetInt(4);
			this->BossStruct[this->_Count[0]]._X = Section.Rows[i].GetInt(5);
			this->BossStruct[this->_Count[0]]._Y = Section.Rows[i].GetInt(6);
			this->BossStruct[this->_Count[0]]._Duration = Section.Rows[i].GetInt(7) * 60 * 1000;
			strcpy_s(this->BossStruct[this->_Count[0]]._Name, sizeof(this->BossStruct[this->_Count[0]]._Name), (Section.Rows[i].GetStringPtr(8)));
			this->_Count[0]++;
		}
	}

	if (Group.GetSection(2, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->BossStruct[this->_Count[1]]._Type = Section.Rows[i].GetInt(0);
			this->BossStruct[this->_Count[1]]._Index = Section.Rows[i].GetInt(1);
			this->BossStruct[this->_Count[1]]._Level = Section.Rows[i].GetInt(2);
			this->BossStruct[this->_Count[1]]._Luck = Section.Rows[i].GetInt(3);
			this->BossStruct[this->_Count[1]]._Skill = Section.Rows[i].GetInt(4);
			this->BossStruct[this->_Count[1]]._Option = Section.Rows[i].GetInt(5);
			this->BossStruct[this->_Count[1]]._Excelente = Section.Rows[i].GetInt(6);
			this->BossStruct[this->_Count[1]]._Quantity = Section.Rows[i].GetInt(7);
			this->BossStruct[this->_Count[1]]._Monster[1] = Section.Rows[i].GetInt(8);
			this->_Count[1]++;
		}
	}

	return true;
}

void cBossEvent::Run()
{
	if (this->_Active)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		for (int i = 0; i < this->_Count[0]; i++)
		{
			if (Now.wDayOfWeek == this->BossStruct[i]._Day && Now.wHour == this->BossStruct[i]._Hours && Now.wMinute == this->BossStruct[i]._Minutes && Now.wSecond == 0)
			{
				this->_BossName = this->BossStruct[i]._Name;

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "Boss %s aparecerá em 5 Minuto(s)", this->_BossName);
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "Boss %s aparecerá em 4 Minuto(s)", this->_BossName);
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "Boss %s aparecerá em 3 Minuto(s)", this->_BossName);
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "Boss %s aparecerá em 2 Minuto(s)", this->_BossName);
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ATENÇÃO!   ]");
						Func.MsgOutput(Index, 0, "Boss %s aparecerá em 1 Minuto(s)", this->_BossName);
					}
				}

				Sleep(60000);

				this->_Monster = this->BossStruct[i]._Monster[0];

				if (this->BossStruct[i]._MapNumber == -1 && this->BossStruct[i]._X == -1 && this->BossStruct[i]._Y == -1)
				{
					BYTE Sortear = (BYTE)(MapNumber[Func.Rand(0, 9)]);
					BYTE Mapa = MapNumber[Sortear];

					while (Func.GetBoxPosition(Mapa, 10, 10, 240, 240, this->_X, this->_Y) == 0) {}

					this->_Index = Func.MonsterAdd(this->_Monster, Mapa, this->_X, this->_Y);

					this->_Alive = true;

					for (int Index = OBJECT_MIN; Index < OBJECT_MAX; ++Index)
					{
						if (gObj[Index].Connected == 3)
						{
							Func.MsgOutput(Index, 0, "Boss %s apareceu em %s", this->_BossName, MapName[Sortear]);
							Func.MsgOutput(Index, 0, "Mate-o para ser recompensado!");
						}
					}
				}
				else
				{
					if (this->BossStruct[i]._X == -1 && this->BossStruct[i]._Y == -1)
					{
						while (Func.GetBoxPosition(this->BossStruct[i]._MapNumber, 10, 10, 240, 240, this->_X, this->_Y) == 0) {}

						this->_Index = Func.MonsterAdd(this->_Monster, this->BossStruct[i]._MapNumber, this->_X, this->_Y);
					}
					else
					{
						this->_Index = Func.MonsterAdd(this->_Monster, this->BossStruct[i]._MapNumber, this->BossStruct[i]._X, this->BossStruct[i]._Y);
					}

					this->Mapa(this->BossStruct[i]._MapNumber);

					this->_Alive = true;

					for (int Index = OBJECT_MIN; Index < OBJECT_MAX; ++Index)
					{
						if (gObj[Index].Connected == 3)
						{
							Func.MsgOutput(Index, 0, "Boss %s apareceu em %s", this->_BossName, this->_MapName);
							Func.MsgOutput(Index, 0, "Mate-o para ser recompensado!");
						}
					}
				}

				Sleep(this->BossStruct[i]._Duration);

				this->Disappear();
			}
		}
	}
}

void cBossEvent::Disappear()
{
	if (this->_Alive == true)
	{
		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; ++Index)
		{
			if (gObj[Index].Connected == 3)
			{
				Func.MsgOutput(Index, 0, "Boss %s desapareceu!", this->_BossName);
				Func.MsgOutput(Index, 0, "Para onde será que ele(a) foi?");
				Func.MsgOutput(Index, 0, "Tente encontrá-lo da próxima vez.");
			}
		}

		if (gObj[this->_Index].Class == this->_Monster)
		{
			gObj[this->_Index].Live = FALSE;

			gObjDel(this->_Index);
		}

		this->_Alive = false;  this->_Index = -1;
	}
}

void cBossEvent::Mapa(int MapNumber)
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
	case 5:
		this->_MapName = "Exile";
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

void cBossEvent::Finish(int aIndex)
{
	this->Mapa(gObj[aIndex].MapNumber);

	for (int Index = OBJECT_MIN; Index < OBJECT_MAX; ++Index)
	{
		if (gObj[Index].Connected == 3)
		{
			Func.MsgOutput(Index, 0, "%s matou o Boss %s!", gObj[aIndex].Name, this->_BossName);
			Func.MsgOutput(Index, 0, "Localização: %s %02d/%02d", this->_MapName, gObj[aIndex].X, gObj[aIndex].Y);
		}
	}

	Manager.ExecFormat(Query._Query[20], gObj[aIndex].Name);

	for (int i = 0; i < this->_Count[1]; i++)
	{
		if (this->BossStruct[i]._Monster[1] == this->_Monster)
		{
			for (int x = 0; x < this->BossStruct[i]._Quantity; x++)
			{
				int Item = ITEMGET(this->BossStruct[i]._Type, this->BossStruct[i]._Index);

				ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->BossStruct[i]._Level, 0, this->BossStruct[i]._Skill, this->BossStruct[i]._Luck, this->BossStruct[i]._Option, aIndex, this->BossStruct[i]._Excelente);
			}
		}
	}

	Func.FireWork(aIndex);

	gObj[this->_Index].Live = false;

	gObjDel(this->_Index);

	this->_Alive = false; this->_Index = -1;
}

cBossEvent BossEvent;