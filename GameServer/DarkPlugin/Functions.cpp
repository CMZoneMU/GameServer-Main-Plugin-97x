#include "StdAfx.h"

void Functions::Hook(DWORD Function, DWORD Offset)
{
	*(DWORD*)(Offset + 1) = Function - (Offset + 5);
}

void Functions::HookJump(DWORD Offset, LPVOID Function)
{
	*(BYTE*)(Offset) = 0xE9;
	*(DWORD*)(Offset + 1) = (DWORD)Function - (Offset + 5);
}

void Functions::SetNop(DWORD Offset, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		*(BYTE*)(Offset + i) = 0x90;
	}
}

void Functions::SetRRetn(DWORD Offset)
{
	*(BYTE*)(Offset) = 0xC3;
	*(BYTE*)(Offset + 1) = 0x90;
	*(BYTE*)(Offset + 2) = 0x90;
	*(BYTE*)(Offset + 3) = 0x90;
	*(BYTE*)(Offset + 4) = 0x90;
}

int Functions::Get_PlayerIndex(char* Name)
{
	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected > 2)
		{
			if (!strcmp(gObj[i].Name, Name))
			{
				return i;
			}
		}
	}

	return -1;
}

void Functions::Blue(LPCSTR Nome, LPSTR Mensagem, int aIndex)
{
	BYTE Buffer[0xFF] = { 0 };
	BYTE Len = strlen(Mensagem);
	Buffer[0] = 0xC1;
	Buffer[1] = Len + 15;
	Buffer[2] = 0x00;
	strncpy((char*)&Buffer[3], Nome, 10);
	Buffer[13] = 0x7E;
	strncpy((char*)&Buffer[14], Mensagem, Len);

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			DataSend(i, (unsigned char*)Buffer, Buffer[1]);
		}
	}
}

void Functions::Green(LPCSTR Nome, LPSTR Mensagem, int aIndex)
{
	BYTE Buffer[0xFF] = { 0 };
	BYTE Len = strlen(Mensagem);
	Buffer[0] = 0xC1;
	Buffer[1] = Len + 15;
	Buffer[2] = 0x00;
	Buffer[13] = 0x40;
	strncpy((char*)&Buffer[3], Nome, 10);
	strncpy((char*)&Buffer[14], Mensagem, Len);

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			DataSend(i, (unsigned char*)Buffer, Buffer[1]);
		}
	}
}

void Functions::Yellow(LPCSTR Nome, LPSTR Mensagem, int aIndex)
{
	BYTE Buffer[0xFF] = { 0 };
	BYTE Len = strlen(Mensagem);
	Buffer[0] = 0xC1;
	Buffer[1] = Len + 14;
	Buffer[2] = 0x02;
	strncpy((char*)&Buffer[3], Nome, 10);
	strncpy((char*)&Buffer[13], Mensagem, Len);

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			DataSend(i, (unsigned char*)Buffer, Buffer[1]);
		}
	}
}

void Functions::Golden(int aIndex, const char* Format, ...)
{
	char Buffer[512] = "";
	va_list pArguments;

	va_start(pArguments, Format);
	vsprintf(&Buffer[0], Format, pArguments);
	va_end(pArguments);

	BYTE* Packet = (BYTE*)malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet + 2) = 0x02;
	memcpy((Packet + 13), Buffer, strlen(Buffer));
	int Len = (strlen(Buffer) + 0x13);
	*(Packet + 1) = Len;

	DataSend(aIndex, Packet, Len);

	free(Packet);
}

void Functions::Announce(const char* Format, ...)
{
	char Buffer[512] = "";

	va_list pArguments;

	va_start(pArguments, Format);
	vsprintf(Buffer, Format, pArguments);
	va_end(pArguments);

	BYTE* Packet;
	Packet = (BYTE*)malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet + 2) = 0x02;
	memcpy((Packet + 13), Buffer, strlen(Buffer));
	int Len = (strlen(Buffer) + 0x13);
	*(Packet + 1) = Len;

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			DataSend(i, Packet, Len);
		}
	}

	free(Packet);
}

// Correção mana e vida para o cliente atualizar corretamente
void Functions::UpdateCharacter(int aIndex, bool Effect)
{
	gObjCalCharacter(aIndex);
	gObjCalcMaxLifePower(aIndex);

	PMSG_UPDATECHARACTER Result;

	Result.h.c = 0xC1;
	Result.h.size = sizeof(PMSG_UPDATECHARACTER);
	Result.h.head = 0xFE;
	Result.Code = (Effect == true) ? 1 : 2;

	if (Effect == true)
	{
		Result.Experience = gObj[aIndex].Experience;
		Result.NextExperience = gObj[aIndex].NextExp;
		Result.Level = (WORD)(gObj[aIndex].Level);
	}

	Result.LevelUpPoint = gObj[aIndex].LevelUpPoint;
	Result.Strength = (WORD)(gObj[aIndex].Strength);
	Result.Dexterity = (WORD)(gObj[aIndex].Dexterity);
	Result.Vitality = (WORD)(gObj[aIndex].Vitality);
	Result.Energy = (WORD)(gObj[aIndex].Energy);
	Result.Life = (WORD)(gObj[aIndex].Life);
	Result.MaxLife = (WORD)(gObj[aIndex].MaxLife);
	Result.Mana = (WORD)(gObj[aIndex].Mana);
	Result.MaxMana = (WORD)(gObj[aIndex].MaxMana);
	Result.BP = (WORD)(gObj[aIndex].BP);
	Result.MaxBP = (WORD)(gObj[aIndex].MaxBP);

	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

	Func.SendMain(aIndex);
}

int Functions::MonsterAdd(int Monster, int MapNumber, int X, int Y)
{
	int Index = gObjAddMonster(MapNumber);

	if (Index >= 0)
	{
		gObj[Index].Class = Monster;
		gObj[Index].MapNumber = MapNumber;
		gObj[Index].X = X;
		gObj[Index].Y = Y;
		gObj[Index].Live = TRUE;
		gObj[Index].m_State = TRUE;
		gObj[Index].DieRegen = FALSE;

		gObjSetMonster(Index, Monster);
	}

	return Index;
}

void Functions::FireWork(int aIndex)
{
	if (gObj[aIndex].X <= 5 || gObj[aIndex].X >= 250 || gObj[aIndex].Y <= 5 || gObj[aIndex].Y >= 250)
	{
		return;
	}

	char Packet[5] = { -2, -1, 0, 1, 2 };

	BYTE FireWork[10][7];

	for (int i = 0; i < 10; i++)
	{
		BYTE X = (rand() % 5);
		BYTE Y = (rand() % 5);

		FireWork[i][0] = 0xC1;
		FireWork[i][1] = 0x07;
		FireWork[i][2] = 0xF3;
		FireWork[i][3] = 0x40;
		FireWork[i][4] = 0x00;
		FireWork[i][5] = (BYTE)(gObj[aIndex].X + Packet[X]);
		FireWork[i][6] = (BYTE)(gObj[aIndex].Y + Packet[Y]);
	}

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			if (gObj[i].MapNumber == gObj[aIndex].MapNumber)
			{
				for (int Count = 0; Count < 10; Count++)
				{
					DataSend(i, (LPBYTE)(&FireWork[Count]), FireWork[Count][1]);
				}
			}
		}
	}
}

void Functions::MsgOutput(int aIndex, int Type, char* Msg, ...)
{
	char Buffer[250];
	va_list pArgs;
	va_start(pArgs, Msg);
	vsprintf(Buffer, Msg, pArgs);
	va_end(pArgs);
	GCServerMsgStringSend(Buffer, aIndex, Type);
}

void Functions::AllServerAnnounce(char* message, ...)
{
	char szBuffer[512] = "";
	va_list pArguments;

	va_start(pArguments, message);
	vsprintf(&szBuffer[0], message, pArguments);
	va_end(pArguments);

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			GCServerMsgStringSend(&szBuffer[0], i, 0);
		}
	}
}

void Functions::MsgOutputAll(char* message, ...)
{
	char szBuffer[512] = "";
	va_list pArguments;

	va_start(pArguments, message);
	vsprintf(&szBuffer[0], message, pArguments);
	va_end(pArguments);

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			GCServerMsgStringSend(&szBuffer[0], i, 1);
		}
	}
}

int Functions::CheckInventory(int aIndex, int Type, int Level)
{
	int Count = 0;

	for (int i = 12; i < 76; i++)
	{
		if (gObj[aIndex].pInventory[i].m_Type == Type && gObj[aIndex].pInventory[i].m_Level >= Level)
		{
			Count++;
		}
	}

	return Count;
}

int Functions::DeleteInventory(int aIndex, int Type, int Level, int Quantity)
{
	int Count = 0;

	for (int i = 12; i < 76; i++)
	{
		if (gObj[aIndex].pInventory[i].m_Type == Type && gObj[aIndex].pInventory[i].m_Level >= Level)
		{
			gObjInventoryDeleteItem(aIndex, i);

			GCInventoryItemDeleteSend(aIndex, i, 1);

			Count++;

			if (Quantity == Count)
				break;
		}
	}

	return Count;
}

int Functions::GetInventoryEmptySlotCount(LPOBJ lpObj)
{
	int Count = 0;

	for (int i = 0; i < 64; i++)
	{
		if (lpObj->InventoryMap1[i] == 0xFF)
		{
			Count++;
		}
	}

	return Count;
}

