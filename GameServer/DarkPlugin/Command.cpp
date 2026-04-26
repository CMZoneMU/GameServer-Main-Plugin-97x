#include "StdAfx.h"

bool Commands::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Comandos.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active[0] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[0], sizeof(this->_Syntax[0]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Formato, sizeof(this->_Formato), (Section.Rows[0].GetStringPtr(2)));

		this->_Level[0] = Section.Rows[1].GetInt(0);
		this->_Zen[0] = Section.Rows[1].GetInt(1);
		this->_Vip[0] = Section.Rows[1].GetInt(2) > 0 ? true : false;
		this->_Delay = Section.Rows[1].GetInt(3);
		this->_Color = Section.Rows[1].GetInt(4);
	}

	if (Group.GetSection(1, Section))
	{
		this->_Active[1] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[1], sizeof(this->_Syntax[1]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Syntax[2], sizeof(this->_Syntax[2]), (Section.Rows[0].GetStringPtr(2)));
		strcpy_s(this->_Syntax[3], sizeof(this->_Syntax[3]), (Section.Rows[0].GetStringPtr(3)));
		strcpy_s(this->_Syntax[4], sizeof(this->_Syntax[4]), (Section.Rows[0].GetStringPtr(4)));

		this->_Vip[1] = Section.Rows[1].GetInt(0) > 0 ? true : false;
		this->_Level[1] = Section.Rows[1].GetInt(1);
		this->_Zen[1] = Section.Rows[1].GetInt(2);
	}

	if (Group.GetSection(2, Section))
	{
		this->_Active[2] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[5], sizeof(this->_Syntax[5]), (Section.Rows[0].GetStringPtr(1)));

		this->_Vip[2] = Section.Rows[1].GetInt(0) > 0 ? true : false;
		this->_Level[2] = Section.Rows[1].GetInt(1);
		this->_Zen[2] = Section.Rows[1].GetInt(2);
	}

	if (Group.GetSection(3, Section))
	{
		this->_Active[3] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[6], sizeof(this->_Syntax[6]), (Section.Rows[0].GetStringPtr(1)));

		this->_Vip[3] = Section.Rows[1].GetInt(0) > 0 ? true : false;
		this->_Level[3] = Section.Rows[1].GetInt(1);
		this->_Zen[3] = Section.Rows[1].GetInt(2);

		this->_Active[14] = Section.Rows[2].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[18], sizeof(this->_Syntax[18]), (Section.Rows[2].GetStringPtr(1)));

		this->_Vip[5] = Section.Rows[3].GetInt(0) > 0 ? true : false;
		this->_Level[6] = Section.Rows[3].GetInt(1);
		this->_Zen[6] = Section.Rows[3].GetInt(2);
	}

	if (Group.GetSection(4, Section))
	{
		this->_Active[4] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[7], sizeof(this->_Syntax[7]), (Section.Rows[0].GetStringPtr(1)));

		this->_Level[4] = Section.Rows[1].GetInt(0);
		this->_Zen[4] = Section.Rows[1].GetInt(1);
		this->_Type = Section.Rows[1].GetInt(2);
		this->_Ware[0] = Section.Rows[1].GetInt(3);
		this->_Ware[1] = Section.Rows[1].GetInt(4);
		this->_Ware[2] = Section.Rows[1].GetInt(5);
		this->_Ware[3] = Section.Rows[1].GetInt(6);
	}

	if (Group.GetSection(5, Section))
	{
		this->_Active[5] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[8], sizeof(this->_Syntax[8]), (Section.Rows[0].GetStringPtr(1)));

		this->_Vip[4] = Section.Rows[1].GetInt(0) > 0 ? true : false;
		this->_Zen[5] = Section.Rows[1].GetInt(1);
	}

	if (Group.GetSection(6, Section))
	{
		this->_Active[6] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[10], sizeof(this->_Syntax[10]), (Section.Rows[0].GetStringPtr(1)));

		strcpy_s(this->_Notice, sizeof(this->_Notice), (Section.Rows[1].GetStringPtr(0)));
	}

	if (Group.GetSection(7, Section))
	{
		this->_Active[7] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[11], sizeof(this->_Syntax[11]), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(8, Section))
	{
		this->_Active[8] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[12], sizeof(this->_Syntax[12]), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(9, Section))
	{
		this->_Active[9] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[13], sizeof(this->_Syntax[13]), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(10, Section))
	{
		this->_Active[10] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[14], sizeof(this->_Syntax[14]), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(11, Section))
	{
		this->_Active[11] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[15], sizeof(this->_Syntax[15]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Syntax[9], sizeof(this->_Syntax[9]), (Section.Rows[0].GetStringPtr(2)));
	}

	if (Group.GetSection(12, Section))
	{
		this->_Active[12] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[16], sizeof(this->_Syntax[16]), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(13, Section))
	{
		this->_Active[13] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[17], sizeof(this->_Syntax[17]), (Section.Rows[0].GetStringPtr(1)));
	}

	return true;
}

