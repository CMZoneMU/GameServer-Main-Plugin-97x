#include "StdAfx.h"

cBattleEvent::cBattleEvent() : _State(Empty), _Finish(false)
{
}

cBattleEvent::~cBattleEvent()
{
}

bool cBattleEvent::Load()
{
	for (int i = 0; i < 2; i++)
	{
		this->_List[i] = 0;
	}

	this->_Players = std::vector<LPOBJ>();

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/BattleEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[0], sizeof(this->_Syntax[0]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Syntax[1], sizeof(this->_Syntax[1]), (Section.Rows[0].GetStringPtr(2)));
		strcpy_s(this->_Syntax[2], sizeof(this->_Syntax[2]), (Section.Rows[0].GetStringPtr(3)));
		strcpy_s(this->_Syntax[3], sizeof(this->_Syntax[3]), (Section.Rows[0].GetStringPtr(4)));

		this->_MapNumber = Section.Rows[1].GetInt(0);
		this->_X = Section.Rows[1].GetInt(1);
		this->_Y = Section.Rows[1].GetInt(2);
		this->_Points = Section.Rows[1].GetInt(3);

		strcpy_s(this->_Notice, sizeof(this->_Notice), (Section.Rows[2].GetStringPtr(0)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->EventStruct[this->_List[0]]._Day = Section.Rows[i].GetInt(0);
			this->EventStruct[this->_List[0]]._Hours = Section.Rows[i].GetInt(1);
			this->EventStruct[this->_List[0]]._Minutes = Section.Rows[i].GetInt(2);
			this->EventStruct[this->_List[0]]._Time = Section.Rows[i].GetInt(3);
			this->EventStruct[this->_List[0]]._Class = Section.Rows[i].GetInt(4);
			this->_List[0]++;
		}
	}

	if (Group.GetSection(2, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->EventStruct[this->_List[1]]._Type = Section.Rows[i].GetInt(0);
			this->EventStruct[this->_List[1]]._Index = Section.Rows[i].GetInt(1);
			this->EventStruct[this->_List[1]]._Level = Section.Rows[i].GetInt(2);
			this->EventStruct[this->_List[1]]._Luck = Section.Rows[i].GetInt(3);
			this->EventStruct[this->_List[1]]._Skill = Section.Rows[i].GetInt(4);
			this->EventStruct[this->_List[1]]._Option = Section.Rows[i].GetInt(5);
			this->EventStruct[this->_List[1]]._Excelente = Section.Rows[i].GetInt(6);
			this->_List[1]++;
		}
	}

	return true;
}

bool cBattleEvent::Check(LPOBJ lpObj, const char* Text)
{
	if (lpObj->Authority > 1)
	{
		char Buffer[60], *Token = nullptr, *Context = nullptr;

		strcpy_s(Buffer, Text);
		Token = strtok_s(Buffer, " ", &Context);

		if (this->_State == Empty && !_stricmp(Token, this->_Syntax[1]))
		{
			if (Authority.Check(lpObj, 15) == true)
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

				gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X, this->_Y);

				this->Start(atoi(Time), atoi(Class));
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

				lpObj->m_PK_Level = 6;
				GCPkLevelSend(lpObj->m_Index, lpObj->m_PK_Level);

				this->RollBack(lpObj, 0);

				this->CheckBuffs(lpObj);

				gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X, this->_Y);

				Func.MsgOutput(lpObj->m_Index, 1, "Você foi registrado no evento. Aguarde...");
			}

			return true;
		}
	}

	return false;
}

void cBattleEvent::Start(int Time, int Class)
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
	this->_Type = (BYTE)(Class);
}