BOOL Functions::gObjAttackEx(OBJECTSTRUCT* lpObj, OBJECTSTRUCT* lpTargetObj, class CMagicInf* lpMagic, int magicsend, unsigned char MSBFlag, int AttackDamage)
{
	if (lpTargetObj->Authority > 1)
	{
		return FALSE;
	}

	if (!DuelEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!PegaEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!SobreEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!DeathEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!TheftEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!Duel.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!Speed.Attack(lpObj, lpTargetObj, lpMagic))
	{
		return FALSE;
	}

	if (!FlagEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!PairEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!RoletaEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!UfcEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!KingEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (!BattleEvent.Attack(lpObj, lpTargetObj))
	{
		return FALSE;
	}

	if (gObjCalDistance(lpObj, lpTargetObj) > 6)
	{
		return FALSE;
	}

	if (lpTargetObj->Type == MONSTER)
	{
		if (lpTargetObj->m_RecallMon > 0 && Custom[lpTargetObj->m_RecallMon].Pet == true)
		{
			return false;
		}
	}

	if (lpObj->Type == PLAYER && lpTargetObj->Type == PLAYER)
	{
		if (lpObj->PartyNumber != -1 && lpTargetObj->PartyNumber != -1)
		{
			if (lpObj->PartyNumber == lpTargetObj->PartyNumber)
			{
				return FALSE;
			}
		}

		if (Setting._PvP == 1)
		{
			return FALSE;
		}
	}

	return gObjAttack(lpObj, lpTargetObj, lpMagic, magicsend, MSBFlag, AttackDamage);
}

void Functions::gObjLifeCheckEx(LPOBJ lpTargetObj, LPOBJ lpObj, int AttackDamage, int DamageSendType, int MSBFlag, int MSBDamage, BYTE Skill)
{
	if (BossEvent._Active == true)
	{
		if (lpTargetObj->Life <= 0 && lpTargetObj->Live != 0)
		{
			if (lpTargetObj->Type == MONSTER && lpTargetObj->Class == BossEvent._Monster && lpTargetObj->m_Index == BossEvent._Index)
			{
				BossEvent.Finish(lpObj->m_Index);
			}
		}
	}

	if (Natal._Active == true)
	{
		if (lpTargetObj->Life <= 0 && lpTargetObj->Live != 0)
		{
			if (lpTargetObj->Type == MONSTER && lpTargetObj->Class > 0 && lpTargetObj->Class == Natal._Class[0])
			{
				// fix erro: ID dinamico
				Natal.Santa(lpObj->m_Index);

				lpTargetObj->Live = false;

				gObjDel(lpTargetObj->m_Index);
			}
			else if (lpTargetObj->Type == MONSTER && lpTargetObj->Class > 0 && lpTargetObj->Class == Natal._Class[1])
			{
				// fix erro: ID dinamico
				Natal.Globin(lpObj->m_Index);

				lpTargetObj->Live = false;

				gObjDel(lpTargetObj->m_Index);
			}
		}
	}

	if (Pascoa._Active == true)
	{
		if (lpTargetObj->Life <= 0 && lpTargetObj->Live != 0)
		{
			if (lpTargetObj->Type == MONSTER && lpTargetObj->Class > 0 && lpTargetObj->Class == Pascoa._Class[0])
			{
				// fix erro: ID agora e dinamico
				Pascoa.Assasin(lpObj->m_Index);

				lpTargetObj->Live = false;

				gObjDel(lpTargetObj->m_Index);
			}
			else if (lpTargetObj->Type == MONSTER && lpTargetObj->Class > 0 && lpTargetObj->Class == Pascoa._Class[1])
			{
				// fix erro: ID agora e dinamico
				Pascoa.Rabbit(lpObj->m_Index);

				lpTargetObj->Live = false;

				gObjDel(lpTargetObj->m_Index);
			}
		}
	}

	if (Quest._Active == true)
	{
		if (lpTargetObj->Life <= 0 && lpTargetObj->Live != 0)
		{
			if (Quest.PlayerStruct[lpObj->m_Index]._Start == 1 && lpTargetObj->Class == Quest.QuestStruct[Quest.PlayerStruct[lpObj->m_Index]._Index]._Monster)
			{
				Quest.Kill(lpObj->m_Index);
			}
		}
	}

	if (lpTargetObj->Life <= 0 && lpTargetObj->Live != 0)
	{
		if (lpTargetObj->Type == PLAYER)
		{
			if (Custom[lpTargetObj->m_Index].Helper == true)
			{
				Custom[lpTargetObj->m_Index].Helper = false;

				lpTargetObj->m_SkillAttackTime = 0;
				lpTargetObj->m_SkillDefenseTime = 0;
			}
		}
	}

	return gObjLifeCheck(lpTargetObj, lpObj, AttackDamage, DamageSendType, MSBFlag, MSBDamage, Skill);
}

void Functions::gObjPlayerKillerEx(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	DeathEvent.Killer(lpObj, lpTargetObj);
	TheftEvent.Killer(lpObj, lpTargetObj);
	Duel.Killer(lpObj, lpTargetObj);
	FlagEvent.Killer(lpObj, lpTargetObj);
	Ring.Killer(lpObj, lpTargetObj);

	if (Custom[lpTargetObj->m_Index].Helper == true)
	{
		Custom[lpTargetObj->m_Index].Helper = false;

		lpTargetObj->m_SkillAttackTime = 0;
		lpTargetObj->m_SkillDefenseTime = 0;
	}

	if (lpObj->Type == PLAYER && lpTargetObj->Type == PLAYER)
	{
		if (lpObj->m_PK_Level < 3)
		{
			Custom[lpObj->m_Index].Hero++;
		}

		if (lpObj->m_PK_Level > 3)
		{
			Custom[lpObj->m_Index].Killer++;
		}

		CItem* Right = &lpObj->pInventory[0];
		CItem* Left = &lpObj->pInventory[1];

		if (Right->m_Type == ITEMGET(0, 30) || Left->m_Type == ITEMGET(0, 30))
		{
			Custom[lpObj->m_Index].Count[0]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(1, 12) || Left->m_Type == ITEMGET(1, 12))
		{
			Custom[lpObj->m_Index].Count[1]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(1, 14) || Left->m_Type == ITEMGET(1, 14))
		{
			Custom[lpObj->m_Index].Count[2]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(1, 23) || Left->m_Type == ITEMGET(1, 23))
		{
			Custom[lpObj->m_Index].Count[3]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(1, 28) || Left->m_Type == ITEMGET(1, 28))
		{
			Custom[lpObj->m_Index].Count[4]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(1, 31) || Left->m_Type == ITEMGET(1, 31))
		{
			Custom[lpObj->m_Index].Count[5]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(2, 14) || Left->m_Type == ITEMGET(2, 14))
		{
			Custom[lpObj->m_Index].Count[6]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(2, 16) || Left->m_Type == ITEMGET(2, 16))
		{
			Custom[lpObj->m_Index].Count[7]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(2, 17) || Left->m_Type == ITEMGET(2, 17))
		{
			Custom[lpObj->m_Index].Count[8]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(2, 24) || Left->m_Type == ITEMGET(2, 24))
		{
			Custom[lpObj->m_Index].Count[9]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(2, 25) || Left->m_Type == ITEMGET(2, 25))
		{
			Custom[lpObj->m_Index].Count[10]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Right->m_Type == ITEMGET(2, 28) || Left->m_Type == ITEMGET(2, 28))
		{
			Custom[lpObj->m_Index].Count[11]++;

			Func.SendMain(lpObj->m_Index);
		}

		if (Attack.PlayerStruct[lpTargetObj->m_Index]._Attack == true && lpTargetObj->MapNumber != 6)
		{
			Attack.PlayerStruct[lpTargetObj->m_Index]._Attack = false;

			Attack.PlayerStruct[lpTargetObj->m_Index]._Skill = -1;

			Attack.PlayerStruct[lpTargetObj->m_Index]._Time[0] = 0;
		}
		else if (Attack.PlayerStruct[lpTargetObj->m_Index]._OffAttack == true && lpTargetObj->MapNumber != 6)
		{
			Attack.PlayerStruct[lpTargetObj->m_Index]._OffAttack = false;

			Attack.PlayerStruct[lpTargetObj->m_Index]._Skill = -1;

			Attack.PlayerStruct[lpTargetObj->m_Index]._Time[1] = 0;

			GJPUserClose(lpTargetObj->AccountID);

			gObjCloseSet(lpTargetObj->m_Index, 0);

			gObjDel(lpTargetObj->m_Index);
		}
	}

	return gObjPlayerKiller(lpObj, lpTargetObj);
}

void Functions::gObjInterfaceTimeCheckEx(LPOBJ lpObj)
{
	Func.PlayerOut(lpObj);
	CoinEvent.Run(lpObj);
	//Dupe.Run(lpObj);
	Speed.Run(lpObj);
	Attack.Run(lpObj);
	// AutoReset.Run(lpObj); // fix erro: alto uso de CPU por spam de query (movido para gObjSecondProcEx)
	Reward.Run(lpObj);

	Duel.InvitationCheck(lpObj);

	FlagEvent.FlagPoint(lpObj);
	FlagEvent.Die(lpObj);

	if (lpObj->Money > 2000000000 || lpObj->Money < 0)
	{
		lpObj->Money = 2000000000;

		GCMoneySend(lpObj->m_Index, lpObj->Money);
	}

	if (lpObj->Type == PLAYER && lpObj->MapNumber == 0)
	{
		if (lpObj->X >= 139 && lpObj->X <= 148 && lpObj->Y >= 123 && lpObj->Y <= 132)
		{
			if (lpObj->Level >= 1 && lpObj->Level < 6)
			{
				gObjTeleport(lpObj->m_Index, 0, 125, 125);

				Func.MsgOutput(lpObj->m_Index, 1, "Necessário nível 6 para participar do ring!");
				Func.MsgOutput(lpObj->m_Index, 1, "Você foi teleportado.");
			}
		}
	}

	return gObjInterfaceTimeCheck(lpObj);
}

void Functions::gObjSecondProcEx()
{
	DuelEvent.Run();
	PegaEvent.Run();
	SobreEvent.Run();
	QuizEvent.Run();
	PairEvent.Run();
	PairEvent.Move();
	RoletaEvent.Run();
	UfcEvent.Run();
	BattleEvent.Run();
	KingEvent.Run();

	Treasure.Check();

	// fix erro: rodar o auto reset apenas uma vez por segundo para economizar CPU
	for (int n = OBJECT_MIN; n < OBJECT_MAX; n++)
	{
		if (gObj[n].Connected == 3)
		{
			AutoReset.Run(&gObj[n]);
		}
	}

	return gObjSecondProc();
}

void Functions::gObjCloseSetEx(int aIndex, int flag)
{
	DuelEvent.Quit(&gObj[aIndex]);
	PegaEvent.Quit(&gObj[aIndex]);
	SobreEvent.Quit(&gObj[aIndex]);
	DeathEvent.Quit(&gObj[aIndex]);
	CoinEvent.Quit(&gObj[aIndex]);
	TheftEvent.Quit(&gObj[aIndex]);
	Duel.Quit(&gObj[aIndex]);
	Quest.Quit(&gObj[aIndex]);
	FlagEvent.Quit(&gObj[aIndex]);
	Ring.Quit(&gObj[aIndex]);
	PairEvent.Quit(&gObj[aIndex]);
	RoletaEvent.Quit(&gObj[aIndex]);
	Potion.Quit(&gObj[aIndex]);
	AutoReset.Quit(&gObj[aIndex]);
	UfcEvent.Quit(&gObj[aIndex]);
	BattleEvent.Quit(&gObj[aIndex]);
	Pet.Quit(&gObj[aIndex]);
	KingEvent.Quit(&gObj[aIndex]);

	if (Custom[aIndex].Hero > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character Set Hero = Hero + %d Where Name = '%s'", Custom[aIndex].Hero, gObj[aIndex].Name);

		Custom[aIndex].Hero = 0;
	}

	if (Custom[aIndex].Killer > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character Set Killer = Killer + %d Where Name = '%s'", Custom[aIndex].Killer, gObj[aIndex].Name);

		Custom[aIndex].Killer = 0;
	}

	if (Custom[aIndex].Count[0] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword01 = %d WHERE Name = '%s'", Custom[aIndex].Count[0], gObj[aIndex].Name);

		Custom[aIndex].Count[0] = 0;
	}

	if (Custom[aIndex].Count[1] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword02 = %d WHERE Name = '%s'", Custom[aIndex].Count[1], gObj[aIndex].Name);

		Custom[aIndex].Count[1] = 0;
	}

	if (Custom[aIndex].Count[2] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword03 = %d WHERE Name = '%s'", Custom[aIndex].Count[2], gObj[aIndex].Name);

		Custom[aIndex].Count[2] = 0;
	}

	if (Custom[aIndex].Count[3] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword04 = %d WHERE Name = '%s'", Custom[aIndex].Count[3], gObj[aIndex].Name);

		Custom[aIndex].Count[3] = 0;
	}

	if (Custom[aIndex].Count[4] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword05 = %d WHERE Name = '%s'", Custom[aIndex].Count[4], gObj[aIndex].Name);

		Custom[aIndex].Count[4] = 0;
	}

	if (Custom[aIndex].Count[5] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword06 = %d WHERE Name = '%s'", Custom[aIndex].Count[5], gObj[aIndex].Name);

		Custom[aIndex].Count[5] = 0;
	}

	if (Custom[aIndex].Count[6] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword07 = %d WHERE Name = '%s'", Custom[aIndex].Count[6], gObj[aIndex].Name);

		Custom[aIndex].Count[6] = 0;
	}

	if (Custom[aIndex].Count[7] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword08 = %d WHERE Name = '%s'", Custom[aIndex].Count[7], gObj[aIndex].Name);

		Custom[aIndex].Count[7] = 0;
	}

	if (Custom[aIndex].Count[8] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword09 = %d WHERE Name = '%s'", Custom[aIndex].Count[8], gObj[aIndex].Name);

		Custom[aIndex].Count[8] = 0;
	}

	if (Custom[aIndex].Count[9] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword10 = %d WHERE Name = '%s'", Custom[aIndex].Count[9], gObj[aIndex].Name);

		Custom[aIndex].Count[9] = 0;
	}

	if (Custom[aIndex].Count[10] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword11 = %d WHERE Name = '%s'", Custom[aIndex].Count[10], gObj[aIndex].Name);

		Custom[aIndex].Count[10] = 0;
	}

	if (Custom[aIndex].Count[11] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword12 = %d WHERE Name = '%s'", Custom[aIndex].Count[11], gObj[aIndex].Name);

		Custom[aIndex].Count[11] = 0;
	}

	if (Custom[aIndex].Helper == true && gObj[aIndex].Type == PLAYER)
	{
		Custom[aIndex].Helper = false;
	}

	return gObjCloseSet(aIndex, flag);
}

short Functions::gObjDelEx(int aIndex)
{
	DuelEvent.Quit(&gObj[aIndex]);
	PegaEvent.Quit(&gObj[aIndex]);
	SobreEvent.Quit(&gObj[aIndex]);
	DeathEvent.Quit(&gObj[aIndex]);
	CoinEvent.Quit(&gObj[aIndex]);
	TheftEvent.Quit(&gObj[aIndex]);
	Duel.Quit(&gObj[aIndex]);
	Quest.Quit(&gObj[aIndex]);
	FlagEvent.Quit(&gObj[aIndex]);
	Ring.Quit(&gObj[aIndex]);
	PairEvent.Quit(&gObj[aIndex]);
	RoletaEvent.Quit(&gObj[aIndex]);
	Potion.Quit(&gObj[aIndex]);
	AutoReset.Quit(&gObj[aIndex]);
	UfcEvent.Quit(&gObj[aIndex]);
	BattleEvent.Quit(&gObj[aIndex]);
	Pet.Quit(&gObj[aIndex]);
	KingEvent.Quit(&gObj[aIndex]);

	if (Custom[aIndex].Hero > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character Set Hero = Hero + %d Where Name = '%s'", Custom[aIndex].Hero, gObj[aIndex].Name);

		Custom[aIndex].Hero = 0;
	}

	if (Custom[aIndex].Killer > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character Set Killer = Killer + %d Where Name = '%s'", Custom[aIndex].Killer, gObj[aIndex].Name);

		Custom[aIndex].Killer = 0;
	}

	if (Custom[aIndex].Count[0] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword01 = %d WHERE Name = '%s'", Custom[aIndex].Count[0], gObj[aIndex].Name);

		Custom[aIndex].Count[0] = 0;
	}

	if (Custom[aIndex].Count[1] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword02 = %d WHERE Name = '%s'", Custom[aIndex].Count[1], gObj[aIndex].Name);

		Custom[aIndex].Count[1] = 0;
	}

	if (Custom[aIndex].Count[2] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword03 = %d WHERE Name = '%s'", Custom[aIndex].Count[2], gObj[aIndex].Name);

		Custom[aIndex].Count[2] = 0;
	}

	if (Custom[aIndex].Count[3] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword04 = %d WHERE Name = '%s'", Custom[aIndex].Count[3], gObj[aIndex].Name);

		Custom[aIndex].Count[3] = 0;
	}

	if (Custom[aIndex].Count[4] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword05 = %d WHERE Name = '%s'", Custom[aIndex].Count[4], gObj[aIndex].Name);

		Custom[aIndex].Count[4] = 0;
	}

	if (Custom[aIndex].Count[5] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword06 = %d WHERE Name = '%s'", Custom[aIndex].Count[5], gObj[aIndex].Name);

		Custom[aIndex].Count[5] = 0;
	}

	if (Custom[aIndex].Count[6] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword07 = %d WHERE Name = '%s'", Custom[aIndex].Count[6], gObj[aIndex].Name);

		Custom[aIndex].Count[6] = 0;
	}

	if (Custom[aIndex].Count[7] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword08 = %d WHERE Name = '%s'", Custom[aIndex].Count[7], gObj[aIndex].Name);

		Custom[aIndex].Count[7] = 0;
	}

	if (Custom[aIndex].Count[8] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword09 = %d WHERE Name = '%s'", Custom[aIndex].Count[8], gObj[aIndex].Name);

		Custom[aIndex].Count[8] = 0;
	}

	if (Custom[aIndex].Count[9] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword10 = %d WHERE Name = '%s'", Custom[aIndex].Count[9], gObj[aIndex].Name);

		Custom[aIndex].Count[9] = 0;
	}

	if (Custom[aIndex].Count[10] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword11 = %d WHERE Name = '%s'", Custom[aIndex].Count[10], gObj[aIndex].Name);

		Custom[aIndex].Count[10] = 0;
	}

	if (Custom[aIndex].Count[11] > 0 && gObj[aIndex].Type == PLAYER)
	{
		Manager.ExecFormat("UPDATE Character SET Sword12 = %d WHERE Name = '%s'", Custom[aIndex].Count[11], gObj[aIndex].Name);

		Custom[aIndex].Count[11] = 0;
	}

	if (Attack.PlayerStruct[aIndex]._OffAttack == true)
	{
		return TRUE;
	}

	if (Offline.PlayerStruct[aIndex]._Offline == true)
	{
		return TRUE;
	}

	if (Custom[aIndex].Helper == true && gObj[aIndex].Type == PLAYER)
	{
		Custom[aIndex].Helper = false;
	}

	return gObjDel(aIndex);
}

void Functions::gObjUserDieEx(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	DuelEvent.Die(lpObj);
	PairEvent.Die(lpObj);
	UfcEvent.Die(lpObj);
	KingEvent.Die(lpObj);

	SobreEvent.Die(lpObj, lpTargetObj);
	BattleEvent.Die(lpObj, lpTargetObj);

	gObjUserDie(lpObj, lpTargetObj);
}

BYTE Functions::gObjInventoryMoveItemEx(int aIndex, unsigned char source, unsigned char target, int& durSsend, int& durTsend, unsigned char sFlag, unsigned char tFlag, unsigned char* siteminfo)
{
	if (!PegaEvent.Equip(&gObj[aIndex], source, target))
	{
		return (BYTE)(-1);
	}

	if (!FlagEvent.Equip(&gObj[aIndex], source, target))
	{
		return (BYTE)(-1);
	}

	return gObjInventoryMoveItem(aIndex, source, target, durSsend, durTsend, sFlag, tFlag, siteminfo);
}

bool Functions::gObjLevelUpEx(LPOBJ lpObj, int addexp, int iMonsterType, int iEventType)
{
	bool Result = gObjLevelUp(lpObj, addexp, iMonsterType, iEventType);

	PMSG_UPDATEPOINTS pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.size = sizeof(pMsg);
	pMsg.h.head = 0xFE;
	pMsg.subcode = 0x08;
	pMsg.LevelUpPoint = lpObj->LevelUpPoint;

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	Functions::gObjCalCharacterEx(lpObj->m_Index);

	return Result;
}

BOOL Functions::GetBoxPosition(int MapNumber, int X, int Y, int W, int H, short& rX, short& rY)
{
	BOOL Result = FALSE;

	__asm
	{
		PUSH rY;
		PUSH rX;
		PUSH H;
		PUSH W;
		PUSH Y;
		PUSH X;
		PUSH MapNumber;
		MOV ECX, 0x6344538;
		MOV EDI, 0x40277F;
		CALL EDI;
		MOV Result, EAX;
	}

	return Result;
}

char* Functions::lMsgGet(int Number)
{
	char* Result;

	__asm
	{
		PUSH Number;

		MOV ECX, 0x62DE5F0;
		CALL DWORD PTR DS : [0x731188C] ;

		MOV Result, EAX;
	}

	return Result;
}

BOOL Functions::gObjIsConnectedGP(int aIndex)
{
	if (aIndex < 0 || aIndex > 5599)
	{
	}
	else if (gObj[aIndex].Type != 1)
	{
	}
	else if (gObj[aIndex].Connected < 3)
	{
	}
	else if (gObj[aIndex].CloseCount > 0)
	{
	}
	else
	{
		return TRUE;
	}

	return FALSE;
}

void Functions::gObjFixInventoryPointer(OBJECTSTRUCT* lpObj)
{
	if (lpObj->Connected < 2)
	{
	}
	else if (lpObj->pInventory == lpObj->Inventory1)
	{
	}
	else if (lpObj->pInventory == lpObj->Inventory2)
	{
		if (lpObj->pTransaction == TRUE)
		{
		}
		else
		{
			for (BYTE i = 0; i < 108; i++)
			{
				lpObj->Inventory2[i].Clear();
			}

			gObjSetInventory1Pointer(lpObj);
		}
	}
	else
	{
		gObjSetInventory1Pointer(lpObj);
	}
}

void Functions::CGTalkRequestRecv(PMSG_TALKREQUEST* lpMsg, int aIndex)
{
	if (PacketCheckTime(&gObj[aIndex]) == FALSE)
	{
		return;
	}
	if (gObj[aIndex].CloseType != -1)
	{
		return;
	}

	if (!Func.gObjIsConnectedGP(aIndex))
	{
		return;
	}

	if (gObj[aIndex].m_IfState.use > 0)
	{
		return;
	}

	int DealerNumber = MAKE_NUMBER(lpMsg->NumberH, lpMsg->NumberL);

	if (DealerNumber < 0 || DealerNumber > OBJECT_MAX - 1)
	{
		return;
	}

	if (gObj[aIndex].MapNumber != gObj[DealerNumber].MapNumber ||
		(gObj[aIndex].X < (gObj[DealerNumber].X - 5) || gObj[aIndex].X >(gObj[DealerNumber].X + 5)) ||
		(gObj[aIndex].Y < (gObj[DealerNumber].Y - 5) || gObj[aIndex].Y >(gObj[DealerNumber].Y + 5)))
	{
		return;
	}

	int ShopNum = gObj[DealerNumber].ShopNumber;

	if (gObj[DealerNumber].Type == 3)
	{
		if (Functions::NpcTalkEx(&gObj[DealerNumber], &gObj[aIndex]) == TRUE)
		{
			return;
		}
	}

	Func.gObjFixInventoryPointer(&gObj[aIndex]);

	PMSG_TALKRESULT pMsg;
	BYTE bRand;

	pMsg.h.c = 0xC3;
	pMsg.h.head = 0x30;
	pMsg.h.size = sizeof(PMSG_TALKRESULT);
	pMsg.Treasure = 0;

	if (gObj[DealerNumber].Class == 234)    // Npc Server Division
	{
		pMsg.result = 5;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if (gObj[DealerNumber].Type == 3 && ShopNum < 0)
	{
		return;
	}

	if (ShopNum >= 0 && ShopNum < MAX_SHOP)
	{
		if (ShopNum == Treasure.ShopNumber())  // Treasure
		{
			if (!_stricmp(Treasure.Winner(), gObj[aIndex].Name))
			{
				CShop* Shop = &ShopC[ShopNum];

				gObj[aIndex].TargetShopNumber = ShopNum;
				gObj[aIndex].m_IfState.use = 1;
				gObj[aIndex].m_IfState.type = 3;
				gObj[aIndex].m_ShopTime = 0;

				pMsg.result = 0;
				pMsg.Treasure = 1;

				DataSend(aIndex, (LPBYTE)(&pMsg), pMsg.h.size);

				BYTE SendByte[1024];
				PMSG_SHOPITEMCOUNT pShopItemCount;
				int lOfs = sizeof(pShopItemCount);
				int Size = lOfs + Shop->SendItemDataLen;

				pShopItemCount.h.c = 0xC2;
				pShopItemCount.h.sizeH = HIBYTE(Size);
				pShopItemCount.h.sizeL = LOBYTE(Size);
				pShopItemCount.h.head = 0x31;
				pShopItemCount.Type = 0;
				pShopItemCount.count = Shop->ItemCount;

				memcpy_s(SendByte, 1024, &pShopItemCount, sizeof(pShopItemCount));
				memcpy_s(&SendByte[lOfs], (1024 - lOfs), Shop->SendItemData, Shop->SendItemDataLen);

				DataSend(aIndex, SendByte, Size);
			}
		}
		else
		{
			CShop* Shop = &ShopC[ShopNum];
			bRand = (BYTE)(rand() % 2);

			if (Shop->ItemCount < 1)
			{
				if (bRand != 0)
				{
					ChatTargetSend(&gObj[DealerNumber], Func.lMsgGet(MSGGET(4, 119)), aIndex);
				}
				else
				{
					ChatTargetSend(&gObj[DealerNumber], Func.lMsgGet(MSGGET(4, 120)), aIndex);
				}

				return;
			}

			if (gObj[aIndex].m_PK_Level > 4)
			{
				if (bRand != 0)
				{
					ChatTargetSend(&gObj[DealerNumber], Func.lMsgGet(MSGGET(4, 121)), aIndex);
				}
				else
				{
					ChatTargetSend(&gObj[DealerNumber], Func.lMsgGet(MSGGET(4, 122)), aIndex);
				}

				return;
			}

			bRand = (BYTE)(rand() % 6);

			switch (bRand)
			{
			case 0:
			{
				if (*(gMerryXMasNpcEvent) == 1)
				{
					ChatTargetSend(&gObj[DealerNumber], Func.lMsgGet(MSGGET(4, 123)), aIndex);
				}
			} break;
			case 1:
			{
				if (*(gHappyNewYearNpcEvent) == 1)
				{
					ChatTargetSend(&gObj[DealerNumber], Func.lMsgGet(MSGGET(4, 124)), aIndex);
				}
			} break;
			}

			gObj[aIndex].TargetShopNumber = ShopNum;
			gObj[aIndex].m_IfState.use = 1;
			gObj[aIndex].m_IfState.type = 3;
			gObj[aIndex].m_ShopTime = 0;

			pMsg.result = 0;
			pMsg.Treasure = 0;

			DataSend(aIndex, (LPBYTE)(&pMsg), pMsg.h.size);

			BYTE SendByte[1024];
			PMSG_SHOPITEMCOUNT pShopItemCount;
			int lOfs = sizeof(pShopItemCount);
			int Size = lOfs + Shop->SendItemDataLen;

			pShopItemCount.h.c = 0xC2;
			pShopItemCount.h.sizeH = HIBYTE(Size);
			pShopItemCount.h.sizeL = LOBYTE(Size);
			pShopItemCount.h.head = 0x31;
			pShopItemCount.Type = 0;
			pShopItemCount.count = Shop->ItemCount;

			memcpy_s(SendByte, 1024, &pShopItemCount, sizeof(pShopItemCount));
			memcpy_s(&SendByte[lOfs], (1024 - lOfs), Shop->SendItemData, Shop->SendItemDataLen);

			DataSend(aIndex, SendByte, Size);
		}
	}
	else
	{
		bRand = (BYTE)(rand() % 6);

		switch (bRand)
		{
		case 0:
		{
			if (*(gMerryXMasNpcEvent) == 1)
			{
				ChatTargetSend(&gObj[DealerNumber], Func.lMsgGet(MSGGET(4, 123)), aIndex);
			}
		} break;
		case 1:
		{
			if (*(gHappyNewYearNpcEvent) == 1)
			{
				ChatTargetSend(&gObj[DealerNumber], Func.lMsgGet(MSGGET(4, 124)), aIndex);
			}
		} break;
		}

		gObj[aIndex].TargetShopNumber = ShopNum;
		gObj[aIndex].m_IfState.use = 1;
		gObj[aIndex].m_IfState.type = 3;
		gObj[aIndex].m_ShopTime = 0;

		pMsg.result = 0;

		switch (ShopNum)
		{
		case 100:
		{
			if (gObj[aIndex].m_ReqWarehouseOpen != 0)
			{
			}
			else
			{
				gObj[aIndex].m_ReqWarehouseOpen = 1;
				gObj[aIndex].m_IfState.type = 6;
				gObj[aIndex].m_IfState.state = 0;
				gObj[aIndex].WarehouseCount = 0;

				GDGetWarehouseList(aIndex, gObj[aIndex].AccountID);
			}
		} break;
		case 101:
		{
			if (*(bCanChaosBox) == TRUE)
			{
				if (Block.BlockStruct[aIndex]._Active == 1)
				{
					Func.Golden(aIndex, "Conta protegida!");
					Func.Golden(aIndex, "Utilize a senha para desbloquear.");
					return;
				}

				gObj[aIndex].m_IfState.type = 7;
				gObj[aIndex].m_IfState.state = 0;

				pMsg.result = 3;
				pMsg.level1 = (BYTE)(*(gDQChaosSuccessRateLevel1));
				pMsg.level2 = (BYTE)(*(gDQChaosSuccessRateLevel2));
				pMsg.level3 = (BYTE)(*(gDQChaosSuccessRateLevel3));
				pMsg.level4 = (BYTE)(*(gDQChaosSuccessRateLevel4));

				DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
				gObjInventoryTrans(aIndex);

				LogAddTD("[%s][%s] Open Chaos Box", gObj[aIndex].AccountID, gObj[aIndex].Name);

				gObjItemTextSave(&gObj[aIndex]);
				gObjWarehouseTextSave(&gObj[aIndex]);
			}
		} break;
		}
	}
}

void Functions::CGBuyRequestRecv(PMSG_BUYREQUEST* lpMsg, int aIndex)
{
	PMSG_BUYRESULT pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.size = sizeof(PMSG_BUYRESULT);
	pMsg.h.head = 0x32;
	pMsg.Result = -1;

	if (PacketCheckTime(&gObj[aIndex]) == FALSE)
	{
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if (gObj[aIndex].CloseType != -1)
	{
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	Func.gObjFixInventoryPointer(&gObj[aIndex]);

	if (gObj[aIndex].m_ShopTime == 0)
	{
		gObj[aIndex].m_ShopTime = 1;
	}

	if (gObj[aIndex].m_ShopTime > 60)
	{
		if (gObj[aIndex].m_IfState.use != 0 && gObj[aIndex].m_IfState.type == 3)
		{
			gObj[aIndex].TargetShopNumber = -1;
			gObj[aIndex].m_IfState.use = 0;
			gObj[aIndex].m_IfState.type = 0;
		}

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}
	else if (gObj[aIndex].m_IfState.use > 0 && gObj[aIndex].m_IfState.type != 3)
	{
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}
	else
	{
		int ShopNum = gObj[aIndex].TargetShopNumber;

		if (ShopNum < 0 || ShopNum > MAX_SHOP - 1)
		{
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			return;
		}
		else if (lpMsg->Pos > 120 - 1)
		{
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			return;
		}
		else
		{
			if (ShopNum == Treasure.ShopNumber()) // Treasure
			{
				if (!_stricmp(gObj[aIndex].Name, Treasure.Winner()))
				{
					CShop* Shop = &ShopC[ShopNum];

					if (Shop->Item[lpMsg->Pos].IsItem())
					{
						BOOL NoItem = TRUE;

						if (Shop->Item[lpMsg->Pos].m_Type >= ITEMGET(14, 0) && Shop->Item[lpMsg->Pos].m_Type <= ITEMGET(14, 8))
						{
							int Durability = (int)(Shop->Item[lpMsg->Pos].m_Durability);

							if (Durability == 0)
							{
								Durability = 1;
							}

							if (gObjSearchItem(&gObj[aIndex], Shop->Item[lpMsg->Pos].m_Type, Durability) == TRUE)
							{
								NoItem = FALSE;
							}
						}

						if (NoItem != FALSE)
						{
							pMsg.Result = gObjShopBuyInventoryInsertItem(aIndex, Shop->Item[lpMsg->Pos]);

							if (pMsg.Result != 0xFF)
							{
								ItemByteConvert((LPBYTE)(&pMsg.ItemInfo), Shop->Item[lpMsg->Pos]);
							}
						}
					}
				}
			}
			else
			{
				CShop* Shop = &ShopC[ShopNum];

				if (Shop->Item[lpMsg->Pos].IsItem() == TRUE)
				{
					if ((UINT)(gObj[aIndex].Money) < Shop->Item[lpMsg->Pos].m_BuyMoney)
					{
						pMsg.Result = -1;
					}
					else
					{
						BOOL NoItem = TRUE;

						if (Shop->Item[lpMsg->Pos].m_Type >= ITEMGET(14, 0) && Shop->Item[lpMsg->Pos].m_Type <= ITEMGET(14, 8))
						{
							int Durability = (int)(Shop->Item[lpMsg->Pos].m_Durability);

							if (Durability == 0)
							{
								Durability = 1;
							}

							if (gObjSearchItem(&gObj[aIndex], Shop->Item[lpMsg->Pos].m_Type, Durability) == TRUE)
							{
								NoItem = FALSE;

								gObj[aIndex].Money -= (int)Shop->Item[lpMsg->Pos].m_BuyMoney;

								if (gObj[aIndex].Money < 0)
								{
									gObj[aIndex].Money = 0;
								}

								GCMoneySend(aIndex, gObj[aIndex].Money);
							}
						}

						if (NoItem != FALSE)
						{
							pMsg.Result = gObjShopBuyInventoryInsertItem(aIndex, Shop->Item[lpMsg->Pos]);

							if (pMsg.Result != 0xFF)
							{
								ItemByteConvert((LPBYTE)(&pMsg.ItemInfo), Shop->Item[lpMsg->Pos]);

								gObj[aIndex].Money -= (int)Shop->Item[lpMsg->Pos].m_BuyMoney;

								if (gObj[aIndex].Money < 0)
								{
									gObj[aIndex].Money = 0;
								}

								GCMoneySend(aIndex, gObj[aIndex].Money);
							}
						}
					}
				}
			}
		}
	}

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

BOOL Functions::ShopDataLoad()
{
	char Buffer[50];

	for (BYTE i = 0; i != MAX_SHOP; i++)
	{
		sprintf_s(Buffer, "..\\Data\\Shop%d.txt", i);
		ShopC[i].LoadShopItem(Buffer);
	}

	LogAdd("Dados dos NPC's carregado com sucesso!");

	return TRUE;
}

BOOL Functions::gObjSetMonsterEx(int aIndex, int Class)
{
	BOOL Result = gObjSetMonster(aIndex, Class);

	switch (Class)
	{
	case 168:
		gObj[aIndex].Type = 2;
		break;
	case 169:
		gObj[aIndex].Type = 2;
		break;
	case 170:
		gObj[aIndex].Type = 2;
		break;
	case 171:
		gObj[aIndex].Type = 2;
		break;
	case 172:
		gObj[aIndex].Type = 2;
		break;
	case 173:
		gObj[aIndex].Type = 2;
		break;
	case 174:
		gObj[aIndex].Type = 2;
		break;
	case 175:
		gObj[aIndex].Type = 2;
		break;
	case 176:
		gObj[aIndex].Type = 2;
		break;
	case 177:
		gObj[aIndex].Type = 2;
		break;
	case 201:
		gObj[aIndex].Type = 3;
		break;
	case 202:
		gObj[aIndex].Type = 3;
		break;
	case 203:
		gObj[aIndex].Type = 3;
		break;
	case 204:
		gObj[aIndex].Type = 3;
		break;
	case 205:
		gObj[aIndex].Type = 3;
		break;
	case 206:
		gObj[aIndex].Type = 3;
		break;
	case 208:
		gObj[aIndex].Type = 3;
		break;
	case 236:
		gObj[aIndex].Type = 3;
		gObj[aIndex].ShopNumber = -1;
		break;
	case 238:
		gObj[aIndex].Type = 3;
		gObj[aIndex].ShopNumber = 101;
		break;
	case 240:
		gObj[aIndex].Type = 3;
		gObj[aIndex].ShopNumber = 100;
		break;
	}

	return Result;
}

void Functions::GCWarePassSend(int aIndex, PMSG_WAREHOUSEPASSSEND* lpMsg)
{
	switch (lpMsg->Type)
	{
	case 0:
	{
		if (lpMsg->Pass != gObj[aIndex].WarehousePW)
		{
			GCWarehouseStateSend(aIndex, 10);
			return;
		}
		else
		{
			gObj[aIndex].WarehouseLock = 0;
			gObj[aIndex].WarehousePW = 0;
			GCWarehouseStateSend(aIndex, gObj[aIndex].WarehouseLock);
			GCWarehouseRecivePassword(aIndex, lpMsg);
		}
	}
	break;
	case 1:
	{
		gObj[aIndex].WarehouseLock = 1;
		gObj[aIndex].WarehousePW = lpMsg->Pass;
		GCWarehouseStateSend(aIndex, gObj[aIndex].WarehouseLock);
	}
	break;
	case 2:
	{
		if (lpMsg->Pass != gObj[aIndex].WarehousePW)
		{
			GCWarehouseStateSend(aIndex, 10);
			return;
		}
		else
		{
			GCWarehouseStateSend(aIndex, 0);
			GCWarehouseRecivePassword(aIndex, lpMsg);
		}
	}
	break;
	}

	GCWarehouseRecivePassword(aIndex, lpMsg);
}

BOOL Functions::gObjSetCharacterEx(LPBYTE lpdata, int aIndex)
{
	BOOL Return = gObjSetCharacter(lpdata, aIndex);

	if (Return == TRUE)
	{
		if (gObj[aIndex].m_Index != aIndex)
		{
			return Return;
		}

		Speed.Connect(aIndex);
		Attack.Connect(aIndex);

		Manager.Contador(aIndex, gObj[aIndex].Name);

		Manager.Patent(aIndex, gObj[aIndex].Name);

		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Type == PLAYER)
			{
				if (gObj[Index].Connected == 3 && Custom[Index].Patent >= 0)
				{
					Patent.GCReqRankLevelUser(aIndex, Index);
				}
			}
		}

		if (Block.BlockStruct[aIndex]._Active == 1)
		{
			Func.Golden(aIndex, "Conta protegida por senha!");
		}

		Func.SendMain(aIndex);
	}

	return Return;
}

bool Functions::CheckItem(LPOBJ lpObj)
{
	for (int i = 0; i < 11; i++)
	{
		if (lpObj->pInventory[i].IsItem())
		{
			return false;
		}
	}

	return true;
}

void Functions::PlayerOut(LPOBJ lpObj)
{
	if (Custom[lpObj->m_Index].Move == true)
	{
		if (lpObj->Live == TRUE)
		{
			if (lpObj->Class == ELF)
			{
				int X = 171 + rand() % 6;
				int Y = 108 + rand() % 8;

				gObjTeleport(lpObj->m_Index, 3, X, Y);

				Custom[lpObj->m_Index].Move = false;

				if (BattleEvent.PlayerStruct[lpObj->m_Index]._InEvent == true)
				{
					BattleEvent.RollBack(lpObj, 1);

					BattleEvent.PlayerStruct[lpObj->m_Index]._InEvent = false;
				}
			}
			else
			{
				int X = 133 + rand() % 15;
				int Y = 118 + rand() % 15;

				gObjTeleport(lpObj->m_Index, 0, X, Y);

				Custom[lpObj->m_Index].Move = false;

				if (BattleEvent.PlayerStruct[lpObj->m_Index]._InEvent == true)
				{
					BattleEvent.RollBack(lpObj, 1);

					BattleEvent.PlayerStruct[lpObj->m_Index]._InEvent = false;
				}
			}
		}
	}

	if (Duel.DuelStruct[lpObj->m_Index]._Move == true)
	{
		if (lpObj->Live == TRUE)
		{
			if (lpObj->Class == ELF)
			{
				int X = 171 + rand() % 6;
				int Y = 108 + rand() % 8;

				gObjTeleport(lpObj->m_Index, 3, X, Y);

				lpObj->m_PK_Level = 3;
				GCPkLevelSend(lpObj->m_Index, 3);

				Duel.DuelStruct[lpObj->m_Index]._Move = false;
			}
			else
			{
				int X = 133 + rand() % 15;
				int Y = 118 + rand() % 15;

				gObjTeleport(lpObj->m_Index, 0, X, Y);

				lpObj->m_PK_Level = 3;
				GCPkLevelSend(lpObj->m_Index, 3);

				Duel.DuelStruct[lpObj->m_Index]._Move = false;
			}
		}
	}

	if (Custom[lpObj->m_Index].Dead == true)
	{
		if (lpObj->Live == TRUE)
		{
			lpObj->m_PK_Level = 3;
			GCPkLevelSend(lpObj->m_Index, 3);

			Custom[lpObj->m_Index].Dead = false;
		}
	}
}

BOOL Functions::gObjMoveGateEx(int aIndex, int Gate)
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

	if (Custom[aIndex].Helper == true)
	{
		gObj[aIndex].m_SkillAttack = gObj[aIndex].Level / 3 + 45;

		gObj[aIndex].m_ViewSkillState |= 4;

		GCMagicAttackNumberSend(&gObj[aIndex], 28, aIndex, true);
	}

	if (Custom[aIndex].Helper == true)
	{
		gObj[aIndex].m_SkillDefense = gObj[aIndex].Level / 5 + 50;

		gObj[aIndex].m_ViewSkillState |= 8;

		GCMagicAttackNumberSend(&gObj[aIndex], 27, aIndex, true);
	}

	return gObjMoveGate(aIndex, Gate);
}

float Functions::GetStatus(LPOBJ lpObj, BYTE Class, BYTE Type)
{
	int Vit, Energy;
	float Life, Mana, LevelLife, LevelMana, VitalityToLife, EnergyToMana, Return = 0;

	switch (Class)
	{
	case 0:
		Vit = 15;
		Energy = 30;
		Life = 60; Mana = 60;
		LevelLife = 1; LevelMana = 2;
		VitalityToLife = 1; EnergyToMana = 2;
		break;
	case 1:
		Vit = 25;
		Energy = 10;
		Life = 110; Mana = 20;
		LevelLife = 2; LevelMana = 0.5;
		VitalityToLife = 3; EnergyToMana = 1;
		break;
	case 2:
		Vit = 20;
		Energy = 15;
		Life = 80; Mana = 30;
		LevelLife = 1; LevelMana = 1.5;
		VitalityToLife = 2; EnergyToMana = 1.5;
		break;
	case 3:
		Vit = 26;
		Energy = 26;
		Life = 110; Mana = 60;
		LevelLife = 1; LevelMana = 1;
		VitalityToLife = 2; EnergyToMana = 2;
		break;
	}

	if (Type == 0)
	{
		Return = Life + ((lpObj->Level - 1) * LevelLife) + ((lpObj->Vitality - Vit) * VitalityToLife);
	}

	if (Type == 1)
	{
		Return = Mana + ((lpObj->Level - 1) * LevelMana) + ((lpObj->Vitality - Vit) * EnergyToMana);
	}

	return Return;
}

void Functions::GCDamageSend(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage)
{
	PMSG_ATTACKRESULT Result;

	PHeadSetB((LPBYTE)&Result, 0x15, sizeof(Result));

	Result.NumberH = GET_NUMBERH(TargetIndex);
	Result.NumberL = GET_NUMBERL(TargetIndex);
	Result.DamageH = GET_NUMBERH(AttackDamage);
	Result.DamageL = GET_NUMBERL(AttackDamage);
	Result.AttackDamage = AttackDamage;

	if (MSBFlag != FALSE)
	{
		Result.NumberH &= 0x7F;
		Result.NumberL |= 0x80;
	}

	Result.DamageType = MSBDamage;

	if (gObj[TargetIndex].Type == PLAYER)
	{
		DataSend(TargetIndex, (LPBYTE)(&Result), Result.h.size);
	}

	if (gObj[aIndex].Type == PLAYER)
	{
		DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
	}
}

void Functions::GCRefillSend(int aIndex, int Life, BYTE Ipos, BYTE flag)
{
	PMSG_REFILL Result;

	PHeadSetB((LPBYTE)&Result, 0x26, sizeof(Result));

	Result.IPos = Ipos;
	Result.LifeH = GET_NUMBERH(Life);
	Result.LifeL = GET_NUMBERL(Life);
	Result.Flag = 0;
	Result.Life = Life;

	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
}

void Functions::GCManaSend(int aIndex, int Mana, BYTE Ipos, unsigned char flag, WORD BP)
{
	if (aIndex < 0 || aIndex > OBJECT_MAX - 1)
	{
		return;
	}

	if (gObj[aIndex].Type != PLAYER)
	{
		return;
	}

	PMSG_MANASEND Result;

	PHeadSetB((LPBYTE)&Result, 0x27, sizeof(Result));

	Result.IPos = Ipos;
	Result.ManaH = GET_NUMBERH(Mana);
	Result.ManaL = GET_NUMBERL(Mana);
	Result.BPH = GET_NUMBERH(BP);
	Result.BPL = GET_NUMBERL(BP);
	Result.Mana = Mana;
	Result.BP = BP;

	DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
}

int Functions::ItemGetDurabilityEx(int aIndex, int Level, int Excellent)
{
	int Durability = ItemGetDurability(aIndex, Level, Excellent);

	if (Level > 11)
	{
		BYTE itemAttribute = Durability - (Level * 2 - 4);

		if (Level == 12)
		{
			Durability = itemAttribute + Level * 2 + 2;
		}
		else if (Level == 13)
		{
			Durability = itemAttribute + Level * 2 + 6;
		}
		else if (Level == 14)
		{
			Durability = itemAttribute + Level * 2 + 10;
		}
		else if (Level == 15)
		{
			Durability = itemAttribute + Level * 2 + 14;
		}

		if (Durability > 255)
		{
			Durability = 255;
		}
	}

	return Durability;
}

void Functions::SendMain(int aIndex)
{
	PMSG_CHARINFOMAIN Result;

	Result.h.c = 0xC1;
	Result.h.size = sizeof(Result);
	Result.h.head = 0xFE;
	Result.Code = 0x07;
	Result.Class = gObj[aIndex].Class;
	Result.Dexterity = (WORD)(gObj[aIndex].Dexterity);
	Result.AttackSpeed = (WORD)(gObj[aIndex].m_AttackSpeed);
	Result.MagicSpeed = (WORD)(gObj[aIndex].m_MagicSpeed);
	Result.LevelUpPoint = gObj[aIndex].LevelUpPoint;
	Result.Sword[0] = Custom[aIndex].Count[0];
	Result.Sword[1] = Custom[aIndex].Count[1];
	Result.Sword[2] = Custom[aIndex].Count[2];
	Result.Sword[3] = Custom[aIndex].Count[3];
	Result.Sword[4] = Custom[aIndex].Count[4];
	Result.Sword[5] = Custom[aIndex].Count[5];
	Result.Sword[6] = Custom[aIndex].Count[6];
	Result.Sword[7] = Custom[aIndex].Count[7];
	Result.Sword[8] = Custom[aIndex].Count[8];
	Result.Sword[9] = Custom[aIndex].Count[9];
	Result.Sword[10] = Custom[aIndex].Count[10];
	Result.Sword[11] = Custom[aIndex].Count[11];

	DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
}

BYTE Functions::gObjInventoryInsertItem(int aIndex, CItem Item)
{
	int W, H, Width, Height;

	BYTE Blank = 0;

	ItemGetSize(Item.m_Type, Width, Height);

	if (Width == 0 || Height == 0)
	{
		return FALSE;
	}

	for (H = 0; H < 8; H++)
	{
		for (W = 0; W < 8; W++)
		{
			if (*(BYTE*)(gObj[aIndex].pInventoryMap + H * 8 + W) == 255)
			{
				Blank = gObjOnlyInventoryRectCheck(aIndex, W, H, Width, Height);

				if (Blank == 254)
				{
					return -1;
				}

				if (Blank != 255)
				{
					gObj[aIndex].pInventory[Blank] = Item;

					gObjInventoryItemSet(aIndex, Blank, gObj[aIndex].pInventory[Blank].m_Type);
					return Blank;
				}
			}
		}
	}

	return -1;
}

void Functions::ItemSerialCreateRecvEx(SDHP_ITEMCREATERECV* Result)
{
	LPOBJ lpObj = &gObj[Result->aIndex];

	int Loot = Result->lootindex;

	if (Custom[Loot].Pet == true)
	{
		if (Result->Type == ITEMGET(12, 15))
		{
			if (!Func.InventoryFullCheck(Loot, Result->Type))
			{
				Func.MsgOutput(Loot, 1, "[ Aviso ]:O inventário está cheio!");
			}
			else
			{
				Pet.Item(Loot, Result->Type, 0, 0, 0, 0, 0, 0, Result->m_Number);

				Func.MsgOutput(Loot, 1, "[ Sistema ]:Seu mascote pegou uma Chaos!");
				return;
			}
		}

		if (Result->Type == ITEMGET(14, 16))
		{
			if (!Func.InventoryFullCheck(Loot, Result->Type))
			{
				Func.MsgOutput(Loot, 1, "[ Aviso ]: O inventário está cheio!");
			}
			else
			{
				Pet.Item(Loot, Result->Type, 0, 0, 0, 0, 0, 0, Result->m_Number);

				Func.MsgOutput(Loot, 1, "[ Sistema ]: Seu mascote pegou uma Life!");
				return;
			}
		}

		if (Result->Type == ITEMGET(14, 22))
		{
			if (!Func.InventoryFullCheck(Loot, Result->Type))
			{
				Func.MsgOutput(Loot, 1, "[ Aviso ]: O inventário está cheio!");
			}
			else
			{
				Pet.Item(Loot, Result->Type, 0, 0, 0, 0, 0, 0, Result->m_Number);

				Func.MsgOutput(Loot, 1, "[ Sistema ]: Seu mascote pegou uma Creation!");
				return;
			}
		}

		if (Result->Type == ITEMGET(14, 14))
		{
			if (!Func.InventoryFullCheck(Loot, Result->Type))
			{
				Func.MsgOutput(Loot, 1, "[ Aviso ]: O inventário está cheio!");
			}
			else
			{
				Pet.Item(Loot, Result->Type, 0, 0, 0, 0, 0, 0, Result->m_Number);

				Func.MsgOutput(Loot, 1, "[ Sistema ]: Seu mascote pegou uma Soul!");
				return;
			}
		}

		if (Result->Type == ITEMGET(14, 13))
		{
			if (!Func.InventoryFullCheck(Loot, Result->Type))
			{
				Func.MsgOutput(Loot, 1, "O inventário está cheio!");
			}
			else
			{
				Pet.Item(Loot, Result->Type, 0, 0, 0, 0, 0, 0, Result->m_Number);

				Func.MsgOutput(Loot, 1, "Seu mascote pegou uma Bless!");
				return;
			}
		}

		if (Result->Type == ITEMGET(15, 18))
		{
			if (!Func.InventoryFullCheck(Loot, Result->Type))
			{
				Func.MsgOutput(Loot, 1, "O inventário está cheio!");
			}
			else
			{
				Pet.Item(Loot, Result->Type, 0, 0, 0, 0, 0, 0, Result->m_Number);

				Func.MsgOutput(Loot, 1, "Seu mascote pegou uma Luck!");
				return;
			}
		}

		if (Result->Type == ITEMGET(15, 19))
		{
			if (!Func.InventoryFullCheck(Loot, Result->Type))
			{
				Func.MsgOutput(Loot, 1, "O inventário está cheio!");
			}
			else
			{
				Pet.Item(Loot, Result->Type, 0, 0, 0, 0, 0, 0, Result->m_Number);

				Func.MsgOutput(Loot, 1, "Seu mascote pegou uma Skill!");
				return;
			}
		}

		if (Result->Type == ITEMGET(15, 20))
		{
			if (!Func.InventoryFullCheck(Loot, Result->Type))
			{
				Func.MsgOutput(Loot, 1, "O inventário está cheio!");
			}
			else
			{
				Pet.Item(Loot, Result->Type, 0, 0, 0, 0, 0, 0, Result->m_Number);

				Func.MsgOutput(Loot, 1, "Seu mascote pegou uma Level!");
				return;
			}
		}

		if (Result->Type == ITEMGET(15, 23))
		{
			if (!Func.InventoryFullCheck(Loot, Result->Type))
			{
				Func.MsgOutput(Loot, 1, "O inventário está cheio!");
			}
			else
			{
				Pet.Item(Loot, Result->Type, 0, 0, 0, 0, 0, 0, Result->m_Number);

				Func.MsgOutput(Loot, 1, "Seu mascote pegou uma Option!");
				return;
			}
		}
	}

	if (Result->MapNumber == 236)
	{
		if (lpObj->Connected > 1)
		{
			CItem CreateItem;

			CreateItem.m_Level = Result->Level;
			CreateItem.m_Durability = Result->Dur;

			CreateItem.Convert(Result->Type, Result->Op1, Result->Op2, Result->Op3, Result->NewOption, 1);
			CreateItem.m_Number = Result->m_Number;

			BYTE btItemPos = Func.gObjInventoryInsertItem(Result->aIndex, CreateItem);

			if (btItemPos == (BYTE)-1)
			{
				LogAddTD("Error: Falha ao inserir o item no inventário [%s][%s]", lpObj->AccountID, lpObj->Name);
			}
			else
			{
				GCInventoryItemOneSend(Result->aIndex, btItemPos);
			}
		}
	}
	else
	{
		ItemSerialCreateRecv(Result);
	}
}

int Functions::InventoryFullCheck(int aIndex, short Item)
{
	int W, H, Width, Height, Result = 0;

	BYTE Blank = 0;

	ItemGetSize(Item, Width, Height);

	if (Width == 0 || Height == 0)
	{
		return Result;
	}

	for (H = 0; H < 8; H++)
	{
		for (W = 0; W < 8; W++)
		{
			if (*(BYTE*)(gObj[aIndex].pInventoryMap + (H * 8) + W) == 255)
			{
				Blank = gObjOnlyInventoryRectCheck(aIndex, W, H, Width, Height);

				if (Blank == 254)
				{
					return Result;
				}

				if (Blank != 255)
				{
					Result++;
				}
			}
		}
	}

	return Result;
}

BOOL Functions::CGItemDropRequestEx(PMSG_ITEMTHROW* lpMsg, int aIndex, BOOL Type)
{
	PMSG_ITEMTHROW_RESULT Result;

	PHeadSetB((LPBYTE)&Result, 0x23, sizeof(Result));
	Result.Result = true;
	Result.Ipos = lpMsg->Ipos;

	if (gObj[aIndex].m_IfState.use != 0)
	{
		if (gObj[aIndex].m_IfState.type != 3)
		{
			Result.Result = false;

			DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
			return FALSE;
		}
	}

	if (gObj[aIndex].pTransaction == 1)
	{
		Result.Result = false;

		DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
		return FALSE;
	}

	if (gObj[aIndex].pInventory[lpMsg->Ipos].m_Type >= ITEMGET(15, 16) && gObj[aIndex].pInventory[lpMsg->Ipos].m_Type <= ITEMGET(15, 23))
	{
		Result.Result = false;

		DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
		return FALSE;
	}

	if (gObj[aIndex].pInventory[lpMsg->Ipos].m_Type == ITEMGET(14, 27))
	{
		BoxWings.Item(aIndex); // [ Alteração ] Box de Asas

		BYTE FireWork[] = { 0xC1, 0x07, 0xF3, 0x40, 0x00, 0x00, 0x00 };
		FireWork[5] = (BYTE)gObj[aIndex].X;
		FireWork[6] = (BYTE)gObj[aIndex].Y;

		DataSend(aIndex, (LPBYTE)(&FireWork), FireWork[1]);

		gObjInventoryDeleteItem(aIndex, lpMsg->Ipos);

		DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
	}

	if (gObj[aIndex].pInventory[lpMsg->Ipos].m_Type == ITEMGET(14, 28))
	{
		BoxExclusive.Item(aIndex); // [ Alteração ] Box de Exclusivos

		BYTE FireWork[] = { 0xC1, 0x07, 0xF3, 0x40, 0x00, 0x00, 0x00 };
		FireWork[5] = (BYTE)gObj[aIndex].X;
		FireWork[6] = (BYTE)gObj[aIndex].Y;

		DataSend(aIndex, (LPBYTE)(&FireWork), FireWork[1]);

		gObjInventoryDeleteItem(aIndex, lpMsg->Ipos);

		DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
	}

	if (gObj[aIndex].pInventory[lpMsg->Ipos].m_Type == ITEMGET(14, 29))
	{
		BoxWeapons.Item(aIndex); // [ Alteração ] Box de Armas

		BYTE FireWork[] = { 0xC1, 0x07, 0xF3, 0x40, 0x00, 0x00, 0x00 };
		FireWork[5] = (BYTE)gObj[aIndex].X;
		FireWork[6] = (BYTE)gObj[aIndex].Y;

		DataSend(aIndex, (LPBYTE)(&FireWork), FireWork[1]);

		gObjInventoryDeleteItem(aIndex, lpMsg->Ipos);

		DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
	}

	if (gObj[aIndex].pInventory[lpMsg->Ipos].m_Type == ITEMGET(14, 30))
	{
		BoxLimited.Item(aIndex); // [ Alteração ] Box de Limitados

		BYTE FireWork[] = { 0xC1, 0x07, 0xF3, 0x40, 0x00, 0x00, 0x00 };
		FireWork[5] = (BYTE)gObj[aIndex].X;
		FireWork[6] = (BYTE)gObj[aIndex].Y;

		DataSend(aIndex, (LPBYTE)(&FireWork), FireWork[1]);

		gObjInventoryDeleteItem(aIndex, lpMsg->Ipos);

		DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
	}

	if (gObj[aIndex].pInventory[lpMsg->Ipos].m_Type == ITEMGET(14, 31))
	{
		BoxSets.Item(aIndex); // [ Alteração ] Box de Sets

		BYTE FireWork[] = { 0xC1, 0x07, 0xF3, 0x40, 0x00, 0x00, 0x00 };
		FireWork[5] = (BYTE)gObj[aIndex].X;
		FireWork[6] = (BYTE)gObj[aIndex].Y;

		DataSend(aIndex, (LPBYTE)(&FireWork), FireWork[1]);

		gObjInventoryDeleteItem(aIndex, lpMsg->Ipos);

		DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
	}

	return CGItemDropRequest(lpMsg, aIndex, Type);
}

void Functions::CSPJoinIdPassRequestEx(PMSG_IDPASS* lpMsg, int aIndex)
{
	char Account[11], Serial[17];

	Disconnect.DisconnectStruct[aIndex]._Send = true;
	Disconnect.DisconnectStruct[aIndex]._Timer = 0;
	Disconnect.DisconnectStruct[aIndex]._Count = 0;

	Account[10] = 0, Serial[16] = 0;

	memcpy(Serial, lpMsg->Serial, sizeof(lpMsg->Serial));
	memcpy(Account, lpMsg->Id, 10);
	BuxConvert(Account, 10);

	Manager.CheckBlock(aIndex, Account);

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3 && Attack.PlayerStruct[i]._OffAttack == true)
		{
			if (_tcsstr(gObj[i].AccountID, Account))
			{
				GJPUserClose(Account);

				Attack.PlayerStruct[i]._OffAttack = false;

				Attack.PlayerStruct[i]._Skill = -1;

				Attack.PlayerStruct[i]._Time[1] = 0;

				CloseClient(i);

				gObjDel(i);
			}
		}
		else if (gObj[i].Connected == 3 && Offline.PlayerStruct[i]._Offline == true)
		{
			if (_tcsstr(gObj[i].AccountID, Account))
			{
				GJPUserClose(Account);

				Offline.PlayerStruct[i]._Offline = false;

				CloseClient(i);

				gObjDel(i);
			}
		}
	}

	return CSPJoinIdPassRequest(lpMsg, aIndex);
}

