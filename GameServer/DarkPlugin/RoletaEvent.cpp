#include "StdAfx.h"

cRoletaEvent::cRoletaEvent() : _State(Empty)
{
}

cRoletaEvent::~cRoletaEvent()
{
}

bool cRoletaEvent::Load()
{
	this->_Players = std::vector<LPOBJ>();

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/RoletaEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[0], sizeof(this->_Syntax[0]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Syntax[1], sizeof(this->_Syntax[1]), (Section.Rows[0].GetStringPtr(2)));

		this->_MapNumber = Section.Rows[1].GetInt(0);
		this->_X = Section.Rows[1].GetInt(1);
		this->_Y = Section.Rows[1].GetInt(2);

		strcpy_s(this->_Notice, sizeof(this->_Notice), (Section.Rows[2].GetStringPtr(0)));
	}

	return true;
}

bool cRoletaEvent::Check(LPOBJ lpObj, const char* Text)
{
	if (lpObj->Authority > 1)
	{
		char Buffer[60], *Token = nullptr, *Context = nullptr;

		strcpy_s(Buffer, Text);
		Token = strtok_s(Buffer, " ", &Context);

		if (this->_State == Empty && !_stricmp(Token, this->_Syntax[1]))
		{
			if (Authority.Check(lpObj, 13) == true)
			{
				char* Time = strtok_s(nullptr, " ", &Context);

				if (!Time)
				{
					Func.MsgOutput(lpObj->m_Index, 1, "Erro de sintaxe!");
					Func.MsgOutput(lpObj->m_Index, 1, "Digite: %s <tempo>", this->_Syntax[1]);
					return true;
				}

				gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X, this->_Y);

				this->Start(atoi(Time));
				return true;
			}
		}
	}
	else
	{
		if (!_stricmp(Text, this->_Syntax[0]))
		{
			if (this->_State == Register)
			{
				auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

				if (it != this->_Players.cend())
				{
					Func.MsgOutput(lpObj->m_Index, 1, "Você já está registrado no evento. Aguarde.");
					return true;
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

				this->_Players.push_back(lpObj);

				this->PlayerStruct[lpObj->m_Index]._InEvent = true;

				gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X, this->_Y);

				Func.MsgOutput(lpObj->m_Index, 1, "Você foi registrado no evento. Aguarde...");
			}

			return true;
		}
	}

	return false;
}

void cRoletaEvent::Start(int Time)
{
	if (Time == 0)
	{
		Time++;
	}

	if (this->_Players.size() > 0)
	{
		this->_Players.clear();
	}

	this->_State = Register;
	this->_Count = (Time * 60) + 1;
}

void cRoletaEvent::Run()
{
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
			if (this->_Players.size() < 2)
			{
				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						Func.MsgOutput(i, 0, "[   ROLETA RUSSA   ]");

						Func.MsgOutput(i, 0, "Evento encerrado. Mínimo de participantes não atingido.");

						Func.MsgOutput(i, 0, "Participantes premiados com 10 Golds!");

						Manager.ExecFormat("UPDATE MEMB_INFO SET Gold = Gold + 10 WHERE memb___id = '%s'", gObj[i].AccountID);

						Manager.CoinCount(i, gObj[i].AccountID);

						if (this->PlayerStruct[i]._InEvent == true)
						{
							this->PlayerStruct[i]._InEvent = false;

							Custom[i].Move = true;
						}
					}
				}

				this->_State = Empty;
				this->_Count = 0;
			}
			else
			{
				Func.AllServerAnnounce("Inscrições para o evento encerradas.");

				this->_State = Progress;
				this->_Count = 6;
			}
		}
		else
		{
			if ((this->_Count % 60) == 0)
			{
				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3)
					{
						Func.MsgOutput(i, 0, "[   ROLETA RUSSA   ]");

						Func.MsgOutput(i, 0, "O evento começará em %d Minuto(s)", (this->_Count / 60));

						Func.MsgOutput(i, 0, "Para participar, utilize o comando: %s", this->_Syntax[0]);
					}
				}
			}
		}
	}
	break;
	case Progress:
	{
		switch (this->_Count)
		{
		case 5:
		case 4:
		case 3:
		case 2:
		case 1:
		{
			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3)
				{
					Func.MsgOutput(i, 0, "[   ROLETA RUSSA   ]");

					Func.MsgOutput(i, 0, "O evento começará em %d Segundo(s)", this->_Count);
				}
			}
		}
		break;
		case 0:
		{
			Func.AllServerAnnounce("O evento começou!");

			this->_State = Waiting;
		}
		break;
		}
	}
	break;
	case Waiting:
	{
		if (this->_Players.size() == 1 || this->_Players.size() == 0)
		{
			this->_State = Final;
			this->_Count = 0;
		}
	}
	break;
	case Final:
	{
		if (this->_Players.size() == 0)
		{
			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3)
				{
					Func.MsgOutput(i, 0, "[   ROLETA RUSSA   ]");

					Func.MsgOutput(i, 0, "O evento não teve vencedor!");
				}
			}

			this->_Players.clear();

			this->_State = Empty;
			this->_Count = 0;
		}
		else
		{
			LPOBJ lpObj = this->_Players.front();

			Manager.ExecFormat(Query._Query[34], lpObj->Name);
			Manager.ExecFormat(Query._Query[35], lpObj->AccountID);

			this->PlayerStruct[lpObj->m_Index]._InEvent = false;

			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3)
				{
					Func.MsgOutput(i, 0, "[   ROLETA RUSSA   ]");

					Func.MsgOutput(i, 0, "%s venceu o evento!", lpObj->Name);

					Func.MsgOutput(i, 0, this->_Notice);
				}
			}

			Func.FireWork(lpObj->m_Index);

			this->_Players.clear();

			this->_State = Empty;
			this->_Count = 0;
		}
	}
	break;
	}
}