void cBattleEvent::Run()
{
	if (this->_Active == false)
	{
		return;
	}

	SYSTEMTIME Now;
	GetLocalTime(&Now);

	for (int i = 0; i < this->_List[0]; i++)
	{
		if (Now.wDayOfWeek == this->EventStruct[i]._Day && Now.wHour == this->EventStruct[i]._Hours && Now.wMinute == this->EventStruct[i]._Minutes && Now.wSecond == 0)
		{
			if (this->_State == Empty)
			{
				this->Start(this->EventStruct[i]._Time, this->EventStruct[i]._Class);
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
				for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
				{
					if (gObj[i].Connected == 3 && this->PlayerStruct[i]._InEvent == true)
					{
						Func.MsgOutput(i, 0, "[    BATTLE ROYALE    ]");
						Func.MsgOutput(i, 0, "Evento encerrado. Mínimo de participantes não atingido.");

						Func.MsgOutput(i, 0, "Participantes premiados com 10 Golds!");

						Manager.ExecFormat("UPDATE MEMB_INFO SET Gold = Gold + 10 WHERE memb___id = '%s'", gObj[i].AccountID);

						Manager.CoinCount(i, gObj[i].AccountID);

						Custom[i].Move = true;

						gObj[i].m_PK_Level = 3;
						GCPkLevelSend(i, gObj[i].m_PK_Level);

						this->RollBack(&gObj[i], 1);

						this->PlayerStruct[i]._InEvent = false;
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
						Func.MsgOutput(i, 0, "[    BATTLE ROYALE    ]");
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
			for (auto it = this->_Players.cbegin(); it != this->_Players.cend(); ++it)
			{
				if ((*it)->Connected == 3)
				{
					Func.MsgOutput((*it)->m_Index, 0, "O Battle Royale começará em %d Segundo(s)", this->_Count);
				}
			}
		}
		break;
		case 0:
		{
			Func.AllServerAnnounce("O Battle Royale começou!");

			int Index = 0;

			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3 && BattleEvent.PlayerStruct[i]._InEvent == true)
				{
					Index = i;
				}
			}

			if (Index > 0)
			{
				this->_Sortear = rand() % this->_List[1];

				ItemSerialCreateSend(Index, this->_MapNumber, this->_X - 8 + rand() % 16, this->_Y - 12 + rand() % 24, ITEMGET(this->EventStruct[this->_Sortear]._Type, this->EventStruct[this->_Sortear]._Index), this->EventStruct[this->_Sortear]._Level, 0, this->EventStruct[this->_Sortear]._Skill, this->EventStruct[this->_Sortear]._Luck, this->EventStruct[this->_Sortear]._Option, -1, this->EventStruct[this->_Sortear]._Excelente);

				this->_Sortear = rand() % this->_List[1];

				ItemSerialCreateSend(Index, this->_MapNumber, this->_X - 8 + rand() % 16, this->_Y - 12 + rand() % 24, ITEMGET(this->EventStruct[this->_Sortear]._Type, this->EventStruct[this->_Sortear]._Index), this->EventStruct[this->_Sortear]._Level, 0, this->EventStruct[this->_Sortear]._Skill, this->EventStruct[this->_Sortear]._Luck, this->EventStruct[this->_Sortear]._Option, -1, this->EventStruct[this->_Sortear]._Excelente);

				this->_Sortear = rand() % this->_List[1];

				ItemSerialCreateSend(Index, this->_MapNumber, this->_X - 8 + rand() % 16, this->_Y - 12 + rand() % 24, ITEMGET(this->EventStruct[this->_Sortear]._Type, this->EventStruct[this->_Sortear]._Index), this->EventStruct[this->_Sortear]._Level, 0, this->EventStruct[this->_Sortear]._Skill, this->EventStruct[this->_Sortear]._Luck, this->EventStruct[this->_Sortear]._Option, -1, this->EventStruct[this->_Sortear]._Excelente);

				this->_Sortear = rand() % this->_List[1];

				ItemSerialCreateSend(Index, this->_MapNumber, this->_X - 8 + rand() % 16, this->_Y - 12 + rand() % 24, ITEMGET(this->EventStruct[this->_Sortear]._Type, this->EventStruct[this->_Sortear]._Index), this->EventStruct[this->_Sortear]._Level, 0, this->EventStruct[this->_Sortear]._Skill, this->EventStruct[this->_Sortear]._Luck, this->EventStruct[this->_Sortear]._Option, -1, this->EventStruct[this->_Sortear]._Excelente);

				this->_Sortear = rand() % this->_List[1];

				ItemSerialCreateSend(Index, this->_MapNumber, this->_X - 8 + rand() % 16, this->_Y - 12 + rand() % 24, ITEMGET(this->EventStruct[this->_Sortear]._Type, this->EventStruct[this->_Sortear]._Index), this->EventStruct[this->_Sortear]._Level, 0, this->EventStruct[this->_Sortear]._Skill, this->EventStruct[this->_Sortear]._Luck, this->EventStruct[this->_Sortear]._Option, -1, this->EventStruct[this->_Sortear]._Excelente);

				this->_Sortear = rand() % this->_List[1];

				ItemSerialCreateSend(Index, this->_MapNumber, this->_X - 8 + rand() % 16, this->_Y - 12 + rand() % 24, ITEMGET(this->EventStruct[this->_Sortear]._Type, this->EventStruct[this->_Sortear]._Index), this->EventStruct[this->_Sortear]._Level, 0, this->EventStruct[this->_Sortear]._Skill, this->EventStruct[this->_Sortear]._Luck, this->EventStruct[this->_Sortear]._Option, -1, this->EventStruct[this->_Sortear]._Excelente);

				this->_Sortear = rand() % this->_List[1];

				ItemSerialCreateSend(Index, this->_MapNumber, this->_X - 8 + rand() % 16, this->_Y - 12 + rand() % 24, ITEMGET(this->EventStruct[this->_Sortear]._Type, this->EventStruct[this->_Sortear]._Index), this->EventStruct[this->_Sortear]._Level, 0, this->EventStruct[this->_Sortear]._Skill, this->EventStruct[this->_Sortear]._Luck, this->EventStruct[this->_Sortear]._Option, -1, this->EventStruct[this->_Sortear]._Excelente);

				this->_Sortear = rand() % this->_List[1];

				ItemSerialCreateSend(Index, this->_MapNumber, this->_X - 8 + rand() % 16, this->_Y - 12 + rand() % 24, ITEMGET(this->EventStruct[this->_Sortear]._Type, this->EventStruct[this->_Sortear]._Index), this->EventStruct[this->_Sortear]._Level, 0, this->EventStruct[this->_Sortear]._Skill, this->EventStruct[this->_Sortear]._Luck, this->EventStruct[this->_Sortear]._Option, -1, this->EventStruct[this->_Sortear]._Excelente);

				this->_Sortear = rand() % this->_List[1];

				ItemSerialCreateSend(Index, this->_MapNumber, this->_X - 8 + rand() % 16, this->_Y - 12 + rand() % 24, ITEMGET(this->EventStruct[this->_Sortear]._Type, this->EventStruct[this->_Sortear]._Index), this->EventStruct[this->_Sortear]._Level, 0, this->EventStruct[this->_Sortear]._Skill, this->EventStruct[this->_Sortear]._Luck, this->EventStruct[this->_Sortear]._Option, -1, this->EventStruct[this->_Sortear]._Excelente);

				this->_Sortear = rand() % this->_List[1];

				ItemSerialCreateSend(Index, this->_MapNumber, this->_X - 8 + rand() % 16, this->_Y - 12 + rand() % 24, ITEMGET(this->EventStruct[this->_Sortear]._Type, this->EventStruct[this->_Sortear]._Index), this->EventStruct[this->_Sortear]._Level, 0, this->EventStruct[this->_Sortear]._Skill, this->EventStruct[this->_Sortear]._Luck, this->EventStruct[this->_Sortear]._Option, -1, this->EventStruct[this->_Sortear]._Excelente);

				Index = 0;
			}

			_beginthread(cBattleEvent::Drop, 0, NULL);

			this->_State = Fight;
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
			this->_Finish = true;

			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3)
				{
					if (this->PlayerStruct[i]._InEvent == true)
					{
						Custom[i].Move = true;

						gObj[i].m_PK_Level = 3;
						GCPkLevelSend(i, gObj[i].m_PK_Level);

						this->RollBack(&gObj[i], 1);

						this->PlayerStruct[i]._InEvent = false;
					}
				}
			}

			Func.AllServerAnnounce("O Battle Royale não teve vencedor!");

			this->_Players.clear();

			this->_State = Empty;
			this->_Count = 0;
		}
		else
		{
			LPOBJ lpObj = this->_Players.front();

			lpObj->m_PK_Level = 3;
			GCPkLevelSend(lpObj->m_Index, 3);

			Manager.ExecFormat(Query._Query[38], lpObj->Name);
			Manager.ExecFormat(Query._Query[39], lpObj->AccountID);

			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3)
				{
					Func.MsgOutput(i, 0, "%s venceu o Battle Royale!", lpObj->Name);
					Func.MsgOutput(i, 0, this->_Notice);
				}
			}

			Custom[lpObj->m_Index].Move = true;

			this->RollBack(lpObj, 1);

			this->PlayerStruct[lpObj->m_Index]._InEvent = false;

			this->_Finish = true;

			this->_Players.clear();

			this->_State = Empty;
			this->_Count = 0;
		}
	}
	break;
	}
}

