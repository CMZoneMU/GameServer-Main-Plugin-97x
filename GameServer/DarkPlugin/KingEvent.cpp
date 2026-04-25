#include "StdAfx.h"

cKingEvent::cKingEvent() : _State(Empty)
{
}

cKingEvent::~cKingEvent()
{
}

bool cKingEvent::Load()
{
	this->_List = 0;

	this->_Players[0] = std::vector<KingPlayer>();
	this->_Players[1] = std::vector<KingPlayer>();

	memset(this->EventStruct, 0, sizeof(this->EventStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/KingEvent.txt"), Group);

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

bool cKingEvent::Check(LPOBJ lpObj, const char* Text)
{
	if (lpObj->Authority > 1)
	{
		char Buffer[60], *Token = nullptr, *Context = nullptr;

		strcpy_s(Buffer, Text);
		Token = strtok_s(Buffer, " ", &Context);

		if (this->_State == Empty && !_stricmp(Token, this->_Syntax[1]))
		{
			if (Authority.Check(lpObj, 14) == true)
			{
				char* Time = strtok_s(nullptr, " ", &Context);
				char* Class = strtok_s(nullptr, " ", &Context);

				if (!Time || !Class)
				{
					Func.MsgOutput(lpObj->m_Index, 1, "Erro de sintaxe!");
					Func.MsgOutput(lpObj->m_Index, 1, "Digite: %s <tempo> <class>", this->_Syntax[1]);
					Func.MsgOutput(lpObj->m_Index, 1, "ID de classes: ");
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
						Func.MsgOutput(lpObj->m_Index, 1, "Rei exclusivo para Dark Wizards e Soul Masters");
						break;
					case 1:
						Func.MsgOutput(lpObj->m_Index, 1, "Rei exclusivo para Dark Knights e Blade Knights");
						break;
					case 2:
						Func.MsgOutput(lpObj->m_Index, 1, "Rei exclusivo para Elfs e Muse Elfs");
						break;
					case 3:
						Func.MsgOutput(lpObj->m_Index, 1, "Rei exclusivo para Magic Gladiators");
						break;
					}

					return true;
				}

				if (this->_Players[0].size() > 0)
				{
					for (auto it = this->_Players[0].cbegin(); it != this->_Players[0].cend(); ++it)
					{
						if (it->lpObj == lpObj)
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

				KingPlayer Player;

				Player.Die = false;

				Player.lpObj = lpObj;

				Custom[lpObj->m_Index].InEvent = true;

				this->_Players[0].push_back(Player);

				gObjTeleport(lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);
				Func.MsgOutput(lpObj->m_Index, 1, "Você foi registrado no evento. Aguarde...");
			}

			return true;
		}
	}

	return false;
}

void cKingEvent::Start(int Time, int Class)
{
	if (Time == 0)
	{
		Time++;
	}

	if (this->_Players[0].size() > 0)
	{
		this->_Players[0].clear();
	}

	if (this->_Players[1].size() > 0)
	{
		this->_Players[1].clear();
	}

	this->_State = Register;
	this->_Count = (Time * 60) + 1;
	this->_Type = (BYTE)(Class);
}

void cKingEvent::Run()
{
	if (this->_Active == false)
	{
		return;
	}

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
			if (this->_Players[0].size() < 2)
			{
				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3 && Custom[i].InEvent == true)
					{
						Func.MsgOutput(i, 0, "[   REI DO MU   ]");

						Func.MsgOutput(i, 0, "Evento encerrado. Mínimo de participantes não atingido.");

						Func.MsgOutput(i, 0, "Participantes premiados com 10 Golds!");

						Manager.ExecFormat("UPDATE MEMB_INFO SET Gold = Gold + 10 WHERE memb___id = '%s'", gObj[i].AccountID);

						Manager.CoinCount(i, gObj[i].AccountID);

						Custom[i].InEvent = false;

						Custom[i].Move = true;
					}
				}

				this->_State = Empty;
				this->_Count = 0;
			}
			else
			{

				sprintf_s(KingEvent._Buffer[0], "Inscrições para o evento encerradas.");
				sprintf_s(KingEvent._Buffer[1], "PRIMEIRA RODADA!");

				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						GCServerMsgStringSend(KingEvent._Buffer[0], i, 0);
						GCServerMsgStringSend(KingEvent._Buffer[1], i, 0);
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
				sprintf_s(KingEvent._Buffer[0], "O Rei do Mu começará em %d Minuto(s)", (this->_Count / 60));
				sprintf_s(KingEvent._Buffer[1], "Para participar, utilize o comando: %s", this->_Syntax[0]);

				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						GCServerMsgStringSend(KingEvent._Buffer[0], i, 0);
						GCServerMsgStringSend(KingEvent._Buffer[1], i, 0);
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
			switch (this->_Players[0].size())
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
				this->_Selected[0] = this->_Players[0].front();

				sprintf_s(KingEvent._Buffer[0], "[   REI DO MU   ]");

				sprintf_s(KingEvent._Buffer[1], "%s venceu de W.O.", this->_Selected[0].lpObj->Name);

				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						GCServerMsgStringSend(KingEvent._Buffer[0], i, 0);
						GCServerMsgStringSend(KingEvent._Buffer[1], i, 0);
					}
				}

				this->_Players[1].push_back(this->_Selected[0]);

				this->_State = NextStage;
				this->_Count = 0;
			}
			break;
			default:
			{
				auto Player1 = this->_Players[0].begin();
				auto Player2 = (--this->_Players[0].end());

				while (true)
				{
					if (Player1->lpObj->m_socket == INVALID_SOCKET || Player1->lpObj->Connected != 3)
					{
						this->_Players[0].erase(Player1);

						Player1 = this->_Players[0].begin();
					}
					else if (Player2->lpObj->m_socket == INVALID_SOCKET || Player2->lpObj->Connected != 3)
					{
						this->_Players[0].erase(Player2);

						Player2 = (--this->_Players[0].end());
					}
					else
					{
						break;
					}
				}

				if (Player1 == Player2)
				{
					goto SelectWO;
				}
				else
				{
					this->_Selected[0] = *Player1;
					this->_Selected[1] = *Player2;

					this->_Selected[0].Die = false;
					this->_Selected[0].Quit = false;
					this->_Selected[0].Score = 0;
					this->_Selected[1].Die = false;
					this->_Selected[1].Quit = false;
					this->_Selected[1].Score = 0;

					sprintf_s(KingEvent._Buffer[0], "[   REI DO MU   ]");

					sprintf_s(KingEvent._Buffer[1], "%s  vs  %s", this->_Selected[0].lpObj->Name, this->_Selected[1].lpObj->Name);

					for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
					{
						if (gObj[i].Connected == 3)
						{
							GCServerMsgStringSend(KingEvent._Buffer[0], i, 0);
							GCServerMsgStringSend(KingEvent._Buffer[1], i, 0);
						}
					}

					Func.MsgOutput(this->_Selected[0].lpObj->m_Index, 0, "[    ATENÇÃO    ]");
					Func.MsgOutput(this->_Selected[1].lpObj->m_Index, 0, "[    ATENÇÃO    ]");

					this->_Sended = false;

					this->_State = Progress;
					this->_Count = 6;

					gObjTeleport(this->_Selected[0].lpObj->m_Index, this->_MapNumber[1], this->_X[1], this->_Y[1]);
					gObjTeleport(this->_Selected[1].lpObj->m_Index, this->_MapNumber[1], this->_X[1], this->_Y[1]);

					this->_Selected[0].lpObj->m_PK_Level = 6;
					this->_Selected[0].Select = true;
					this->_Selected[1].lpObj->m_PK_Level = 6;
					this->_Selected[1].Select = true;
					GCPkLevelSend(this->_Selected[0].lpObj->m_Index, 6);
					GCPkLevelSend(this->_Selected[1].lpObj->m_Index, 6);

					this->_Players[0].erase(Player2);
					this->_Players[0].erase(Player1);
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
		case 3:
		case 2:
		case 1:
		{
			Func.MsgOutput(this->_Selected[0].lpObj->m_Index, 0, "Você poderá atacar em %d segundo(s)", this->_Count);
			Func.MsgOutput(this->_Selected[1].lpObj->m_Index, 0, "Você poderá atacar em %d segundo(s)", this->_Count);
		}
		break;
		case 0:
		{
			if (this->_Sended == false)
			{
				Func.MsgOutput(this->_Selected[0].lpObj->m_Index, 0, "Já!");
				Func.MsgOutput(this->_Selected[1].lpObj->m_Index, 0, "Já!");

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
			if (this->_Selected[0].Die && this->_Selected[1].Die)
			{
				Func.AllServerAnnounce("Draw!");

				this->_Sended = true;

				this->_State = Progress;
				this->_Count = 0;

			}
			else
			{
				BYTE Winner = (this->_Selected[0].Die) ? 1 : 0;
				BYTE Loser = (Winner == 1) ? 0 : 1;

				this->_Selected[Winner].Score++;

				sprintf_s(KingEvent._Buffer[0], "[    PLACAR    ]");

				sprintf_s(KingEvent._Buffer[1], "%s  vs  %s", this->_Selected[0].lpObj->Name, this->_Selected[1].lpObj->Name);

				sprintf_s(KingEvent._Buffer[2], "%d   x   %d", this->_Selected[0].Score, this->_Selected[1].Score);

				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						GCServerMsgStringSend(KingEvent._Buffer[0], i, 0);
						GCServerMsgStringSend(KingEvent._Buffer[1], i, 0);
						GCServerMsgStringSend(KingEvent._Buffer[2], i, 0);
					}
				}

				if (this->_Selected[Winner].Score >= 5)
				{
					Func.AllServerAnnounce("%s venceu!", this->_Selected[Winner].lpObj->Name);

					this->_Players[1].push_back(this->_Selected[Winner]);

					this->_Selected[0].lpObj->m_PK_Level = 3;
					this->_Selected[0].Select = false;
					this->_Selected[1].lpObj->m_PK_Level = 3;
					this->_Selected[1].Select = false;
					GCPkLevelSend(this->_Selected[0].lpObj->m_Index, 3);
					GCPkLevelSend(this->_Selected[1].lpObj->m_Index, 3);

					gObjTeleport(this->_Selected[Winner].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);
					gObjTeleport(this->_Selected[Loser].lpObj->m_Index, 0, 125, 125);

					Custom[this->_Selected[Loser].lpObj->m_Index].InEvent = false;

					this->_State = Select;
					this->_Count = 0;
				}
				else
				{
					this->_Sended = true;

					this->_State = Progress;
					this->_Count = 0;
				}
			}

			this->_Selected[0].Die = false;
			this->_Selected[1].Die = false;
		}
	}
	break;
	case NextStage:
	{
		if (this->_Players[0].size() > 0)
		{
			this->_Players[0].clear();
		}

		this->_Players[0] = this->_Players[1];

		if (this->_Players[1].size() > 0)
		{
			this->_Players[1].clear();
		}

		this->_Selected[0].lpObj = NULL;
		this->_Selected[1].lpObj = NULL;

		switch (this->_Players[0].size())
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
			if ((this->_Players[0].size() % 2) == 0)
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
		BYTE Winner = (this->_Selected[0].Quit) ? 1 : 0;
		BYTE Loser = (Winner == 1) ? 0 : 1;

		Func.AllServerAnnounce("%s venceu por W.O.", this->_Selected[Winner].lpObj->Name);

		this->_Players[1].push_back(this->_Selected[Winner]);

		this->_Selected[0].lpObj->m_PK_Level = 3;
		this->_Selected[0].Select = false;
		this->_Selected[1].lpObj->m_PK_Level = 3;
		this->_Selected[1].Select = false;
		GCPkLevelSend(this->_Selected[0].lpObj->m_Index, 3);
		GCPkLevelSend(this->_Selected[1].lpObj->m_Index, 3);

		gObjTeleport(this->_Selected[Winner].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);
		gObjTeleport(this->_Selected[Loser].lpObj->m_Index, 0, 125, 125);

		Custom[this->_Selected[Loser].lpObj->m_Index].InEvent = false;

		this->_State = Select;
		this->_Count = 0;
	}
	break;
	case Final:
	{
		LPOBJ lpObj = this->_Players[0].front().lpObj;

		Manager.ExecFormat("UPDATE Character SET ReiEvent = 0");

		Manager.ExecFormat(Query._Query[40], lpObj->Name);
		Manager.ExecFormat(Query._Query[41], lpObj->AccountID);

		sprintf_s(KingEvent._Buffer[0], "%s é o campeão do Rei do Mu!", lpObj->Name);
		sprintf_s(KingEvent._Buffer[1], this->_Notice);

		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].Connected == 3)
			{
				GCServerMsgStringSend(KingEvent._Buffer[0], i, 0);
				GCServerMsgStringSend(KingEvent._Buffer[1], i, 0);
			}
		}

		gObjTeleport(lpObj->m_Index, 0, 125, 125);

		Custom[lpObj->m_Index].InEvent = false;

		this->_Players[0].clear();
		this->_Players[1].clear();

		this->_State = Empty;
		this->_Count = 0;
	}
	break;
	}
}