void Functions::GCItemDurSendEx(int aIndex, BYTE pos, BYTE dur, unsigned char flag)
{
	if (gObj[aIndex].pInventory[8].IsItem() == true)
	{
		if (gObj[aIndex].pInventory[8].m_Type >= ITEMGET(13, 0) && gObj[aIndex].pInventory[8].m_Type <= ITEMGET(13, 3))
		{
			if (gObj[aIndex].pInventory[8].m_Level == 15)
			{
				gObj[aIndex].pInventory[8].m_Durability = 255.0f;
			}
		}
	}

	for (int i = 12; i < 76; i++)
	{
		if (gObj[aIndex].pInventory[i].IsItem() == true)
		{
			if (gObj[aIndex].pInventory[i].m_Type >= ITEMGET(14, 0) && gObj[aIndex].pInventory[i].m_Type <= ITEMGET(14, 8))
			{
				if (gObj[aIndex].pInventory[i].m_Durability == 1.0f)
				{
					gObj[aIndex].pInventory[i].m_Durability = 256.0f;
				}
			}
		}
	}

	return GCItemDurSend(aIndex, pos, dur, flag);
}

int	Functions::Rand(int Min, int Max)
{
	if (Min == Max)
	{
		return Min;
	}

	int Rand = rand();

	int Result = Min + Rand / (RAND_MAX / (Max - Min) + 1);

	return Result;
}

