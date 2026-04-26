#include "StdAfx.h"

cSobreEvent::cSobreEvent() : _State(Empty)
{
}

cSobreEvent::~cSobreEvent()
{
}

bool cSobreEvent::Load()
{
	this->_List = 0;

	this->_Players = std::vector<LPOBJ>();

	memset(this->EventStruct, 0, sizeof(this->EventStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/SobreEvent.txt"), Group);

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

bool cSobreEvent::Check(LPOBJ lpObj, const char* Text)
{
	if (lpObj->Authority > 1)
	{
		char Buffer[60], *Token = nullptr, *Context = nullptr;

		strcpy_s(Buffer, Text);
		Token = strtok_s(Buffer, " ", &Context);

		if (this->_State == Empty && !_stricmp(Token, this->_Syntax[1]))
		{
			if (Authority.Check(lpObj, 11) == true)
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
			if (this->_State == Register && lpObj->Live == TRUE)
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

				Custom[lpObj->m_Index].InEvent = true;

				lpObj->m_PK_Level = 6;
				GCPkLevelSend(lpObj->m_Index, 6);
				gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X, this->_Y);
				Func.MsgOutput(lpObj->m_Index, 1, "Você foi registrado no evento. Aguarde...");
			}

			return true;
		}
	}

	return false;
}

void cSobreEvent::Start(int Time)
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

void cSobreEvent::Run()
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
				this->Start(5);
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
			if (this->_Players.size() < 2)
			{
				for (auto it = this->_Players.cbegin(); it != this->_Players.cend(); ++it)
				{
					if ((*it)->Connected == 3)
					{
						Custom[(*it)->m_Index].Move = true;

						Custom[(*it)->m_Index].InEvent = false;

						(*it)->m_PK_Level = 3;
						GCPkLevelSend((*it)->m_Index, 3);
					}
				}

				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3 && Custom[i].InEvent == true)
					{
						Func.MsgOutput(i, 0, "[   SURVIVOR   ]");

						Func.MsgOutput(i, 0, "Evento encerrado. Mínimo de participantes não atingido.");

						Func.MsgOutput(i, 0, "Participantes premiados com 10 Golds!");

						Manager.ExecFormat("UPDATE MEMB_INFO SET Gold = Gold + 10 WHERE memb___id = '%s'", gObj[i].AccountID);

						Manager.CoinCount(i, gObj[i].AccountID);
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
				Func.AllServerAnnounce("Survivor começará em %d Minuto(s)", (this->_Count / 60));
				Func.AllServerAnnounce("Para participar, utilize o comando: %s", this->_Syntax[0]);
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
			for (auto it = this->_Players.cbegin(); it != this->_Players.cend(); ++it)
			{
				if ((*it)->Connected == 3)
				{
					Func.MsgOutput((*it)->m_Index, 0, "O Survivor começará em %d Segundo(s)", this->_Count);
				}
			}
		}
		break;
		case 0:
		{
			Func.AllServerAnnounce("O Survivor começou!");

			this->_State = Fight;
			this->_Count = 0;
		}
		break;
		}
	}
	break;
	case Fight:
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
					Func.MsgOutput(i, 0, "[   SURVIVOR    ]");

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

			Custom[lpObj->m_Index].InEvent = false;
			Custom[lpObj->m_Index].Move = true;

			lpObj->m_PK_Level = 3;
			GCPkLevelSend(lpObj->m_Index, 3);

			Manager.ExecFormat(Query._Query[15], lpObj->Name);
			Manager.ExecFormat(Query._Query[16], lpObj->AccountID);

			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3)
				{
					Func.MsgOutput(i, 0, "%s é o campeão do Survivor!", lpObj->Name);
					Func.MsgOutput(i, 0, this->_Notice);
				}
			}

			this->_Players.clear();

			this->_State = Empty;
			this->_Count = 0;
		}
	}
	break;
	}
}

bool cSobreEvent::Attack(LPOBJ lpObj, LPOBJ Target)
{
	auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), Target);

	if (it != this->_Players.cend())
	{
		if (this->_State == Register || this->_State == Progress)
		{
			if ((*it)->Type == PLAYER)
			{
				return false;
			}
		}
	}

	return true;
}

void cSobreEvent::Die(LPOBJ lpObj, LPOBJ Target)
{
	if (this->_State == Fight)
	{
		if (this->_Players.size() > 1 && Custom[lpObj->m_Index].InEvent == true)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

			if (it != this->_Players.cend())
			{
				if (lpObj->Type == PLAYER && Target->Type == PLAYER)
				{
					Func.AllServerAnnounce("%s Eliminado(a) do Survivor!", lpObj->Name);

					Custom[lpObj->m_Index].Dead = true;

					Custom[lpObj->m_Index].InEvent = false;

					this->_Players.erase(it);
				}
			}
		}
	}
}

void cSobreEvent::Quit(LPOBJ lpObj)
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

				Custom[lpObj->m_Index].InEvent = false;

				lpObj->m_PK_Level = 3;
				GCPkLevelSend(lpObj->m_Index, 3);

				this->_Players.erase(it);
			}
		}
	}
}

cSobreEvent SobreEvent;
