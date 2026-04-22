#include "StdAfx.h"

cMaster::cMaster() : _Active(false)
{
}

bool cMaster::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Master.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(1)));

		this->_Level[0] = Section.Rows[1].GetInt(0);
		this->_Zen[0] = Section.Rows[1].GetInt(1);
		this->_Remove[0] = Section.Rows[1].GetInt(2);
		this->_Return[0] = Section.Rows[1].GetInt(3);
		this->_NeedFor[0] = Section.Rows[1].GetInt(4);
		this->_NeedAgi[0] = Section.Rows[1].GetInt(5);
		this->_NeedVit[0] = Section.Rows[1].GetInt(6);
		this->_NeedEne[0] = Section.Rows[1].GetInt(7);
		this->_Resets[0] = Section.Rows[1].GetInt(8);

		this->_Level[1] = Section.Rows[2].GetInt(0);
		this->_Zen[1] = Section.Rows[2].GetInt(1);
		this->_Remove[1] = Section.Rows[2].GetInt(2);
		this->_Return[1] = Section.Rows[2].GetInt(3);
		this->_NeedFor[1] = Section.Rows[2].GetInt(4);
		this->_NeedAgi[1] = Section.Rows[2].GetInt(5);
		this->_NeedVit[1] = Section.Rows[2].GetInt(6);
		this->_NeedEne[1] = Section.Rows[2].GetInt(7);
		this->_Resets[1] = Section.Rows[2].GetInt(8);

		this->_Level[2] = Section.Rows[3].GetInt(0);
		this->_Zen[2] = Section.Rows[3].GetInt(1);
		this->_Remove[2] = Section.Rows[3].GetInt(2);
		this->_Return[2] = Section.Rows[3].GetInt(3);
		this->_NeedFor[2] = Section.Rows[3].GetInt(4);
		this->_NeedAgi[2] = Section.Rows[3].GetInt(5);
		this->_NeedVit[2] = Section.Rows[3].GetInt(6);
		this->_NeedEne[2] = Section.Rows[3].GetInt(7);
		this->_Resets[2] = Section.Rows[3].GetInt(8);

		this->_Level[3] = Section.Rows[4].GetInt(0);
		this->_Zen[3] = Section.Rows[4].GetInt(1);
		this->_Remove[3] = Section.Rows[4].GetInt(2);
		this->_Return[3] = Section.Rows[4].GetInt(3);
		this->_NeedFor[3] = Section.Rows[4].GetInt(4);
		this->_NeedAgi[3] = Section.Rows[4].GetInt(5);
		this->_NeedVit[3] = Section.Rows[4].GetInt(6);
		this->_NeedEne[3] = Section.Rows[4].GetInt(7);
		this->_Resets[3] = Section.Rows[4].GetInt(8);
	}

	return true;
}

