#include "StdAfx.h"

void WareHouse(OBJECTSTRUCT* Npc, OBJECTSTRUCT* lpObj)
{
	if (Block.BlockStruct[lpObj->m_Index]._Active == 1)
	{
		ChatTargetSend(Npc, "Conta protegida por senha!", lpObj->m_Index);
		return;
	}

	Custom[lpObj->m_Index].Delay[1] = (GetTickCount() - Custom[lpObj->m_Index].Delay[2]) / 1000;

	if (Custom[lpObj->m_Index].Delay[1] < 5 && lpObj->m_ReqWarehouseOpen == true)
	{
		sprintf_s(Command._Buffer, "Aguarde %d %s para usar o baú.", (5 - Custom[lpObj->m_Index].Delay[1]), (5 - Custom[lpObj->m_Index].Delay[1] == 1) ? "segundo" : "segundos");
		ChatTargetSend(Npc, Command._Buffer, lpObj->m_Index);
		return;
	}
	else
	{
		lpObj->m_ReqWarehouseOpen = 1;
		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 6;
		lpObj->m_IfState.state = 0;

		GDGetWarehouseList(lpObj->m_Index, lpObj->AccountID);

		Manager.ExecFormat("UPDATE warehouse SET CheckVault = 1 WHERE AccountID = '%s'", lpObj->AccountID);

		ChatTargetSend(Npc, "Deixe seus itens comigo, aqui estarão seguros!", lpObj->m_Index);
	}
}