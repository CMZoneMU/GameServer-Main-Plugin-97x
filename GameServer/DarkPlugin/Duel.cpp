#include "StdAfx.h"

bool cDuel::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Duel.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Level = Section.Rows[0].GetInt(1);
		this->_Zen = Section.Rows[0].GetInt(2);

		strcpy_s(this->_Column, sizeof(this->_Column), (Section.Rows[0].GetStringPtr(3)));
		strcpy_s(this->_Coin, sizeof(this->_Coin), (Section.Rows[0].GetStringPtr(4)));

		strcpy_s(this->_Syntax[0], sizeof(this->_Syntax[0]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(this->_Syntax[1], sizeof(this->_Syntax[1]), (Section.Rows[0].GetStringPtr(6)));

		this->_MapNumber[0] = Section.Rows[1].GetInt(0);
		this->_X[0] = Section.Rows[1].GetInt(1);
		this->_Y[0] = Section.Rows[1].GetInt(2);
		this->_Time[0] = Section.Rows[1].GetInt(3) * 60;
		this->_Score[0] = Section.Rows[1].GetInt(4);

		this->_MapNumber[1] = Section.Rows[2].GetInt(0);
		this->_X[1] = Section.Rows[2].GetInt(1);
		this->_Y[1] = Section.Rows[2].GetInt(2);
		this->_Time[1] = Section.Rows[2].GetInt(3) * 60;
		this->_Score[1] = Section.Rows[2].GetInt(4);

		this->_MapNumber[2] = Section.Rows[3].GetInt(0);
		this->_X[2] = Section.Rows[3].GetInt(1);
		this->_Y[2] = Section.Rows[3].GetInt(2);
		this->_Time[2] = Section.Rows[3].GetInt(3) * 60;
		this->_Score[2] = Section.Rows[3].GetInt(4);

		this->_MapNumber[3] = Section.Rows[4].GetInt(0);
		this->_X[3] = Section.Rows[4].GetInt(1);
		this->_Y[3] = Section.Rows[4].GetInt(2);
		this->_Time[3] = Section.Rows[4].GetInt(3) * 60;
		this->_Score[3] = Section.Rows[4].GetInt(4);
	}

	return true;
}

int cDuel::GetPlayer(std::string Name)
{
	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			if (!strcmp(gObj[i].Name, Name.c_str()))
			{
				return i;
			}
		}
	}

	return -1;
}

bool cDuel::Attack(LPOBJ lpObj, LPOBJ Target)
{
	if (lpObj->Type == PLAYER && Target->Type == PLAYER)
	{
		if (this->DuelStruct[lpObj->m_Index]._Attack == true)
		{
			return false;
		}
	}

	return true;
}

bool cDuel::CheckRoom(int aIndex, int Target)
{
	if (!this->RoomStruct[0]._Live && !this->RoomStruct[0]._Invitation)
	{
		this->RoomStruct[0]._Invitation = true;

		this->DuelStruct[aIndex]._Room = 0;

		this->DuelStruct[Target]._Room = 0;

		this->DuelStruct[aIndex]._State = 1;
		return true;
	}
	else if (!this->RoomStruct[1]._Live && !this->RoomStruct[1]._Invitation)
	{
		this->RoomStruct[1]._Invitation = true;

		this->DuelStruct[aIndex]._Room = 1;

		this->DuelStruct[Target]._Room = 1;

		this->DuelStruct[aIndex]._State = 1;
		return true;
	}
	else if (!this->RoomStruct[2]._Live && !this->RoomStruct[2]._Invitation)
	{
		this->RoomStruct[2]._Invitation = true;

		this->DuelStruct[aIndex]._Room = 2;

		this->DuelStruct[Target]._Room = 2;

		this->DuelStruct[aIndex]._State = 1;
		return true;
	}
	else if (!this->RoomStruct[3]._Live && !this->RoomStruct[3]._Invitation)
	{
		this->RoomStruct[3]._Invitation = true;

		this->DuelStruct[aIndex]._Room = 3;

		this->DuelStruct[Target]._Room = 3;

		this->DuelStruct[aIndex]._State = 1;
		return true;
	}

	return false;
}