void cBattleEvent::RollBack(LPOBJ lpObj, int Value)
{
	if (this->PlayerStruct[lpObj->m_Index]._InEvent == true)
	{
		WORD Class = lpObj->Class;

		switch (Value)
		{
		case 0: // - Armazena e limpa.
		{
			for (int i = 0; i < 60; i++)
			{
				this->PlayerStruct[lpObj->m_Index].MagicBack[i] = lpObj->Magic[i];

				lpObj->Magic[i].Clear();
			}

			for (int i = 0; i < 76; i++)
			{
				this->PlayerStruct[lpObj->m_Index].InventoryBack[i] = lpObj->pInventory[i];

				gObjInventoryDeleteItem(lpObj->m_Index, i);

				GCInventoryItemDeleteSend(lpObj->m_Index, i, 1);

				lpObj->pInventory[i].Clear();
			}

			this->PlayerStruct[lpObj->m_Index]._Level = lpObj->Level;
			this->PlayerStruct[lpObj->m_Index]._Points = lpObj->LevelUpPoint;
			this->PlayerStruct[lpObj->m_Index]._Strength = lpObj->Strength;
			this->PlayerStruct[lpObj->m_Index]._Dexterity = lpObj->Dexterity;
			this->PlayerStruct[lpObj->m_Index]._Vitality = lpObj->Vitality;
			this->PlayerStruct[lpObj->m_Index]._Energy = lpObj->Energy;

			lpObj->Level = 400;
			lpObj->LevelUpPoint = this->_Points;

			lpObj->Strength = Class == 0 ? 18 : Class == 1 ? 28 : Class == 2 ? 22 : Class == 3 ? 26 : 26;
			lpObj->Dexterity = Class == 0 ? 18 : Class == 1 ? 20 : Class == 2 ? 25 : Class == 3 ? 26 : 20;
			lpObj->Vitality = Class == 0 ? 15 : Class == 1 ? 25 : Class == 2 ? 20 : Class == 3 ? 26 : 20;
			lpObj->Energy = Class == 0 ? 30 : Class == 1 ? 10 : Class == 2 ? 15 : Class == 3 ? 26 : 15;

			lpObj->Life = lpObj->MaxLife;
			lpObj->AddLife = 0;
			lpObj->Mana = lpObj->MaxMana;
			lpObj->AddMana = 0;
			lpObj->MaxLife = Func.GetStatus(lpObj, Class, 0);
			lpObj->MaxMana = Func.GetStatus(lpObj, Class, 1);
			gObjSetBP(lpObj->m_Index);
			lpObj->BP = lpObj->MaxBP / 2;
			lpObj->AddBP = 0;

			GCItemListSend(lpObj->m_Index);
			GCEquipmentSend(lpObj->m_Index);
			gObjMakePreviewCharSet(lpObj->m_Index);
			GCMagicListMultiSend(lpObj);
			gObjClearViewport(lpObj);

			Func.UpdateCharacter(lpObj->m_Index, true);
		}
		break;
		case 1: // - Limpa e faz a devolução.
		{
			for (int i = 0; i < 60; i++)
			{
				lpObj->Magic[i].Clear();

				lpObj->Magic[i] = this->PlayerStruct[lpObj->m_Index].MagicBack[i];
			}

			for (int i = 0; i < 76; i++)
			{
				gObjInventoryDeleteItem(lpObj->m_Index, i);

				GCInventoryItemDeleteSend(lpObj->m_Index, i, 1);

				lpObj->pInventory[i].Clear();

				if (i < 12)
				{
					lpObj->pInventory[i] = this->PlayerStruct[lpObj->m_Index].InventoryBack[i];
				}
				else
				{
					gObjShopBuyInventoryInsertItem(lpObj->m_Index, this->PlayerStruct[lpObj->m_Index].InventoryBack[i]);
				}
			}

			lpObj->Level = this->PlayerStruct[lpObj->m_Index]._Level;
			lpObj->LevelUpPoint = this->PlayerStruct[lpObj->m_Index]._Points;
			lpObj->Strength = this->PlayerStruct[lpObj->m_Index]._Strength;
			lpObj->Dexterity = this->PlayerStruct[lpObj->m_Index]._Dexterity;
			lpObj->Vitality = this->PlayerStruct[lpObj->m_Index]._Vitality;
			lpObj->Energy = this->PlayerStruct[lpObj->m_Index]._Energy;

			lpObj->Life = lpObj->MaxLife;
			lpObj->AddLife = 0;
			lpObj->Mana = lpObj->MaxMana;
			lpObj->AddMana = 0;
			lpObj->MaxLife = Func.GetStatus(lpObj, Class, 0);
			lpObj->MaxMana = Func.GetStatus(lpObj, Class, 1);
			gObjSetBP(lpObj->m_Index);
			lpObj->BP = lpObj->MaxBP / 2;
			lpObj->AddBP = 0;

			GCItemListSend(lpObj->m_Index);
			GCEquipmentSend(lpObj->m_Index);
			gObjMakePreviewCharSet(lpObj->m_Index);
			GCMagicListMultiSend(lpObj);
			gObjClearViewport(lpObj);

			Func.UpdateCharacter(lpObj->m_Index, true);
		}
		break;
		}
	}
}