bool Commands::Management(LPBYTE Protocolo, int aIndex)
{
	if (DuelEvent.Check(&gObj[aIndex], (const char*)&Protocolo[13]))
	{
		return true;
	}

	if (PegaEvent.Check(&gObj[aIndex], (const char*)&Protocolo[13]))
	{
		return true;
	}

	if (SobreEvent.Check(&gObj[aIndex], (const char*)&Protocolo[13]))
	{
		return true;
	}

	if (PairEvent.Check(&gObj[aIndex], (const char*)&Protocolo[13]))
	{
		return true;
	}

	if (RoletaEvent.Check(&gObj[aIndex], (const char*)&Protocolo[13]))
	{
		return true;
	}

	if (UfcEvent.Check(&gObj[aIndex], (const char*)&Protocolo[13]))
	{
		return true;
	}

	if (KingEvent.Check(&gObj[aIndex], (const char*)&Protocolo[13]))
	{
		return true;
	}

	if (BattleEvent.Check(&gObj[aIndex], (const char*)&Protocolo[13]))
	{
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), "/info"))
	{
		this->Information(aIndex);
		return true;
	}

	if (!_strnicmp((const char*)(&Protocolo[13]), "/testevent", 10))
	{
		this->TestEvent(aIndex, (const char*)(&Protocolo[13]));
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), "/sm"))
	{
		this->Class(aIndex, 0);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), "/bk"))
	{
		this->Class(aIndex, 1);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), "/elf"))
	{
		this->Class(aIndex, 2);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), "/mg"))
	{
		this->Class(aIndex, 3);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), "/finalizar"))
	{
		this->Finish(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), "/abrirbau"))
	{
		this->OpenWare(aIndex);
		return true;
	}

	for (int i = 0; i < Teleport._Count; i++)
	{
		if (!_stricmp((const char*)(&Protocolo[13]), Teleport.TeleportStruct[i]._Syntax))
		{
			DuelEvent.Quit(&gObj[aIndex]);
			PegaEvent.Quit(&gObj[aIndex]);
			SobreEvent.Quit(&gObj[aIndex]);
			DeathEvent.Quit(&gObj[aIndex]);
			TheftEvent.Quit(&gObj[aIndex]);
			Duel.Quit(&gObj[aIndex]);
			FlagEvent.Quit(&gObj[aIndex]);
			PairEvent.Quit(&gObj[aIndex]);
			RoletaEvent.Quit(&gObj[aIndex]);
			UfcEvent.Quit(&gObj[aIndex]);
			BattleEvent.Quit(&gObj[aIndex]);
			KingEvent.Quit(&gObj[aIndex]);

			Teleport.Run(aIndex, i);
			return true;
		}
	}

	if (!_stricmp((const char*)(&Protocolo[13]), this->_Syntax[5]))
	{
		this->ReAdd(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), this->_Syntax[6]))
	{
		this->Clear(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), this->_Syntax[18]))
	{
		this->Killer(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), this->_Syntax[8]))
	{
		this->Money(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), this->_Syntax[14]))
	{
		this->FireWork(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), this->_Syntax[9]))
	{
		this->Register(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), Reset._Syntax))
	{
		Reset.Run(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), Master._Syntax))
	{
		Master.Run(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), Bonus._Syntax))
	{
		Bonus.Command(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), Duel._Syntax[1]))
	{
		Duel.Accept(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), Roleta._Syntax))
	{
		Roleta.Command(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(&Protocolo[13]), Offline._Syntax))
	{
		Offline.Command(aIndex);
		return true;
	}

	if (!_memicmp(&Protocolo[13], "/war", strlen("/war")))
	{
		this->War(aIndex, (char*)(Protocolo + 13 + strlen("/war")));
		return true;
	}

	if (!_memicmp(&Protocolo[13], "/track", strlen("/track")))
	{
		this->Track(aIndex, (char*)(Protocolo + 13 + strlen("/track")));
		return true;
	}

	if (!_memicmp(&Protocolo[13], "/trace", strlen("/trace")))
	{
		this->Trace(aIndex, (char*)(Protocolo + 13 + strlen("/trace")));
		return true;
	}

	if (!_memicmp(&Protocolo[13], "/rei", strlen("/rei")))
	{
		this->Rei(aIndex, (char*)(Protocolo + 13 + strlen("/rei")));
		return true;
	}

	if (!_memicmp(&Protocolo[13], "/gold", strlen("/gold")))
	{
		Pack.Gold(aIndex, (char*)(Protocolo + 13 + strlen("/gold")));
		return true;
	}

	if (!_memicmp(&Protocolo[13], "/nick", strlen("/nick")))
	{
		if (Block.BlockStruct[aIndex]._Active == 1)
		{
			Func.Golden(aIndex, "Conta protegida!");
			Func.Golden(aIndex, "Utilize a senha para desbloquear.");
			return true;
		}

		this->Nick(aIndex, (char*)(Protocolo + 13 + strlen("/nick")));
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[0], strlen(this->_Syntax[0])))
	{
		this->Post(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[0])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[1], strlen(this->_Syntax[1])))
	{
		this->Add(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[1])), 1);
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[2], strlen(this->_Syntax[2])))
	{
		this->Add(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[2])), 2);
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[3], strlen(this->_Syntax[3])))
	{
		this->Add(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[3])), 3);
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[4], strlen(this->_Syntax[4])))
	{
		this->Add(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[4])), 4);
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[7], strlen(this->_Syntax[7])))
	{
		if (Block.BlockStruct[aIndex]._Active == 1)
		{
			Func.Golden(aIndex, "Conta protegida!");
			Func.Golden(aIndex, "Utilize a senha para desbloquear.");
			return true;
		}

		this->Ware(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[7])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[10], strlen(this->_Syntax[10])))
	{
		this->Premiar(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[10])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[11], strlen(this->_Syntax[11])))
	{
		this->MoveAll(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[11])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[12], strlen(this->_Syntax[12])))
	{
		this->Skin(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[12])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[13], strlen(this->_Syntax[13])))
	{
		this->Move(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[13])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[15], strlen(this->_Syntax[15])))
	{
		this->Evento(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[15])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[16], strlen(this->_Syntax[16])))
	{
		this->Disconnect(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[16])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], this->_Syntax[17], strlen(this->_Syntax[17])))
	{
		this->Drop(aIndex, (char*)(Protocolo + 13 + strlen(this->_Syntax[17])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], QuizEvent._Syntax[0], strlen(QuizEvent._Syntax[0])))
	{
		QuizEvent.Check(aIndex, (char*)(Protocolo + 13 + strlen(QuizEvent._Syntax[0])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], Bank._Syntax, strlen(Bank._Syntax)))
	{
		if (Block.BlockStruct[aIndex]._Active == 1)
		{
			Func.Golden(aIndex, "Conta protegida!");
			Func.Golden(aIndex, "Utilize a senha para desbloquear.");
			return true;
		}

		Bank.Check(aIndex, (char*)(Protocolo + 13 + strlen(Bank._Syntax)));
		return true;
	}

	if (!_memicmp(&Protocolo[13], Attack._Syntax, strlen(Attack._Syntax)))
	{
		Attack.Command(aIndex, (char*)(Protocolo + 13 + strlen(Attack._Syntax)));
		return true;
	}

	if (!_memicmp(&Protocolo[13], Duel._Syntax[0], strlen(Duel._Syntax[0])))
	{
		Duel.Invitation(aIndex, (char*)(Protocolo + 13 + strlen(Duel._Syntax[0])));
		return true;
	}

	if (!_memicmp(&Protocolo[13], Potion._Syntax, strlen(Potion._Syntax)))
	{
		Potion.Command(aIndex, (char*)(Protocolo + 13 + strlen(Potion._Syntax)));
		return true;
	}

	if (!_memicmp(&Protocolo[13], Rank._Syntax, strlen(Rank._Syntax)))
	{
		Rank.Command(aIndex, (char*)(Protocolo + 13 + strlen(Rank._Syntax)));
		return true;
	}

	if (!_memicmp(&Protocolo[13], AutoReset._Syntax, strlen(AutoReset._Syntax)))
	{
		AutoReset.Command(aIndex, (char*)(Protocolo + 13 + strlen(AutoReset._Syntax)));
		return true;
	}

	if (!_memicmp(&Protocolo[13], Party._Syntax, strlen(Party._Syntax)))
	{
		Party.Command(aIndex, (char*)(Protocolo + 13 + strlen(Party._Syntax)));
		return true;
	}

	if (!_memicmp(&Protocolo[13], Buy._Syntax, strlen(Buy._Syntax)))
	{
		if (Block.BlockStruct[aIndex]._Active == 1)
		{
			Func.Golden(aIndex, "Conta protegida!");
			Func.Golden(aIndex, "Utilize a senha para desbloquear.");
			return true;
		}

		Buy.Run(aIndex, (char*)(Protocolo + 13 + strlen(Buy._Syntax)));
		return true;
	}

	if (!_memicmp(&Protocolo[13], Pet._Syntax, strlen(Pet._Syntax)))
	{
		Pet.Command(aIndex, (char*)(Protocolo + 13 + strlen(Pet._Syntax)));
		return true;
	}

	if (!_memicmp(&Protocolo[13], Block._Syntax, strlen(Block._Syntax)))
	{
		Block.Run(aIndex, (char*)(Protocolo + 13 + strlen(Block._Syntax)));
		return true;
	}

	return false;
}

