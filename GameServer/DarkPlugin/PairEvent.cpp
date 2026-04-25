#include "StdAfx.h"

cPairEvent::cPairEvent() : _State(Empty)
{
}

cPairEvent::~cPairEvent()
{
}

bool cPairEvent::Load()
{
	this->_List = 0;

	this->_Teams[0] = std::vector<PairTeam>();
	this->_Teams[1] = std::vector<PairTeam>();
	this->_Registered = std::vector<LPOBJ>();

	memset(this->EventStruct, 0, sizeof(this->EventStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/PairEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[0], sizeof(this->_Syntax[0]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Syntax[1], sizeof(this->_Syntax[1]), (Section.Rows[0].GetStringPtr(2)));

		this->_MapNumber[0] = Section.Rows[1].GetInt(0);
		this->_X[0] = Section.Rows[1].GetInt(1);
		this->_Y[0] = Section.Rows[1].GetInt(2);
		this->_MapNumber[1] = Section.Rows[1].GetInt(3);
		this->_X[1] = Section.Rows[1].GetInt(4);
		this->_Y[1] = Section.Rows[1].GetInt(5);

		strcpy_s(this->_Notice, sizeof(this->_Notice), (Section.Rows[2].GetStringPtr(0)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->EventStruct[this->_List].Day = Section.Rows[i].GetInt(0);
			this->EventStruct[this->_List].Hours = Section.Rows[i].GetInt(1);
			this->EventStruct[this->_List].Minutes = Section.Rows[i].GetInt(2);
			this->_List++;
		}
	}

	return true;
}

bool cPairEvent::Check(LPOBJ lpObj, const char* Text)
{
	if (lpObj->Authority > 1)
	{
		char Buffer[60], *Token = nullptr, *Context = nullptr;

		strcpy_s(Buffer, Text);
		Token = strtok_s(Buffer, " ", &Context);

		if (this->_State == Empty && !_stricmp(Token, this->_Syntax[1]))
		{
			if (Authority.Check(lpObj, 12) == true)
			{
				char* Time = strtok_s(nullptr, " ", &Context);
				char* Class = strtok_s(nullptr, " ", &Context);

				if (!Time || !Class)
				{
					Func.MsgOutput(lpObj->m_Index, 1, "Erro de sintaxe!");
					Func.MsgOutput(lpObj->m_Index, 1, "Digite: %s <tempo> <class>", this->_Syntax[1]);
					Func.MsgOutput(lpObj->m_Index, 1, "ID de classes:");
					Func.MsgOutput(lpObj->m_Index, 1, "0: Wizard    | 1: Knight    | 2: Elf");
					Func.MsgOutput(lpObj->m_Index, 1, "3: Gladiator | 4: Todos");
					return true;
				}

				gObjTeleport(lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);

				this->Start(atoi(Time), atoi(Class));
				return true;
			}
		}
	}
	else
	{
		if (!_stricmp(Text, this->_Syntax[0]))
		{
			if (this->_State == Register && lpObj->Live == TRUE)
			{
				if (this->_Type != 4 && lpObj->Class != this->_Type)
				{
					switch (this->_Type)
					{
					case 0:
						Func.MsgOutput(lpObj->m_Index, 1, "Evento exclusivo para Dark Wizards e Soul Masters.");
						break;
					case 1:
						Func.MsgOutput(lpObj->m_Index, 1, "Evento exclusivo para Dark Knights e Blade Knights.");
						break;
					case 2:
						Func.MsgOutput(lpObj->m_Index, 1, "Evento exclusivo para Elfs e Muse Elfs.");
						break;
					case 3:
						Func.MsgOutput(lpObj->m_Index, 1, "Evento exclusivo para Magic Gladiators.");
						break;
					}

					return true;
				}

				if (this->_Registered.size() > 0)
				{
					for (auto it = this->_Registered.cbegin(); it != this->_Registered.cend(); ++it)
					{
						if ((*it) == lpObj)
						{
							Func.MsgOutput(lpObj->m_Index, 1, "Você já está registrado no evento. Aguarde.");
							return true;
						}
					}
				}

				if (lpObj->Level < 50)
				{
					Func.MsgOutput(lpObj->m_Index, 1, "É necessário 50 de level.");
					return true;
				}
				else if (lpObj->PartyNumber != -1)
				{
					Func.MsgOutput(lpObj->m_Index, 1, "Saia da party para participar.");
					return true;
				}

				Custom[lpObj->m_Index].InEvent = true;

				this->_Registered.push_back(lpObj);

				gObjTeleport(lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);
				Func.MsgOutput(lpObj->m_Index, 1, "Você foi registrado no evento. Aguarde...");
			}

			return true;
		}
	}

	return false;
}

void cPairEvent::Start(int Time, int Class)
{
	if (Time == 0)
	{
		Time++;
	}

	if (this->_Teams[0].size() > 0)
	{
		this->_Teams[0].clear();
	}

	if (this->_Teams[1].size() > 0)
	{
		this->_Teams[1].clear();
	}

	if (this->_Registered.size() > 0)
	{
		this->_Registered.clear();
	}

	this->_State = Register;
	this->_Count = (Time * 60) + 1;
	this->_Type = (BYTE)(Class);
}

void cPairEvent::Run()
{
	SYSTEMTIME Now;
	GetLocalTime(&Now);

	for (int i = 0; i < this->_List; i++)
	{
		if (Now.wDayOfWeek == this->EventStruct[i].Day && Now.wHour == this->EventStruct[i].Hours && Now.wMinute == this->EventStruct[i].Minutes && Now.wSecond == 0)
		{
			if (this->_State == Empty)
			{
				this->Start(5, 4);
			}
		}
	}

	if (this->_State == Empty)
	{
		return;
	}

	if (this->_Count > 0)
	{
		this->_Count--;
	}

	switch (this->_State)
	{
	case Register:
	{
		if (this->_Count == 0)
		{
			if (this->_Registered.size() < 4)
			{
				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3 && Custom[i].InEvent == true)
					{
						Func.MsgOutput(i, 0, "[   MATA-MATA DE DUPLAS   ]");
						Func.MsgOutput(i, 0, "Evento encerrado. Mínimo de participantes não atingido.");

						Func.MsgOutput(i, 0, "Participantes premiados com 10 Golds!");

						Manager.ExecFormat("UPDATE MEMB_INFO SET Gold = Gold + 10 WHERE memb___id = '%s'", gObj[i].AccountID);

						Manager.CoinCount(i, gObj[i].AccountID);

						if (Custom[i].InEvent == true)
						{
							Custom[i].InEvent = false;

							Custom[i].Move = true;
						}
					}
				}

				this->_State = Empty;
				this->_Count = 0;
			}
			else
			{
				PairTeam Team;
				memset(&Team, 0, sizeof(Team));

				std::sort(this->_Registered.begin(), this->_Registered.end());

				BYTE id = 0;

				for (std::vector<LPOBJ>::const_iterator it = this->_Registered.cbegin(); it != this->_Registered.cend(); ++it)
				{
					Team.Player[id].lpObj = (*it);

					++id;

					if (id == 2)
					{
						this->_Teams[0].push_back(Team);

						id = 0;
					}
				}

				if (id == 1)
				{
					Func.MsgOutput(Team.Player[0].lpObj->m_Index, 1, "Você foi eliminado por falta de jogadores!");

					Custom[Team.Player[0].lpObj->m_Index].Move = true;
					Custom[Team.Player[0].lpObj->m_Index].InEvent = false;

					auto it = std::find(this->_Registered.cbegin(), this->_Registered.cend(), Team.Player[0].lpObj);

					if (it != this->_Registered.cend())
					{
						this->_Registered.erase(it);
					}

					Team.Player[0].lpObj = NULL;
					Team.Player[1].lpObj = NULL;
				}

				sprintf_s(this->_Buffer[0], "Inscrições para o evento encerradas.");
				sprintf_s(this->_Buffer[1], "PRIMEIRA RODADA!");

				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						GCServerMsgStringSend(this->_Buffer[0], i, 0);
						GCServerMsgStringSend(this->_Buffer[1], i, 0);
					}
				}

				this->_State = Select;
				this->_Count = 3;
			}
		}
		else
		{
			if ((this->_Count % 60) == 0)
			{
				sprintf_s(this->_Buffer[0], "[   MATA-MATA DE DUPLAS   ]");
				sprintf_s(this->_Buffer[1], "O evento começará em %d Minuto(s)", (this->_Count / 60));
				sprintf_s(this->_Buffer[2], "Para participar, utilize o comando: %s", this->_Syntax[0]);

				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						GCServerMsgStringSend(this->_Buffer[0], i, 0);
						GCServerMsgStringSend(this->_Buffer[1], i, 0);
						GCServerMsgStringSend(this->_Buffer[2], i, 0);
					}
				}
			}
		}
	}
	break;
	case Select:
	{
		if (this->_Count == 0)
		{
			switch (this->_Teams[0].size())
			{
			case 0:
			{
				this->_State = NextStage;
				this->_Count = 0;
			}
			break;
			case 1:
			{
			SelectWO:
				this->_Selected[0] = this->_Teams[0].front();

				sprintf_s(this->_Buffer[0], "[   MATA-MATA DE DUPLAS   ]");

				if (this->_Selected[0].Player[0].lpObj && this->_Selected[0].Player[1].lpObj)
				{
					sprintf_s(this->_Buffer[1], "(%s + %s) venceram por W.O.", this->_Selected[0].Player[0].lpObj->Name, this->_Selected[0].Player[1].lpObj->Name);
				}
				else if (this->_Selected[0].Player[0].lpObj && !this->_Selected[0].Player[1].lpObj)
				{
					sprintf_s(this->_Buffer[1], "%s venceu por W.O.", this->_Selected[0].Player[0].lpObj->Name);
				}
				else if (!this->_Selected[0].Player[0].lpObj && this->_Selected[0].Player[1].lpObj)
				{
					sprintf_s(this->_Buffer[1], "%s venceu por W.O.", this->_Selected[0].Player[1].lpObj->Name);
				}

				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						GCServerMsgStringSend(this->_Buffer[0], i, 0);
						GCServerMsgStringSend(this->_Buffer[1], i, 0);
					}
				}

				this->_Teams[1].push_back(this->_Selected[0]);

				this->_State = NextStage;
				this->_Count = 0;
			}
			break;
			default:
			{
				std::vector<PairTeam>::iterator Team1, Team2;

				while (true)
				{
					Team1 = this->_Teams[0].begin();
					Team2 = (--this->_Teams[0].end());

					if (!Team1->Player[0].lpObj)
					{
						Team1->Player[0].Quit = true;
					}

					if (!Team1->Player[1].lpObj)
					{
						Team1->Player[1].Quit = true;
					}

					if (!Team2->Player[0].lpObj)
					{
						Team2->Player[0].Quit = true;
					}

					if (!Team2->Player[1].lpObj)
					{
						Team2->Player[1].Quit = true;
					}

					if (Team1->Player[0].Quit && Team1->Player[1].Quit || !Team1->Player[0].lpObj || !Team1->Player[1].lpObj)
					{
						this->_Teams[0].erase(Team1);
						continue;
					}

					if (Team2->Player[0].Quit && Team2->Player[1].Quit || !Team2->Player[0].lpObj || !Team2->Player[1].lpObj)
					{
						this->_Teams[0].erase(Team2);
						continue;
					}

					break;
				}

				if (Team1 == Team2)
				{
					goto SelectWO;
				}
				else
				{
					this->_Selected[0] = *Team1;
					this->_Selected[0].Score = 0;
					this->_Selected[0].Player[0].Die = false;
					this->_Selected[0].Player[0].Quit = false;
					this->_Selected[0].Player[0].Select = false;
					this->_Selected[0].Player[1].Die = false;
					this->_Selected[0].Player[1].Quit = false;
					this->_Selected[0].Player[1].Select = false;

					this->_Selected[1] = *Team2;
					this->_Selected[1].Score = 0;
					this->_Selected[1].Player[0].Die = false;
					this->_Selected[1].Player[0].Quit = false;
					this->_Selected[1].Player[0].Select = false;
					this->_Selected[1].Player[1].Die = false;
					this->_Selected[1].Player[1].Quit = false;
					this->_Selected[1].Player[1].Select = false;

					sprintf_s(this->_Buffer[0], "[   MATA-MATA DE DUPLAS   ]");

					if (this->_Selected[0].Player[0].lpObj && this->_Selected[0].Player[1].lpObj && this->_Selected[1].Player[0].lpObj && this->_Selected[1].Player[1].lpObj)
					{
						sprintf_s(this->_Buffer[1], "(%s + %s)  vs  (%s + %s)", this->_Selected[0].Player[0].lpObj->Name, this->_Selected[0].Player[1].lpObj->Name, this->_Selected[1].Player[0].lpObj->Name, this->_Selected[1].Player[1].lpObj->Name);
					}

					for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
					{
						if (gObj[i].Connected == 3)
						{
							GCServerMsgStringSend(this->_Buffer[0], i, 0);
							GCServerMsgStringSend(this->_Buffer[1], i, 0);
						}
					}

					this->_Sended = false;
					this->_State = Progress;
					this->_Count = 8;
					this->_Teams[0].erase(Team2);
					this->_Teams[0].erase(Team1);
				}
			}
			break;
			}
		}
	}
	break;
	case Progress:
	{
		switch (this->_Count)
		{
		case 5:
		{
			if (this->_Selected[0].Player[0].lpObj)
			{
				Func.MsgOutput(this->_Selected[0].Player[0].lpObj->m_Index, 0, "[    ATENÇÃO    ]");

				this->_Selected[0].Player[0].lpObj->m_PK_Level = 6;
				this->_Selected[0].Player[0].Select = true;

				gObjTeleport(this->_Selected[0].Player[0].lpObj->m_Index, this->_MapNumber[1], this->_X[1] - 1, this->_Y[1] - 1);
				GCPkLevelSend(this->_Selected[0].Player[0].lpObj->m_Index, 6);
			}

			if (this->_Selected[0].Player[1].lpObj)
			{
				Func.MsgOutput(this->_Selected[0].Player[1].lpObj->m_Index, 0, "[    ATENÇÃO    ]");

				this->_Selected[0].Player[1].lpObj->m_PK_Level = 6;
				this->_Selected[0].Player[1].Select = true;

				gObjTeleport(this->_Selected[0].Player[1].lpObj->m_Index, this->_MapNumber[1], this->_X[1] + 1, this->_Y[1] - 1);
				GCPkLevelSend(this->_Selected[0].Player[1].lpObj->m_Index, 6);
			}

			if (this->_Selected[1].Player[0].lpObj)
			{
				Func.MsgOutput(this->_Selected[1].Player[0].lpObj->m_Index, 0, "[    ATENÇÃO    ]");

				this->_Selected[1].Player[0].lpObj->m_PK_Level = 6;
				this->_Selected[1].Player[0].Select = true;

				gObjTeleport(this->_Selected[1].Player[0].lpObj->m_Index, this->_MapNumber[1], this->_X[1] - 1, this->_Y[1] + 1);
				GCPkLevelSend(this->_Selected[1].Player[0].lpObj->m_Index, 6);
			}

			if (this->_Selected[1].Player[1].lpObj)
			{
				Func.MsgOutput(this->_Selected[1].Player[1].lpObj->m_Index, 0, "[    ATENÇÃO    ]");

				this->_Selected[1].Player[1].lpObj->m_PK_Level = 6;
				this->_Selected[1].Player[1].Select = true;

				gObjTeleport(this->_Selected[1].Player[1].lpObj->m_Index, this->_MapNumber[1], this->_X[1] + 1, this->_Y[1] + 1);
				GCPkLevelSend(this->_Selected[1].Player[1].lpObj->m_Index, 6);
			}
		}
		break;
		case 3:
		case 2:
		case 1:
		{
			if (this->_Selected[0].Player[0].lpObj)
			{
				Func.MsgOutput(this->_Selected[0].Player[0].lpObj->m_Index, 0, "Você poderá atacar em %d segundo(s)", this->_Count);
			}

			if (this->_Selected[0].Player[1].lpObj)
			{
				Func.MsgOutput(this->_Selected[0].Player[1].lpObj->m_Index, 0, "Você poderá atacar em %d segundo(s)", this->_Count);
			}

			if (this->_Selected[1].Player[0].lpObj)
			{
				Func.MsgOutput(this->_Selected[1].Player[0].lpObj->m_Index, 0, "Você poderá atacar em %d segundo(s)", this->_Count);
			}

			if (this->_Selected[1].Player[1].lpObj)
			{
				Func.MsgOutput(this->_Selected[1].Player[1].lpObj->m_Index, 0, "Você poderá atacar em %d segundo(s)", this->_Count);
			}
		}
		break;
		case 0:
		{
			if (this->_Sended == false)
			{
				if (this->_Selected[0].Player[0].lpObj)
				{
					Func.MsgOutput(this->_Selected[0].Player[0].lpObj->m_Index, 0, "Já!");
				}

				if (this->_Selected[0].Player[1].lpObj)
				{
					Func.MsgOutput(this->_Selected[0].Player[1].lpObj->m_Index, 0, "Já!");
				}

				if (this->_Selected[1].Player[0].lpObj)
				{
					Func.MsgOutput(this->_Selected[1].Player[0].lpObj->m_Index, 0, "Já!");
				}

				if (this->_Selected[1].Player[1].lpObj)
				{
					Func.MsgOutput(this->_Selected[1].Player[1].lpObj->m_Index, 0, "Já!");
				}

				this->_Sended = true;
			}
		}
		break;
		default:
			break;
		}
	}
	break;
	case Died:
	{
		if (this->_Count == 0)
		{
			if ((this->_Selected[0].Player[0].Die || !this->_Selected[0].Player[0].lpObj) &&
				(this->_Selected[0].Player[1].Die || !this->_Selected[0].Player[1].lpObj) &&
				(this->_Selected[1].Player[0].Die || !this->_Selected[1].Player[0].lpObj) &&
				(this->_Selected[1].Player[1].Die || !this->_Selected[1].Player[1].lpObj))
			{
				Func.AllServerAnnounce("Draw!");

				this->_Sended = false;

				this->_State = Progress;
				this->_Count = 8;
			}
			else
			{
				BYTE Winner = ((this->_Selected[0].Player[0].Die && this->_Selected[0].Player[1].Die) || (this->_Selected[0].Player[0].Die && this->_Selected[0].Player[1].Quit) || (this->_Selected[0].Player[0].Quit && this->_Selected[0].Player[1].Die)) ? 1 : 0;
				BYTE Loser = (Winner == 1) ? 0 : 1;

				this->_Selected[Winner].Score++;

				sprintf_s(this->_Buffer[0], "[    PLACAR    ]");

				if (this->_Selected[0].Player[0].lpObj && this->_Selected[0].Player[1].lpObj && this->_Selected[1].Player[0].lpObj && this->_Selected[1].Player[1].lpObj)
				{
					sprintf_s(this->_Buffer[1], "(%s + %s)  vs  (%s + %s)", this->_Selected[0].Player[0].lpObj->Name, this->_Selected[0].Player[1].lpObj->Name, this->_Selected[1].Player[0].lpObj->Name, this->_Selected[1].Player[1].lpObj->Name);
				}

				sprintf_s(this->_Buffer[2], "%d   x   %d", this->_Selected[0].Score, this->_Selected[1].Score);

				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						GCServerMsgStringSend(this->_Buffer[0], i, 0);
						GCServerMsgStringSend(this->_Buffer[1], i, 0);
						GCServerMsgStringSend(this->_Buffer[2], i, 0);
					}
				}

				if (this->_Selected[Winner].Score >= 5)
				{
					if (this->_Selected[Winner].Player[0].lpObj && this->_Selected[Winner].Player[1].lpObj)
					{
						Func.AllServerAnnounce("(%s + %s) venceram!", this->_Selected[Winner].Player[0].lpObj->Name, this->_Selected[Winner].Player[1].lpObj->Name);
					}
					else if (this->_Selected[Winner].Player[0].lpObj && !this->_Selected[Winner].Player[1].lpObj)
					{
						Func.AllServerAnnounce("%s venceu!", this->_Selected[Winner].Player[0].lpObj->Name);
					}
					else if (!this->_Selected[Winner].Player[0].lpObj && this->_Selected[Winner].Player[1].lpObj)
					{
						Func.AllServerAnnounce("%s venceu!", this->_Selected[Winner].Player[1].lpObj->Name);
					}

					this->_Teams[1].push_back(this->_Selected[Winner]);

					if (this->_Selected[Winner].Player[0].lpObj)
					{
						this->_Selected[Winner].Player[0].lpObj->m_PK_Level = 3;
						this->_Selected[Winner].Player[0].Select = false;

						GCPkLevelSend(this->_Selected[Winner].Player[0].lpObj->m_Index, 3);
						gObjTeleport(this->_Selected[Winner].Player[0].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);
					}

					if (this->_Selected[Winner].Player[1].lpObj)
					{
						this->_Selected[Winner].Player[1].lpObj->m_PK_Level = 3;
						this->_Selected[Winner].Player[1].Select = false;

						GCPkLevelSend(this->_Selected[Winner].Player[1].lpObj->m_Index, 3);
						gObjTeleport(this->_Selected[Winner].Player[1].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);
					}

					if (this->_Selected[Loser].Player[0].lpObj)
					{
						this->_Selected[Loser].Player[0].lpObj->m_PK_Level = 3;
						this->_Selected[Loser].Player[0].Select = false;

						GCPkLevelSend(this->_Selected[Loser].Player[0].lpObj->m_Index, 3);
						gObjTeleport(this->_Selected[Loser].Player[0].lpObj->m_Index, 0, 125, 125);

						Custom[this->_Selected[Loser].Player[0].lpObj->m_Index].InEvent = false;
					}

					if (this->_Selected[Loser].Player[1].lpObj)
					{
						this->_Selected[Loser].Player[1].lpObj->m_PK_Level = 3;
						this->_Selected[Loser].Player[1].Select = false;

						GCPkLevelSend(this->_Selected[Loser].Player[1].lpObj->m_Index, 3);
						gObjTeleport(this->_Selected[Loser].Player[1].lpObj->m_Index, 0, 125, 125);

						Custom[this->_Selected[Loser].Player[1].lpObj->m_Index].InEvent = false;
					}

					this->_State = Select;
					this->_Count = 0;
				}
				else
				{
					this->_Sended = false;
					this->_State = Progress;
					this->_Count = 8;
				}
			}

			this->_Selected[0].Player[0].Die = false;
			this->_Selected[0].Player[1].Die = false;
			this->_Selected[1].Player[0].Die = false;
			this->_Selected[1].Player[1].Die = false;
		}
	}
	break;
	case NextStage:
	{
		if (this->_Teams[0].size() > 0)
		{
			this->_Teams[0].clear();
		}

		this->_Teams[0] = this->_Teams[1];

		if (this->_Teams[1].size() > 0)
		{
			this->_Teams[1].clear();
		}

		memset(&this->_Selected, 0, sizeof(this->_Selected));

		switch (this->_Teams[0].size())
		{
		case 0:
		{
			this->_State = Empty;
			this->_Count = 0;
		}
		break;
		case 1:
		{
			this->_State = Final;
			this->_Count = 0;
		}
		break;
		default:
		{
			if ((this->_Teams[0].size() % 2) == 0)
			{
				Func.AllServerAnnounce("RODADA FINAL!");
			}
			else
			{
				Func.AllServerAnnounce("PRÓXIMA RODADA!");
			}

			this->_State = Select;
			this->_Count = 0;
		}
		break;
		}
	}
	break;
	case WO:
	{
		BYTE Winner = (this->_Selected[0].Player[0].Quit && this->_Selected[0].Player[1].Quit) || (!this->_Selected[0].Player[0].lpObj) || (!this->_Selected[0].Player[1].lpObj) ? 1 : 0;
		BYTE Loser = (Winner == 1) ? 0 : 1;

		if (this->_Selected[Winner].Player[0].lpObj && this->_Selected[Winner].Player[1].lpObj)
		{
			Func.AllServerAnnounce("(%s + %s) venceram por W.O.", this->_Selected[Winner].Player[0].lpObj->Name, this->_Selected[Winner].Player[1].lpObj->Name);
		}
		else if (this->_Selected[Winner].Player[0].lpObj && !this->_Selected[Winner].Player[1].lpObj)
		{
			Func.AllServerAnnounce("%s venceu por W.O.", this->_Selected[Winner].Player[0].lpObj->Name);
		}
		else if (!this->_Selected[Winner].Player[0].lpObj && this->_Selected[Winner].Player[1].lpObj)
		{
			Func.AllServerAnnounce("%s venceu por W.O.", this->_Selected[Winner].Player[1].lpObj->Name);
		}

		this->_Teams[1].push_back(this->_Selected[Winner]);

		this->_Selected[0].Player[0].Select = false;
		this->_Selected[0].Player[1].Select = false;
		this->_Selected[1].Player[0].Select = false;
		this->_Selected[1].Player[1].Select = false;

		if (this->_Selected[Winner].Player[0].lpObj)
		{
			this->_Selected[Winner].Player[0].lpObj->m_PK_Level = 3;

			GCPkLevelSend(this->_Selected[Winner].Player[0].lpObj->m_Index, 3);
			gObjTeleport(this->_Selected[Winner].Player[0].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);
		}

		if (this->_Selected[Winner].Player[1].lpObj)
		{
			this->_Selected[Winner].Player[1].lpObj->m_PK_Level = 3;

			GCPkLevelSend(this->_Selected[Winner].Player[1].lpObj->m_Index, 3);
			gObjTeleport(this->_Selected[Winner].Player[1].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);
		}

		if (this->_Selected[Loser].Player[0].lpObj)
		{
			this->_Selected[Loser].Player[0].lpObj->m_PK_Level = 3;

			GCPkLevelSend(this->_Selected[Loser].Player[0].lpObj->m_Index, 3);
			gObjTeleport(this->_Selected[Loser].Player[0].lpObj->m_Index, 0, 125, 125);

			Custom[this->_Selected[Loser].Player[0].lpObj->m_Index].InEvent = false;
		}

		if (this->_Selected[Loser].Player[1].lpObj)
		{
			this->_Selected[Loser].Player[1].lpObj->m_PK_Level = 3;

			GCPkLevelSend(this->_Selected[Loser].Player[1].lpObj->m_Index, 3);
			gObjTeleport(this->_Selected[Loser].Player[1].lpObj->m_Index, 0, 125, 125);

			Custom[this->_Selected[Loser].Player[1].lpObj->m_Index].InEvent = false;
		}

		this->_State = Select;
		this->_Count = 0;
	}
	break;
	case Final:
	{
		PairTeam Team = this->_Teams[0].front();

		if (Team.Player[0].lpObj)
		{
			Manager.ExecFormat(Query._Query[32], Team.Player[0].lpObj->Name);
			Manager.ExecFormat(Query._Query[33], Team.Player[0].lpObj->AccountID);
		}

		if (Team.Player[1].lpObj)
		{
			Manager.ExecFormat(Query._Query[32], Team.Player[1].lpObj->Name);
			Manager.ExecFormat(Query._Query[33], Team.Player[1].lpObj->AccountID);
		}

		sprintf_s(this->_Buffer[0], "[   MATA-MATA DE DUPLAS   ]");

		if (Team.Player[0].lpObj && Team.Player[1].lpObj)
		{
			sprintf_s(this->_Buffer[1], "%s e %s são os campeões!", Team.Player[0].lpObj->Name, Team.Player[1].lpObj->Name);
		}
		else if (Team.Player[0].lpObj && !Team.Player[1].lpObj)
		{
			sprintf_s(this->_Buffer[1], "%s é o campeão!", Team.Player[0].lpObj->Name);
		}
		else if (!Team.Player[0].lpObj && Team.Player[1].lpObj)
		{
			sprintf_s(this->_Buffer[1], "%s é o campeão!", Team.Player[1].lpObj->Name);
		}

		sprintf_s(this->_Buffer[2], this->_Notice);

		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].Connected == 3)
			{
				GCServerMsgStringSend(this->_Buffer[0], i, 0);
				GCServerMsgStringSend(this->_Buffer[1], i, 0);
				GCServerMsgStringSend(this->_Buffer[2], i, 0);
			}
		}

		if (Team.Player[0].lpObj)
		{
			gObjTeleport(Team.Player[0].lpObj->m_Index, 0, 125, 125);

			Custom[Team.Player[0].lpObj->m_Index].InEvent = false;
		}

		if (Team.Player[1].lpObj)
		{
			gObjTeleport(Team.Player[1].lpObj->m_Index, 0, 125, 125);

			Custom[Team.Player[1].lpObj->m_Index].InEvent = false;
		}

		this->_Teams[0].clear();
		this->_Teams[1].clear();

		this->_Registered.clear();

		this->_State = Empty;
		this->_Count = 0;
	}
	break;
	}
}