bool cKingEvent::Attack(LPOBJ lpObj, LPOBJ Target)
{
	if (this->_State == Progress)
	{
		if (this->_Selected[0].lpObj != lpObj && this->_Selected[1].lpObj != lpObj &&
			this->_Selected[0].lpObj != Target && this->_Selected[1].lpObj != Target)
		{
			return true;
		}

		if (this->_Selected[0].lpObj == lpObj && this->_Selected[1].lpObj == Target ||
			this->_Selected[1].lpObj == lpObj && this->_Selected[0].lpObj == Target)
		{
			if (this->_Count == 0)
			{
				return true;
			}

			return false;
		}

		if (this->_Selected[0].lpObj == lpObj && this->_Selected[1].lpObj->Type == MONSTER ||
			this->_Selected[1].lpObj == lpObj && this->_Selected[0].lpObj->Type == MONSTER)
		{
			return true;
		}

		return false;
	}

	return true;
}

void cKingEvent::Die(LPOBJ lpObj)
{
	if (this->_State == Progress || this->_State == Died)
	{
		if (this->_Selected[0].lpObj == lpObj)
		{
			this->_Selected[0].Die = true;
		}

		if (this->_Selected[1].lpObj == lpObj)
		{
			this->_Selected[1].Die = true;
		}

		if (this->_State == Progress && (this->_Selected[0].Die || this->_Selected[1].Die))
		{
			this->_State = Died;
			this->_Count = 4;
		}
	}
}