void Functions::CGUseItemRecvEx(PMSG_USEITEM* lpMsg, int aIndex)
{
	CItem* Item = &gObj[aIndex].pInventory[lpMsg->inventoryPos];
	CItem* Add = &gObj[aIndex].pInventory[lpMsg->inventoryTarget];

	if (Potion._Active[0] == true)
	{
		if (Item->m_Type >= ITEMGET(14, 0) && Item->m_Type <= ITEMGET(14, 6))
		{
			if (Custom[aIndex].Time == 1)
			{
				return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
			}
		}

		Custom[aIndex].Time = 1;
	}

	if (Item->m_Type == ITEMGET(15, 16))
	{
		Manager.ExecFormat("UPDATE MEMB_INFO SET Gold = Gold + 10 WHERE memb___id = '%s'", gObj[aIndex].AccountID);

		Func.FireWork(aIndex);

		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3)
			{
				Func.MsgOutput(Index, 0, "%s utilizou a Jewel of Gold!", gObj[aIndex].Name);
				Func.MsgOutput(Index, 0, "Premiação: 10 Golds.");
			}
		}

		gObjInventoryItemSet(aIndex, lpMsg->inventoryPos, -1);
		gObj[aIndex].pInventory[lpMsg->inventoryPos].Clear();
		GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
		GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);
	}

	if (Item->m_Type == ITEMGET(15, 17))
	{
		Manager.ExecFormat("UPDATE MEMB_INFO SET Gold = Gold + 640 WHERE memb___id = '%s'", gObj[aIndex].AccountID);

		Func.FireWork(aIndex);

		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3)
			{
				Func.MsgOutput(Index, 0, "%s utilizou a Jewel of Gold!", gObj[aIndex].Name);
				Func.MsgOutput(Index, 0, "Premiação: 640 Golds.");
			}
		}

		gObjInventoryItemSet(aIndex, lpMsg->inventoryPos, -1);
		gObj[aIndex].pInventory[lpMsg->inventoryPos].Clear();
		GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
		GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);
	}

	if (Item->m_Type == ITEMGET(15, 23))
	{
		if (Add->m_Type >= ITEMGET(12, 0) && Add->m_Type <= ITEMGET(12, 6))
		{
			if (Add->m_Excellent >= 31)
			{
				return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
			}

			int Count = 0;
			int Option[6];

			int Excelente = Add->m_Excellent;

			if (Excelente >= 128)
			{
				Excelente -= 128;
			}

			if (Excelente >= 64)
			{
				Excelente -= 64;
			}

			if (Excelente >= 32)
			{
				Excelente -= 32;
			}

			for (int i = 16; i >= 1; i /= 2)
			{
				if (Excelente >= i)
				{
					Excelente -= i;
				}
				else
				{
					Option[Count] = i;
					Count++;
				}
			}

			Add->m_Excellent += Option[(rand() % (Count))];

			memset(Option, 0, sizeof(Option));

			gObjInventoryItemSet(aIndex, lpMsg->inventoryPos, -1);
			gObj[aIndex].pInventory[lpMsg->inventoryPos].Clear();
			GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
			GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);

			gObj[aIndex].pInventory[lpMsg->inventoryTarget].Convert(Add->m_Type, Add->m_Skill, Add->m_Luck, Add->m_Option, Add->m_Excellent, 1);
		}
		else
		{
			if (Add->m_Excellent >= 63)
			{
				return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
			}

			int Excelente = Add->m_Excellent;

			int Count = 0;
			int Option[7];

			if (Excelente >= 128)
			{
				Excelente -= 128;
			}

			if (Excelente >= 64)
			{
				Excelente -= 64;
			}

			for (int i = 32; i >= 1; i /= 2)
			{
				if (Excelente >= i)
				{
					Excelente -= i;
				}
				else
				{
					Option[Count] = i;
					Count++;
				}
			}

			Add->m_Excellent += Option[(rand() % (Count))];

			memset(Option, 0, sizeof(Option));

			gObjInventoryItemSet(aIndex, lpMsg->inventoryPos, -1);
			gObj[aIndex].pInventory[lpMsg->inventoryPos].Clear();
			GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
			GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);

			gObj[aIndex].pInventory[lpMsg->inventoryTarget].Convert(Add->m_Type, Add->m_Skill, Add->m_Luck, Add->m_Option, Add->m_Excellent, 1);
		}
	}

	if (Item->m_Type == ITEMGET(15, 18))
	{
		if (Add->m_Luck == 1)
		{
			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		Add->m_Luck = 1;
		gObjInventoryItemSet(aIndex, lpMsg->inventoryPos, -1);
		gObj[aIndex].pInventory[lpMsg->inventoryPos].Clear();
		GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
		GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);

		gObj[aIndex].pInventory[lpMsg->inventoryTarget].Convert(Add->m_Type, Add->m_Skill, Add->m_Luck, Add->m_Option, Add->m_Excellent, 1);
	}

	if (Item->m_Type == ITEMGET(15, 19))
	{
		if (Add->m_Type >= ITEMGET(12, 0) && Add->m_Type <= ITEMGET(12, 19) || Add->m_Type == ITEMGET(4, 7) && Add->m_Type == ITEMGET(4, 15))
		{
			Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		if (Add->m_Type <= ITEMGET(0, 31) && Add->m_Type <= ITEMGET(0, 2) && Add->m_Type >= ITEMGET(0, 18))
		{
			Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		if (Add->m_Type >= ITEMGET(1, 0) && Add->m_Type <= ITEMGET(1, 8) && Add->m_Type == ITEMGET(1, 4))
		{
			Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		if (Add->m_Type >= ITEMGET(2, 0) && Add->m_Type <= ITEMGET(2, 14) && Add->m_Type >= ITEMGET(2, 7) || Add->m_Type == ITEMGET(2, 0))
		{
			Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		if (Add->m_Type >= ITEMGET(5, 0) && Add->m_Type <= ITEMGET(5, 14))
		{
			Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		if (Add->m_Type >= ITEMGET(6, 0) && Add->m_Type <= ITEMGET(6, 16))
		{
			if (Add->m_Type <= ITEMGET(6, 3) && Add->m_Type >= ITEMGET(6, 13))
			{
				Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

				return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
			}
		}

		if (Add->m_Type >= ITEMGET(7, 0) && Add->m_Type <= ITEMGET(7, 31))
		{
			Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		if (Add->m_Type >= ITEMGET(8, 0) && Add->m_Type <= ITEMGET(8, 31))
		{
			Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		if (Add->m_Type >= ITEMGET(9, 0) && Add->m_Type <= ITEMGET(9, 31))
		{
			Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		if (Add->m_Type >= ITEMGET(10, 0) && Add->m_Type <= ITEMGET(10, 31))
		{
			Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		if (Add->m_Type >= ITEMGET(11, 0) && Add->m_Type <= ITEMGET(11, 31))
		{
			Func.MsgOutput(aIndex, 1, "O item não possui atributo skill.");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		if (Add->m_Skill == 1)
		{
			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		Add->m_Skill = 1;
		gObjInventoryItemSet(aIndex, lpMsg->inventoryPos, -1);
		gObj[aIndex].pInventory[lpMsg->inventoryPos].Clear();
		GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
		GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);

		gObj[aIndex].pInventory[lpMsg->inventoryTarget].Convert(Add->m_Type, Add->m_Skill, Add->m_Luck, Add->m_Option, Add->m_Excellent, 1);
	}

	if (Item->m_Type == ITEMGET(15, 20))
	{
		if (Add->m_Level < 11 || Add->m_Level == 15)
		{
			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}

		Add->m_Level++;
		gObjInventoryItemSet(aIndex, lpMsg->inventoryPos, -1);
		gObj[aIndex].pInventory[lpMsg->inventoryPos].Clear();
		GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
		GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);

		gObj[aIndex].pInventory[lpMsg->inventoryTarget].Convert(Add->m_Type, Add->m_Skill, Add->m_Luck, Add->m_Option, Add->m_Excellent, 1);
	}

	if (Item->m_Type == ITEMGET(15, 22))
	{
		if (Add->m_Type == ITEMGET(12, 0))
		{
			int Item = ITEMGET(12, 3);

			if (!Func.InventoryFullCheck(aIndex, Item))
			{
				Func.MsgOutput(aIndex, 1, "O inventário está cheio!");

				return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
			}
			else
			{
				gObjInventoryDeleteItem(aIndex, lpMsg->inventoryPos);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);
				GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);

				ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, Add->m_Level, 0, Add->m_Skill, Add->m_Luck, Add->m_Option, aIndex, Add->m_Excellent);

				gObjInventoryDeleteItem(aIndex, lpMsg->inventoryTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryTarget, 1);
			}
		}

		if (Add->m_Type == ITEMGET(12, 1))
		{
			int Item = ITEMGET(12, 4);

			if (!Func.InventoryFullCheck(aIndex, Item))
			{
				Func.MsgOutput(aIndex, 1, "O inventário está cheio!");

				return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
			}
			else
			{
				gObjInventoryDeleteItem(aIndex, lpMsg->inventoryPos);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);
				GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);

				ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, Add->m_Level, 0, Add->m_Skill, Add->m_Luck, Add->m_Option, aIndex, Add->m_Excellent);

				gObjInventoryDeleteItem(aIndex, lpMsg->inventoryTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryTarget, 1);
			}
		}

		if (Add->m_Type == ITEMGET(12, 2))
		{
			int Item = ITEMGET(12, 5);

			if (!Func.InventoryFullCheck(aIndex, Item))
			{
				Func.MsgOutput(aIndex, 1, "O inventário está cheio!");

				return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
			}
			else
			{
				gObjInventoryDeleteItem(aIndex, lpMsg->inventoryPos);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);
				GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);

				ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, Add->m_Level, 0, Add->m_Skill, Add->m_Luck, Add->m_Option, aIndex, Add->m_Excellent);

				gObjInventoryDeleteItem(aIndex, lpMsg->inventoryTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryTarget, 1);
			}
		}

		if (Add->m_Type == ITEMGET(12, 6))
		{
			Func.MsgOutput(aIndex, 1, "Sua asa não possui evolução!");

			return Functions::GCRefillSend(aIndex, gObj[aIndex].Life, 0xFD, 1);
		}
	}

	return CGUseItemRecv(lpMsg, aIndex);
}