bool cBattleEvent::Attack(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpTargetObj);

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

void cBattleEvent::Die(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if (this->_State == Fight)
	{
		if (this->_Players.size() > 1 && this->PlayerStruct[lpObj->m_Index]._InEvent == true)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

			if (it != this->_Players.cend())
			{
				if (lpObj->Type == PLAYER && lpTargetObj->Type == PLAYER)
				{
					Custom[lpObj->m_Index].Dead = true;

					Custom[lpObj->m_Index].Move = true;

					Func.AllServerAnnounce("%s eliminado(a) do Battle Royale!", lpObj->Name);

					this->_Players.erase(it);
				}
			}
		}
	}
}

void cBattleEvent::Quit(LPOBJ lpObj)
{
	if (this->_State != Empty)
	{
		if (this->_Players.size() > 0)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

			if (it != this->_Players.cend())
			{
				if (this->PlayerStruct[lpObj->m_Index]._InEvent == true)
				{
					lpObj->m_PK_Level = 3;
					GCPkLevelSend(lpObj->m_Index, 3);

					Custom[lpObj->m_Index].Move = true;

					this->RollBack(lpObj, 1);

					this->PlayerStruct[lpObj->m_Index]._InEvent = false;

					this->_Players.erase(it);
				}
			}
		}
	}
}