void Commands::Post(int aIndex, char* msg)
{
	if (strlen(msg) >= 1 && this->_Active[0] == true)
	{
		if (gObj[aIndex].Level < this->_Level[0])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[0]);
			return;
		}
		else if (gObj[aIndex].Money < this->_Zen[0])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[0]);
			return;
		}
		else if (this->_Vip[0] == true && Custom[aIndex].VipCount < 1)
		{
			Func.MsgOutput(aIndex, 1, "Exclusivo apenas para vip's.");
			return;
		}

		DWORD Delay = (GetTickCount() - Custom[aIndex].Delay[0]) / 1000;

		if (Delay < this->_Delay)
		{
			Func.MsgOutput(aIndex, 1, "Aguarde %d %s para usar novamente.", (this->_Delay - Delay), (this->_Delay - Delay == 1) ? "segundo" : "segundos");
			return;
		}
		else
		{
			QuizEvent.Winner(aIndex, msg);

			sprintf(this->_Buffer, this->_Formato, msg);

			switch (Custom[aIndex].VipCount)
			{
			case 0:
				Func.PostSend(6, gObj[aIndex].Name, this->_Buffer, msg);
				break;
			case 1:
				Func.PostSend(7, gObj[aIndex].Name, this->_Buffer, msg);
				break;
			case 2:
				Func.PostSend(8, gObj[aIndex].Name, this->_Buffer, msg);
				break;
			case 3:
				Func.PostSend(9, gObj[aIndex].Name, this->_Buffer, msg);
				break;
			}

			Custom[aIndex].Delay[0] = GetTickCount();

			GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[0]);
		}
	}
}

void Commands::Add(int aIndex, char* msg, int Status)
{
	if (this->_Active[1] == true)
	{
		int Pontos = atoi(msg);

		if (strlen(msg) < 1 || Pontos <= 0)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Exemplo -> %s <Número>", this->_Syntax[1]);
			Func.MsgOutput(aIndex, 1, "Exemplo -> %s <Número>", this->_Syntax[2]);
			Func.MsgOutput(aIndex, 1, "Exemplo -> %s <Número>", this->_Syntax[3]);
			Func.MsgOutput(aIndex, 1, "Exemplo -> %s <Número>", this->_Syntax[4]);
			return;
		}
		else if (gObj[aIndex].Level < this->_Level[1])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[1]);
			return;
		}
		else if (gObj[aIndex].Money < this->_Zen[1])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[1]);
			return;
		}
		else if (Pontos > gObj[aIndex].LevelUpPoint)
		{
			Func.MsgOutput(aIndex, 1, "Faltam %d pontos.", (Pontos - gObj[aIndex].LevelUpPoint));
			return;
		}
		else if (this->_Vip[1] == true && Custom[aIndex].VipCount < 1)
		{
			Func.MsgOutput(aIndex, 1, "Exclusivo apenas para vip's.");
			return;
		}
		else
		{
			if (Status == 1)
			{
				if ((gObj[aIndex].Strength + Pontos) > 32767)
				{
					Func.MsgOutput(aIndex, 1, "O limite de pontos é 32767");
					return;
				}
				else
				{
					gObj[aIndex].Strength += Pontos;

					Func.MsgOutput(aIndex, 1, "Adicionado %d pontos em força.", Pontos);
				}
			}
			else if (Status == 2)
			{
				if ((gObj[aIndex].Dexterity + Pontos) > 32767)
				{
					Func.MsgOutput(aIndex, 1, "O limite de pontos é 32767");
					return;
				}
				else
				{
					gObj[aIndex].Dexterity += Pontos;

					Func.MsgOutput(aIndex, 1, "Adicionado %d pontos em agilidade.", Pontos);
				}
			}
			else if (Status == 3)
			{
				if ((gObj[aIndex].Vitality + Pontos) > 32767)
				{
					Func.MsgOutput(aIndex, 1, "O limite de pontos é 32767");
					return;
				}
				else
				{
					gObj[aIndex].Vitality += Pontos;

					gObj[aIndex].MaxLife += gObj[aIndex].VitalityToLife * Pontos;
					gObj[aIndex].Life = gObj[aIndex].MaxLife;
					gObj[aIndex].AddLife = 0;

					Func.MsgOutput(aIndex, 1, "Adicionado %d pontos em vitalidade.", Pontos);
				}
			}
			else if (Status == 4)
			{
				if ((gObj[aIndex].Energy + Pontos) > 32767)
				{
					Func.MsgOutput(aIndex, 1, "O limite de pontos é 32767");
					return;
				}
				else
				{
					gObj[aIndex].Energy += Pontos;

					gObj[aIndex].MaxMana += gObj[aIndex].EnergyToMana * Pontos;
					gObj[aIndex].Mana = gObj[aIndex].MaxMana;
					gObj[aIndex].AddMana = 0;

					gObjSetBP(aIndex);
					gObj[aIndex].BP = gObj[aIndex].MaxBP / 2;
					gObj[aIndex].AddBP = 0;

					Func.MsgOutput(aIndex, 1, "Adicionado %d pontos em energia.", Pontos);
				}
			}

			GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[1]);

			gObj[aIndex].LevelUpPoint -= Pontos;

			Func.UpdateCharacter(aIndex, false);
		}
	}
}

void Commands::ReAdd(int aIndex)
{
	if (this->_Active[2] == true)
	{
		if (gObj[aIndex].Level < this->_Level[2])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[2]);
			return;
		}
		else if (gObj[aIndex].Money < this->_Zen[2])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[2]);
			return;
		}
		else if (this->_Vip[2] == true && Custom[aIndex].VipCount < 1)
		{
			Func.MsgOutput(aIndex, 1, "Exclusivo apenas para vip's.");
			return;
		}

		int Pontos, Resto;

		WORD Class = gObj[aIndex].Class;

		Resto = Class == 0 ? 81 : Class == 1 ? 83 : Class == 2 ? 82 : Class == 3 ? 104 : 106;

		Pontos = (gObj[aIndex].Strength + gObj[aIndex].Dexterity + gObj[aIndex].Vitality + gObj[aIndex].Energy) - Resto;

		if (Pontos <= 0)
		{
			Func.MsgOutput(aIndex, 1, "Pontos insuficientes para redistribuição!");
			return;
		}

		gObj[aIndex].LevelUpPoint += Pontos;

		GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[2]);

		gObj[aIndex].Strength = Class == 0 ? 18 : Class == 1 ? 28 : Class == 2 ? 22 : Class == 3 ? 26 : 26;
		gObj[aIndex].Dexterity = Class == 0 ? 18 : Class == 1 ? 20 : Class == 2 ? 25 : Class == 3 ? 26 : 20;
		gObj[aIndex].Vitality = Class == 0 ? 15 : Class == 1 ? 25 : Class == 2 ? 20 : Class == 3 ? 26 : 20;
		gObj[aIndex].Energy = Class == 0 ? 30 : Class == 1 ? 10 : Class == 2 ? 15 : Class == 3 ? 26 : 15;
		gObj[aIndex].MaxLife = Func.GetStatus(&gObj[aIndex], Class, 0);
		gObj[aIndex].Life = gObj[aIndex].MaxLife;
		gObj[aIndex].AddLife = 0;
		gObj[aIndex].MaxMana = Func.GetStatus(&gObj[aIndex], Class, 1);
		gObj[aIndex].Mana = gObj[aIndex].MaxMana;
		gObj[aIndex].AddMana = 0;
		gObjSetBP(aIndex);
		gObj[aIndex].BP = gObj[aIndex].MaxBP / 2;
		gObj[aIndex].AddBP = 0;

		Func.UpdateCharacter(aIndex, false);

		Func.MsgOutput(aIndex, 1, "%d disponiveis para distribuição.", gObj[aIndex].LevelUpPoint);
	}
}