BOOL Functions::NpcTalkEx(OBJECTSTRUCT* lpNpc, OBJECTSTRUCT* lpObj)
{
	switch (lpNpc->Class)
	{
	case 201:
	{
		Treasure.Talk(lpNpc, lpObj);
		return FALSE;
	}
	break;
	case 202:
	{
		if (DeathEvent._Portal == true)
		{
			DeathEvent.Talk(lpNpc, lpObj);
			return TRUE;
		}
		else if (TheftEvent._Portal == true)
		{
			TheftEvent.Talk(lpNpc, lpObj);
			return TRUE;
		}
		else if (FlagEvent._Portal == true)
		{
			FlagEvent.Talk(lpNpc, lpObj, 1);
			return TRUE;
		}
		else
		{
			ChatTargetSend(lpNpc, "Nenhum evento foi inicializado. Aguarde...", lpObj->m_Index);
			return TRUE;
		}
	}
	break;
	case 203:
	{
		Quest.Talk(lpNpc, lpObj);
		return TRUE;
	}
	break;
	case 204:
	{
		FlagEvent.Talk(lpNpc, lpObj, 0);
		return TRUE;
	}
	break;
	case 205:
	{
		FlagEvent.Talk(lpNpc, lpObj, 0);
		return TRUE;
	}
	break;
	case 206:
	{
		if (lpObj->Level > 180)
		{
			ChatTargetSend(lpNpc, "Você já pode se virar sozinho(a)!", lpObj->m_Index);
			return TRUE;
		}
		else if (Custom[lpObj->m_Index].Helper == true)
		{
			ChatTargetSend(lpNpc, "Você já recebeu a minha ajuda!", lpObj->m_Index);
			return TRUE;
		}

		lpObj->m_SkillAttack = lpObj->Level / 3 + 45;

		lpObj->m_ViewSkillState |= 4;

		GCMagicAttackNumberSend(lpObj, 28, lpObj->m_Index, true);

		lpObj->m_SkillDefense = lpObj->Level / 5 + 50;

		lpObj->m_ViewSkillState |= 8;

		GCMagicAttackNumberSend(lpObj, 27, lpObj->m_Index, true);

		Custom[lpObj->m_Index].Helper = true;

		ChatTargetSend(lpNpc, "Eu aumentei a sua defesa e ataque!", lpObj->m_Index);
	}
	break;
	case 208:
	{
		Collector.Talk(lpNpc, lpObj);
		return TRUE;
	}
	break;
	case 240:
	{
		WareHouse(lpNpc, lpObj);
		return TRUE;
	}
	break;
	}

	return NpcTalk(lpNpc, lpObj);
}