bool cPairEvent::Attack(LPOBJ lpObj, LPOBJ Target)
{
	if (this->_State == Select || this->_State == Died || this->_State == NextStage || this->_State == WO)
	{
		if ((this->_Selected[0].Player[0].lpObj == lpObj && this->_Selected[0].Player[1].lpObj == Target) ||
			(this->_Selected[0].Player[1].lpObj == lpObj && this->_Selected[0].Player[0].lpObj == Target) ||
			(this->_Selected[1].Player[0].lpObj == lpObj && this->_Selected[1].Player[1].lpObj == Target) ||
			(this->_Selected[1].Player[1].lpObj == lpObj && this->_Selected[1].Player[0].lpObj == Target))
		{
			return false;
		}
	}
	else if (this->_State == Progress)
	{
		if (this->_Selected[0].Player[0].lpObj != lpObj && this->_Selected[0].Player[0].lpObj != Target &&
			this->_Selected[0].Player[1].lpObj != lpObj && this->_Selected[0].Player[1].lpObj != Target &&
			this->_Selected[1].Player[0].lpObj != lpObj && this->_Selected[1].Player[0].lpObj != Target &&
			this->_Selected[1].Player[1].lpObj != lpObj && this->_Selected[1].Player[1].lpObj != Target)
		{
			return true;
		}

		if ((this->_Selected[0].Player[0].lpObj == lpObj && this->_Selected[0].Player[1].lpObj == Target) ||
			(this->_Selected[0].Player[1].lpObj == lpObj && this->_Selected[0].Player[0].lpObj == Target) ||
			(this->_Selected[1].Player[0].lpObj == lpObj && this->_Selected[1].Player[1].lpObj == Target) ||
			(this->_Selected[1].Player[1].lpObj == lpObj && this->_Selected[1].Player[0].lpObj == Target))
		{
			return false;
		}

		if (((this->_Selected[0].Player[0].lpObj == lpObj || this->_Selected[0].Player[1].lpObj == lpObj) && (this->_Selected[1].Player[0].lpObj == Target || this->_Selected[1].Player[1].lpObj == Target)) ||
			((this->_Selected[1].Player[0].lpObj == lpObj || this->_Selected[1].Player[1].lpObj == lpObj) && (this->_Selected[0].Player[0].lpObj == Target || this->_Selected[0].Player[1].lpObj == Target)))
		{
			if (this->_Count == 0)
			{
				return true;
			}

			return false;
		}

		if (Target->Type == MONSTER)
		{
			return true;
		}
	}

	return true;
}

