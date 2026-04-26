#include "StdAfx.h"

cFlagEvent::cFlagEvent() : _Active(false), _Portal(false), _Progress(false), _Team(0)
{
}

bool cFlagEvent::Load()
{
	this->_Count = 0;

	memset(this->FlagStruct, 0, sizeof(this->FlagStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/FlagEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Level = Section.Rows[0].GetInt(1);
		this->_Zen = Section.Rows[0].GetInt(2);

		this->_MapNumber = Section.Rows[1].GetInt(0);
		this->_X[0] = Section.Rows[1].GetInt(1);
		this->_Y[0] = Section.Rows[1].GetInt(2);
		this->_X[1] = Section.Rows[1].GetInt(3);
		this->_Y[1] = Section.Rows[1].GetInt(4);
		this->_Amount = Section.Rows[1].GetInt(5);

		strcpy_s(this->_Column, sizeof(this->_Column), (Section.Rows[1].GetStringPtr(6)));
		strcpy_s(this->_Coin, sizeof(this->_Coin), (Section.Rows[1].GetStringPtr(7)));
		strcpy_s(this->_Syntax[2], sizeof(this->_Syntax[2]), (Section.Rows[1].GetStringPtr(8)));
		strcpy_s(this->_Syntax[3], sizeof(this->_Syntax[3]), (Section.Rows[1].GetStringPtr(9)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->FlagStruct[this->_Count]._Day = Section.Rows[i].GetInt(0);
			this->FlagStruct[this->_Count]._Hours = Section.Rows[i].GetInt(1);
			this->FlagStruct[this->_Count]._Minutes = Section.Rows[i].GetInt(2);
			this->FlagStruct[this->_Count]._Duration = Section.Rows[i].GetInt(3) * 60 * 1000;
			this->_Count++;
		}
	}

	return true;
}

void cFlagEvent::Run()
{
	if (this->_Active)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		for (int i = 0; i < this->_Count; i++)
		{
			if (Now.wDayOfWeek == this->FlagStruct[i]._Day && Now.wHour == this->FlagStruct[i]._Hours && Now.wMinute == this->FlagStruct[i]._Minutes && Now.wSecond == 0)
			{
				this->_Players[0] = 0; this->_Players[1] = 0; this->_Portal = true;

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 5 Minuto(s)");
						Func.MsgOutput(Index, 0, "Fale com o Murphy para participar.");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 4 Minuto(s)");
						Func.MsgOutput(Index, 0, "Fale com o Murphy para participar.");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 3 Minuto(s)");
						Func.MsgOutput(Index, 0, "Fale com o Murphy para participar.");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 2 Minuto(s)");
						Func.MsgOutput(Index, 0, "Fale com o Murphy para participar.");
					}
				}

				Sleep(60000);

				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");
						Func.MsgOutput(Index, 0, "O evento inicia em 1 Minuto(s)");
						Func.MsgOutput(Index, 0, "Fale com o Murphy para participar.");
					}
				}

				Sleep(60000);

				if (Team.size() > 1)
				{
					this->_EventState = 1;

					for (sFlagEvent i : Team)
					{
						if (i._Team == Blue)
						{
							i.lpObj->m_PK_Level = 6;
							GCPkLevelSend(i.lpObj->m_Index, i.lpObj->m_PK_Level);
						}
						else
						{
							i.lpObj->m_PK_Level = 6;
							GCPkLevelSend(i.lpObj->m_Index, i.lpObj->m_PK_Level);
						}
					}

					for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
					{
						if (gObj[Index].Connected == 3)
						{
							Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

							Func.MsgOutput(Index, 0, "Inscrições para o evento encerradas.");

							Func.MsgOutput(Index, 0, "O evento começou!");
						}
					}

					this->_Points[0] = 0; this->_Points[1] = 0; this->_Portal = false;

					this->_Progress = true; this->Move(0);
				}
				else
				{
					if (Team.size() == 1 && this->_EventState == 0)
					{
						for (sFlagEvent i : Team)
						{
							gObjTeleport(i.lpObj->m_Index, 0, 125, 125);
						}

						this->_Portal = false;

						for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
						{
							if (gObj[Index].Connected == 3)
							{
								if (this->PlayerStruct[Index]._InEvent == true)
								{
									this->PlayerStruct[Index]._InEvent = false;
									this->PlayerStruct[Index]._Status = false;
									this->PlayerStruct[Index]._Team = -1;
								}

								Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

								Func.MsgOutput(Index, 0, "Evento encerrado. Mínimo de participantes não atingido.");
							}
						}
					}
				}

				if (this->_Progress == true)
				{
					Sleep(this->FlagStruct[i]._Duration);

					this->Finish(1);
				}
			}
		}
	}
}