void Functions::PChatProcEx(PMSG_CHATDATA* Message, int aIndex)
{
	char* SendText = &Message->Message[0];

	if (SendText[0] == '@' && SendText[1] == '>')
	{
		for (unsigned int i = 0; i < strlen(SendText); i++)
		{
			if (SendText[i] == '\'')
			{
				SendText[i] = '"';
			}
		}
	}

	return PChatProc(Message, aIndex);
}

void Functions::GCResultSend(int aIndex, BYTE headcode, BYTE result)
{
	PMSG_DEFRESULT Result;

	PHeadSetB((LPBYTE)&Result, headcode, sizeof(Result));
	Result.result = result;

	DataSend(aIndex, (UCHAR*)&Result, Result.h.size);
}

void Functions::CGGuildRequestRecvEx(PMSG_GUILDJOINQ* lpMsg, int aIndex)
{
	int Number = MAKE_NUMBER(lpMsg->NumberH, lpMsg->NumberL);

	if (Number < 0 || Number > OBJECT_MAX - 1)
	{
		return;
	}

	if (gObj[Number].GuildNumber > 0)
	{
		int MaxGuildMember = gObj[Number].Level / 10;

		if (MaxGuildMember > 30)
		{
			MaxGuildMember = 30;
		}

		if (gObj[Number].lpGuild->TotalCount >= MaxGuildMember)
		{
			Func.GCResultSend(aIndex, 0x51, 0x02);
			return;
		}
	}

	CGGuildRequestRecv(lpMsg, aIndex);
}

