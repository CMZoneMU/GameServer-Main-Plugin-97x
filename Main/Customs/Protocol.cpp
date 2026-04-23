#include "StdAfx.h"


void cProtocol::ProtocolCore(LPBYTE aRecv)
{
	BYTE Head = aRecv[(aRecv[0] == 0xC2 || aRecv[0] == 0xC4) ? 3 : 2];
	BYTE SubCode = aRecv[(aRecv[0] == 0xC2 || aRecv[0] == 0xC4) ? 4 : 3];

	Protocol.MainCheck();

	switch (Head)
	{
	case 0x02:
	{
		Protocol.Message((CHAT_WHISPER*)aRecv);
	}
	break;
	case 0x0E:
	{
		Protocol.GCLiveClient((PMSG_LIVE_CLIENT*)aRecv);
	}
	break;
	/*case 0x15:
	{
		Visual.RecvDamage((PMSG_ATTACKRESULT*)aRecv); // Função de receber dano, mas não funciona direito, então desativei.
	}
	break;*/
	case 0x17:
	{
		Visual.Killed((PMSG_DIEPLAYER*)aRecv);
	}
	break;
	case 0x26:
	{
		Visual.RecvHP((PMSG_REFILL*)aRecv);
	}
	break;
	case 0x27:
	{
		Visual.RecvMP((PMSG_MANASEND*)aRecv);
	}
	break;
	case 0x30:
		Treasure = ((PMSG_TALKRESULT*)(aRecv))->Treasure > 0 ? true : false;
		break;
	case 0xF1:
	{
		switch (SubCode)
		{
		case 0x00:
		{
			Visual.Index((PMSG_JOINRESULT*)aRecv);
		}
		break;
		}
	}
	break;
	case 0xF3:
	{
		switch (SubCode)
		{
		case 0x03:
		{
			Visual.Respawn();

			Protocol.Agility();
		}
		break;
		case 0x04:
		{
			Visual.Respawn();
		}
		break;
		case 0x05:
		{
			Protocol.Update = false;
		}
		break;
		case 0x06:
		{
			Protocol.Update = false;
			Protocol.RealLevelUpPoint--;
		}
		break;
		case 0xE2:
		{
			HPBar.Clear();

			PMSG_HEALTHBAR* lpMsg = (PMSG_HEALTHBAR*)(aRecv);

			for (int i = 0; i < lpMsg->Count; i++)
			{
				PMSG_HEALTHBAR_INFO* Info = (PMSG_HEALTHBAR_INFO*)(&aRecv[sizeof(PMSG_HEALTHBAR) + (sizeof(PMSG_HEALTHBAR_INFO) * i)]);
				HPBar.Insert(Info->Index, Info->Rate);
			}
		}
		break;
		case 0xE5:
		{
			Patent.GCReqRankLevelUser((PMSG_CUSTOM_RANKUSER*)aRecv);
		}
		break;
		case 0xE6:
		{
			// [ Novo ]: Receber informações do personagem, como resets, cash, event points, etc. Com efeito.
			Protocol.GCCharacterInfo((PMSG_CUSTOM_CHARACTER_INFO_RECV*)aRecv);
		}
		break;
		}		
	}
	break;
	case 0xFE:
	{
		switch (SubCode)
		{
		case 0x01: // Update - Com efeito.
		{
			PMSG_LEVELUP Result;
			PMSG_UPDATECHARACTER* Info = (PMSG_UPDATECHARACTER*)(aRecv);

			Protocol.Update = true;
			Protocol.Level = Info->Level;
			Protocol.LevelUpPoint = Info->LevelUpPoint;
			Protocol.RealLevelUpPoint = Info->LevelUpPoint;
			Protocol.Experience = Info->Experience;
			Protocol.NextExperience = Info->NextExperience;
			Protocol.Strength = Info->Strength;
			Protocol.Dexterity = Info->Dexterity;
			Protocol.Vitality = Info->Vitality;
			Protocol.Energy = Info->Energy;
			Protocol.Life = Info->Life;
			Protocol.MaxLife = Info->MaxLife;
			Protocol.Mana = Info->Mana;
			Protocol.MaxMana = Info->MaxMana;
			Protocol.BP = Info->BP;
			Protocol.MaxBP = Info->MaxBP;
			Visual.Life = Info->MaxLife;
			Visual.Mana = Info->MaxMana;
			Visual.Ag = Info->MaxBP;

			Result.h.c = 0xC1;
			Result.h.size = sizeof(Result);
			Result.h.head = 0xF3;
			Result.subcode = 0x05;

			LevelUpRecv(&Result);
		}
		break;
		case 0x02: // Update - Sem efeito.
		{
			PMSG_LVPOINTADDRESULT Result;
			PMSG_UPDATECHARACTER* Info = (PMSG_UPDATECHARACTER*)(aRecv);

			Protocol.Update = true;
			Protocol.LevelUpPoint = Info->LevelUpPoint + 1;
			Protocol.RealLevelUpPoint = Info->LevelUpPoint;
			Protocol.Strength = Info->Strength - 1;
			Protocol.Dexterity = Info->Dexterity;
			Protocol.Vitality = Info->Vitality;
			Protocol.Energy = Info->Energy;
			Protocol.Life = Info->Life;
			Protocol.MaxLife = Info->MaxLife;
			Protocol.Mana = Info->Mana;
			Protocol.MaxMana = Info->MaxMana;
			Protocol.BP = Info->BP;
			Protocol.MaxBP = Info->MaxBP;
			Visual.Life = Info->MaxLife;
			Visual.Mana = Info->MaxMana;
			Visual.Ag = Info->MaxBP;

			Result.h.c = 0xC1;
			Result.h.size = sizeof(Result);
			Result.h.head = 0xF3;
			Result.subcode = 0x06;
			Result.ResultType = 0x10;
			Result.MaxLifeAndMana = Info->MaxLife;
			Result.MaxBP = Info->MaxBP;

			LevelUpAddPoint(&Result);
		}
		break;
		case 0x07:
		{
			PMSG_CHARINFOMAIN* Info = (PMSG_CHARINFOMAIN*)(aRecv);

			Protocol.Class = Info->Class;
			Protocol.Dexterity = Info->Dexterity;
			Protocol.AttackSpeed = Info->AttackSpeed;
			Protocol.MagicSpeed = Info->MagicSpeed;
			Protocol.RealLevelUpPoint = Info->LevelUpPoint;
			Protocol.Sword[0] = Info->Sword[0];
			Protocol.Sword[1] = Info->Sword[1];
			Protocol.Sword[2] = Info->Sword[2];
			Protocol.Sword[3] = Info->Sword[3];
			Protocol.Sword[4] = Info->Sword[4];
			Protocol.Sword[5] = Info->Sword[5];
			Protocol.Sword[6] = Info->Sword[6];
			Protocol.Sword[7] = Info->Sword[7];
			Protocol.Sword[8] = Info->Sword[8];
			Protocol.Sword[9] = Info->Sword[9];
			Protocol.Sword[10] = Info->Sword[10];
			Protocol.Sword[11] = Info->Sword[11];
		}
		break;
		case 0x08:
		{
			PMSG_UPDATEPOINTS* Info = (PMSG_UPDATEPOINTS*)(aRecv);

			Protocol.RealLevelUpPoint = Info->LevelUpPoint;
		}
		break;
		}
	}
	break;
	}
}