void Commands::Clear(int aIndex)
{
	if (this->_Active[3] == true)
	{
		if (gObj[aIndex].Level < this->_Level[3])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[3]);
			return;
		}
		else if (gObj[aIndex].Money < this->_Zen[3])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[3]);
			return;
		}
		else if (this->_Vip[3] == true && Custom[aIndex].VipCount < 1)
		{
			Func.MsgOutput(aIndex, 1, "Exclusivo apenas para vip's.");
			return;
		}
		else if (Custom[aIndex].InEvent == true || DeathEvent.PlayerStruct[aIndex]._InEvent == true || TheftEvent.PlayerStruct[aIndex]._InEvent == true || FlagEvent.PlayerStruct[aIndex]._InEvent == true || BattleEvent.PlayerStruct[aIndex]._InEvent == true)
		{
			Func.MsgOutput(aIndex, 1, "Proibido usar o comando no evento.");
			return;
		}
		else if (Duel.DuelStruct[aIndex]._Duel == true)
		{
			Func.MsgOutput(aIndex, 1, "Proibido usar o comando no duelo.");
			return;
		}
		else
		{
			if (gObj[aIndex].m_PK_Level != 3)
			{
				gObj[aIndex].m_PK_Level = 3;
				gObj[aIndex].m_PK_Count = 0;
				gObj[aIndex].m_PK_Time = 0;

				GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[3]);

				GCPkLevelSend(aIndex, gObj[aIndex].m_PK_Level);

				Func.MsgOutput(aIndex, 1, "Seu PK/Hero foi limpo com sucesso.");
			}
			else
			{
				Func.MsgOutput(aIndex, 1, "Você não é pk nem hero.");
			}
		}
	}
}

void Commands::Killer(int aIndex)
{
	if (this->_Active[14] == true)
	{
		if (gObj[aIndex].Level < this->_Level[6])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[6]);
			return;
		}
		else if (gObj[aIndex].Money < this->_Zen[6])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[6]);
			return;
		}
		else if (this->_Vip[5] == true && Custom[aIndex].VipCount < 1)
		{
			Func.MsgOutput(aIndex, 1, "Exclusivo apenas para vip's.");
			return;
		}
		else
		{
			if (gObj[aIndex].m_PK_Level < 6)
			{
				gObj[aIndex].m_PK_Level = 6;

				GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[6]);

				GCPkLevelSend(aIndex, gObj[aIndex].m_PK_Level);

				Func.MsgOutput(aIndex, 1, "Você agora é um assassino.");
			}
			else
			{
				Func.MsgOutput(aIndex, 1, "Você já é um assassino.");
			}
		}
	}
}

void Commands::Ware(int aIndex, char* msg)
{
	if (this->_Active[4] == true)
	{
		Custom[aIndex].Ware = atoi(msg);

		if (strlen(msg) < 1 || Custom[aIndex].Ware < 0)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s <Número>", this->_Syntax[7]);
			return;
		}
		else if (gObj[aIndex].Level < this->_Level[4])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[4]);
			return;
		}
		else if (gObj[aIndex].Money < this->_Zen[4])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[4]);
			return;
		}
		else if (gObj[aIndex].m_IfState.use != 0)
		{
			Func.MsgOutput(aIndex, 1, "Feche todas as janelas para mudar de baú.");
			return;
		}

		Manager.CheckVault(aIndex, gObj[aIndex].AccountID);

		if (Custom[aIndex].Ware > this->_Ware[Custom[aIndex].VipCount] && this->_Type == 0)
		{
			Func.MsgOutput(aIndex, 1, "O seu limite de baús é %d", this->_Ware[Custom[aIndex].VipCount]);
			return;
		}
		else if (Custom[aIndex].Ware > Custom[aIndex].Vault[1] && this->_Type == 1)
		{
			Func.MsgOutput(aIndex, 1, "O seu limite de baús é %d", Custom[aIndex].Vault[1]);
			return;
		}
		else if (Custom[aIndex].Vault[0] == Custom[aIndex].Ware)
		{
			Func.MsgOutput(aIndex, 1, "O baú %d já está sendo utilizado.", Custom[aIndex].Ware);
			return;
		}

		Custom[aIndex].Delay[1] = (GetTickCount() - Custom[aIndex].Delay[2]) / 1000;

		if (Custom[aIndex].Delay[1] < 5)
		{
			Func.MsgOutput(aIndex, 1, "Aguarde %d %s para usar novamente.", (5 - Custom[aIndex].Delay[1]), (5 - Custom[aIndex].Delay[1] == 1) ? "segundo" : "segundos");
			return;
		}

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Commands::Change, (void*)aIndex, 0, 0);

		Custom[aIndex].Delay[2] = GetTickCount();

		GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[4]);
	}
}

void Commands::Change(int aIndex)
{
	while (true)
	{
		for (int i = 5; i >= 1; i--)
		{
			CGWarehouseUseEnd(aIndex);

			gObj[aIndex].m_IfState.state = 0;
			gObj[aIndex].m_IfState.type = 0;
			gObj[aIndex].m_IfState.use = 0;
			gObj[aIndex].LoadWareHouseInfo = 0;
			gObj[aIndex].WarehouseSave = 0;

			gObj[aIndex].m_ReqWarehouseOpen = true;

			Func.MsgOutput(aIndex, 1, "Selecionando baú em %d %s", i, (i == 1) ? "segundo." : "segundos.");

			if (i == 3)
			{
				Manager.ExecFormat("EXEC MuOnline.dbo.MUDAR_BAU '%s', %d", gObj[aIndex].AccountID, Custom[aIndex].Ware);
			}
			else if (i == 1)
			{
				gObj[aIndex].m_ReqWarehouseOpen = false;

				Func.MsgOutput(aIndex, 1, "O baú %d foi selecionado com sucesso.", Custom[aIndex].Ware);
			}

			Sleep(1000);
		}
		break;
	}

	_endthread();
}

void Commands::Money(int aIndex)
{
	if (this->_Active[5] == true)
	{
		if (this->_Vip[4] == true && Custom[aIndex].VipCount < 1)
		{
			Func.MsgOutput(aIndex, 1, "Exclusivo apenas para vip's.");
			return;
		}

		Func.MsgOutput(aIndex, 1, "Zen adicionado com sucesso.");

		GCMoneySend(aIndex, gObj[aIndex].Money = this->_Zen[5]);
	}
}

void Commands::Premiar(int aIndex, char* msg)
{
	if (this->_Active[6] == true && Authority.Check(&gObj[aIndex], 0) == true)
	{
		memset(this->_Name[0], 0, sizeof(this->_Name[0]));

		this->_Number = 0;

		sscanf(msg, "%s %d", this->_Name[0], &this->_Number);

		int Index = Func.Get_PlayerIndex(this->_Name[0]);

		if (strlen(msg) < 1 || this->_Number <= 0 || this->_Number > 100)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s <Nome> <Valor>", this->_Syntax[10]);
			Func.MsgOutput(aIndex, 1, "Limite de 100 por premiação!");
			return;
		}
		else if (gObj[Index].Connected < 3)
		{
			Func.MsgOutput(aIndex, 1, "O Personagem não se encontra.");
			return;
		}

		Manager.ExecFormat(Query._Query[6], this->_Number, gObj[Index].AccountID);

		Func.AllServerAnnounce(this->_Notice, this->_Name[0], this->_Number);

		Log2("GameMaster: %s", gObj[aIndex].Name);
		Log2("Jogador: %s, Prêmio: %d", gObj[Index].Name, this->_Number);
	}
}