void cPairEvent::Die(LPOBJ lpObj)
{
	if (this->_State == Progress || this->_State == Died)
	{
		if (this->_Selected[0].Player[0].lpObj == lpObj)
		{
			this->_Selected[0].Player[0].Die = true;
			this->_Selected[0].Player[0].Move = 7;
		}

		if (this->_Selected[0].Player[1].lpObj == lpObj)
		{
			this->_Selected[0].Player[1].Die = true;
			this->_Selected[0].Player[1].Move = 7;
		}

		if (this->_Selected[1].Player[0].lpObj == lpObj)
		{
			this->_Selected[1].Player[0].Die = true;
			this->_Selected[1].Player[0].Move = 7;
		}

		if (this->_Selected[1].Player[1].lpObj == lpObj)
		{
			this->_Selected[1].Player[1].Die = true;
			this->_Selected[1].Player[1].Move = 7;
		}

		if (this->_State == Progress && ((this->_Selected[0].Player[0].Die && this->_Selected[0].Player[1].Die) || (this->_Selected[1].Player[0].Die && this->_Selected[1].Player[1].Die)))
		{
			this->_State = Died;
			this->_Count = 4;
		}
	}
}

void cPairEvent::Move()
{
	if (this->_State == Progress || this->_State == Died)
	{
		if (this->_Selected[0].Player[0].Move > 0)
		{
			this->_Selected[0].Player[0].Move--;

			if (this->_Selected[0].Player[0].Move == 1 && this->_Selected[0].Player[0].lpObj)
			{
				if (this->_Selected[0].Player[0].lpObj->RegenOk == 0)
				{
					gObjTeleport(this->_Selected[0].Player[0].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);

					this->_Selected[0].Player[0].Move = 0;
				}
			}
		}

		if (this->_Selected[0].Player[1].Move > 0)
		{
			this->_Selected[0].Player[1].Move--;

			if (this->_Selected[0].Player[1].Move == 1 && this->_Selected[0].Player[1].lpObj)
			{
				if (this->_Selected[0].Player[1].lpObj->RegenOk == 0)
				{
					gObjTeleport(this->_Selected[0].Player[1].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);

					this->_Selected[0].Player[1].Move = 0;
				}
			}
		}

		if (this->_Selected[1].Player[0].Move > 0)
		{
			this->_Selected[1].Player[0].Move--;

			if (this->_Selected[1].Player[0].Move == 1 && this->_Selected[1].Player[0].lpObj)
			{
				if (this->_Selected[1].Player[0].lpObj->RegenOk == 0)
				{
					gObjTeleport(this->_Selected[1].Player[0].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);

					this->_Selected[1].Player[0].Move = 0;
				}
			}
		}

		if (this->_Selected[1].Player[1].Move > 0)
		{
			this->_Selected[1].Player[1].Move--;

			if (this->_Selected[1].Player[1].Move == 1 && this->_Selected[1].Player[1].lpObj)
			{
				if (this->_Selected[1].Player[1].lpObj->RegenOk == 0)
				{
					gObjTeleport(this->_Selected[1].Player[1].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);

					this->_Selected[1].Player[1].Move = 0;
				}
			}
		}
	}
}