void cBattleEvent::CheckBuffs(LPOBJ lpObj)
{
	if (lpObj->m_SkillAttackTime > 1)
		lpObj->m_SkillAttackTime = 1;
	if (lpObj->m_SkillDefenseTime > 1)
		lpObj->m_SkillDefenseTime = 1;
	if (lpObj->m_WizardSkillDefenseTime > 1)
		lpObj->m_WizardSkillDefenseTime = 1;
	if (lpObj->m_SkillAddLifeTime > 1)
		lpObj->m_SkillAddLifeTime = 1;
	if (lpObj->m_SkillHardenTime > 1)
		lpObj->m_SkillHardenTime = 1;
	if (lpObj->m_SkillMagumReduceDefenseTime > 1)
		lpObj->m_SkillMagumReduceDefenseTime = 1;
}

void cBattleEvent::Drop(void* lpParam)
{
	while (true)
	{
		Sleep(9000);

		int Index = 0;

		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].Connected == 3 && BattleEvent.PlayerStruct[i]._InEvent == true)
			{
				Index = i;
			}
		}

		if (Index > 0)
		{
			BattleEvent._Sortear = rand() % BattleEvent._List[1];

			ItemSerialCreateSend(Index, BattleEvent._MapNumber, BattleEvent._X - 8 + rand() % 16, BattleEvent._Y - 12 + rand() % 24, ITEMGET(BattleEvent.EventStruct[BattleEvent._Sortear]._Type, BattleEvent.EventStruct[BattleEvent._Sortear]._Index), BattleEvent.EventStruct[BattleEvent._Sortear]._Level, 0, BattleEvent.EventStruct[BattleEvent._Sortear]._Skill, BattleEvent.EventStruct[BattleEvent._Sortear]._Luck, BattleEvent.EventStruct[BattleEvent._Sortear]._Option, -1, BattleEvent.EventStruct[BattleEvent._Sortear]._Excelente);

			BattleEvent._Sortear = rand() % BattleEvent._List[1];

			ItemSerialCreateSend(Index, BattleEvent._MapNumber, BattleEvent._X - 8 + rand() % 16, BattleEvent._Y - 12 + rand() % 24, ITEMGET(BattleEvent.EventStruct[BattleEvent._Sortear]._Type, BattleEvent.EventStruct[BattleEvent._Sortear]._Index), BattleEvent.EventStruct[BattleEvent._Sortear]._Level, 0, BattleEvent.EventStruct[BattleEvent._Sortear]._Skill, BattleEvent.EventStruct[BattleEvent._Sortear]._Luck, BattleEvent.EventStruct[BattleEvent._Sortear]._Option, -1, BattleEvent.EventStruct[BattleEvent._Sortear]._Excelente);

			BattleEvent._Sortear = rand() % BattleEvent._List[1];

			ItemSerialCreateSend(Index, BattleEvent._MapNumber, BattleEvent._X - 8 + rand() % 16, BattleEvent._Y - 12 + rand() % 24, ITEMGET(BattleEvent.EventStruct[BattleEvent._Sortear]._Type, BattleEvent.EventStruct[BattleEvent._Sortear]._Index), BattleEvent.EventStruct[BattleEvent._Sortear]._Level, 0, BattleEvent.EventStruct[BattleEvent._Sortear]._Skill, BattleEvent.EventStruct[BattleEvent._Sortear]._Luck, BattleEvent.EventStruct[BattleEvent._Sortear]._Option, -1, BattleEvent.EventStruct[BattleEvent._Sortear]._Excelente);

			BattleEvent._Sortear = rand() % BattleEvent._List[1];

			ItemSerialCreateSend(Index, BattleEvent._MapNumber, BattleEvent._X - 8 + rand() % 16, BattleEvent._Y - 12 + rand() % 24, ITEMGET(BattleEvent.EventStruct[BattleEvent._Sortear]._Type, BattleEvent.EventStruct[BattleEvent._Sortear]._Index), BattleEvent.EventStruct[BattleEvent._Sortear]._Level, 0, BattleEvent.EventStruct[BattleEvent._Sortear]._Skill, BattleEvent.EventStruct[BattleEvent._Sortear]._Luck, BattleEvent.EventStruct[BattleEvent._Sortear]._Option, -1, BattleEvent.EventStruct[BattleEvent._Sortear]._Excelente);

			BattleEvent._Sortear = rand() % BattleEvent._List[1];

			ItemSerialCreateSend(Index, BattleEvent._MapNumber, BattleEvent._X - 8 + rand() % 16, BattleEvent._Y - 12 + rand() % 24, ITEMGET(BattleEvent.EventStruct[BattleEvent._Sortear]._Type, BattleEvent.EventStruct[BattleEvent._Sortear]._Index), BattleEvent.EventStruct[BattleEvent._Sortear]._Level, 0, BattleEvent.EventStruct[BattleEvent._Sortear]._Skill, BattleEvent.EventStruct[BattleEvent._Sortear]._Luck, BattleEvent.EventStruct[BattleEvent._Sortear]._Option, -1, BattleEvent.EventStruct[BattleEvent._Sortear]._Excelente);

			BattleEvent._Sortear = rand() % BattleEvent._List[1];

			ItemSerialCreateSend(Index, BattleEvent._MapNumber, BattleEvent._X - 8 + rand() % 16, BattleEvent._Y - 12 + rand() % 24, ITEMGET(BattleEvent.EventStruct[BattleEvent._Sortear]._Type, BattleEvent.EventStruct[BattleEvent._Sortear]._Index), BattleEvent.EventStruct[BattleEvent._Sortear]._Level, 0, BattleEvent.EventStruct[BattleEvent._Sortear]._Skill, BattleEvent.EventStruct[BattleEvent._Sortear]._Luck, BattleEvent.EventStruct[BattleEvent._Sortear]._Option, -1, BattleEvent.EventStruct[BattleEvent._Sortear]._Excelente);

			BattleEvent._Sortear = rand() % BattleEvent._List[1];

			ItemSerialCreateSend(Index, BattleEvent._MapNumber, BattleEvent._X - 8 + rand() % 16, BattleEvent._Y - 12 + rand() % 24, ITEMGET(BattleEvent.EventStruct[BattleEvent._Sortear]._Type, BattleEvent.EventStruct[BattleEvent._Sortear]._Index), BattleEvent.EventStruct[BattleEvent._Sortear]._Level, 0, BattleEvent.EventStruct[BattleEvent._Sortear]._Skill, BattleEvent.EventStruct[BattleEvent._Sortear]._Luck, BattleEvent.EventStruct[BattleEvent._Sortear]._Option, -1, BattleEvent.EventStruct[BattleEvent._Sortear]._Excelente);

			BattleEvent._Sortear = rand() % BattleEvent._List[1];

			ItemSerialCreateSend(Index, BattleEvent._MapNumber, BattleEvent._X - 8 + rand() % 16, BattleEvent._Y - 12 + rand() % 24, ITEMGET(BattleEvent.EventStruct[BattleEvent._Sortear]._Type, BattleEvent.EventStruct[BattleEvent._Sortear]._Index), BattleEvent.EventStruct[BattleEvent._Sortear]._Level, 0, BattleEvent.EventStruct[BattleEvent._Sortear]._Skill, BattleEvent.EventStruct[BattleEvent._Sortear]._Luck, BattleEvent.EventStruct[BattleEvent._Sortear]._Option, -1, BattleEvent.EventStruct[BattleEvent._Sortear]._Excelente);

			BattleEvent._Sortear = rand() % BattleEvent._List[1];

			ItemSerialCreateSend(Index, BattleEvent._MapNumber, BattleEvent._X - 8 + rand() % 16, BattleEvent._Y - 12 + rand() % 24, ITEMGET(BattleEvent.EventStruct[BattleEvent._Sortear]._Type, BattleEvent.EventStruct[BattleEvent._Sortear]._Index), BattleEvent.EventStruct[BattleEvent._Sortear]._Level, 0, BattleEvent.EventStruct[BattleEvent._Sortear]._Skill, BattleEvent.EventStruct[BattleEvent._Sortear]._Luck, BattleEvent.EventStruct[BattleEvent._Sortear]._Option, -1, BattleEvent.EventStruct[BattleEvent._Sortear]._Excelente);

			BattleEvent._Sortear = rand() % BattleEvent._List[1];

			ItemSerialCreateSend(Index, BattleEvent._MapNumber, BattleEvent._X - 8 + rand() % 16, BattleEvent._Y - 12 + rand() % 24, ITEMGET(BattleEvent.EventStruct[BattleEvent._Sortear]._Type, BattleEvent.EventStruct[BattleEvent._Sortear]._Index), BattleEvent.EventStruct[BattleEvent._Sortear]._Level, 0, BattleEvent.EventStruct[BattleEvent._Sortear]._Skill, BattleEvent.EventStruct[BattleEvent._Sortear]._Luck, BattleEvent.EventStruct[BattleEvent._Sortear]._Option, -1, BattleEvent.EventStruct[BattleEvent._Sortear]._Excelente);
		}

		if (BattleEvent._Finish == true)
		{
			BattleEvent._Finish = false;

			_endthread();
		}
	}

	_endthread();
}

cBattleEvent BattleEvent;

