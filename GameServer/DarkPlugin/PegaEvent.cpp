#include "StdAfx.h"

cPegaEvent::cPegaEvent() : _State(Empty)
{
}

cPegaEvent::~cPegaEvent()
{
}

bool cPegaEvent::Load()
{
	this->_Players = std::vector<LPOBJ>();

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/PegaEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(&this->_Syntax[0][0], sizeof(this->_Syntax[0]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(&this->_Syntax[1][0], sizeof(this->_Syntax[1]), (Section.Rows[0].GetStringPtr(2)));

		this->_MapNumber = Section.Rows[1].GetInt(0);
		this->_X = Section.Rows[1].GetInt(1);
		this->_Y = Section.Rows[1].GetInt(2);

		strcpy_s(&this->_Notice[0][0], sizeof(this->_Notice[0]), (Section.Rows[2].GetStringPtr(0)));
		strcpy_s(&this->_Notice[1][0], sizeof(this->_Notice[1]), (Section.Rows[3].GetStringPtr(0)));
		strcpy_s(&this->_Notice[2][0], sizeof(this->_Notice[2]), (Section.Rows[4].GetStringPtr(0)));
	}

	return true;
}

bool cPegaEvent::Check(LPOBJ lpObj, const char* Text)
{
	if (lpObj->Authority > 1)
	{
		char Buffer[60], *Token = nullptr, *Context = nullptr;

		strcpy_s(Buffer, Text);
		Token = strtok_s(Buffer, " ", &Context);

		if (this->_State == Empty && !_stricmp(Token, this->_Syntax[1]))
		{
			if (Authority.Check(lpObj, 10) == true)
			{
				char* Time = strtok_s(nullptr, " ", &Context);

				if (!Time)
				{
					Func.MsgOutput(lpObj->m_Index, 1, "Erro de sintaxe! Digite: %s <tempo>", this->_Syntax[1]);
					Func.MsgOutput(lpObj->m_Index, 1, "Exemplo -> %s 3", this->_Syntax[1]);
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
				if (!this->CheckItem(lpObj))
				{
					return true;
				}

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

				gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X, this->_Y);

				Custom[lpObj->m_Index].InEvent = true;

				Func.MsgOutput(lpObj->m_Index, 1, "Você foi registrado no evento. Aguarde...");
			}

			return true;
		}
	}

	return false;
}

void cPegaEvent::Start(int Time)
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

void cPegaEvent::Run()
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
			if (this->_Players.size() < 5)
			{
				for (auto it = this->_Players.cbegin(); it != this->_Players.cend(); ++it)
				{
					if ((*it)->Connected == 3)
					{
						Custom[(*it)->m_Index].Move = true;

						Custom[(*it)->m_Index].InEvent = false;
					}
				}

				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3 && Custom[i].InEvent == true)
					{
						Func.MsgOutput(i, 0, "[   PEGA-PEGA   ]");
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

				this->_State = Capture;
				this->_Count = 6;
			}
		}
		else
		{
			if ((this->_Count % 60) == 0)
			{
				Func.AllServerAnnounce("Pega-Pega começará em %d Minuto(s)", (this->_Count / 60));
				Func.AllServerAnnounce("Para participar, utilize o comando: %s", this->_Syntax[0]);
			}
		}
	}
	break;
	case Capture:
	{
		switch (this->_Count)
		{
		case 5:
		case 4:
		case 3:
		case 2:
		case 1:
		{
			for (auto it = this->_Players.cbegin(); it != this->_Players.cend(); ++it)
			{
				if ((*it)->Connected == 3)
				{
					Func.MsgOutput((*it)->m_Index, 0, "O GM começará a pegar em %d Segundo(s)", this->_Count);
				}
			}
		}
		break;
		case 0:
		{
			Func.AllServerAnnounce("Corra! O GM começou a capturar!");

			this->_State = Progress;
		}
		break;
		}
	}
	break;
	case Progress:
		break;
	case Final:
	{
		Manager.ExecFormat(Query._Query[11], this->_Name[2]);

		Manager.ExecFormat(Query._Query[12], this->_Account[0]);
		Manager.ExecFormat(Query._Query[13], this->_Account[1]);
		Manager.ExecFormat(Query._Query[14], this->_Account[2]);

		Func.AllServerAnnounce("[   PEGA-PEGA   ]");

		Func.AllServerAnnounce("1º Lugar: %s / %s", this->_Name[2], this->_Notice[2]);

		Func.AllServerAnnounce("2º Lugar: %s / %s", this->_Name[1], this->_Notice[1]);

		Func.AllServerAnnounce("3º Lugar: %s / %s", this->_Name[0], this->_Notice[0]);

		for (auto it = this->_Players.cbegin(); it != this->_Players.cend(); ++it)
		{
			if ((*it)->Connected == 3)
			{
				Custom[(*it)->m_Index].InEvent = false;
			}
		}

		this->_Players.clear();

		this->_State = Empty;
		this->_Count = 0;
	}
	break;
	}
}