void Commands::MoveAll(int aIndex, char* msg)
{
	if (this->_Active[7] == true && Authority.Check(&gObj[aIndex], 1) == true)
	{
		this->_MapNumber[0] = -1, this->_X[0] = -1, this->_Y[0] = -1;

		sscanf(msg, "%d %d %d", &this->_MapNumber[0], &this->_X[0], &this->_Y[0]);

		if (strlen(msg) < 1 || this->_MapNumber[0] == -1 || this->_X[0] == -1 || this->_Y[0] == -1)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s <Mapa> <X> <Y>", this->_Syntax[11]);
			return;
		}

		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].AuthorityCode == 0)
			{
				gObjTeleport(i, this->_MapNumber[0], this->_X[0], this->_Y[0]);
			}
		}

		Func.MsgOutput(aIndex, 1, "Movidos com sucesso.");
	}
}

void Commands::Skin(int aIndex, char* msg)
{
	if (this->_Active[8] == true && Authority.Check(&gObj[aIndex], 2) == true)
	{
		memset(this->_Name[0], 0, sizeof(this->_Name[0]));

		this->_Number = -1;

		sscanf(msg, "%s %d", this->_Name[0], &this->_Number);

		int Index = Func.Get_PlayerIndex(this->_Name[0]);

		if (strlen(msg) < 1)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s <Nome> <Número>", this->_Syntax[12]);
			return;
		}
		else if (gObj[Index].Connected < 3)
		{
			Func.MsgOutput(aIndex, 1, "Personagem não se encontra.");
			return;
		}

		gObj[Index].m_Change = this->_Number;
		gObjViewportListProtocolCreate(&gObj[Index]);

		if (Index == aIndex)
		{
			Func.MsgOutput(aIndex, 1, "%s Mudou de skin.", gObj[aIndex].Name);
		}
		else
		{
			Func.MsgOutput(aIndex, 1, "Skin adicionada.");

			Func.MsgOutput(Index, 1, "Skin adicionada por %s", gObj[aIndex].Name);
		}
	}
}

void Commands::Move(int aIndex, char* msg)
{
	if (this->_Active[9] == true && Authority.Check(&gObj[aIndex], 3) == true)
	{
		memset(this->_Name[0], 0, sizeof(this->_Name[0]));

		this->_MapNumber[0] = -1, this->_X[0] = -1, this->_Y[0] = -1;

		sscanf(msg, "%s %d %d %d", &this->_Name[0], &this->_MapNumber[0], &this->_X[0], &this->_Y[0]);

		int Index = Func.Get_PlayerIndex(this->_Name[0]);

		if (strlen(msg) < 1 || this->_MapNumber[0] == -1 || this->_X[0] == -1 || this->_Y[0] == -1)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s <Nome> <Mapa> <X> <Y>", this->_Syntax[13]);
			return;
		}
		else if (gObj[Index].Connected < 3)
		{
			Func.MsgOutput(aIndex, 1, "Personagem não se encontra.");
			return;
		}

		gObjTeleport(Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);

		if (Index == aIndex)
		{
			Func.MsgOutput(aIndex, 1, "Você foi movido com sucesso.");
		}
		else
		{
			Func.MsgOutput(aIndex, 1, "Movido com sucesso.");

			Func.MsgOutput(Index, 1, "Você foi movido por %s", gObj[aIndex].Name);
		}
	}
}

void Commands::FireWork(int aIndex)
{
	if (Authority.Check(&gObj[aIndex], 4) == true && this->_Active[10] == true)
	{
		Func.FireWork(aIndex);
	}
}

void Commands::Evento(int aIndex, char* msg)
{
	if (this->_Active[11] == true && Authority.Check(&gObj[aIndex], 6) == true)
	{
		memset(this->_Name[1], 0, sizeof(this->_Name[1]));

		this->_MapNumber[1] = -1, this->_X[1] = -1, this->_Y[1] = -1;

		sscanf(msg, "%s %d %d %d %d", &this->_Name[1], &this->_MapNumber[1], &this->_X[1], &this->_Y[1], &this->_Count);

		if (strlen(msg) < 1 || this->_MapNumber[1] == -1 || this->_X[1] == -1 || this->_Y[1] == -1 || this->_Count > 60)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s <Nome do evento> <Mapa> <X> <Y> <Time>", this->_Syntax[15]);
			Func.MsgOutput(aIndex, 1, "Limite do time 60 segundos.");
			return;
		}

		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].Connected == 3)
			{
				Func.MsgOutput(i, 0, "Evento %s Inicializado!", this->_Name[1]);
				Func.MsgOutput(i, 0, "Para participar, utilize o comando: %s", this->_Syntax[9]);
			}
		}

		_beginthread(&Commands::Run, NULL, 0);

		this->_Event = true;

		gObjTeleport(aIndex, this->_MapNumber[1], this->_X[1], this->_Y[1]);
	}
}

void Commands::Register(int aIndex)
{
	if (this->_Active[11] == true && gObj[aIndex].AuthorityCode < 1)
	{
		if (Custom[aIndex].Waiting == true)
		{
			Func.MsgOutput(aIndex, 1, "Você já está registrado no evento. Aguarde.");
			return;
		}
		else if (this->_Event == true)
		{
			Func.MsgOutput(aIndex, 1, "Aguarde você será movido em instantes.");

			Custom[aIndex].Waiting = true;
		}
		else
		{
			Func.MsgOutput(aIndex, 1, "Nenhum evento inicializado.");
		}
	}
}

void Commands::Run(void * lpParam)
{
	while (Command._Count > 1)
	{
		Command._Count--;

		for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			if (gObj[i].Connected == 3)
			{
				Func.MsgOutput(i, 0, "Evento %s inicia em %d Segundo(s)", Command._Name[1], Command._Count);

				Func.MsgOutput(i, 1, "Para participar, utilize o comando: %s", Command._Syntax[9]);
			}
		}

		Sleep(1000);
	}

	Func.AllServerAnnounce("Inscrições para o evento encerradas!");

	Command._Event = false; Command._Count = 0;

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			if (Custom[i].Waiting == true)
			{
				gObjTeleport(i, Command._MapNumber[1], Command._X[1], Command._Y[1]);

				Custom[i].Waiting = false;
			}
		}
	}
}

void Commands::Disconnect(int aIndex, char* msg)
{
	if (this->_Active[12] == true && Authority.Check(&gObj[aIndex], 8) == true)
	{
		if (strlen(msg) < 1)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s <Nome>", this->_Syntax[16]);
			return;
		}

		memset(this->_Name[0], 0, sizeof(this->_Name[0]));

		sscanf(msg, "%s", &this->_Name[0]);

		int Index = Func.Get_PlayerIndex(this->_Name[0]);

		if (gObj[Index].Connected < 3)
		{
			Func.MsgOutput(aIndex, 1, "Personagem não se encontra.");
			return;
		}

		CloseClient(Index);

		Func.AllServerAnnounce("%s Foi desconnectado por %s", gObj[Index].Name, gObj[aIndex].Name);
	}
}

void Commands::Drop(int aIndex, char* msg)
{
	if (this->_Active[13] == true && Authority.Check(&gObj[aIndex], 5) == true)
	{
		int Type = -1, Index = -1, Level = -1, Skill = 0, Luck = 0, Option = 0, Excelente = 0;

		sscanf(msg, "%d %d %d %d %d %d %d", &Type, &Index, &Level, &Skill, &Luck, &Option, &Excelente);

		if (strlen(msg) < 1 || Type == -1 || Index == -1 || Level == -1)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s <Type> <Index> <Level> <Skill> <Luck> <Option> <Exc> <Anc>", this->_Syntax[17]);
			return;
		}

		int Item = ITEMGET(Type, Index);

		ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, Level, 0, Skill, Luck, Option, aIndex, Excelente);

		Func.MsgOutput(aIndex, 1, "Item criado com sucesso.");
	}
}