int cFlagEvent::GetIndex()
{
	int Index = -1;

	if (this->_EventState == 1)
	{
		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].Connected == 3)
			{
				if (this->PlayerStruct[i]._InEvent == true && this->PlayerStruct[i]._Status == true)
				{
					Index = i;
				}
			}
		}
	}

	return Index;
}

bool cFlagEvent::Teleport(LPOBJ lpObj)
{
	if (this->_EventState == 1)
	{
		if (this->PlayerStruct[lpObj->m_Index]._InEvent == true)
		{
			return false;
		}
	}

	return true;
}

bool cFlagEvent::Attack(LPOBJ lpObj, LPOBJ Target)
{
	if (this->_EventState == 1)
	{
		if (this->PlayerStruct[lpObj->m_Index]._InEvent == 1 && this->PlayerStruct[Target->m_Index]._InEvent == 1)
		{
			if (lpObj->MapNumber == this->_MapNumber && Target->MapNumber == this->_MapNumber)
			{
				if (lpObj->Y > 158 && this->PlayerStruct[lpObj->m_Index]._Team == Red)
				{
					return false;
				}
				else if (lpObj->Y < 158 && this->PlayerStruct[lpObj->m_Index]._Team == Blue)
				{
					return false;
				}
				else if (this->PlayerStruct[lpObj->m_Index]._Team == Red && this->PlayerStruct[Target->m_Index]._Team == Red || this->PlayerStruct[lpObj->m_Index]._Team == Blue && this->PlayerStruct[Target->m_Index]._Team == Blue)
				{
					return false;
				}
			}
		}
	}
	else if (this->_EventState == 0)
	{
		if (this->PlayerStruct[lpObj->m_Index]._InEvent == true && this->PlayerStruct[Target->m_Index]._InEvent == true)
		{
			if (lpObj->MapNumber == this->_MapNumber && Target->MapNumber == this->_MapNumber)
			{
				return false;
			}
		}
	}

	return true;
}

void cFlagEvent::FlagPoint(LPOBJ lpObj)
{
	if (this->PlayerStruct[lpObj->m_Index]._Status == true && this->PlayerStruct[lpObj->m_Index]._InEvent == true)
	{
		if (this->PlayerStruct[lpObj->m_Index]._Team == Red && this->_FlagState[Blue] != 1)
		{
			return;
		}
		else if (this->PlayerStruct[lpObj->m_Index]._Team == Blue && this->_FlagState[Red] != 1)
		{
			return;
		}

		if (this->PlayerStruct[lpObj->m_Index]._Team == Red)
		{
			if (lpObj->MapNumber == this->_MapNumber)
			{
				if (lpObj->Y < 158)
				{
					if (this->_FlagState[Blue] == 1)
					{
						this->PlayerStruct[lpObj->m_Index]._Status = false;

						this->_Points[Red]++;

						this->_FlagState[Blue] = 2;

						Manager.ExecFormat(Query._Query[29], lpObj->Name);

						int ID = this->GetIndex();

						if (ID != -1)
						{
							this->PlayerStruct[ID]._Status = false;
						}

						this->_FlagState[Red] = 0;

						if (this->_Points[0] < 10)
						{
							for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
							{
								if (gObj[Index].Connected == 3)
								{
									Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

									Func.MsgOutput(Index, 0, "%s marcou ponto para equipe vermelha!", lpObj->Name);

									Func.MsgOutput(Index, 0, "Total de pontos: %d", this->_Points[Red]);
								}
							}

							this->Move(1);
						}
						else
						{
							this->Finish(0);
						}
					}
				}
			}
		}

		if (this->PlayerStruct[lpObj->m_Index]._Team == Blue)
		{
			if (lpObj->MapNumber == this->_MapNumber)
			{
				if (lpObj->Y > 158)
				{
					if (this->_FlagState[Red] == 1)
					{
						this->PlayerStruct[lpObj->m_Index]._Status = false;

						this->_Points[Blue]++;

						this->_FlagState[Red] = 2;

						Manager.ExecFormat(Query._Query[29], lpObj->Name);

						int ID = this->GetIndex();

						if (ID != -1)
						{
							this->PlayerStruct[ID]._Status = false;
						}

						this->_FlagState[Blue] = 0;

						if (this->_Points[1] < 10)
						{
							for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
							{
								if (gObj[Index].Connected == 3)
								{
									Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

									Func.MsgOutput(Index, 0, "%s marcou ponto para equipe azul!", lpObj->Name);

									Func.MsgOutput(Index, 0, "Total de pontos: %d", this->_Points[Blue]);
								}
							}

							this->Move(1);
						}
						else
						{
							this->Finish(0);
						}
					}
				}
			}
		}
	}
}

