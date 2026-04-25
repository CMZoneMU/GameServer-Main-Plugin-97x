#include "StdAfx.h"

void ProtocolCoreEx(BYTE protoNum,LPBYTE aRecv,DWORD aLen,short aIndex,DWORD Encrypt,int Serial)
{
	Disconnect.Check(aIndex);

	switch (protoNum)
	{
	case 0x00:
		{
			if ((char)aRecv[13] == '/')
			{
				Command.Management(aRecv, aIndex);
			}

			if ((!memcmp(&aRecv[13], "!", strlen("!"))))
			{
				if (gObj[aIndex].Authority > 1)
				{
					Func.AllServerAnnounce("%s: %s", gObj[aIndex].Name, aRecv + 14);
					return;
				}
			}

			if ((!memcmp(&aRecv[13], "#", strlen("#"))))
			{
				if (gObj[aIndex].Authority > 1)
				{
					for (int i = OBJECT_MIN; i != OBJECT_MAX; i++)
					{
						if (gObj[i].Connected == 3)
						{
							Func.MsgOutput(i, 0, "[    %s    ]", gObj[aIndex].Name);

							Func.MsgOutput(i, 0, "%s", aRecv + 14);
						}
					}
				}
			}
		}
		break;
	case 0x03:
		{
			if (aRecv[0] == 0xC1)
			{
				if (aRecv[1] == 0x09)
				{
					if (aRecv[2] == 0x03)
					{
						if (gObj[aIndex].CheckSumTableNum < 0)
						{
							gObjCloseSet(aIndex, 0);
							return;
						}
					}
				}
			}

			Connect.PlayerConnect(aIndex);
		}
		break;
	case 0x19:
	    {
		    Speed.Skill(&gObj[aIndex], gObj[aIndex].UseMagicNumber);
	    }
		break;
	case 0x1E:
	    {
		    Speed.Skill(&gObj[aIndex], gObj[aIndex].UseMagicNumber);
	    }
		break;
	case 0x30:
		{
			if (aRecv[1] == 0x06)
			{
				if (aRecv[2] == 0x30)
				{
				   if (gObj[aIndex].WarehouseSave == 1)
				   {
					   CGWarehouseUseEnd(aIndex);
				   }
			    }
			}
		}
		break;
	case 0x31:
	{
		Func.CGCloseWindow(aIndex);
		return;
	}
	break;
	case 0x32:
	{
		GCItemListSend(aIndex);
	}
	break;
	case 0x33:
	{
		if (Block.BlockStruct[aIndex]._Active == 1)
		{
			Func.Golden(aIndex, "Conta protegida!");
			Func.Golden(aIndex, "Utilize a senha para desbloquear.");
			return;
		}
	}
	break;
	case 0x36:
	{
		if (Custom[aIndex].InEvent == true || DeathEvent.PlayerStruct[aIndex]._InEvent == true || TheftEvent.PlayerStruct[aIndex]._InEvent == true || FlagEvent.PlayerStruct[aIndex]._InEvent == true || RoletaEvent.PlayerStruct[aIndex]._InEvent == true || BattleEvent.PlayerStruct[aIndex]._InEvent == true)
		{
			Func.MsgOutput(aIndex, 1, "Proibido dar trade no evento.");
			return;
		}
		else if (Duel.DuelStruct[aIndex]._Duel == true)
		{
			Func.MsgOutput(aIndex, 1, "Proibido dar trade no duelo.");
			return;
		}

		if (RoletaEvent.Trade((PMSG_TRADE_REQUEST *)aRecv, aIndex) == false)
		{
			return;
		}

		if (Block.BlockStruct[aIndex]._Active == 1)
		{
			Func.Golden(aIndex, "Conta protegida!");
			Func.Golden(aIndex, "Utilize a senha para desbloquear.");
			return;
		}
	}
	break;
	case 0x37:
		{
			if (aRecv[0] == 0xC1)
			{
				if (aRecv[1] == 0x04 || aRecv[2] == 0x37)
				{
					if (gObj[aIndex].pTransaction == 1)
					{
						gObj[aIndex].pTransaction = 0;

						gObjTradeCancel(aIndex);

						gObjCloseSet(aIndex, 0);
						return;
					}
				}
			}

			if (Block.BlockStruct[aIndex]._Active == 1)
			{
				Func.Golden(gObj[aIndex].TargetNumber, "Esse jogador não pode receber trade.");
				return;
			}
		}
		break;
	case 0x40:
	{
		if (Custom[aIndex].InEvent == true || DeathEvent.PlayerStruct[aIndex]._InEvent == true || TheftEvent.PlayerStruct[aIndex]._InEvent == true || FlagEvent.PlayerStruct[aIndex]._InEvent == true || RoletaEvent.PlayerStruct[aIndex]._InEvent == true || BattleEvent.PlayerStruct[aIndex]._InEvent == true)
		{
			Func.MsgOutput(aIndex, 1, "Proibido formar party no evento.");
			return;
		}
	}
	break;
	case 0x55:  
		{
			if ((gObj[aIndex].m_IfState.use == 0) || (gObj[aIndex].m_IfState.use == 1 && gObj[aIndex].m_IfState.type == 3 ) || (gObj[aIndex].m_IfState.use == 0 && gObj[aIndex].m_IfState.type == 15))  
			{
				return;
			}
		}
		break;
	case 0xF3:
		{
			PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2 *)aRecv;

			switch(lpDef->subcode)
			{
			case 0x01:
				{
					if (Create((PMSG_CHARCREATE *)aRecv, aIndex) == true)
					{
						JGCharacterCreateFailSend(aIndex, gObj[aIndex].Name);
						return;
					}
				}
				break;
			}

			switch (aRecv[3])
			{
			case 0x06:
			{
				switch (aRecv[4])
				{
				case 0:
					if ((unsigned short)(gObj[aIndex].Strength + 1) > 32767)
					{
						return;
					}
					break;
				case 1:
					if ((unsigned short)(gObj[aIndex].Dexterity + 1) > 32767)
					{
						return;
					}
					break;
				case 2:
					if ((unsigned short)(gObj[aIndex].Vitality + 1) > 32767)
					{
						return;
					}
					break;
				case 3:
					if ((unsigned short)(gObj[aIndex].Energy + 1) > 32767)
					{
						return;
					}
					break;
				}
			}
			break;
			}
		}
		break;
	}

	ProtocolCore(protoNum,aRecv,aLen,aIndex,Encrypt,Serial);
}