void cMaster::Run(int aIndex)
{
	if (this->_Active)
	{
		if (this->_Level[Custom[aIndex].VipCount] > gObj[aIndex].Level)
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[Custom[aIndex].VipCount]);
			return;
		}
		else if (this->_Zen[Custom[aIndex].VipCount] > gObj[aIndex].Money)
		{
			Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[Custom[aIndex].VipCount]);
			return;
		}
		else if (this->_Remove[Custom[aIndex].VipCount] == 0 && !Func.CheckItem(&gObj[aIndex]))
		{
			Func.MsgOutput(aIndex, 1, "Remova todos os itens.");
			return;
		}
		else if (Custom[aIndex].InEvent == true || DeathEvent.PlayerStruct[aIndex]._InEvent == true || TheftEvent.PlayerStruct[aIndex]._InEvent == true || FlagEvent.PlayerStruct[aIndex]._InEvent == true || RoletaEvent.PlayerStruct[aIndex]._InEvent == true || BattleEvent.PlayerStruct[aIndex]._InEvent == true)
		{
			Func.MsgOutput(aIndex, 1, "Proibido usar o comando no evento.");
			return;
		}
		else if (Duel.DuelStruct[aIndex]._Duel == true)
		{
			Func.MsgOutput(aIndex, 1, "Proibido usar o comando no duelo.");
			return;
		}
		else if (gObj[aIndex].Strength < this->_NeedFor[Custom[aIndex].VipCount] && this->_NeedFor[Custom[aIndex].VipCount] > 0)
		{
			Func.MsgOutput(aIndex, 1, "Você não possui força %d", this->_NeedFor[Custom[aIndex].VipCount]);
			return;
		}
		else if (gObj[aIndex].Dexterity < this->_NeedAgi[Custom[aIndex].VipCount] && this->_NeedAgi[Custom[aIndex].VipCount] > 0)
		{
			Func.MsgOutput(aIndex, 1, "Você não possui agilidade %d", this->_NeedAgi[Custom[aIndex].VipCount]);
			return;
		}
		else if (gObj[aIndex].Vitality < this->_NeedVit[Custom[aIndex].VipCount] && this->_NeedVit[Custom[aIndex].VipCount] > 0)
		{
			Func.MsgOutput(aIndex, 1, "Você não possui vitalidade %d", this->_NeedVit[Custom[aIndex].VipCount]);
			return;
		}
		else if (gObj[aIndex].Energy < this->_NeedEne[Custom[aIndex].VipCount] && this->_NeedEne[Custom[aIndex].VipCount] > 0)
		{
			Func.MsgOutput(aIndex, 1, "Você não possui energia %d", this->_NeedEne[Custom[aIndex].VipCount]);
			return;
		}

		Custom[aIndex].MasterPoint = Manager.MasterPoint(gObj[aIndex].Name);

		if (Custom[aIndex].MasterPoint < this->_Resets[Custom[aIndex].VipCount] && this->_Resets[Custom[aIndex].VipCount] > 0)
		{
			Func.MsgOutput(aIndex, 1, "Necessário %d Master Points!", this->_Resets[Custom[aIndex].VipCount]);
			return;
		}
		
		Custom[aIndex].MasterCount = Manager.CountMasters(gObj[aIndex].Name) + 1;

		gObj[aIndex].Experience = 0;

		gObj[aIndex].Level = 1;

		gObj[aIndex].LevelUpPoint = 0;

		gObj[aIndex].Money -= this->_Zen[Custom[aIndex].VipCount];

		GCMoneySend(aIndex, gObj[aIndex].Money);

		Manager.ExecFormat("UPDATE Character SET MasterPoint = MasterPoint - %d WHERE Name = '%s'", this->_Resets[Custom[aIndex].VipCount], gObj[aIndex].Name);

		Custom[aIndex].MasterPoint -= this->_Resets[Custom[aIndex].VipCount];

		WORD Class = gObj[aIndex].Class;

		gObj[aIndex].Strength = Class == 0 ? 18 : Class == 1 ? 28 : Class == 2 ? 22 : Class == 3 ? 26 : 26;
		gObj[aIndex].Dexterity = Class == 0 ? 18 : Class == 1 ? 20 : Class == 2 ? 25 : Class == 3 ? 26 : 20;
		gObj[aIndex].Vitality = Class == 0 ? 15 : Class == 1 ? 25 : Class == 2 ? 20 : Class == 3 ? 26 : 20;
		gObj[aIndex].Energy = Class == 0 ? 30 : Class == 1 ? 10 : Class == 2 ? 15 : Class == 3 ? 26 : 15;

		Manager.ExecFormat(Query._Query[1], gObj[aIndex].Name);

		switch (Custom[aIndex].VipCount)
		{
		case 0:
		{
			Manager.ExecFormat(Query._Query[2], gObj[aIndex].AccountID);
		}
		break;
		case 1:
		{
			Manager.ExecFormat(Query._Query[3], gObj[aIndex].AccountID);
		}
		break;
		case 2:
		{
			Manager.ExecFormat(Query._Query[4], gObj[aIndex].AccountID);
		}
		break;
		case 3:
		{
			Manager.ExecFormat(Query._Query[5], gObj[aIndex].AccountID);
		}
		break;
		}

		if (this->_Return[Custom[aIndex].VipCount] == 1)
		{
			if (gObj[aIndex].Class == ELF)
			{
				int X = 171 + rand() % 6;
				int Y = 108 + rand() % 8;

				gObjTeleport(aIndex, 3, X, Y);
			}
			else
			{
				int X = 133 + rand() % 15;
				int Y = 118 + rand() % 15;

				gObjTeleport(aIndex, 0, X, Y);
			}
		}

		// [Novo]: Correção mana e bp apos resetar

		gObj[aIndex].AddLife = 0;
		gObj[aIndex].AddMana = 0;
		gObj[aIndex].AddBP = 0;

		// [Novo]: Recalcula primeiro
		gObj[aIndex].MaxLife = Func.GetStatus(&gObj[aIndex], Class, 0);
		gObj[aIndex].MaxMana = Func.GetStatus(&gObj[aIndex], Class, 1);
		gObjSetBP(aIndex);

		// [Novo]: Depois preenche os atuais
		gObj[aIndex].Life = gObj[aIndex].MaxLife;
		gObj[aIndex].Mana = gObj[aIndex].MaxMana;
		gObj[aIndex].BP = gObj[aIndex].MaxBP / 2;

		// [Novo]: Força recálculo completo antes de enviar
		gObjCalCharacter(aIndex);
		gObjCalcMaxLifePower(aIndex);

		Func.UpdateCharacter(aIndex, true);

		Func.MsgOutput(aIndex, 1, "Master reset efetuado com sucesso!");

		if (this->_Resets[Custom[aIndex].VipCount] > 0 || this->_Resets[Custom[aIndex].VipCount] == -1)
		{
			Func.MsgOutput(aIndex, 1, "Master resets: %d / Master Points: %d", Custom[aIndex].MasterCount, Custom[aIndex].MasterPoint);
		}
	}
}

cMaster Master;