void cProtocol::Message(CHAT_WHISPER* lpMsg)
{
	this->Buffer[10] = 0;

	memcpy(this->Buffer, lpMsg->Name, sizeof(lpMsg->Name));

	if (lpMsg->Type > 0)
	{
		GCMsgStringSend(this->Buffer, lpMsg->Message, lpMsg->Type);

		lpMsg->Type = 0;
	}
	else
	{
		GCMsgStringSend(this->Buffer, lpMsg->Message, 0x00);
	}
}

void cProtocol::GCLiveClient(PMSG_LIVE_CLIENT* lpMsg)
{
	Protocol.Tick = GetTickCount() - lpMsg->TickCount;
}
//--------------------- Novos Protocolos de Envio  ---------------------------------

// [ Novo ]: Receber informações do personagem, como resets, cash, event points, etc. Com efeito.
void cProtocol::GCCharacterInfo(PMSG_CUSTOM_CHARACTER_INFO_RECV* lpMsg)
{
	this->Reset = lpMsg->Reset;
	this->Cash = lpMsg->Cash;
	this->EventPoint = lpMsg->EventPoint;
	this->AccountLevel = lpMsg->Vip;
	this->AccountExpireDays = lpMsg->VipDays;
	this->OnlineCount = lpMsg->OnlineCount; 
}


//-----------------------------  FIM ------------------------------------------------
void cProtocol::Agility()
{
	switch (Protocol.Class)
	{
	case 0:
		*(BYTE*)(0x447AF5 + 6) = 0x02;
		break;
	case 1:
		*(BYTE*)(0x447AF5 + 6) = 0x0F;
		break;
	case 2:
		*(BYTE*)(0x447AF5 + 6) = 0x02;
		*(BYTE*)(0x4481E1 + 6) = 0x02;
		break;
	case 3:
		*(BYTE*)(0x447AF5 + 6) = 0x02;
		break;
	}
}

void cProtocol::MainCheck()
{
	if (MAIN_STATE == 5)
	{
		*(BYTE*)(0x5215FF + 6) = 0x07;
	}
	else
	{
		*(BYTE*)(0x5215FF + 6) = 0x28;

		SetWindowText(GameWindow, "MU");
	}
}

cProtocol Protocol;