bool cPegaEvent::CheckItem(LPOBJ lpObj)
{
	if (lpObj->pInventory[7].IsItem())
	{
		Func.MsgOutput(lpObj->m_Index, 1, "Você não pode participar do evento!");
		Func.MsgOutput(lpObj->m_Index, 1, "Proibido usar asas.");
		return false;
	}

	if (lpObj->pInventory[8].IsItem() && lpObj->pInventory[8].m_Type == ITEMGET(13, 2))
	{
		Func.MsgOutput(lpObj->m_Index, 1, "Você não pode participar do evento!");
		Func.MsgOutput(lpObj->m_Index, 1, "Proibido usar o uniria.");
		return false;
	}
	else if (lpObj->pInventory[8].IsItem() && lpObj->pInventory[8].m_Type == ITEMGET(13, 3))
	{
		Func.MsgOutput(lpObj->m_Index, 1, "Você não pode participar do evento!");
		Func.MsgOutput(lpObj->m_Index, 1, "Proibido usar o dinorant.");
		return false;
	}

	return true;
}

bool cPegaEvent::Attack(LPOBJ lpObj, LPOBJ Target)
{
	auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), Target);

	if (it != this->_Players.cend())
	{
		if (this->_State == Register || this->_State == Capture)
		{
			if ((*it)->Type == PLAYER)
			{
				return false;
			}
		}
	}

	if (this->_State == Progress && lpObj->Authority > 1)
	{
		if (this->_Players.size() > 0)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), Target);

			if (it != this->_Players.cend())
			{
				Func.AllServerAnnounce("%s - Capturado!", Target->Name);

				switch (this->_Players.size())
				{
				case 3:
				{
					strcpy_s(this->_Name[0], Target->Name);
					strcpy_s(this->_Account[0], Target->AccountID);
				}
				break;
				case 2:
				{
					strcpy_s(this->_Name[1], Target->Name);
					strcpy_s(this->_Account[1], Target->AccountID);

					gObjTeleport(Target->m_Index, 0, 125, 125);

					Custom[Target->m_Index].InEvent = false;

					this->_Players.erase(it);

					it = this->_Players.cbegin();

					strcpy_s(this->_Name[2], (*it)->Name);
					strcpy_s(this->_Account[2], (*it)->AccountID);

					gObjTeleport((*it)->m_Index, 0, 125, 125);

					Custom[(*it)->m_Index].InEvent = false;

					this->_State = Final;
				}
				break;
				case 1:
				{
					strcpy_s(this->_Name[2], Target->Name);
					strcpy_s(this->_Account[2], Target->AccountID);
				}
				break;
				}

				gObjTeleport(Target->m_Index, 0, 125, 125);

				Custom[Target->m_Index].InEvent = false;

				this->_Players.erase(it);
			}
		}
		else
		{
			if (this->_Players.size() > 0)
			{
				auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

				if (it != this->_Players.cend())
				{
					return false;
				}

				it = std::find(this->_Players.cbegin(), this->_Players.cend(), Target);

				if (it != this->_Players.cend())
				{
					return false;
				}
			}
		}
	}

	return true;
}

void cPegaEvent::Quit(LPOBJ lpObj)
{
	if (this->_State != Empty && lpObj->Type == PLAYER)
	{
		if (this->_Players.size() > 0)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

			if (it != this->_Players.cend())
			{
				if (this->_State == Capture || this->_State == Progress)
				{
					switch (this->_Players.size())
					{
					case 3:
					{
						strcpy_s(this->_Name[0], lpObj->Name);
						strcpy_s(this->_Account[0], lpObj->AccountID);
					}
					break;
					case 2:
					{
						strcpy_s(this->_Name[1], lpObj->Name);
						strcpy_s(this->_Account[1], lpObj->AccountID);

						lpObj->MapNumber = 0; lpObj->X = 125; lpObj->Y = 125;

						Custom[lpObj->m_Index].InEvent = false;

						this->_Players.erase(it);

						it = this->_Players.cbegin();

						strcpy_s(this->_Name[2], (*it)->Name);
						strcpy_s(this->_Account[2], (*it)->AccountID);

						Custom[(*it)->m_Index].InEvent = false;

						this->_State = Final;
					}
					break;
					case 1:
					{
						strcpy_s(this->_Name[2], lpObj->Name);
						strcpy_s(this->_Account[2], lpObj->AccountID);
					}
					break;
					}

					(*it)->MapNumber = 0; (*it)->X = 125; (*it)->Y = 125;

					Custom[(*it)->m_Index].InEvent = false;

					this->_Players.erase(it);
				}
				else
				{
					lpObj->MapNumber = 0; lpObj->X = 125; lpObj->Y = 125;

					Custom[lpObj->m_Index].InEvent = false;

					this->_Players.erase(it);
				}
			}
		}
	}
}

bool cPegaEvent::Equip(LPOBJ lpObj, BYTE SourcePos, BYTE TargetPos)
{
	if (this->_State != Empty)
	{
		if (this->_Players.size() > 0)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

			if (it != this->_Players.cend())
			{
				if (TargetPos == 7)
				{
					Func.MsgOutput(lpObj->m_Index, 1, "Você não pode equipar asas no evento.");
					return false;
				}

				if (TargetPos == 8)
				{
					if (lpObj->pInventory[SourcePos].m_Type == ITEMGET(13, 2))
					{
						Func.MsgOutput(lpObj->m_Index, 1, "Você não pode equipar o uniria no evento.");
						return false;
					}
					else if (lpObj->pInventory[SourcePos].m_Type == ITEMGET(13, 3))
					{
						Func.MsgOutput(lpObj->m_Index, 1, "Você não pode equipar o dinorant no evento.");
						return false;
					}
				}
			}
		}
	}

	return true;
}

bool cPegaEvent::Teleport(LPOBJ lpObj)
{
	if (this->_State != Empty)
	{
		if (Custom[lpObj->m_Index].InEvent == true)
		{
			return false;
		}
	}

	return true;
}

cPegaEvent PegaEvent;