void cDuel::DuelRoom(int aIndex, int Target, int Room)
{
	this->RoomStruct[Room]._Invitation = false;

	this->RoomStruct[Room]._Live = true;

	this->RoomStruct[Room]._Index = aIndex;

	this->RoomStruct[Room]._Target = Target;

	Func.MsgOutput(aIndex, 0, "[   DUELO   ]");
	Func.MsgOutput(aIndex, 0, "%s VS %s - Sala : %d", gObj[this->RoomStruct[Room]._Index].Name, gObj[this->RoomStruct[Room]._Target].Name, (Room + 1));

	Func.MsgOutput(Target, 0, "[   DUELO   ]");
	Func.MsgOutput(Target, 0, "%s VS %s - Sala : %d", gObj[this->RoomStruct[Room]._Index].Name, gObj[this->RoomStruct[Room]._Target].Name, (Room + 1));

	if (this->DuelStruct[aIndex]._Total > 0 && this->DuelStruct[Target]._Total > 0)
	{
		this->RoomStruct[Room]._Total = this->DuelStruct[aIndex]._Total + this->DuelStruct[Target]._Total;
	}

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)cDuel::Run, (void*)Room, 0, 0);
}

void cDuel::InvitationSend(int aIndex, int Target)
{
	this->DuelStruct[aIndex]._State = 1;
	this->DuelStruct[Target]._State = 2;

	this->DuelStruct[aIndex]._Time = 0;
	this->DuelStruct[Target]._Time = 0;

	this->DuelStruct[aIndex]._Total = 0;
	this->DuelStruct[Target]._Total = 0;

	this->DuelStruct[aIndex]._Index = Target;
	this->DuelStruct[Target]._Index = aIndex;

	Func.MsgOutput(aIndex, 1, "Convite de duelo enviado.", gObj[aIndex].Name);

	if (this->_Count > 0)
	{
		this->DuelStruct[aIndex]._Total = this->_Count;
		this->DuelStruct[Target]._Total = this->_Count;

		Func.MsgOutput(Target, 1, "%s lhe convidou para um duelo.", gObj[aIndex].Name);
		Func.MsgOutput(Target, 1, "Deseja aceitar? Digite: %s", this->_Syntax[1]);
		Func.MsgOutput(Target, 1, "Duelo valendo %d %s", this->_Count, this->_Coin);

		this->_Count = 0;
	}
	else
	{
		Func.MsgOutput(Target, 1, "%s lhe convidou para um duelo.", gObj[aIndex].Name);
		Func.MsgOutput(Target, 1, "Deseja aceitar? Digite: %s", this->_Syntax[1]);
	}
}

void cDuel::InvitationCancel(int aIndex, int Target)
{
	this->DuelStruct[aIndex]._State = 0;
	this->DuelStruct[Target]._State = 0;

	this->DuelStruct[aIndex]._Time = 0;
	this->DuelStruct[Target]._Time = 0;

	this->DuelStruct[aIndex]._Index = 0;
	this->DuelStruct[Target]._Index = 0;

	this->RoomStruct[this->DuelStruct[aIndex]._Room]._Live = false;
	this->RoomStruct[this->DuelStruct[Target]._Room]._Live = false;

	this->RoomStruct[this->DuelStruct[aIndex]._Room]._Invitation = false;
	this->RoomStruct[this->DuelStruct[Target]._Room]._Invitation = false;

	this->RoomStruct[this->DuelStruct[aIndex]._Room]._Total = 0;
	this->RoomStruct[this->DuelStruct[Target]._Room]._Total = 0;

	this->DuelStruct[aIndex]._Room = 0;
	this->DuelStruct[Target]._Room = 0;

	Func.MsgOutput(aIndex, 1, "Duelo cancelado.");
	Func.MsgOutput(Target, 1, "Duelo cancelado.");
}

