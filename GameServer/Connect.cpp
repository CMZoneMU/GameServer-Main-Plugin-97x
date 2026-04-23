#include "StdAfx.h"

void ConnectServer::PlayerConnect(int aIndex)
{
	// [ Novo ]: Atualiza as informações de Resets, Cash e Vip para o Main
	this->UpdateCharacterInfo(aIndex); 
	
	Custom[aIndex].VipCount = Manager.VipCount(gObj[aIndex].AccountID);
	Custom[aIndex].ResetCount = Manager.CountResets(gObj[aIndex].Name);
	Manager.CoinCount(aIndex, gObj[aIndex].AccountID);

	Manager.JewelsCount(aIndex, gObj[aIndex].AccountID);
	Manager.CheckBonus(aIndex, gObj[aIndex].AccountID);
	Manager.CoinCount(aIndex, gObj[aIndex].AccountID);

	if (Custom[aIndex].VipCount == 0)
	{
		Func.MsgOutput(aIndex, 0, Message._Buffer[0], gObj[aIndex].Name); // Free
	}
	else if (Custom[aIndex].VipCount == 1)
	{
		Func.MsgOutput(aIndex, 0, Message._Buffer[1], gObj[aIndex].Name); //  Vip Bonus
	}
	else if (Custom[aIndex].VipCount == 2)
	{
		Func.MsgOutput(aIndex, 0, Message._Buffer[2], gObj[aIndex].Name); // Vip Premium
	}
	else if (Custom[aIndex].VipCount == 3)
	{
		Func.MsgOutput(aIndex, 0, Message._Buffer[2], gObj[aIndex].Name); // Super Vip
	}

	if (gObj[aIndex].Authority == 1)
	{
		if (Custom[aIndex].VipCount < Setting._Type && Setting._Type != 4)
		{
			Func.MsgOutput(aIndex, 1, "[ Aviso ]: Servidor exclusivo para vips!");
			gObjCloseSet(aIndex, 2);
		}

		if (Setting._Type == 4)
		{
			if (Custom[aIndex].ResetCount > Setting._MaxReset)
			{
				Func.MsgOutput(aIndex, 1, "[ Aviso ]: Sala exclusiva para até %d resets!", Setting._MaxReset);
				gObjCloseSet(aIndex, 2);
			}
		}
	}

	if (Setting._Announce[0] == 1 && gObj[aIndex].AuthorityCode == 0)
	{
		Func.Announce("| PLAYER | %s acabou de logar-se!", gObj[aIndex].Name);
	}

	if (Setting._Announce[1] == 1 && gObj[aIndex].AuthorityCode > 1)
	{
		Func.AllServerAnnounce(Message._Buffer[4], gObj[aIndex].Name);
	}

	Manager.CheckVault(aIndex, gObj[aIndex].AccountID);

	if (Custom[aIndex].Vault[1] == 0 && Command._Type == 1)
	{
		Manager.ExecFormat("UPDATE warehouse SET Count = Count + %d WHERE AccountID = '%s'", Command._Ware[Custom[aIndex].VipCount], gObj[aIndex].AccountID);

		Custom[aIndex].Vault[1] = Command._Ware[Custom[aIndex].VipCount];
	}

	Reward.Connect(aIndex);
	Quest.Connect(aIndex);
}

// [ Novo ]: Conta a quantidade de jogadores online para enviar ao Main
int ConnectServer::GetOnlineUserCount()
{
	int count = 0;

	for (int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if (gObj[i].Type == PLAYER && gObj[i].Connected == 3)
		{
			count++;
		}
	}

	return count;
}

// [ Novo ]: Atualiza as informações de Resets, Cash e Vip para o Main
void ConnectServer::UpdateCharacterInfo(int aIndex)
{
	if (aIndex < 0 || aIndex >= OBJECT_MAX)
	{
		return;
	}

	Manager.CoinCount(aIndex, gObj[aIndex].AccountID);
	Custom[aIndex].ResetCount = Manager.CountResets(gObj[aIndex].Name);
	Custom[aIndex].MasterCount = Manager.CountMasters(gObj[aIndex].Name);
	Custom[aIndex].MasterPoint = Manager.MasterPoint(gObj[aIndex].Name);
	Custom[aIndex].VipCount = Manager.VipCount(gObj[aIndex].AccountID);
	Custom[aIndex].VipDays = Manager.VipDays(gObj[aIndex].AccountID);

	Connect.GCCharacterInfoSend(aIndex);
}

// [ Novo ]: Printa as informações de Resets, Cash e Vip para o Main
void ConnectServer::GCCharacterInfoSend(int aIndex)
{
	if (aIndex < 0 || aIndex >= OBJECT_MAX)
	{
		return;
	}

	PMSG_CUSTOM_CHARACTER_INFO pMsg = { 0 };


	pMsg.h.set(0xF3, 0xE6, sizeof(pMsg));
	pMsg.Reset = Custom[aIndex].ResetCount;
	pMsg.MasterReset = Custom[aIndex].MasterCount;
	pMsg.MasterPoint = Custom[aIndex].MasterPoint;
	pMsg.Cash = Custom[aIndex].Coin[5];
	pMsg.EventPoint = Custom[aIndex].Coin[3];
	pMsg.Vip = Custom[aIndex].VipCount;
	pMsg.VipDays = Custom[aIndex].VipDays;
	pMsg.OnlineCount = GetOnlineUserCount();

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.h.size);
}

ConnectServer Connect;