bool cRoletaEvent::Attack(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpTargetObj);

	if (it != this->_Players.cend())
	{
		if (this->_State != Empty)
		{
			if ((*it)->Type == 1 && this->PlayerStruct[(*it)->m_Index]._InEvent == true)
			{
				return false;
			}
		}
	}

	return true;
}

bool cRoletaEvent::Trade(PMSG_TRADE_REQUEST * Result, int aIndex)
{
	if (this->_State == Waiting && this->_Time == 0 && gObj[aIndex].Authority > 1)
	{
		int Target = MAKE_NUMBER(Result->NumberH, Result->NumberL);

		if (this->PlayerStruct[Target]._InEvent == true)
		{
			this->_Time = 5;

			this->PlayerStruct[Target]._Index = Target;

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)cRoletaEvent::Fire, (void*)Target, 0, 0);
			return false;
		}
	}

	return true;
}

void cRoletaEvent::Fire(int aIndex)
{
	while (true)
	{
		if (RoletaEvent._Time > 0)
		{
			RoletaEvent._Time--;

			switch (RoletaEvent._Time)
			{
			case 4:
			{
				Func.AllServerAnnounce("[    ATENÇÃO    ]");
			}
			break;
			case 3:
			{
				Func.AllServerAnnounce("Colocando a bala no tambor...");
			}
			break;
			case 2:
			{
				Func.AllServerAnnounce("Girando o tambor e engatilhando...");
			}
			break;
			case 1:
			{
				Func.AllServerAnnounce("Fogo!");
			}
			break;
			case 0:
			{
				int Target = RoletaEvent.PlayerStruct[aIndex]._Index;

				srand(time(NULL));

				int Sortear = rand() % 6;

				if (Sortear == 2 || Sortear == 5)
				{
					Func.AllServerAnnounce("%s eliminado(a)!", gObj[Target].Name);

					RoletaEvent.Die(&gObj[Target]);
				}
				else
				{
					Func.AllServerAnnounce("%s escapou ileso!", gObj[Target].Name);
				}
			}
			break;
			}
		}
		else
		{
			_endthread();
		}

		Sleep(1000);
	}
}

void cRoletaEvent::Die(LPOBJ Target)
{
	auto it = std::find(RoletaEvent._Players.cbegin(), RoletaEvent._Players.cend(), Target);

	if (it != this->_Players.cend())
	{
		Target->Live = FALSE;
		Target->RegenTime = GetTickCount();
		Target->DieRegen = TRUE;

		GCDiePlayerSend(Target, Target->m_Index, 0, 0);

		Custom[Target->m_Index].Move = true;

		this->PlayerStruct[Target->m_Index]._InEvent = false;

		this->_Players.erase(it);
	}
}

void cRoletaEvent::Quit(LPOBJ lpObj)
{
	if (this->_State != Empty)
	{
		if (this->_Players.size() > 0)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

			if (it != this->_Players.cend())
			{
				lpObj->MapNumber = 0;
				lpObj->X = 125;
				lpObj->Y = 125;

				this->PlayerStruct[lpObj->m_Index]._InEvent = false;

				this->_Players.erase(it);
			}
		}
	}
}

cRoletaEvent RoletaEvent;