void Functions::CGCloseWindow(int aIndex)
{
	if (gObj[aIndex].m_IfState.use && gObj[aIndex].m_IfState.type)
	{
		if (gObj[aIndex].m_IfState.type == 7)
		{
			return;
		}

		if (gObj[aIndex].m_IfState.type == 3)
		{
			gObj[aIndex].TargetShopNumber = -1;
		}

		if (gObj[aIndex].m_IfState.type == 1)
		{
			gObjTradeCancel(aIndex);
		}

		if (gObj[aIndex].m_IfState.type == 6)
		{
			CGWarehouseUseEnd(aIndex);
		}

		if (gObj[aIndex].m_IfState.type == 13)
		{
			ChaosBoxInit(&gObj[aIndex]);
			gObjInventoryCommit(aIndex);
		}

		gObj[aIndex].m_IfState.state = 0;
		gObj[aIndex].m_IfState.type = 0;
		gObj[aIndex].m_IfState.use = 0;
	}
}

void Functions::gObjTeleportMagicUseEx(int aIndex, BYTE X, BYTE Y)
{
	if (PegaEvent.Teleport(&gObj[aIndex]) == false)
	{
		X = (BYTE)gObj[aIndex].X;
		Y = (BYTE)gObj[aIndex].Y;

		Func.MsgOutput(aIndex, 1, "Proibido teleporte no evento.");
	}

	if (FlagEvent.Teleport(&gObj[aIndex]) == false)
	{
		X = (BYTE)gObj[aIndex].X;
		Y = (BYTE)gObj[aIndex].Y;

		Func.MsgOutput(aIndex, 1, "Proibido teleporte no evento.");
	}

	gObjTeleportMagicUse(aIndex, X, Y);
}

