#include "StdAfx.h"

bool cCollector::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Collector.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Section = Section.Rows[0].GetInt(1);
	}

	if (Group.GetSection(1, Section))
	{
		this->_Type[0] = Section.Rows[0].GetInt(0);
		this->_Index[0] = Section.Rows[0].GetInt(1);
		this->_Level[0] = Section.Rows[0].GetInt(2);
		this->_Quantity[0] = Section.Rows[0].GetInt(3);
		this->_Value[0] = Section.Rows[0].GetInt(4);
		strcpy_s(&this->_Name[0][0], sizeof(this->_Name[0]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(&this->_Coin[0][0], sizeof(this->_Coin[0]), (Section.Rows[0].GetStringPtr(6)));
	}

	if (Group.GetSection(2, Section))
	{
		this->_Type[1] = Section.Rows[0].GetInt(0);
		this->_Index[1] = Section.Rows[0].GetInt(1);
		this->_Level[1] = Section.Rows[0].GetInt(2);
		this->_Quantity[1] = Section.Rows[0].GetInt(3);
		this->_Value[1] = Section.Rows[0].GetInt(4);
		strcpy_s(&this->_Name[1][0], sizeof(this->_Name[1]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(&this->_Coin[1][0], sizeof(this->_Coin[1]), (Section.Rows[0].GetStringPtr(6)));
	}

	if (Group.GetSection(3, Section))
	{
		this->_Type[2] = Section.Rows[0].GetInt(0);
		this->_Index[2] = Section.Rows[0].GetInt(1);
		this->_Level[2] = Section.Rows[0].GetInt(2);
		this->_Quantity[2] = Section.Rows[0].GetInt(3);
		this->_Value[2] = Section.Rows[0].GetInt(4);
		strcpy_s(&this->_Name[2][0], sizeof(this->_Name[2]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(&this->_Coin[2][0], sizeof(this->_Coin[2]), (Section.Rows[0].GetStringPtr(6)));
	}

	if (Group.GetSection(4, Section))
	{
		this->_Type[3] = Section.Rows[0].GetInt(0);
		this->_Index[3] = Section.Rows[0].GetInt(1);
		this->_Level[3] = Section.Rows[0].GetInt(2);
		this->_Quantity[3] = Section.Rows[0].GetInt(3);
		this->_Value[3] = Section.Rows[0].GetInt(4);
		strcpy_s(&this->_Name[3][0], sizeof(this->_Name[3]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(&this->_Coin[3][0], sizeof(this->_Coin[3]), (Section.Rows[0].GetStringPtr(6)));
	}

	if (Group.GetSection(5, Section))
	{
		this->_Type[4] = Section.Rows[0].GetInt(0);
		this->_Index[4] = Section.Rows[0].GetInt(1);
		this->_Level[4] = Section.Rows[0].GetInt(2);
		this->_Quantity[4] = Section.Rows[0].GetInt(3);
		this->_Value[4] = Section.Rows[0].GetInt(4);
		strcpy_s(&this->_Name[4][0], sizeof(this->_Name[4]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(&this->_Coin[4][0], sizeof(this->_Coin[4]), (Section.Rows[0].GetStringPtr(6)));
	}

	return true;
}

void cCollector::Talk(OBJECTSTRUCT* Npc, OBJECTSTRUCT* lpObj)
{
	if (!this->_Active)
	{
		ChatTargetSend(Npc, "Fui desabilitado.", lpObj->m_Index);
		return;
	}

	INT Item1 = ITEMGET(this->_Type[0], this->_Index[0]);
	INT Item2 = ITEMGET(this->_Type[1], this->_Index[1]);
	INT Item3 = ITEMGET(this->_Type[2], this->_Index[2]);
	INT Item4 = ITEMGET(this->_Type[3], this->_Index[3]);
	INT Item5 = ITEMGET(this->_Type[4], this->_Index[4]);

	if (Func.CheckInventory(lpObj->m_Index, Item1, this->_Level[0]) >= this->_Quantity[0] && this->_Section >= 1)
	{
		Func.DeleteInventory(lpObj->m_Index, Item1, this->_Level[0], this->_Quantity[0]);

		Manager.ExecFormat(Query._Query[19], this->_Value[0], lpObj->AccountID);

		Connect.UpdateCharacterInfo(lpObj->m_Index); // Collector cpp

		if (this->_Quantity[0] > 1)
		{
			sprintf_s(this->_Buffer, "%s coletadas com sucesso.", this->_Name[0]);
			ChatTargetSend(Npc, this->_Buffer, lpObj->m_Index);
		}
		else
		{
			sprintf_s(this->_Buffer, "%s coletada com sucesso.", this->_Name[0]);
			ChatTargetSend(Npc, this->_Buffer, lpObj->m_Index);
		}

		Func.MsgOutput(lpObj->m_Index, 1, "Prêmio: %d %s", this->_Value[0], this->_Coin[0]);
	}

	if (Func.CheckInventory(lpObj->m_Index, Item2, this->_Level[1]) >= this->_Quantity[1] && this->_Section >= 2)
	{
		Func.DeleteInventory(lpObj->m_Index, Item2, this->_Level[1], this->_Quantity[1]);

		Manager.ExecFormat(Query._Query[19], this->_Value[1], lpObj->AccountID);

		Connect.UpdateCharacterInfo(lpObj->m_Index); // Collector cpp

		if (this->_Quantity[1] > 1)
		{
			sprintf_s(this->_Buffer, "%s coletadas com sucesso.", this->_Name[1]);
			ChatTargetSend(Npc, this->_Buffer, lpObj->m_Index);
		}
		else
		{
			sprintf_s(this->_Buffer, "%s coletada com sucesso.", this->_Name[1]);
			ChatTargetSend(Npc, this->_Buffer, lpObj->m_Index);
		}

		Func.MsgOutput(lpObj->m_Index, 1, "Prêmio: %d %s", this->_Value[1], this->_Coin[1]);
	}

	if (Func.CheckInventory(lpObj->m_Index, Item3, this->_Level[2]) >= this->_Quantity[2] && this->_Section >= 3)
	{
		Func.DeleteInventory(lpObj->m_Index, Item3, this->_Level[2], this->_Quantity[2]);

		Manager.ExecFormat(Query._Query[19], this->_Value[2], lpObj->AccountID);

		Connect.UpdateCharacterInfo(lpObj->m_Index); // Collector cpp

		if (this->_Quantity[2] > 1)
		{
			sprintf_s(this->_Buffer, "%s coletadas com sucesso.", this->_Name[2]);
			ChatTargetSend(Npc, this->_Buffer, lpObj->m_Index);
		}
		else
		{
			sprintf_s(this->_Buffer, "%s coletada com sucesso.", this->_Name[2]);
			ChatTargetSend(Npc, this->_Buffer, lpObj->m_Index);
		}

		Func.MsgOutput(lpObj->m_Index, 1, "Prêmio: %d %s", this->_Value[2], this->_Coin[2]);
	}

	if (Func.CheckInventory(lpObj->m_Index, Item4, this->_Level[3]) >= this->_Quantity[3] && this->_Section >= 4)
	{
		Func.DeleteInventory(lpObj->m_Index, Item4, this->_Level[3], this->_Quantity[3]);

		Manager.ExecFormat(Query._Query[19], this->_Value[3], lpObj->AccountID);

		Connect.UpdateCharacterInfo(lpObj->m_Index); // Collector cpp

		if (this->_Quantity[3] > 1)
		{
			sprintf_s(this->_Buffer, "%s coletadas com sucesso.", this->_Name[3]);
			ChatTargetSend(Npc, this->_Buffer, lpObj->m_Index);
		}
		else
		{
			sprintf_s(this->_Buffer, "%s coletada com sucesso.", this->_Name[3]);
			ChatTargetSend(Npc, this->_Buffer, lpObj->m_Index);
		}

		Func.MsgOutput(lpObj->m_Index, 1, "Prêmio: %d %s", this->_Value[3], this->_Coin[3]);
	}

	if (Func.CheckInventory(lpObj->m_Index, Item5, this->_Level[4]) >= this->_Quantity[4] && this->_Section == 5)
	{
		Func.DeleteInventory(lpObj->m_Index, Item5, this->_Level[4], this->_Quantity[4]);

		Manager.ExecFormat(Query._Query[19], this->_Value[4], lpObj->AccountID);

		Connect.UpdateCharacterInfo(lpObj->m_Index); // Collector cpp

		if (this->_Quantity[4] > 1)
		{
			sprintf_s(this->_Buffer, "%s coletadas com sucesso.", this->_Name[4]);
			ChatTargetSend(Npc, this->_Buffer, lpObj->m_Index);
		}
		else
		{
			sprintf_s(this->_Buffer, "%s coletada com sucesso.", this->_Name[4]);
			ChatTargetSend(Npc, this->_Buffer, lpObj->m_Index);
		}

		Func.MsgOutput(lpObj->m_Index, 1, "Prêmio: %d %s", this->_Value[4], this->_Coin[4]);
	}

	ChatTargetSend(Npc, "Volte quando tiver o necessário para a troca.", lpObj->m_Index);

	Func.MsgOutput(lpObj->m_Index, 0, "[    TABELA    ]");

	if (this->_Section >= 1)
	{
		Func.MsgOutput(lpObj->m_Index, 0, "%d %s = %d %s", this->_Quantity[0], this->_Name[0], this->_Value[0], this->_Coin[0]);
	}

	if (this->_Section >= 2)
	{
		Func.MsgOutput(lpObj->m_Index, 0, "%d %s = %d %s", this->_Quantity[1], this->_Name[1], this->_Value[1], this->_Coin[1]);
	}

	if (this->_Section >= 3)
	{
		Func.MsgOutput(lpObj->m_Index, 0, "%d %s = %d %s", this->_Quantity[2], this->_Name[2], this->_Value[2], this->_Coin[2]);
	}

	if (this->_Section >= 4)
	{
		Func.MsgOutput(lpObj->m_Index, 0, "%d %s = %d %s", this->_Quantity[3], this->_Name[3], this->_Value[3], this->_Coin[3]);
	}

	if (this->_Section == 5)
	{
		Func.MsgOutput(lpObj->m_Index, 0, "%d %s = %d %s", this->_Quantity[4], this->_Name[4], this->_Value[4], this->_Coin[4]);
	}
}

cCollector Collector;