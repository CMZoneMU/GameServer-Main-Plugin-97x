#pragma once

struct PMSG_CUSTOM_CHARACTER_INFO_SEND
{
	PBMSG_HEAD h;
	int Reset;
	int MasterReset;
	int MasterPoint;
	int Cash;
	int EventPoint;
	int Vip;
	int VipDays;
};

class ConnectServer
{
public:
	void PlayerConnect(int aIndex);
	void GCCharacterInfoSend(int aIndex);
	void UpdateCharacterInfo(int aIndex); // [ Novo ]: Atualiza as informações de Resets, Cash e Vip para o Main
	int  GetOnlineUserCount(); // [ Novo ]: Conta a quantidade de jogadores online para enviar ao Main
};

extern ConnectServer Connect;