bool Commands::War(int aIndex, char* msg)
{
	if (strlen(msg) < 1 || strlen(&msg[1]) > 8)
	{
		Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
		Func.MsgOutput(aIndex, 1, "Digite: /war <Guild>");
		return false;
	}
	else if (!_stricmp(msg, gObj[aIndex].GuildName))
	{
		Func.MsgOutput(aIndex, 1, "Proibido war contra a própria guild!");
		return false;
	}

	return true;
}

void Commands::Track(int aIndex, char* msg)
{
	if (gObj[aIndex].AuthorityCode > 1)
	{
		if (strlen(msg) < 1)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: /track <Nome>");
			return;
		}

		memset(this->_Name[0], 0, sizeof(this->_Name[0]));

		sscanf(msg, "%s", &this->_Name[0]);

		int Index = Func.Get_PlayerIndex(this->_Name[0]);

		if (gObj[Index].Connected < 3)
		{
			Func.MsgOutput(aIndex, 1, "Personagem não se encontra.");
			return;
		}

		gObjTeleport(Index, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y);
	}
}

void Commands::Trace(int aIndex, char* msg)
{
	if (gObj[aIndex].AuthorityCode > 1)
	{
		if (strlen(msg) < 1)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: /trace <Nome>");
			return;
		}

		memset(this->_Name[0], 0, sizeof(this->_Name[0]));

		sscanf(msg, "%s", &this->_Name[0]);

		int Index = Func.Get_PlayerIndex(this->_Name[0]);

		if (gObj[Index].Connected < 3)
		{
			Func.MsgOutput(aIndex, 1, "Personagem não se encontra.");
			return;
		}

		gObjTeleport(aIndex, gObj[Index].MapNumber, gObj[Index].X, gObj[Index].Y);
	}
}

void Commands::Class(int aIndex, int Type)
{
	if (Custom[aIndex].VipCount > 0)
	{
		if (Block.BlockStruct[aIndex]._Active == 1)
		{
			Func.Golden(aIndex, "Conta protegida!");
			Func.Golden(aIndex, "Utilize a senha para desbloquear.");
			return;
		}
		else if (gObj[aIndex].m_IfState.use != 0)
		{
			Func.MsgOutput(aIndex, 1, "Feche todas as janelas para executar o comando.");
			return;
		}
		else if (gObj[aIndex].m_RecallMon >= 0)
		{
			Func.MsgOutput(aIndex, 1, "Remova a invocação para executar o comando.");
			return;
		}

		for (int i = 0; i < 11; i++)
		{
			if (gObj[aIndex].pInventory[i].m_Type > 0)
			{
				Func.MsgOutput(aIndex, 1, "Remova os itens equipados!");
				return;
			}
		}

		switch (Type)
		{
		case 0: // - Soul Master
		{
			gObj[aIndex].Class = WIZARD;
			gObj[aIndex].ChangeUP = 1;
			gObj[aIndex].DBClass = 1;

			BYTE New = (gObj[aIndex].Class << 5) & 0xE0;
			New |= (gObj[aIndex].ChangeUP << 4) & 0x10;

			GCSendQuestPrize(aIndex, 201, New);

			Func.MsgOutput(aIndex, 1, "Classe alterada para: Soul Master");
		}
		break;
		case 1: // - Blade Knight
		{
			gObj[aIndex].Class = KNIGHT;
			gObj[aIndex].ChangeUP = 1;
			gObj[aIndex].DBClass = 17;

			BYTE New = (gObj[aIndex].Class << 5) & 0xE0;
			New |= (gObj[aIndex].ChangeUP << 4) & 0x10;

			GCSendQuestPrize(aIndex, 201, New);

			Func.MsgOutput(aIndex, 1, "Classe alterada para: Blade Knight");
		}
		break;
		case 2: // - Muse Elf
		{
			gObj[aIndex].Class = ELF;
			gObj[aIndex].ChangeUP = 1;
			gObj[aIndex].DBClass = 33;

			BYTE New = (gObj[aIndex].Class << 5) & 0xE0;
			New |= (gObj[aIndex].ChangeUP << 4) & 0x10;

			GCSendQuestPrize(aIndex, 201, New);

			Func.MsgOutput(aIndex, 1, "Classe alterada para: Muse Elf");
		}
		break;
		case 3: // - Magic Gladiator
		{
			gObj[aIndex].Class = MAGIC;
			gObj[aIndex].ChangeUP = 0;
			gObj[aIndex].DBClass = 48;

			BYTE New = (gObj[aIndex].Class << 5) & 0xE0;
			New |= (gObj[aIndex].ChangeUP << 4) & 0x10;

			GCSendQuestPrize(aIndex, 201, New);

			Func.MsgOutput(aIndex, 1, "Classe alterada para: Magic Gladiator");
		}
		break;
		}

		for (int i = 0; i < 60; i++) // Zero Magic
		{
			if (gObj[aIndex].Magic[i].IsMagic() == 1)
			{
				gObj[aIndex].Magic[i].Clear();
			}
		}

		WORD Class = gObj[aIndex].Class;

		Func.CheckBuffs(&gObj[aIndex]);

		gObjMakePreviewCharSet(aIndex);

		gObjClearViewport(&gObj[aIndex]);
		gObjViewportListProtocolCreate(&gObj[aIndex]);

		GCMagicListMultiSend(&gObj[aIndex]);

		gObj[aIndex].Life = gObj[aIndex].MaxLife;
		gObj[aIndex].AddLife = 0;
		gObj[aIndex].Mana = gObj[aIndex].MaxMana;
		gObj[aIndex].AddMana = 0;
		gObj[aIndex].MaxLife = Func.GetStatus(&gObj[aIndex], Class, 0);
		gObj[aIndex].MaxMana = Func.GetStatus(&gObj[aIndex], Class, 1);
		gObjSetBP(aIndex);
		gObj[aIndex].BP = gObj[aIndex].MaxBP / 2;
		gObj[aIndex].AddBP = 0;

		Func.UpdateCharacter(aIndex, false);
	}
	else
	{
	    Func.MsgOutput(aIndex, 1, "Você não possui o plano vip necessário!");
    }
}

void Commands::Information(int aIndex)
{
	Manager.CoinCount(aIndex, gObj[aIndex].AccountID);

	Custom[aIndex].MasterPoint = Manager.MasterPoint(gObj[aIndex].Name);

	int ResetsDay = Manager.CountDay(gObj[aIndex].Name);

	Func.MsgOutput(aIndex, 0, "Resets: %d, EventPoint: %d, Cash: %d", Custom[aIndex].ResetCount, Custom[aIndex].MasterPoint, Custom[aIndex].Coin[5]);
	Func.MsgOutput(aIndex, 0, "Pontos de patentes: %d, Resets Diários: %d", Custom[aIndex].Patent, ResetsDay);

	switch (Custom[aIndex].VipCount)
	{
	case 0:
		Func.MsgOutput(aIndex, 0, "Sua conta é: Free");
		break;
	case 1:
		Func.MsgOutput(aIndex, 0, "Sua conta é: VIP Bonus");
		break;
	case 2:
		Func.MsgOutput(aIndex, 0, "Sua conta é: VIP Premium");
		break;
	}
}