void cKingEvent::Quit(LPOBJ lpObj)
{
	if (this->_State != Empty)
	{
		if (this->_Selected[0].lpObj == lpObj)
		{
			if (this->_Selected[0].Select == true)
			{
				this->_Selected[0].Quit = true;

				this->_Selected[0].lpObj->MapNumber = 0;

				this->_Selected[0].lpObj->X = 125;

				this->_Selected[0].lpObj->Y = 125;

				this->_Selected[0].lpObj->m_PK_Level = 3;

				GCPkLevelSend(this->_Selected[0].lpObj->m_Index, 3);

				this->_State = WO;
				this->_Count = 0;
			}
		}
		else if (this->_Selected[1].lpObj == lpObj)
		{
			if (this->_Selected[1].Select == true)
			{
				this->_Selected[1].Quit = true;

				this->_Selected[1].lpObj->MapNumber = 0;

				this->_Selected[1].lpObj->X = 125;

				this->_Selected[1].lpObj->Y = 125;

				this->_Selected[1].lpObj->m_PK_Level = 3;

				GCPkLevelSend(this->_Selected[1].lpObj->m_Index, 3);

				this->_State = WO;
				this->_Count = 0;
			}
		}
		else
		{
			if (this->_Players[0].size() > 0)
			{
				for (auto it = this->_Players[0].cbegin(); it != this->_Players[0].cend(); ++it)
				{
					if (it->lpObj == lpObj)
					{
						lpObj->MapNumber = 0; lpObj->X = 125; lpObj->Y = 125;

						Custom[lpObj->m_Index].InEvent = false;

						lpObj->m_PK_Level = 3;

						GCPkLevelSend(lpObj->m_Index, 3);

						this->_Players[0].erase(it);
						break;
					}
				}
			}

			if (this->_Players[1].size() > 0)
			{
				for (auto it = this->_Players[1].cbegin(); it != this->_Players[1].cend(); ++it)
				{
					if (it->lpObj == lpObj)
					{
						lpObj->MapNumber = 0; lpObj->X = 125; lpObj->Y = 125;

						Custom[lpObj->m_Index].InEvent = false;

						lpObj->m_PK_Level = 3;

						GCPkLevelSend(lpObj->m_Index, 3);

						this->_Players[1].erase(it);
						break;
					}
				}
			}
		}
	}
}

cKingEvent KingEvent;