void cFlagEvent::Killer(LPOBJ lpObj, LPOBJ Target)
{
	if (this->_EventState == 1)
	{
		if (this->PlayerStruct[lpObj->m_Index]._InEvent == true && this->PlayerStruct[Target->m_Index]._InEvent == true)
		{
			if (this->PlayerStruct[lpObj->m_Index]._Team == Blue && this->PlayerStruct[Target->m_Index]._Team == Red)
			{
				this->PlayerStruct[Target->m_Index]._Move = 7;

				if (this->PlayerStruct[Target->m_Index]._Status == true)
				{
					this->PlayerStruct[Target->m_Index]._Status = false;

					this->_FlagState[this->PlayerStruct[lpObj->m_Index]._Team] = 0;

					for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
					{
						if (gObj[Index].Connected == 3)
						{
							Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

							Func.MsgOutput(Index, 0, "A equipe azul recuperou a bandeira!");
						}
					}
				}
			}
			else if (this->PlayerStruct[lpObj->m_Index]._Team == Red && this->PlayerStruct[Target->m_Index]._Team == Blue)
			{
				this->PlayerStruct[Target->m_Index]._Move = 7;

				if (this->PlayerStruct[Target->m_Index]._Status == true)
				{
					this->PlayerStruct[Target->m_Index]._Status = false;

					this->_FlagState[this->PlayerStruct[lpObj->m_Index]._Team] = 0;

					for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
					{
						if (gObj[Index].Connected == 3)
						{
							Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

							Func.MsgOutput(Index, 0, "A equipe vermelha recuperou a bandeira!");
						}
					}
				}
			}
		}
	}
}

void cFlagEvent::Die(LPOBJ lpObj)
{
	if (this->_EventState == 1)
	{
		if (this->PlayerStruct[lpObj->m_Index]._InEvent == true)
		{
			if (this->PlayerStruct[lpObj->m_Index]._Move >= 2)
			{
				this->PlayerStruct[lpObj->m_Index]._Move--;
			}

			if (this->PlayerStruct[lpObj->m_Index]._Move == 1)
			{
				if (lpObj->RegenOk == 0)
				{
					if (this->PlayerStruct[lpObj->m_Index]._Team == Blue)
					{
						gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X[1], this->_Y[1]);
					}
					else if (this->PlayerStruct[lpObj->m_Index]._Team == Red)
					{
						gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X[0], this->_Y[0]);
					}
				}

				this->PlayerStruct[lpObj->m_Index]._Move = 0;
			}
		}
	}
}