void Commands::Nick(int aIndex, char* msg)
{
	if (Custom[aIndex].VipCount > 0)
	{
		if (gObj[aIndex].GuildNumber > 0)
		{
			Func.MsgOutput(aIndex, 1, "Necessário sair da guild para efetuar a troca.");
			return;
		}

		while (std::isspace(*msg))
		{
			++msg;
		}

		if (strlen(msg) <= 4 || strlen(msg) >= 11)
		{
			Func.MsgOutput(aIndex, 1, "Necessário 4 a 10 dígitos para efetuar a troca.");
			return;
		}
		else if (Func.CheckString(msg) == false)
		{
			Func.MsgOutput(aIndex, 1, "Você utilizou caracteres inválidos!");
			return;
		}
		else if (Manager.CheckNick(aIndex, msg))
		{
			Func.MsgOutput(aIndex, 1, "O nome de usuário já existe!");
			return;
		}

		Manager.CoinCount(aIndex, gObj[aIndex].AccountID);

		if (Custom[aIndex].Coin[3] < 15000)
		{
			Func.MsgOutput(aIndex, 1, "É necessário 15000 de Golds.");
			return;
		}

		Custom[aIndex].Coin[3] -= 15000;

		Manager.ExecFormat("UPDATE MEMB_INFO SET Gold = Gold - 15000 WHERE memb___id = '%s'", gObj[aIndex].AccountID);

		if (gObj[aIndex].Level >= 1 && gObj[aIndex].Level <= 6)
		{
			Manager.ExecFormat("UPDATE Character SET cLevel = %d WHERE Name = '%s'", gObj[aIndex].Level, gObj[aIndex].Name);

			Manager.ExecFormat("UPDATE Character SET LevelUpPoint = %d WHERE Name = '%s'", gObj[aIndex].LevelUpPoint, gObj[aIndex].Name);

			Manager.ExecFormat("UPDATE Character SET Money = %d WHERE Name = '%s'", gObj[aIndex].Money, gObj[aIndex].Name);

			Manager.ExecFormat("UPDATE Character SET Strenght = %d WHERE Name = '%s'", gObj[aIndex].Strength, gObj[aIndex].Name);
			Manager.ExecFormat("UPDATE Character SET Dexterity = %d WHERE Name = '%s'", gObj[aIndex].Dexterity, gObj[aIndex].Name);
			Manager.ExecFormat("UPDATE Character SET Vitality = %d WHERE Name = '%s'", gObj[aIndex].Vitality, gObj[aIndex].Name);
			Manager.ExecFormat("UPDATE Character SET Energy = %d WHERE Name = '%s'", gObj[aIndex].Energy, gObj[aIndex].Name);
		}

		Manager.ExecFormat("UPDATE Character SET Name = '%s' WHERE Name = '%s'", msg, gObj[aIndex].Name);

		for (int i = 1; i <= 5; i++)
		{
			Manager.ExecFormat("UPDATE AccountCharacter SET GameID%d = '%s' WHERE GameID%d = '%s'", i, msg, i, gObj[aIndex].Name);
		}

		Manager.ExecFormat("UPDATE AccountCharacter SET GameIDC = '%s' WHERE GameIDC = '%s'", msg, gObj[aIndex].Name);

		gObjCloseSet(aIndex, 1);

		Func.MsgOutput(aIndex, 1, "Troca efetuada com sucesso.");
	}
	else
	{
		Func.MsgOutput(aIndex, 1, "Você não possui o plano vip necessário!");
	}
}

void Commands::Rei(int aIndex, char* msg)
{
	if (gObj[aIndex].AuthorityCode > 1)
	{
		memset(this->_Name[0], 0, sizeof(this->_Name[0]));

		this->_Number = 0;

		sscanf(msg, "%s %d", this->_Name[0], &this->_Number);

		int Index = Func.Get_PlayerIndex(this->_Name[0]);

		if (strlen(msg) < 1 || this->_Number <= 0 || this->_Number > 1)
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: /rei <Nome> 1");
			return;
		}
		else if (gObj[Index].Connected < 3)
		{
			Func.MsgOutput(aIndex, 1, "O jogador não está online!");
			return;
		}

		Manager.ExecFormat("UPDATE Character SET ReiEvent = 0");

		Manager.ExecFormat("UPDATE Character SET ReiEvent = ReiEvent + %d WHERE Name = '%s'", this->_Number, gObj[Index].Name);

		Func.AllServerAnnounce("%s é o novo Rei do Mu Fenix!", this->_Name[0], this->_Number);
	}
}

void Commands::Finish(int aIndex)
{
	if (gObj[aIndex].Authority > 1)
	{
		if (DuelEvent._State != DuelEvent.Empty)
		{
			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3 && Custom[i].InEvent == true)
				{
					Custom[i].InEvent = false;

					Custom[i].Move = true;

					if (gObj[i].m_PK_Level != 3)
					{
						gObj[i].m_PK_Level = 3;
						GCPkLevelSend(i, 3);
					}
				}
			}

			DuelEvent._Players[0].clear();
			DuelEvent._Players[1].clear();

			DuelEvent._State = DuelEvent.Empty;
			DuelEvent._Count = 0;

			Func.AllServerAnnounce("O Mata-Mata foi encerrado por: %s", gObj[aIndex].Name);
		}

		if (PairEvent._State != PairEvent.Empty)
		{
			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3 && Custom[i].InEvent == true)
				{
					Custom[i].InEvent = false;

					Custom[i].Move = true;

					if (gObj[i].m_PK_Level != 3)
					{
						gObj[i].m_PK_Level = 3;
						GCPkLevelSend(i, 3);
					}
				}
			}

			PairEvent._Teams[0].clear();
			PairEvent._Teams[1].clear();

			PairEvent._Registered.clear();

			PairEvent._State = PairEvent.Empty;
			PairEvent._Count = 0;

			Func.AllServerAnnounce("O Dupla PVP foi encerrado por: %s", gObj[aIndex].Name);
		}

		if (PegaEvent._State != PegaEvent.Empty)
		{
			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3 && Custom[i].InEvent == true)
				{
					Custom[i].InEvent = false;

					Custom[i].Move = true;

					gObj[i].UseMagicNumber = 0;
				}
			}

			PegaEvent._Players.clear();

			PegaEvent._State = PairEvent.Empty;
			PegaEvent._Count = 0;

			Func.AllServerAnnounce("O Pega-Pega foi encerrado por: %s", gObj[aIndex].Name);
		}

		if (SobreEvent._State != SobreEvent.Empty)
		{
			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3 && Custom[i].InEvent == true)
				{
					Custom[i].InEvent = false;

					Custom[i].Move = true;

					if (gObj[i].m_PK_Level != 3)
					{
						gObj[i].m_PK_Level = 3;
						GCPkLevelSend(i, 3);
					}
				}
			}

			SobreEvent._Players.clear();

			SobreEvent._State = SobreEvent.Empty;
			SobreEvent._Count = 0;

			Func.AllServerAnnounce("O Survivor foi encerrado por: %s", gObj[aIndex].Name);
		}

		if (RoletaEvent._State != RoletaEvent.Empty)
		{
			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3 && RoletaEvent.PlayerStruct[i]._InEvent == true)
				{
					RoletaEvent.PlayerStruct[i]._InEvent = false;

					Custom[i].Move = true;

					if (gObj[i].m_PK_Level != 3)
					{
						gObj[i].m_PK_Level = 3;
						GCPkLevelSend(i, 3);
					}
				}
			}

			RoletaEvent._Players.clear();

			RoletaEvent._State = RoletaEvent.Empty;
			RoletaEvent._Count = 0;

			Func.AllServerAnnounce("O Roleta Russa foi encerrado por: %s", gObj[aIndex].Name);
		}

		if (UfcEvent._State != UfcEvent.Empty)
		{
			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3 && Custom[i].InEvent == true)
				{
					Custom[i].InEvent = false;

					Custom[i].Move = true;

					if (gObj[i].m_PK_Level != 3)
					{
						gObj[i].m_PK_Level = 3;
						GCPkLevelSend(i, 3);
					}
				}
			}

			UfcEvent._Players[0].clear();
			UfcEvent._Players[1].clear();

			UfcEvent._State = UfcEvent.Empty;
			UfcEvent._Count = 0;

			Func.AllServerAnnounce("O Ufc foi encerrado por: %s", gObj[aIndex].Name);
		}

		if (KingEvent._State != KingEvent.Empty)
		{
			for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3 && Custom[i].InEvent == true)
				{
					Custom[i].InEvent = false;

					Custom[i].Move = true;

					if (gObj[i].m_PK_Level != 3)
					{
						gObj[i].m_PK_Level = 3;
						GCPkLevelSend(i, 3);
					}
				}
			}

			KingEvent._Players[0].clear();
			KingEvent._Players[1].clear();

			KingEvent._State = KingEvent.Empty;
			KingEvent._Count = 0;

			Func.AllServerAnnounce("O Rei do Mu foi encerrado por: %s", gObj[aIndex].Name);
		}

		Func.MsgOutput(aIndex, 1, "Os eventos foram encerrados com sucesso.");
	}
	else
	{
		Func.MsgOutput(aIndex, 1, "Exclusivo para staff!");
	}
}

