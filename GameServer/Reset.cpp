#include "StdAfx.h"

cReset::cReset() : _Active(false)
{
}

bool cReset::Load()
{
	this->_Count = 0;

	memset(this->ResetStruct, 0, sizeof(this->ResetStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Reset.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Type = Section.Rows[0].GetInt(1);
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(2)));

		this->_Teleport[0] = Section.Rows[1].GetInt(0);
		this->_Teleport[1] = Section.Rows[2].GetInt(0);
		this->_Teleport[2] = Section.Rows[3].GetInt(0);
		this->_Teleport[3] = Section.Rows[4].GetInt(0);

		this->_Remove[0] = Section.Rows[1].GetInt(1);
		this->_Remove[1] = Section.Rows[2].GetInt(1);
		this->_Remove[2] = Section.Rows[3].GetInt(1);
		this->_Remove[3] = Section.Rows[4].GetInt(1);
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->ResetStruct[this->_Count]._VipCount = Section.Rows[i].GetInt(0);
			this->ResetStruct[this->_Count]._ResetsMin = Section.Rows[i].GetInt(1);
			this->ResetStruct[this->_Count]._ResetsMax = Section.Rows[i].GetInt(2);
			this->ResetStruct[this->_Count]._Points = Section.Rows[i].GetInt(3);
			this->ResetStruct[this->_Count]._Level = Section.Rows[i].GetInt(4);
			this->ResetStruct[this->_Count]._Money = Section.Rows[i].GetInt(5);
			this->_Count++;
		}
	}

	return true;
}

void cReset::Run(int aIndex)
{
	if (this->_Active)
	{
		int ResetCount = 0;

		if (HappyEvent._Event == false)
		{
			ResetCount = Manager.CountResets(gObj[aIndex].Name) + 1;
		}
		else
		{
			ResetCount = Manager.CountResets(gObj[aIndex].Name) + 2;
		}

		for (int i = 0; i < this->_Count; i++)
		{
			if (Custom[aIndex].VipCount == this->ResetStruct[i]._VipCount)
			{
				if (ResetCount >= this->ResetStruct[i]._ResetsMin && ResetCount <= this->ResetStruct[i]._ResetsMax || this->ResetStruct[i]._ResetsMax == -1)
				{
					if (gObj[aIndex].Level < this->ResetStruct[i]._Level)
					{
						Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->ResetStruct[i]._Level);
						return;
					}
					else if (gObj[aIndex].Money < this->ResetStruct[i]._Money)
					{
						Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->ResetStruct[i]._Money);
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

					Custom[aIndex].ResetCount = ResetCount;

					gObj[aIndex].Experience = 0;
					gObj[aIndex].Level = 1;

					WORD Class = gObj[aIndex].Class;

					gObj[aIndex].Money -= this->ResetStruct[i]._Money;

					GCMoneySend(aIndex, gObj[aIndex].Money);

					if (this->_Type == 2)
					{
						gObj[aIndex].LevelUpPoint = 0;

						for (int x = (i - 1); x >= 0; x--)
						{
							if (this->ResetStruct[x]._VipCount != this->ResetStruct[i]._VipCount) break;

							gObj[aIndex].LevelUpPoint += (this->ResetStruct[x]._ResetsMax - (this->ResetStruct[x]._ResetsMin - 1)) * this->ResetStruct[x]._Points;

							ResetCount -= this->ResetStruct[x]._ResetsMax - (this->ResetStruct[x]._ResetsMin - 1);
						}

						gObj[aIndex].LevelUpPoint += ResetCount * this->ResetStruct[i]._Points;

						gObj[aIndex].Strength = Class == 0 ? 18 : Class == 1 ? 28 : Class == 2 ? 22 : Class == 3 ? 26 : 26;
						gObj[aIndex].Dexterity = Class == 0 ? 18 : Class == 1 ? 20 : Class == 2 ? 25 : Class == 3 ? 26 : 20;
						gObj[aIndex].Vitality = Class == 0 ? 15 : Class == 1 ? 25 : Class == 2 ? 20 : Class == 3 ? 26 : 20;
						gObj[aIndex].Energy = Class == 0 ? 30 : Class == 1 ? 10 : Class == 2 ? 15 : Class == 3 ? 26 : 15;

					}

					if (this->_Teleport[Custom[aIndex].VipCount] == 1)
					{
						if (gObj[aIndex].MapNumber == 9 || gObj[aIndex].MapNumber >= 11 && gObj[aIndex].MapNumber <= 16)
						{
							// Empty
						}
						else
						{
							if (HappyEvent._Event == false)
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
						}
					}

					// correção mana e bp apos resetar

					gObj[aIndex].AddLife = 0;
					gObj[aIndex].AddMana = 0;
					gObj[aIndex].AddBP = 0;

					// recalcula primeiro
					gObj[aIndex].MaxLife = Func.GetStatus(&gObj[aIndex], Class, 0);
					gObj[aIndex].MaxMana = Func.GetStatus(&gObj[aIndex], Class, 1);
					gObjSetBP(aIndex);

					// depois preenche os atuais
					gObj[aIndex].Life = gObj[aIndex].MaxLife;
					gObj[aIndex].Mana = gObj[aIndex].MaxMana;
					gObj[aIndex].BP = gObj[aIndex].MaxBP / 2;

					// força recálculo completo antes de enviar
					gObjCalCharacter(aIndex);
					gObjCalcMaxLifePower(aIndex);

					Func.UpdateCharacter(aIndex, true);

					Manager.ExecFormat("UPDATE Character SET MasterPoint = MasterPoint +1 WHERE Name = '%s'", gObj[aIndex].Name);

					if (HappyEvent._Event == false)
					{
						Manager.ExecFormat(Query._Query[0], gObj[aIndex].Name);
					}
					else
					{
						Manager.ExecFormat("UPDATE Character SET Resets = Resets + 2, ResetsDay = ResetsDay + 2, ResetsWeek = ResetsWeek + 2, ResetsMonth = ResetsMonth + 2 WHERE Name = '%s'", gObj[aIndex].Name);
					}

					Connect.UpdateCharacterInfo(aIndex); // Envia as informações de Resets, Cash e Vip para o Main
					Func.MsgOutput(aIndex, 1, "Reset efetuado com sucesso!");
					Func.MsgOutput(aIndex, 1, "Resets: %d / Pontos: %d", Custom[aIndex].ResetCount, gObj[aIndex].LevelUpPoint);
				}
			}
		}
	}
}

cReset Reset;