void cFlagEvent::Move(int Team)
{
	if (this->_EventState == 1)
	{
		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].MapNumber == this->_MapNumber)
			{
				if (this->PlayerStruct[i]._InEvent == true)
				{
					std::list<LPOBJ> List;

					List.push_front(&gObj[i]);

					if (Team == 0)
					{
						if (gObj[i].RegenOk == 0)
						{
							int X = rand() % 6;
							int Y = rand() % 3;

							for (LPOBJ Player : List)
							{
								if (this->PlayerStruct[Player->m_Index]._Team == Red)
								{
									gObjTeleport(Player->m_Index, this->_MapNumber, this->_X[0], this->_Y[0]);
								}
								if (this->PlayerStruct[Player->m_Index]._Team == Blue)
								{
									gObjTeleport(Player->m_Index, this->_MapNumber, this->_X[1], this->_Y[1]);
								}
							}

							this->_FlagState[0] = 0;
							this->_FlagState[1] = 0;
						}
					}
					else if (Team == 1)
					{
						if (gObj[i].RegenOk == 0)
						{
							int X = rand() % 6;
							int Y = rand() % 3;

							for (LPOBJ Player : List)
							{
								if (this->PlayerStruct[Player->m_Index]._Team == Red)
								{
									gObjTeleport(Player->m_Index, this->_MapNumber, 30 + X, 150 + Y);
								}
								else if (this->PlayerStruct[Player->m_Index]._Team == Blue)
								{
									gObjTeleport(Player->m_Index, this->_MapNumber, 30 + X, 165 - Y);
								}
							}

							this->_FlagState[0] = 0;
							this->_FlagState[1] = 0;
						}
					}
				}
			}
		}
	}
}

void cFlagEvent::Talk(LPOBJ lpNpc, LPOBJ lpObj, BYTE Mode)
{
	if (this->_Active == true)
	{
		if (this->_EventState == 1 && Mode == 0)
		{
			if (lpNpc->Class == 205)
			{
				if (this->PlayerStruct[lpObj->m_Index]._InEvent == true && this->PlayerStruct[lpObj->m_Index]._Team == Blue)
				{
					if (this->_FlagState[Red] == 0)
					{
						this->_FlagState[Red] = 1;

						this->PlayerStruct[lpObj->m_Index]._Status = true;

						Func.MsgOutput(lpObj->m_Index, 1, "Corra para o seu campo!");

						for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
						{
							if (gObj[Index].Connected == 3)
							{
								Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

								Func.MsgOutput(Index, 0, "%s está com a bandeira: %s", lpObj->Name, this->PlayerStruct[lpObj->m_Index]._Team == Blue ? "Vermelha" : "Azul");
							}
						}
					}
					else
					{
						int Index = this->GetIndex();

						if (Index != lpObj->m_Index)
						{
							sprintf_s(this->_Buffer, "%s já pegou a bandeira.", lpObj->Name);
							ChatTargetSend(lpNpc, this->_Buffer, lpObj->m_Index);
						}
						else
						{
							ChatTargetSend(lpNpc, "Corra para o seu campo!", lpObj->m_Index);
						}
					}
				}
			}

			if (lpNpc->Class == 204)
			{
				if (this->PlayerStruct[lpObj->m_Index]._InEvent == true && this->PlayerStruct[lpObj->m_Index]._Team == Red)
				{
					if (this->_FlagState[Blue] == 0)
					{
						this->_FlagState[Blue] = 1;

						this->PlayerStruct[lpObj->m_Index]._Status = true;

						Func.MsgOutput(lpObj->m_Index, 1, "Corra para o seu campo!");

						for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
						{
							if (gObj[Index].Connected == 3)
							{
								Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

								Func.MsgOutput(Index, 0, "%s está com a bandeira: %s", lpObj->Name, this->PlayerStruct[lpObj->m_Index]._Team == Red ? "Azul" : "Vermelha");
							}
						}
					}
					else
					{
						int Index = this->GetIndex();

						if (Index != lpObj->m_Index)
						{
							sprintf_s(this->_Buffer, "%s já pegou a bandeira.", lpObj->Name);
							ChatTargetSend(lpNpc, this->_Buffer, lpObj->m_Index);
						}
						else
						{
							ChatTargetSend(lpNpc, "Corra para o seu campo!", lpObj->m_Index);
						}
					}
				}
			}
		}
		else if (this->_Portal == true && Mode == 1)
		{
			if (PlayerStruct[lpObj->m_Index]._InEvent == false)
			{
				if (Team.size() < 32)
				{
					if (lpObj->Level < this->_Level)
					{
						sprintf_s(this->_Buffer, "É necessário %d de level.", this->_Level);
						ChatTargetSend(lpNpc, this->_Buffer, lpObj->m_Index);
						return;
					}
					else if (lpObj->Money < this->_Zen)
					{
						sprintf_s(this->_Buffer, "É necessário %d de zen.", this->_Zen);
						ChatTargetSend(lpNpc, this->_Buffer, lpObj->m_Index);
						return;
					}
					else if (!this->CheckItem(lpObj))
					{
						return;
					}
					else if (this->_Team == 0)
					{
						this->PlayerStruct[lpObj->m_Index]._Team = Blue;
						this->PlayerStruct[lpObj->m_Index]._InEvent = true;
						this->PlayerStruct[lpObj->m_Index].lpObj = lpObj;

						this->_Team = 1;

						this->_Blue++;
					}
					else if (this->_Team == 1)
					{
						this->PlayerStruct[lpObj->m_Index]._Team = Red;
						this->PlayerStruct[lpObj->m_Index]._InEvent = 1;
						this->PlayerStruct[lpObj->m_Index].lpObj = lpObj;

						this->_Team = 0;

						this->_Red++;
					}

					GCItemListSend(lpObj->m_Index);
					GCEquipmentSend(lpObj->m_Index);

					gObjClearViewport(&gObj[lpObj->m_Index]);

					GCMoneySend(lpObj->m_Index, lpObj->Money -= this->_Zen);

					Team.push_back(this->PlayerStruct[lpObj->m_Index]);

					Func.MsgOutput(lpObj->m_Index, 1, "Você é da equipe: %s", this->PlayerStruct[lpObj->m_Index]._Team == Red ? "Vermelha" : "Azul");

					Func.MsgOutput(lpObj->m_Index, 1, "Você foi registrado no evento. Aguarde...");

					if (this->PlayerStruct[lpObj->m_Index]._Team == Red)
					{
						gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X[0], this->_Y[0]);
					}
					else if (this->PlayerStruct[lpObj->m_Index]._Team == Blue)
					{
						gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X[1], this->_Y[1]);
					}
				}
				else
				{
					ChatTargetSend(lpNpc, "Máximo de 32 participantes no evento.", lpObj->m_Index);
				}
			}
			else
			{
				Func.MsgOutput(lpObj->m_Index, 1, "Você já está registrado no evento. Aguarde.");
			}
		}
	}
}