void Commands::OpenWare(int aIndex)
{
	if (Custom[aIndex].VipCount <= 0)
	{
		Func.MsgOutput(aIndex, 1, "Exclusivo apenas para vip's.");
		return;
	}

	if (Custom[aIndex].InEvent == true ||
		DeathEvent.PlayerStruct[aIndex]._InEvent == true ||
		TheftEvent.PlayerStruct[aIndex]._InEvent == true ||
		FlagEvent.PlayerStruct[aIndex]._InEvent == true ||
		BattleEvent.PlayerStruct[aIndex]._InEvent == true)
	{
		Func.MsgOutput(aIndex, 1, "Proibido usar o comando no evento.");
		return;
	}

	if (Duel.DuelStruct[aIndex]._Duel == true)
	{
		Func.MsgOutput(aIndex, 1, "Proibido usar o comando no duelo.");
		return;
	}

	if (gObj[aIndex].Live == 0)
	{
		Func.MsgOutput(aIndex, 1, "Você não pode usar o baú morto.");
		return;
	}

	if (gObj[aIndex].m_IfState.use != 0)
	{
		Func.MsgOutput(aIndex, 1, "Feche todas as janelas para executar o comando.");
		return;
	}

	Custom[aIndex].Delay[1] = (GetTickCount() - Custom[aIndex].Delay[2]) / 1000;

	if (Custom[aIndex].Delay[1] < 10)
	{
		Func.MsgOutput(aIndex, 1, "Aguarde %d %s para usar o baú.",(10 - Custom[aIndex].Delay[1]),(10 - Custom[aIndex].Delay[1] == 1) ? "segundo" : "segundos");
		return;
	}

	CGWarehouseUseEnd(aIndex);

	gObj[aIndex].LoadWareHouseInfo = 0;
	gObj[aIndex].WarehouseSave = 0;
	gObj[aIndex].m_ReqWarehouseOpen = true;
	gObj[aIndex].m_IfState.use = 1;
	gObj[aIndex].m_IfState.type = 6;
	gObj[aIndex].m_IfState.state = 0;

	GDGetWarehouseList(aIndex, gObj[aIndex].AccountID);

	Custom[aIndex].Delay[2] = GetTickCount();

	Func.MsgOutput(aIndex, 1, "Solicitando abertura do baú...");
}

// [ Novo ]: Comando para testar eventos
bool Commands::TestEvent(int aIndex, const char* Text)
{
	LPOBJ lpObj = &gObj[aIndex];

	if (Authority.Check(lpObj, 9) == false)
	{
		return false;
	}

	char Cmd[60] = { 0 };
	char Arg[60] = { 0 };
	char Buffer[60] = { 0 };
	char* Token = nullptr;
	char* Context = nullptr;

	strcpy_s(Buffer, Text);

	Token = strtok_s(Buffer, " ", &Context);
	if (!Token) return false;
	strcpy_s(Cmd, Token);

	Token = strtok_s(nullptr, " ", &Context);
	if (Token) strcpy_s(Arg, Token);

	// Pascoa
	if (!_stricmp(Cmd, Pascoa._Syntax[2]) && !_stricmp(Arg, Pascoa._Syntax[3]))
	{
		Pascoa.StartManual();
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Pascoa iniciado.");
		return true;
	}

	// Natal
	if (!_stricmp(Cmd, Natal._Syntax[2]) && !_stricmp(Arg, Natal._Syntax[3]))
	{
		Natal.StartManual();
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Natal iniciado.");
		return true;
	}

	// Treasure
	if (!_stricmp(Cmd, Treasure._Syntax[2]) && !_stricmp(Arg, Treasure._Syntax[3]))
	{
		Treasure.StartManual();
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Treasure iniciado.");
		return true;
	}

	// DuelEvent
	if (!_stricmp(Cmd, DuelEvent._Syntax[2]) && !_stricmp(Arg, DuelEvent._Syntax[3]))
	{
		DuelEvent.Start(1, 4);
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Duel iniciado.");
		return true;
	}

	// KingEvent
	if (!_stricmp(Cmd, KingEvent._Syntax[2]) && !_stricmp(Arg, KingEvent._Syntax[3]))
	{
		KingEvent.Start(1, 4);
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento King iniciado.");
		return true;
	}

	// UfcEvent
	if (!_stricmp(Cmd, UfcEvent._Syntax[2]) && !_stricmp(Arg, UfcEvent._Syntax[3]))
	{
		UfcEvent.Start(1, 4);
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Ufc iniciado.");
		return true;
	}

	// BattleEvent
	if (!_stricmp(Cmd, BattleEvent._Syntax[2]) && !_stricmp(Arg, BattleEvent._Syntax[3]))
	{
		BattleEvent.Start(1, 4);
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Battle iniciado.");
		return true;
	}

	// PegaEvent
	if (!_stricmp(Cmd, PegaEvent._Syntax[2]) && !_stricmp(Arg, PegaEvent._Syntax[3]))
	{
		PegaEvent.Start(1);
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Pega iniciado.");
		return true;
	}

	// SobreEvent
	if (!_stricmp(Cmd, SobreEvent._Syntax[2]) && !_stricmp(Arg, SobreEvent._Syntax[3]))
	{
		SobreEvent.Start(1);
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Sobre iniciado.");
		return true;
	}

	// QuizEvent
	if (!_stricmp(Cmd, QuizEvent._Syntax[2]) && !_stricmp(Arg, QuizEvent._Syntax[3]))
	{
		QuizEvent.StartManual();
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Quiz iniciado.");
		return true;
	}

	// FlagEvent
	if (!_stricmp(Cmd, FlagEvent._Syntax[2]) && !_stricmp(Arg, FlagEvent._Syntax[3]))
	{
		FlagEvent.StartManual();
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Flag iniciado.");
		return true;
	}

	// DropEvent
	if (!_stricmp(Cmd, DropEvent._Syntax[2]) && !_stricmp(Arg, DropEvent._Syntax[3]))
	{
		DropEvent.StartManual();
		Func.MsgOutput(aIndex, 1, "[Aviso]: Teste do evento Drop iniciado.");
		return true;
	}

	return false;
}


Commands Command;





