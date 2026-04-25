#include "StdAfx.h"

cBonus::cBonus() : _Active(false), _LevelUpPoint(0), _Resets(0), _Money(0)
{
}

bool cBonus::Load()
{
	this->_Count = 0;

	memset(this->BonusStruct, 0, sizeof(this->BonusStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Bonus.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_LevelUpPoint = Section.Rows[0].GetInt(1);
		this->_Resets = Section.Rows[0].GetInt(2);
		this->_Money = Section.Rows[0].GetInt(3);

		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(4)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->BonusStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->BonusStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->BonusStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			this->BonusStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			this->BonusStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			this->BonusStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			this->BonusStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->BonusStruct[this->_Count]._Class = Section.Rows[i].GetInt(7);
			this->_Count++;
		}
	}

	return true;
}

void cBonus::Command(int aIndex)
{
	if (this->_Active)
	{
		if (Custom[aIndex].Bonus == 0)
		{
			if (this->_Count > 0)
			{
				for (int i = 0; i < this->_Count; i++)
				{
					if (gObj[aIndex].Class == this->BonusStruct[i]._Class)
					{
						int Item = ITEMGET(this->BonusStruct[i]._Type, this->BonusStruct[i]._Index);

						if (!Func.InventoryFullCheck(aIndex, Item))
						{
							Func.MsgOutput(aIndex, 1, "O inventário está cheio!");
							return;
						}

						ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, this->BonusStruct[i]._Level, 0, this->BonusStruct[i]._Skill, this->BonusStruct[i]._Luck, this->BonusStruct[i]._Option, aIndex, this->BonusStruct[i]._Excelente);
					}
				}
			}

			if (this->_LevelUpPoint > 0)
			{
				gObj[aIndex].LevelUpPoint += this->_LevelUpPoint;
			}
			else if (this->_LevelUpPoint == -1)
			{
				gObj[aIndex].Strength = 32767;
				gObj[aIndex].Dexterity = 32767;
				gObj[aIndex].Vitality = 32767;
				gObj[aIndex].Energy = 32767;
			}

			if (this->_Resets > 0)
			{
				Custom[aIndex].ResetCount += this->_Resets;

				Manager.ExecFormat("UPDATE Character SET Resets = Resets + %d WHERE Name = '%s'", this->_Resets, gObj[aIndex].Name);
			}

			if (this->_Money > 0)
			{
				GCMoneySend(aIndex, gObj[aIndex].Money += this->_Money);
			}

			switch (gObj[aIndex].Class)
			{
			case 0:
			{
				gObj[aIndex].Class = WIZARD;
				gObj[aIndex].ChangeUP = 1;
				gObj[aIndex].DBClass = 1;

				BYTE Class = (gObj[aIndex].Class << 5) & 0xE0;
				Class |= (gObj[aIndex].ChangeUP << 4) & 0x10;

				GCSendQuestPrize(gObj[aIndex].m_Index, 201, Class);
			}
			break;
			case 1:
			{
				gObj[aIndex].Class = KNIGHT;
				gObj[aIndex].ChangeUP = 1;
				gObj[aIndex].DBClass = 17;

				BYTE Class = (gObj[aIndex].Class << 5) & 0xE0;
				Class |= (gObj[aIndex].ChangeUP << 4) & 0x10;

				GCSendQuestPrize(gObj[aIndex].m_Index, 201, Class);
			}
			break;
			case 2:
			{
				gObj[aIndex].Class = ELF;
				gObj[aIndex].ChangeUP = 1;
				gObj[aIndex].DBClass = 33;

				BYTE Class = (gObj[aIndex].Class << 5) & 0xE0;
				Class |= (gObj[aIndex].ChangeUP << 4) & 0x10;

				GCSendQuestPrize(gObj[aIndex].m_Index, 201, Class);
			}
			break;
			}

			Custom[aIndex].Bonus++;

			Manager.ExecFormat("UPDATE MEMB_INFO SET Bonus = Bonus + 1 WHERE memb___id = '%s'", gObj[aIndex].AccountID);

			gObjMakePreviewCharSet(aIndex);

			gObjClearViewport(&gObj[aIndex]);
			gObjViewportListProtocolCreate(&gObj[aIndex]);

			Func.UpdateCharacter(aIndex, false);

			Func.MsgOutput(aIndex, 1, "Bônus resgatado com sucesso.");
		}
		else
		{
			Func.MsgOutput(aIndex, 1, "Seu bônus já foi resgatado.");
		}
	}
}

cBonus Bonus;