bool cFlagEvent::CheckItem(LPOBJ lpObj)
{
	if (lpObj->pInventory[7].IsItem())
	{
		Func.MsgOutput(lpObj->m_Index, 1, "Você não pode participar do evento!");
		Func.MsgOutput(lpObj->m_Index, 1, "Proibido usar asas no evento.");
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

void cFlagEvent::Winner(int Team)
{
	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].MapNumber == this->_MapNumber)
		{
			if (this->PlayerStruct[i]._InEvent == true)
			{
				std::list<LPOBJ> List;

				List.push_front(&gObj[i]);

				if (Team == Red)
				{
					for (LPOBJ Player : List)
					{
						if (this->PlayerStruct[Player->m_Index]._Team == Red)
						{
							Manager.ExecFormat(Query._Query[30], this->_Column, this->_Column, this->_Amount, Player->AccountID);
						}
					}
				}
				else if (Team == Blue)
				{
					for (LPOBJ Player : List)
					{
						if (this->PlayerStruct[Player->m_Index]._Team == Blue)
						{
							Manager.ExecFormat(Query._Query[30], this->_Column, this->_Column, this->_Amount, Player->AccountID);
						}
					}
				}
			}
		}
	}

	Func.AllServerAnnounce("Prêmio: %d %s", this->_Amount, this->_Coin);
}

int cFlagEvent::Diference(int v1, int v2)
{
	int Value = v1 > v2 ? (v1 - v2) : v2 > v1 ? (v2 - v1) : 0;

	return Value;
}