void Functions::Refresh(int aIndex)
{
	PMSG_CHARMAPJOINRESULT Join;
	Join.h.c = 0xC3;
	Join.h.head = 0xF3;
	Join.h.size = 0x33;
	Join.subcode = 0x03;
	Join.MapX = gObj[aIndex].X;
	Join.MapY = gObj[aIndex].Y;
	Join.MapNumber = gObj[aIndex].MapNumber;
	Join.Dir = gObj[aIndex].Dir;
	Join.Exp = gObj[aIndex].Experience;
	Join.NextExp = gObj[aIndex].NextExp;
	Join.LevelUpPoint = gObj[aIndex].LevelUpPoint;
	Join.Str = gObj[aIndex].Strength;
	Join.Dex = gObj[aIndex].Dexterity;
	Join.Vit = gObj[aIndex].Vitality;
	Join.Energy = gObj[aIndex].Energy;
	Join.Money = gObj[aIndex].Money;
	Join.PkLevel = gObj[aIndex].m_PK_Level;
	Join.Life = (short)gObj[aIndex].Life;
	Join.MaxLife = (short)((double)gObj[aIndex].AddLife + gObj[aIndex].MaxLife);
	Join.Mana = (short)gObj[aIndex].Mana;
	Join.MaxMana = (short)((double)gObj[aIndex].AddMana + gObj[aIndex].MaxMana);
	Join.CtlCode = (short)gObj[aIndex].Authority;
	Join.BP = gObj[aIndex].BP;
	Join.MaxBP = gObj[aIndex].AddBP + gObj[aIndex].MaxBP;

	DataSend(aIndex, (LPBYTE)(&Join), Join.h.size);

	PMSG_CHARREGEN Regen;
	Regen.h.c = 0xC3;
	Regen.h.head = 0xF3;
	Regen.h.size = 0x24;
	Regen.subcode = 0x04;
	Regen.Dir = gObj[aIndex].Dir;
	Regen.MapX = LOBYTE(gObj[aIndex].X);
	Regen.MapY = LOBYTE(gObj[aIndex].Y);
	Regen.Life = (float)gObj[aIndex].Life;
	Regen.Mana = (float)gObj[aIndex].Mana;
	Regen.Exp = gObj[aIndex].Experience;
	Regen.MapNumber = gObj[aIndex].MapNumber;
	Regen.Money = gObj[aIndex].Money;
	Regen.BP = LOWORD(gObj[aIndex].BP);

	gObj[aIndex].PathCount = 0;

	DataSend(aIndex, (LPBYTE)(&Regen), Regen.h.size);

	CGRequestQuestInfo(aIndex);
	DGGuildMemberInfoRequest(aIndex);
}

void Functions::HealthBarSend(LPOBJ lpObj)
{
	BYTE Buffer[1500];
	PMSG_HEALTHBAR Result;
	PMSG_HEALTHBAR_INFO Info;

	Result.h.c = 0xC2;
	Result.h.head = 0xF3;
	Result.Code = 0xE2;
	Result.Count = 0;

	int Size = sizeof(Result);

	for (int i = 0; i < 75; i++)
	{
		if (lpObj->VpPlayer[i].State != 1 && lpObj->VpPlayer[i].State != 2)
		{
			continue;
		}

		if (lpObj->VpPlayer[i].Type != MONSTER)
		{
			continue;
		}

		if (OBJECT_RANGE(lpObj->VpPlayer[i].Number) == 0)
		{
			continue;
		}

		LPOBJ lpTargetObj = &gObj[lpObj->VpPlayer[i].Number];

		if (lpTargetObj->Class == 200 || lpTargetObj->Live == 0 || lpTargetObj->m_State != 2)
		{
			continue;
		}

		Info.Index = lpObj->VpPlayer[i].Number;
		Info.Rate = (BYTE)((lpTargetObj->Life * 100) / (lpTargetObj->MaxLife + lpTargetObj->AddLife));

		memcpy(&Buffer[Size], &Info, sizeof(Info));
		Size += sizeof(Info);
		Result.Count++;
	}

	Result.h.sizeH = HIBYTE(Size);
	Result.h.sizeL = LOBYTE(Size);

	memcpy(Buffer, &Result, sizeof(Result));

	DataSend(lpObj->m_Index, Buffer, Size);
}

void Functions::gObjViewportListCreateEx(short aIndex)
{
	gObjViewportListCreate(aIndex);

	if (gObj[aIndex].Type == PLAYER)
	{
		Func.HealthBarSend(&gObj[aIndex]);

		for (int Index = OBJECT_MIN; Index < OBJECT_MAX; Index++)
		{
			if (gObj[Index].Connected == 3 && Custom[Index].Patent >= 0)
			{
				Patent.GCReqRankLevelUser(aIndex, Index);
			}
		}
	}
}

void Functions::CGWarehouseUseEndEx(int aIndex)
{
	Manager.ExecFormat("UPDATE warehouse SET CheckVault = 0 WHERE AccountID = '%s'", gObj[aIndex].AccountID);

	return CGWarehouseUseEnd(aIndex);
}

BOOL Functions::Position(int aIndex, int MapNumber, int X, int Y, int View)
{
	if (gObj[aIndex].MapNumber != MapNumber)
	{
		return FALSE;
	}

	if (gObj[aIndex].X < (X - View) || gObj[aIndex].X >(X + View) || gObj[aIndex].Y < (Y - View) || gObj[aIndex].Y >(Y + View))
	{
		return FALSE;
	}

	return TRUE;
}

void Functions::CheckBuffs(LPOBJ lpObj)
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

bool Functions::CheckString(const std::string& str)
{
	if (str.find("_GM") != std::string::npos ||
		str.find("-GM") != std::string::npos ||
		str.find("GM-") != std::string::npos ||
		str.find("GM_") != std::string::npos ||
		str.find("-ADM") != std::string::npos ||
		str.find("_ADM") != std::string::npos ||
		str.find("ADM-") != std::string::npos ||
		str.find("ADM_") != std::string::npos)
	{
		return false;
	}

	for (char i : str)
	{
		if (!(std::isalnum(i) || i == '-' || i == '_' || std::strchr("[]", i) != nullptr))
		{
			return false;
		}
	}

	return true;
}

void Functions::CGLiveClient(PMSG_CLIENTTIME* lpMsg, short aIndex)
{
	if (gObj[aIndex].Connected > EMPTY)
	{
		gObj[aIndex].ConnectCheckTime = GetTickCount();
	}

	PMSG_LIVE_CLIENT Result;

	PHeadSetB((LPBYTE)&Result, 0x0E, sizeof(Result));

	Result.TickCount = lpMsg->Time;

	DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
}

void Functions::CGSellRequestRecvEx(PMSG_SELLREQUEST* lpMsg, int aIndex)
{
	PMSG_SELLRESULT Result;

	PHeadSetB((LPBYTE)&Result, 0x33, sizeof(Result));
	Result.Result = false;
	Result.Money = 0;

	if (gObj[aIndex].pInventory[lpMsg->Pos].m_Type >= ITEMGET(15, 16) && gObj[aIndex].pInventory[lpMsg->Pos].m_Type <= ITEMGET(15, 23))
	{
		DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
		return;
	}

	return CGSellRequestRecv(lpMsg, aIndex);
}

void Functions::gObjCalCharacterEx(int aIndex)
{
	gObjCalCharacter(aIndex);

	Func.SendMain(aIndex);
}

void Functions::CGPCharDelEx(PMSG_CHARDELETE* lpMsg, int aIndex)
{
	PMSG_RESULT Result;

	PHeadSubSetB((LPBYTE)&Result, 0xF3, 0x02, sizeof(Result));
	Result.result = 0;

	if (Block.BlockStruct[aIndex]._Active == 1)
	{
		Result.result = 2;
		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
		return;
	}

	return CGPCharDel(lpMsg, aIndex);
}

void Functions::DataSendAll(unsigned char* lpMsg, int Size)
{
	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Connected == 3)
		{
			if (gObj[i].Type == 1)
			{
				DataSend(i, (unsigned char*)lpMsg, Size);
			}
		}
	}
}

void Functions::PostSend(int Type, char Send[20], const char* Message, ...)
{
	char Buffer[1024];
	va_list pArguments;
	va_start(pArguments, Message);
	vsprintf(Buffer, Message, pArguments);
	va_end(pArguments);

	CHAT_WHISPER Result;

	memcpy(Result.Name, Send, 10);

	memcpy(Result.Message, Buffer, 90);

	Result.Type = Type;

	Result.h.set((LPBYTE)&Result, 2, sizeof(CHAT_WHISPER));

	DataSendAll((LPBYTE)&Result, Result.h.size);
}

void Functions::Thread(void* lpParam)
{
	while (true)
	{
		News.Run();

		BossEvent.Run();
		DeathEvent.Run();
		HappyEvent.Run();
		RaffleEvent.Run();
		TheftEvent.Run();
		FlagEvent.Run();
		DropEvent.Run();
		Natal.Run();
		Pascoa.Run();

		Sleep(1000);
	}

	_endthread();
}

void Functions::ReadCommonEx()
{
	Setting.Load();
	Corrections.Load();
	Query.Load();
	Balancer.Load();
	News.Load();
	Authority.Load();
	Command.Load();
	Bank.Load();
	Attack.Load();
	Reset.Load();
	Master.Load();
	Treasure.Load();
	Collector.Load();
	Speed.Load();
	Teleport.Load();
	Blood.Load();
	DuelEvent.Load();
	PegaEvent.Load();
	SobreEvent.Load();
	DeathEvent.Load();
	BossEvent.Load();
	HappyEvent.Load();
	QuizEvent.Load();
	CoinEvent.Load();
	RaffleEvent.Load();
	TheftEvent.Load();
	FlagEvent.Load();
	PairEvent.Load();
	RoletaEvent.Load();
	Drop.Load();
	Message.Load();
	BoxWings.Load(); // [ Alteração ] - Adicionado Box Wings.
	BoxExclusive.Load(); // [ Alteração ] - Adicionado Box Exclusive.
	BoxWeapons.Load(); // [ Alteração ] - Adicionado Box Weapons.
	BoxLimited.Load(); // [ Alteração ] - Adicionado Box Limited.
	BoxSets.Load(); // [ Alteração ] - Adicionado Box Sets.
	Duel.Load();
	Bonus.Load();
	Roleta.Load();
	Potion.Load();
	Quest.Load();
	Rank.Load();
	Ring.Load();
	AutoReset.Load();
	Offline.Load();
	Party.Load();
	DropEvent.Load();
	Experience.Load();
	UfcEvent.Load();
	BattleEvent.Load();
	Natal.Load();
	Reward.Load();
	Buy.Load();
	Pet.Load();
	Patent.Load();
	Attribute.Load();
	DevilEvent.Load();
	Block.Load();
	KingEvent.Load();
	Pascoa.Load();

	return ReadCommon();
}

Functions Func;