void cDuel::InvitationCheck(LPOBJ lpObj)
{
	int Target = this->DuelStruct[lpObj->m_Index]._Index;

	if (this->DuelStruct[lpObj->m_Index]._State == 2)
	{
		this->DuelStruct[lpObj->m_Index]._Time++;

		if (this->DuelStruct[lpObj->m_Index]._Time > 10)
		{
			this->InvitationCancel(lpObj->m_Index, Target);
		}
	}

	if (this->DuelStruct[Target]._State == 1 || this->DuelStruct[Target]._State == 2)
	{
		if (gObj[Target].Connected < 3)
		{
			this->InvitationCancel(lpObj->m_Index, Target);
		}
	}
}

void cDuel::Invitation(int aIndex, char* msg)
{
	if (!this->_Active)
	{
		Func.MsgOutput(aIndex, 1, "Comando desabilitado.");
		return;
	}

	memset(this->_Name, 0, sizeof(this->_Name));

	this->_Count = 0;

	sscanf(msg, "%s %d", &this->_Name, &this->_Count);

	int Index = this->GetPlayer(this->_Name);

	if (strlen(msg) < 1 || this->_Count > 20)
	{
		Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
		Func.MsgOutput(aIndex, 1, "Digite: %s <Nome>", this->_Syntax[0]);
		Func.MsgOutput(aIndex, 1, "Duelando apostado:");
		Func.MsgOutput(aIndex, 1, "Digite: %s <Nome> <Quantidade>", this->_Syntax[0]);
		Func.MsgOutput(aIndex, 1, "Limite por aposta: 20 Golds.");
		return;
	}
	else if (aIndex == Index)
	{
		Func.MsgOutput(aIndex, 1, "Você não pode duelar contra você mesmo.");
		return;
	}
	else if (Index == -1)
	{
		Func.MsgOutput(aIndex, 1, "O oponente escolhido não está online.");
		return;
	}
	else if (this->DuelStruct[aIndex]._State == 1 || this->DuelStruct[aIndex]._State == 2 || this->DuelStruct[aIndex]._State == 3)
	{
		Func.MsgOutput(aIndex, 1, "Você já está em um duelo.");
		return;
	}
	else if (this->DuelStruct[Index]._State == 1 || this->DuelStruct[Index]._State == 2 || this->DuelStruct[Index]._State == 3)
	{
		Func.MsgOutput(aIndex, 1, "Seu oponente já está em um duelo.");
		return;
	}
	else if (gObj[aIndex].m_IfState.use != 0)
	{
		Func.MsgOutput(aIndex, 1, "Você está ocupado no momento.");
		return;
	}
	else if (gObj[Index].m_IfState.use != 0)
	{
		Func.MsgOutput(aIndex, 1, "Seu oponente está ocupado no momento.");
		return;
	}
	else if (gObj[aIndex].Level < this->_Level)
	{
		Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level);
		return;
	}
	else if (gObj[aIndex].Money < this->_Zen)
	{
		Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen);
		return;
	}
	else if (gObj[Index].Level < this->_Level)
	{
		Func.MsgOutput(aIndex, 1, "O oponente não possui level %d", this->_Level);
		return;
	}
	else if (gObj[Index].Money < this->_Zen)
	{
		Func.MsgOutput(aIndex, 1, "O oponente não possui zen %d", this->_Zen);
		return;
	}

	if (this->_Count == 0)
	{
		if (this->CheckRoom(aIndex, Index) == false)
		{
			Func.MsgOutput(aIndex, 1, "Não existem salas liberadas no momento.");
			return;
		}

		this->InvitationSend(aIndex, Index);
	}
	else if (this->_Count > 0)
	{
		if (this->_Count > Custom[aIndex].Coin[1])
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d %s", this->_Count, this->_Coin);
			return;
		}
		else if (this->_Count > Custom[Index].Coin[1])
		{
			Func.MsgOutput(aIndex, 1, "O oponente não possui %d %s", this->_Count, this->_Coin);
			return;
		}
		else if (this->CheckRoom(aIndex, Index) == false)
		{
			Func.MsgOutput(aIndex, 1, "Não existem salas liberadas no momento.");
			return;
		}

		this->InvitationSend(aIndex, Index);
	}
}