void cPairEvent::Quit(LPOBJ lpObj)
{
	if (this->_State != Empty)
	{
		auto it = std::find(this->_Registered.cbegin(), this->_Registered.cend(), lpObj);

		if (it != this->_Registered.cend())
		{
			lpObj->m_PK_Level = 3;

			gObjTeleport(lpObj->m_Index, 0, 125, 125);

			Custom[lpObj->m_Index].InEvent = false;

			this->_Registered.erase(it);
		}

		if (this->_Selected[0].Player[0].lpObj == lpObj || this->_Selected[0].Player[1].lpObj == lpObj)
		{
			BYTE id = this->_Selected[0].Player[0].lpObj == lpObj ? 0 : 1;

			if (this->_Selected[0].Player[id].Select == true)
			{
				this->_Selected[0].Player[id].Quit = true;

				if (this->_Selected[0].Player[id].lpObj)
				{
					this->_Selected[0].Player[id].lpObj->MapNumber = 0;
					this->_Selected[0].Player[id].lpObj->X = 125;
					this->_Selected[0].Player[id].lpObj->Y = 125;
					this->_Selected[0].Player[id].lpObj->m_PK_Level = 3;

					GCPkLevelSend(lpObj->m_Index, 3);

					Custom[lpObj->m_Index].InEvent = false;

					this->_Selected[0].Player[id].lpObj = NULL;
				}
			}

			if (!this->_Selected[0].Player[0].lpObj || !this->_Selected[0].Player[1].lpObj)
			{
				this->_State = WO;
				this->_Count = 0;
			}
		}
		else if (this->_Selected[1].Player[0].lpObj == lpObj || this->_Selected[1].Player[1].lpObj == lpObj)
		{
			BYTE id = this->_Selected[1].Player[0].lpObj == lpObj ? 0 : 1;

			if (this->_Selected[1].Player[id].Select == true)
			{
				this->_Selected[1].Player[id].Quit = true;

				if (this->_Selected[1].Player[id].lpObj)
				{
					gObjTeleport(this->_Selected[1].Player[id].lpObj->m_Index, 0, 125, 125);

					this->_Selected[1].Player[id].lpObj->m_PK_Level = 3;

					GCPkLevelSend(lpObj->m_Index, 3);

					Custom[lpObj->m_Index].InEvent = false;

					this->_Selected[1].Player[id].lpObj = NULL;
				}
			}

			if (!this->_Selected[1].Player[0].lpObj || !this->_Selected[1].Player[1].lpObj)
			{
				this->_State = WO;
				this->_Count = 0;
			}
		}
		else
		{
			if (this->_Teams[0].size() > 0)
			{
				for (auto it = this->_Teams[0].begin(); it != this->_Teams[0].end(); ++it)
				{
					LPOBJ lpTemp = NULL;

					if (it->Player[0].lpObj == lpObj)
					{
						lpTemp = it->Player[0].lpObj;
					}

					if (it->Player[1].lpObj == lpObj)
					{
						lpTemp = it->Player[1].lpObj;
					}

					if (lpTemp)
					{
						it->Player[lpTemp == it->Player[0].lpObj ? 0 : 1].lpObj = NULL;

						gObjTeleport(lpObj->m_Index, 0, 125, 125);

						Custom[lpObj->m_Index].InEvent = false;

						if (!it->Player[0].lpObj && !it->Player[1].lpObj || !it->Player[0].lpObj || !it->Player[1].lpObj)
						{
							if (it->Player[0].lpObj)
							{
								Custom[it->Player[0].lpObj->m_Index].InEvent = false;

								gObjTeleport(it->Player[0].lpObj->m_Index, 0, 125, 125);
							}

							if (it->Player[1].lpObj)
							{
								Custom[it->Player[1].lpObj->m_Index].InEvent = false;

								gObjTeleport(it->Player[1].lpObj->m_Index, 0, 125, 125);
							}

							this->_Teams[0].erase(it);
						}

						break;
					}
				}
			}

			if (this->_Teams[1].size() > 0)
			{
				for (auto it = this->_Teams[1].begin(); it != this->_Teams[1].end(); ++it)
				{
					LPOBJ lpTemp = NULL;

					if (it->Player[0].lpObj == lpObj)
					{
						lpTemp = it->Player[0].lpObj;
					}

					if (it->Player[1].lpObj == lpObj)
					{
						lpTemp = it->Player[1].lpObj;
					}

					if (lpTemp)
					{
						gObjTeleport(lpObj->m_Index, 0, 125, 125);

						Custom[lpObj->m_Index].InEvent = false;

						it->Player[lpTemp == it->Player[0].lpObj ? 0 : 1].lpObj = NULL;

						if (!it->Player[0].lpObj && !it->Player[1].lpObj || !it->Player[0].lpObj || !it->Player[1].lpObj)
						{
							if (it->Player[0].lpObj)
							{
								Custom[it->Player[0].lpObj->m_Index].InEvent = false;

								gObjTeleport(it->Player[0].lpObj->m_Index, 0, 125, 125);
							}

							if (it->Player[1].lpObj)
							{
								Custom[it->Player[1].lpObj->m_Index].InEvent = false;

								gObjTeleport(it->Player[1].lpObj->m_Index, 0, 125, 125);
							}

							this->_Teams[1].erase(it);
						}

						break;
					}
				}
			}
		}
	}
}

cPairEvent PairEvent;