void cFlagEvent::Finish(BYTE Mode)
{
	if (this->_EventState == 1)
	{
		if (Mode == 0)
		{
			if (this->_Points[0] >= 10 && this->_Points[1] < 10)
			{
				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

						Func.MsgOutput(Index, 0, "A equipe vermelha venceu!");
					}
				}

				this->Winner(Red);
			}
			else if (this->_Points[1] >= 10 && this->_Points[0] < 10)
			{
				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

						Func.MsgOutput(Index, 0, "A equipe azul venceu!");
					}
				}

				this->Winner(Blue);
			}
		}
		else if (Mode == 1)
		{
			if (this->_Points[0] > this->_Points[1])
			{
				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

						Func.MsgOutput(Index, 0, "Infelizmente o tempo foi esgotado.");

						Func.MsgOutput(Index, 0, "A equipe vermelha venceu!");
					}
				}

				this->Winner(Red);
			}
			else if (this->_Points[0] < this->_Points[1])
			{
				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

						Func.MsgOutput(Index, 0, "Infelizmente o tempo foi esgotado.");

						Func.MsgOutput(Index, 0, "A equipe azul venceu!");
					}
				}

				this->Winner(Blue);
			}
			else
			{
				for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
				{
					if (gObj[Index].Connected == 3)
					{
						Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

						Func.MsgOutput(Index, 0, "Houve um empate entre a equipe vermelha e azul!");
					}
				}
			}

			this->_Progress = false;

		}
		else if (Mode == 2)
		{
			this->_Players[Red] = this->_Red;
			this->_Players[Blue] = this->_Blue;

			if (this->_Players[Red] > this->_Players[Blue])
			{
				if (Diference(this->_Players[Red], this->_Players[Blue]) > 3 || this->_Players[Blue] == 0)
				{
					for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
					{
						if (gObj[Index].Connected == 3)
						{
							Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

							Func.MsgOutput(Index, 0, "A equipe vermelha venceu por W.O.");
						}
					}

					this->Winner(Red);
				}
			}
			else if (this->_Players[Blue] > this->_Players[Red])
			{
				if (Diference(this->_Players[Red], this->_Players[Blue]) > 3 || this->_Players[Red] == 0)
				{
					for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
					{
						if (gObj[Index].Connected == 3)
						{
							Func.MsgOutput(Index, 0, "[   ROUBA BANDEIRA   ]");

							Func.MsgOutput(Index, 0, "A equipe azul venceu por W.O.");
						}
					}

					this->Winner(Blue);
				}
			}
		}

		for (sFlagEvent i : Team)
		{
			i.lpObj->m_PK_Level = 3;
			GCPkLevelSend(i.lpObj->m_Index, i.lpObj->m_PK_Level);

			gObjTeleport(i.lpObj->m_Index, 0, 125, 125);
		}

		this->_Red = 0; this->_Blue = 0; this->_Team = 0;

		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3 && this->PlayerStruct[Index]._InEvent == true)
			{
				this->PlayerStruct[Index]._InEvent = false;
				this->PlayerStruct[Index]._Status = false;
				this->PlayerStruct[Index]._Team = -1;
			}
		}

		this->_EventState = 0;

		this->_Players[0] = 0;
		this->_Players[1] = 0;

		this->_FlagState[0] = 0;
		this->_FlagState[1] = 0;

		this->_Points[0] = 0;
		this->_Points[1] = 0;

		Team.clear();
	}
}

void cFlagEvent::Quit(LPOBJ lpObj)
{
	if (this->PlayerStruct[lpObj->m_Index]._InEvent == true)
	{
		this->PlayerStruct[lpObj->m_Index]._InEvent = false;
		this->PlayerStruct[lpObj->m_Index]._Status = false;

		if (this->PlayerStruct[lpObj->m_Index]._Team == Red)
		{
			this->PlayerStruct[lpObj->m_Index]._Team = -1;

			this->_Red--;

			this->_Team = 1;
		}
		else if (this->PlayerStruct[lpObj->m_Index]._Team == Blue)
		{
			this->PlayerStruct[lpObj->m_Index]._Team = -1;

			this->_Blue--;

			this->_Team = 0;
		}

		lpObj->MapNumber = 0; lpObj->X = 125; lpObj->Y = 125;

		Team.remove(this->PlayerStruct[lpObj->m_Index]);

		this->Finish(2);
	}
}

bool cFlagEvent::Equip(LPOBJ lpObj, BYTE SourcePos, BYTE TargetPos)
{
	if (this->PlayerStruct[lpObj->m_Index]._InEvent == true)
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

	return true;
}


void cFlagEvent::StartManual()
{
	this->Finish(0);

	this->_Count = 0;
	this->_Points[0] = 0;
	this->_Points[1] = 0;

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			Func.MsgOutput(i, 0, "[ TESTE ] O evento ROUBA BANDEIRA iniciou!");
			Func.MsgOutput(i, 0, "Fale com o Murphy para participar.");
		}
	}

	this->_Progress = true;
}
cFlagEvent FlagEvent;