void cDuel::AcceptSend(int aIndex, int Target)
{
	this->DuelStruct[aIndex]._Duel = true;
	this->DuelStruct[Target]._Duel = true;

	this->DuelStruct[aIndex]._Attack = true;
	this->DuelStruct[Target]._Attack = true;

	this->DuelStruct[aIndex]._State = 3;
	this->DuelStruct[Target]._State = 3;

	this->DuelStruct[aIndex]._Time = 0;
	this->DuelStruct[Target]._Time = 0;

	this->DuelRoom(Target, aIndex, this->DuelStruct[aIndex]._Room);

	GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen);
	GCMoneySend(Target, gObj[Target].Money -= this->_Zen);

	if (this->DuelStruct[aIndex]._Total > 0 && this->DuelStruct[Target]._Total > 0)
	{
		Custom[aIndex].Coin[1] -= this->DuelStruct[aIndex]._Total;

		Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s - %d WHERE memb___id = '%s'", this->_Column, this->_Column, this->DuelStruct[aIndex]._Total, gObj[aIndex].AccountID);

		Custom[Target].Coin[1] -= this->DuelStruct[Target]._Total;

		Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s - %d WHERE memb___id = '%s'", this->_Column, this->_Column, this->DuelStruct[Target]._Total, gObj[Target].AccountID);
	}
}

void cDuel::Accept(int aIndex)
{
	if (!this->_Active)
	{
		Func.MsgOutput(aIndex, 1, "Comando desabilitado.");
		return;
	}
	else if (this->DuelStruct[aIndex]._State != 2)
	{
		Func.MsgOutput(aIndex, 1, "Não existe nenhum convite ativo.");
		return;
	}
	else if (gObj[this->DuelStruct[aIndex]._Index].Connected < 3)
	{
		Func.MsgOutput(aIndex, 1, "Não foi possível continuar, seu oponente saiu.");

		this->InvitationCancel(aIndex, this->DuelStruct[aIndex]._Index);
		return;
	}
	else if (gObj[aIndex].m_IfState.use == 0)
	{
		this->AcceptSend(aIndex, this->DuelStruct[aIndex]._Index);
		return;
	}
	else
	{
		Func.MsgOutput(aIndex, 1, "Você está ocupado no momento.");
	}
}

void cDuel::ClearRoom(int Room)
{
	this->DuelStruct[this->RoomStruct[Room]._Index]._Duel = false;
	this->DuelStruct[this->RoomStruct[Room]._Target]._Duel = false;

	this->DuelStruct[this->RoomStruct[Room]._Index]._Attack = false;
	this->DuelStruct[this->RoomStruct[Room]._Target]._Attack = false;

	this->DuelStruct[this->RoomStruct[Room]._Index]._State = 0;
	this->DuelStruct[this->RoomStruct[Room]._Target]._State = 0;

	this->DuelStruct[this->RoomStruct[Room]._Index]._Score = 0;
	this->DuelStruct[this->RoomStruct[Room]._Target]._Score = 0;

	this->DuelStruct[this->RoomStruct[Room]._Index]._Total = 0;
	this->DuelStruct[this->RoomStruct[Room]._Target]._Total = 0;

	this->RoomStruct[Room]._Running = false;

	this->RoomStruct[Room]._Invitation = false;

	this->RoomStruct[Room]._Waiting = false;

	this->RoomStruct[Room]._Live = false;

	this->RoomStruct[Room]._Total = 0;

	this->RoomStruct[Room]._Index = 0;
	this->RoomStruct[Room]._Target = 0;

	this->RoomStruct[Room]._Time[0] = 0;
	this->RoomStruct[Room]._Time[1] = 0;
	this->RoomStruct[Room]._Time[2] = 0;
}

