#include "StdAfx.h"

bool cDupe::Serial(LPOBJ lpObj, DWORD Serial, int Local)
{
	this->_Count[0] = 0; this->_Count[1] = 0;

	if (Local == 0)
	{
		for (int i = 0; i < 76; i++)
		{
			if (lpObj->pInventory[i].IsItem() == TRUE)
			{
				int Number = lpObj->pInventory[i].m_Number;

				if (Number != 0 && Number == Serial)
				{
					this->_Count[0]++;
				}
			}
		}
	}

	if (Local == 1)
	{
		for (int i = 0; i < 120; i++)
		{
			if (lpObj->pWarehouse[i].IsItem() == TRUE)
			{
				int Number = lpObj->pWarehouse[i].m_Number;

				if (Number != 0 && Number == Serial)
				{
					this->_Count[1]++;
				}
			}
		}
	}

	if (this->_Count[0] > 1 || this->_Count[1] > 1)
	{
		return false;
	}

	return true;
}

void cDupe::Run(LPOBJ lpObj)
{
	this->_Detected = false;

	for (int i = 0; i < 76; i++)
	{
		if (lpObj->pInventory[i].IsItem() == TRUE)
		{
			DWORD Number = lpObj->pInventory[i].m_Number;

			if (this->Serial(lpObj, Number, 0) == false)
			{
				gObjInventoryDeleteItem(lpObj->m_Index, i);

				GCInventoryItemDeleteSend(lpObj->m_Index, i, 1);

				this->_Detected = true;
			}
		}
	}

	for (int i = 0; i < 120; i++)
	{
		if (lpObj->pWarehouse[i].IsItem() == TRUE)
		{
			DWORD Number = lpObj->pWarehouse[i].m_Number;

			if (this->Serial(lpObj, Number, 1) == false)
			{
				gObjWarehouseDeleteItem(lpObj->m_Index, i);

				CGWarehouseUseEnd(lpObj->m_Index);

				this->_Detected = true;
			}
		}
	}

	for (int i = 0; i < 76; i++)
	{
		for (int w = 0; w < 120; w++)
		{
			if (lpObj->pInventory[i].IsItem() == TRUE)
			{
				if (lpObj->pWarehouse[w].IsItem() == TRUE)
				{
					if (lpObj->pWarehouse[w].m_Number == lpObj->pInventory[i].m_Number && lpObj->pInventory[i].m_Number != 0)
					{
						gObjInventoryDeleteItem(lpObj->m_Index, i);

						GCInventoryItemDeleteSend(lpObj->m_Index, i, 1);

						this->_Detected = true;

					}
				}
			}
		}
	}

	if (this->_Detected == true)
	{
		Func.MsgOutput(lpObj->m_Index, 1, "Item dupados encontrado. Apagados.");
	}
}

cDupe Dupe;