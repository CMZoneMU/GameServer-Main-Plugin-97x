#include "StdAfx.h"

void cPack::Gold(int aIndex, char* msg)
{
	memset(this->_Name, 0, sizeof(this->_Name));

	sscanf(msg, "%s", &this->_Name);

	if (strlen(msg) < 3 || this->_Name[0] == 0 || strcmpi(this->_Name, "pack") && strcmpi(this->_Name, "unpack"))
	{
		Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
		Func.MsgOutput(aIndex, 1, "Digite: /gold pack/unpack.");
		return;
	}

	if (!strcmpi(this->_Name, "pack"))
	{
		if (Func.CheckInventory(aIndex, ITEMGET(15, 16), 0) == 64)
		{
			Func.DeleteInventory(aIndex, ITEMGET(15, 16), 0, 64);

			ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(15, 17), 0, 0, 0, 0, 0, aIndex, 0);

			BYTE FireWork[] = { 0xC1, 0x07, 0xF3, 0x40, 0x00, 0x00, 0x00 };
			FireWork[5] = (BYTE)gObj[aIndex].X;
			FireWork[6] = (BYTE)gObj[aIndex].Y;

			DataSend(aIndex, (LPBYTE)(&FireWork), FireWork[1]);
		}
		else
		{
			Func.MsgOutput(aIndex, 1, "Necessário 64 Jewels Of Gold!");
		}
	}

	if (!strcmpi(this->_Name, "unpack"))
	{
		if (Func.CheckInventory(aIndex, ITEMGET(15, 17), 0) >= 1)
		{
			int Total = 63;

			int Check = Func.InventoryFullCheck(aIndex, ITEMGET(15, 16));

			if (Total > Check)
			{
				Total = Check;
			}

			if (Total == 63)
			{
				Func.DeleteInventory(aIndex, ITEMGET(15, 17), 0, 1);

				for (int i = 0; i < 64; i++)
				{
					ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(15, 16), 0, 0, 0, 0, 0, aIndex, 0);
				}

				BYTE FireWork[] = { 0xC1, 0x07, 0xF3, 0x40, 0x00, 0x00, 0x00 };
				FireWork[5] = (BYTE)gObj[aIndex].X;
				FireWork[6] = (BYTE)gObj[aIndex].Y;

				DataSend(aIndex, (LPBYTE)(&FireWork), FireWork[1]);
			}
			else
			{
				Func.MsgOutput(aIndex, 1, "O inventário está cheio!");
			}
		}
	}
}

cPack Pack;