void cDuel::ZeroStruct(int aIndex, int Target)
{
	this->DuelStruct[aIndex]._Duel = false;
	this->DuelStruct[Target]._Duel = false;

	this->DuelStruct[aIndex]._Attack = false;
	this->DuelStruct[Target]._Attack = false;

	this->DuelStruct[aIndex]._Room = 0;
	this->DuelStruct[Target]._Room = 0;

	this->DuelStruct[aIndex]._Index = 0;
	this->DuelStruct[Target]._Index = 0;

	this->DuelStruct[aIndex]._State = 0;
	this->DuelStruct[Target]._State = 0;

	this->DuelStruct[aIndex]._Time = 0;
	this->DuelStruct[Target]._Time = 0;

	this->DuelStruct[aIndex]._Score = 0;
	this->DuelStruct[Target]._Score = 0;

	this->DuelStruct[aIndex]._Total = 0;
	this->DuelStruct[Target]._Total = 0;
}

void cDuel::Killer(LPOBJ lpObj, LPOBJ Target)
{
	if (lpObj->Type == PLAYER && Target->Type == PLAYER)
	{
		int Room = this->DuelStruct[lpObj->m_Index]._Room;

		if (this->RoomStruct[Room]._Live == true && this->RoomStruct[Room]._Running == true)
		{
			if (this->DuelStruct[lpObj->m_Index]._State == 3 && this->DuelStruct[Target->m_Index]._State == 3 && lpObj->MapNumber == this->_MapNumber[Room])
			{
				this->DuelStruct[lpObj->m_Index]._Score++;

				Func.MsgOutput(lpObj->m_Index, 0, "[    PLACAR    ]");

				Func.MsgOutput(lpObj->m_Index, 0, "%s  vs  %s", lpObj->Name, Target->Name);

				Func.MsgOutput(lpObj->m_Index, 0, "%d   x   %d", this->DuelStruct[lpObj->m_Index]._Score, this->DuelStruct[Target->m_Index]._Score);

				Func.MsgOutput(Target->m_Index, 0, "[    PLACAR    ]");

				Func.MsgOutput(Target->m_Index, 0, "%s  vs  %s", Target->Name, lpObj->Name);

				Func.MsgOutput(Target->m_Index, 0, "%d   x   %d", this->DuelStruct[Target->m_Index]._Score, this->DuelStruct[lpObj->m_Index]._Score);

				if (this->DuelStruct[lpObj->m_Index]._Score == this->_Score[Room])
				{
					this->CheckWinner(lpObj->m_Index, Target->m_Index);
				}
			}
		}
	}
}

void cDuel::CheckWinner(int aIndex, int Target)
{
	int Room = this->DuelStruct[aIndex]._Room;

	if (this->DuelStruct[aIndex]._Score > this->DuelStruct[Target]._Score)
	{
		this->Winner(aIndex, Target, this->DuelStruct[aIndex]._Score, this->DuelStruct[Target]._Score);
	}
	else if (this->DuelStruct[Target]._Score > this->DuelStruct[aIndex]._Score)
	{
		this->Winner(aIndex, Target, this->DuelStruct[aIndex]._Score, this->DuelStruct[Target]._Score);
	}
	else if (this->DuelStruct[aIndex]._Score == this->DuelStruct[Target]._Score)
	{
		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3)
			{
				Func.MsgOutput(Index, 0, "[   DUELO   ]");
				Func.MsgOutput(Index, 0, "Houve um empate entre %s e %s", gObj[aIndex].Name, gObj[Target].Name);
			}
		}

		if (this->DuelStruct[aIndex]._Total > 0 && this->DuelStruct[Target]._Total > 0)
		{
			Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s + %d WHERE memb___id = '%s'", this->_Column, this->_Column, this->DuelStruct[aIndex]._Total, gObj[aIndex].AccountID);
			Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s + %d WHERE memb___id = '%s'", this->_Column, this->_Column, this->DuelStruct[Target]._Total, gObj[Target].AccountID);
		}

		this->DuelStruct[aIndex]._Move = true;
		this->DuelStruct[Target]._Move = true;

		this->ClearRoom(Room);

		this->ZeroStruct(aIndex, Target);

	}
	else if (this->DuelStruct[Target]._Score == this->DuelStruct[aIndex]._Score)
	{
		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3)
			{
				Func.MsgOutput(Index, 0, "[   DUELO   ]");
				Func.MsgOutput(Index, 0, "Houve um empate entre %s e %s", gObj[Target].Name, gObj[aIndex].Name);
			}
		}

		if (this->DuelStruct[Target]._Total > 0 && this->DuelStruct[aIndex]._Total > 0)
		{
			Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s + %d WHERE memb___id = '%s'", this->_Column, this->_Column, this->DuelStruct[Target]._Total, gObj[Target].AccountID);
			Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s + %d WHERE memb___id = '%s'", this->_Column, this->_Column, this->DuelStruct[aIndex]._Total, gObj[aIndex].AccountID);
		}

		this->DuelStruct[Target]._Move = true;
		this->DuelStruct[aIndex]._Move = true;

		this->ClearRoom(Room);

		this->ZeroStruct(aIndex, Target);
	}
}

void cDuel::Winner(int aIndex, int Target, int Score1, int Score2)
{
	int Room = this->DuelStruct[aIndex]._Room;

	gObj[aIndex].m_PK_Level = 3;

	GCPkLevelSend(aIndex, 3);

	gObjTeleport(aIndex, 2, 212, 41);

	for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
	{
		if (gObj[Index].Connected == 3)
		{
			if (this->RoomStruct[Room]._Total == 0)
			{
				Func.MsgOutput(Index, 0, "[   DUELO   ]");

				Func.MsgOutput(Index, 0, "%s venceu um duelo contra %s por %d x %d", gObj[aIndex].Name, gObj[Target].Name, Score1, Score2);
			}
			else if (this->RoomStruct[Room]._Total > 0)
			{
				Func.MsgOutput(Index, 0, "[   DUELO VALENDO   ]");

				Func.MsgOutput(Index, 0, "%s venceu um duelo contra %s por %d x %d", gObj[aIndex].Name, gObj[Target].Name, Score1, Score2);

				Func.MsgOutput(Index, 0, "Valor ganho: %d %s", this->RoomStruct[Room]._Total, this->_Coin);
			}
		}
	}

	Manager.ExecFormat(Query._Query[27], gObj[aIndex].Name);
	Manager.ExecFormat(Query._Query[28], gObj[Target].Name);

	if (this->RoomStruct[Room]._Total > 0)
	{
		Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s + %d WHERE memb___id = '%s'", this->_Column, this->_Column, this->RoomStruct[Room]._Total, gObj[aIndex].AccountID);
	}

	Func.FireWork(aIndex);

	this->DuelStruct[Target]._Move = true;

	this->ClearRoom(Room);

	this->ZeroStruct(aIndex, Target);
}

void cDuel::Run(int Room)
{
	while (true)
	{
		if (Duel.RoomStruct[Room]._Live == true)
		{
			if (!Duel.RoomStruct[Room]._Waiting)
			{
				Duel.RoomStruct[Room]._Time[2]++;

				Func.MsgOutput(Duel.RoomStruct[Room]._Index, 1, "Movendo-se para a sala %d em %d Segundo(s)", (Room + 1), (6 - Duel.RoomStruct[Room]._Time[2]));
				Func.MsgOutput(Duel.RoomStruct[Room]._Target, 1, "Movendo-se para a sala %d em %d Segundo(s)", (Room + 1), (6 - Duel.RoomStruct[Room]._Time[2]));

				if (Duel.RoomStruct[Room]._Time[2] == 5)
				{
					gObjTeleport(Duel.RoomStruct[Room]._Index, Duel._MapNumber[Room], Duel._X[Room], Duel._Y[Room]);
					gObjTeleport(Duel.RoomStruct[Room]._Target, Duel._MapNumber[Room], Duel._X[Room], Duel._Y[Room]);

					gObj[Duel.RoomStruct[Room]._Index].m_PK_Level = 6;
					gObj[Duel.RoomStruct[Room]._Target].m_PK_Level = 6;

					GCPkLevelSend(Duel.RoomStruct[Room]._Index, 6);
					GCPkLevelSend(Duel.RoomStruct[Room]._Target, 6);

					Duel.RoomStruct[Room]._Waiting = true;
				}

			}
			else if (Duel.RoomStruct[Room]._Running == true)
			{
				Duel.RoomStruct[Room]._Time[1]++;

				if (Duel.RoomStruct[Room]._Time[1] >= Duel._Time[Room])
				{
					Func.MsgOutput(Duel.RoomStruct[Room]._Index, 0, "[   DUELO   ]");
					Func.MsgOutput(Duel.RoomStruct[Room]._Index, 0, "Infelizmente o tempo foi esgotado.");

					Func.MsgOutput(Duel.RoomStruct[Room]._Target, 0, "[   DUELO   ]");
					Func.MsgOutput(Duel.RoomStruct[Room]._Target, 0, "Infelizmente o tempo foi esgotado.");

					Duel.RoomStruct[Room]._Time[1] = 0;

					Duel.CheckWinner(Duel.RoomStruct[Room]._Index, Duel.RoomStruct[Room]._Target);

				}
			}
			else
			{
				Duel.RoomStruct[Room]._Time[0]++;

				Func.MsgOutput(Duel.RoomStruct[Room]._Index, 0, "Inicio em %d Segundo(s)", (6 - Duel.RoomStruct[Room]._Time[0]));

				Func.MsgOutput(Duel.RoomStruct[Room]._Target, 0, "Inicio em %d Segundo(s)", (6 - Duel.RoomStruct[Room]._Time[0]));

				if (Duel.RoomStruct[Room]._Time[0] == 5)
				{
					Func.MsgOutput(Duel.RoomStruct[Room]._Index, 0, "O duelo começou!", (11 - Duel.RoomStruct[Room]._Time[0]));

					Func.MsgOutput(Duel.RoomStruct[Room]._Target, 0, "O duelo começou!", (11 - Duel.RoomStruct[Room]._Time[0]));

					Duel.DuelStruct[Duel.RoomStruct[Room]._Index]._Attack = false;

					Duel.DuelStruct[Duel.RoomStruct[Room]._Target]._Attack = false;

					Duel.RoomStruct[Room]._Running = true;

					Duel.RoomStruct[Room]._Time[0] = 0;
				}
			}
		}
		else
		{
			_endthread();
		}

		Sleep(1000);
	}
}

void cDuel::Quit(LPOBJ lpObj)
{
	if (this->DuelStruct[lpObj->m_Index]._Duel == true)
	{
		lpObj->m_PK_Level = 3;

		GCPkLevelSend(lpObj->m_Index, 3);

		lpObj->MapNumber = 0; lpObj->X = 125; lpObj->Y = 125;

		int Room = this->DuelStruct[lpObj->m_Index]._Room;

		int Target = this->DuelStruct[lpObj->m_Index]._Index;

		gObj[Target].m_PK_Level = 3;

		GCPkLevelSend(Target, 3);

		gObjTeleport(Target, 2, 212, 41);

		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3)
			{
				if (this->RoomStruct[Room]._Total == 0)
				{
					Func.MsgOutput(Index, 0, "[   DUELO   ]");

					Func.MsgOutput(Index, 0, "%s venceu um duelo por W.O.", gObj[Target].Name);
				}
				else if (this->RoomStruct[Room]._Total > 0)
				{
					Func.MsgOutput(Index, 0, "[   DUELO VALENDO  ]");

					Func.MsgOutput(Index, 0, "%s venceu um duelo por W.O.", gObj[Target].Name);

					Func.MsgOutput(Index, 0, "Valor ganho: %d %s", this->RoomStruct[Room]._Total, this->_Coin);
				}
			}
		}

		Manager.ExecFormat(Query._Query[27], gObj[Target].Name);
		Manager.ExecFormat(Query._Query[28], lpObj->Name);

		if (this->RoomStruct[Room]._Total > 0)
		{
			Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s + %d WHERE memb___id = '%s'", this->_Column, this->_Column, this->RoomStruct[Room]._Total, gObj[Target].AccountID);
		}

		Func.FireWork(Target);

		Duel.ClearRoom(Room);

		Duel.ZeroStruct(Duel.RoomStruct[Room]._Index, Duel.RoomStruct[Room]._Target);
	}
}

cDuel Duel;