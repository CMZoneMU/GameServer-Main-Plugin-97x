#include "StdAfx.h"

bool cAutoReset::Load()
{
	Tokenizer Token;
	TokenizerGroup Group;
	TokenizerSection Section;

	Token.ParseFile(std::string("./Data/Auto.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Type = Section.Rows[0].GetInt(1);
		this->_VipCount = Section.Rows[0].GetInt(2);
		this->_Money = Section.Rows[0].GetInt(3);
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), Section.Rows[0].GetStringPtr(4));
	}

	return true;
}

void cAutoReset::Run(LPOBJ lpObj)
{
	if (this->AutoStruct[lpObj->m_Index]._Active == true)
	{
		for (int i = 0; i < Reset._Count; i++)
		{
			if (Custom[lpObj->m_Index].VipCount == Reset.ResetStruct[i]._VipCount)
			{
				if (lpObj->Level >= Reset.ResetStruct[i]._Level)
				{
					Reset.Run(lpObj->m_Index);

					// [ Novo ]: Verificar se o char tem pontos para distribuir
					// antes de aplicar o Auto Add
					if (this->AutoStruct[lpObj->m_Index]._Strength > 0 ||
						this->AutoStruct[lpObj->m_Index]._Dexterity > 0 ||
						this->AutoStruct[lpObj->m_Index]._Vitality > 0 ||
						this->AutoStruct[lpObj->m_Index]._Energy > 0)
					{
						const int MaxStat = 32767;

						int AddStr = this->AutoStruct[lpObj->m_Index]._Strength;
						int AddDex = this->AutoStruct[lpObj->m_Index]._Dexterity;
						int AddVit = this->AutoStruct[lpObj->m_Index]._Vitality;
						int AddEne = this->AutoStruct[lpObj->m_Index]._Energy;

						//  [ Novo ]: Bloquear o aumento de status caso o char ja esteja com o 
						// status maximo para evitar o gasto desnecessário de pontos
						if (lpObj->Strength >= MaxStat) AddStr = 0;
						else if ((lpObj->Strength + AddStr) > MaxStat) AddStr = MaxStat - lpObj->Strength;

						if (lpObj->Dexterity >= MaxStat) AddDex = 0;
						else if ((lpObj->Dexterity + AddDex) > MaxStat) AddDex = MaxStat - lpObj->Dexterity;

						if (lpObj->Vitality >= MaxStat) AddVit = 0;
						else if ((lpObj->Vitality + AddVit) > MaxStat) AddVit = MaxStat - lpObj->Vitality;

						if (lpObj->Energy >= MaxStat) AddEne = 0;
						else if ((lpObj->Energy + AddEne) > MaxStat) AddEne = MaxStat - lpObj->Energy;

						// [ Novo ]: Verificar se o char ja esta full antes de aplicar os 
						// status para evitar o gasto desnecessário de pontos
						if (lpObj->Strength >= MaxStat &&
							lpObj->Dexterity >= MaxStat &&
							lpObj->Vitality >= MaxStat &&
							lpObj->Energy >= MaxStat)
						{
							Func.MsgOutput(lpObj->m_Index, 1, "Voce atingiu limite de pontos nos Status");

							this->AutoStruct[lpObj->m_Index]._Active = false;
							this->AutoStruct[lpObj->m_Index]._Points = 0;
							this->AutoStruct[lpObj->m_Index]._Strength = 0;
							this->AutoStruct[lpObj->m_Index]._Dexterity = 0;
							this->AutoStruct[lpObj->m_Index]._Vitality = 0;
							this->AutoStruct[lpObj->m_Index]._Energy = 0;
							return;
						}

						this->AutoStruct[lpObj->m_Index]._Points = AddStr + AddDex + AddVit + AddEne;

						// NADA PRA SOMAR
						if (this->AutoStruct[lpObj->m_Index]._Points <= 0)
						{
							return;
						}

						// SEM PONTOS DISPONÍVEIS
						if (this->AutoStruct[lpObj->m_Index]._Points > lpObj->LevelUpPoint)
						{
							return;
						}

						// APLICAR STATUS
						lpObj->Strength += AddStr;
						lpObj->Dexterity += AddDex;
						lpObj->Vitality += AddVit;
						lpObj->Energy += AddEne;

						lpObj->MaxLife += lpObj->VitalityToLife * AddVit;
						lpObj->Life = lpObj->MaxLife;
						lpObj->AddLife = 0;

						lpObj->MaxMana += lpObj->EnergyToMana * AddEne;
						lpObj->Mana = lpObj->MaxMana;
						lpObj->AddMana = 0;

						gObjSetBP(lpObj->m_Index);
						lpObj->BP = lpObj->MaxBP / 2;
						lpObj->AddBP = 0;

						lpObj->LevelUpPoint -= this->AutoStruct[lpObj->m_Index]._Points;

						Func.UpdateCharacter(lpObj->m_Index, false);

						// CHECAR NOVAMENTE FULL
						if (lpObj->Strength >= MaxStat &&
							lpObj->Dexterity >= MaxStat &&
							lpObj->Vitality >= MaxStat &&
							lpObj->Energy >= MaxStat)
						{
							Func.MsgOutput(lpObj->m_Index, 1, "Voce atingiu limite de pontos nos Status");

							this->AutoStruct[lpObj->m_Index]._Active = false;
							this->AutoStruct[lpObj->m_Index]._Points = 0;
							this->AutoStruct[lpObj->m_Index]._Strength = 0;
							this->AutoStruct[lpObj->m_Index]._Dexterity = 0;
							this->AutoStruct[lpObj->m_Index]._Vitality = 0;
							this->AutoStruct[lpObj->m_Index]._Energy = 0;
							return;
						}
					}
				}
			}
		}
	}
}

void cAutoReset::Command(int aIndex, char* msg)
{
	if (this->_Active == true)
	{
		if (Custom[aIndex].VipCount < this->_VipCount)
		{
			Func.MsgOutput(aIndex, 1, "[ Aviso ]: Voce nao possui o plano vip necessario!");
			return;
		}

		memset(this->_Name, 0, sizeof(this->_Name));

		int Count = 0;

		if (this->AutoStruct[aIndex]._Active == false)
		{
			Count = sscanf(msg, "%s %d %d %d %d",
				this->_Name,
				&this->AutoStruct[aIndex]._Strength,
				&this->AutoStruct[aIndex]._Dexterity,
				&this->AutoStruct[aIndex]._Vitality,
				&this->AutoStruct[aIndex]._Energy);
		}
		else
		{
			Count = sscanf(msg, "%s", this->_Name);
		}

		if (strlen(msg) < 2 || strcmpi(this->_Name, "on") && strcmpi(this->_Name, "off"))
		{
			Func.MsgOutput(aIndex, 1, "[ Aviso ]: Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "[ Aviso ]: Digite: %s on/off.", this->_Syntax);
			Func.MsgOutput(aIndex, 1, "[ Aviso ]: Ou: %s on <For> <Agi> <Vit> <Ene>", this->_Syntax);
			return;
		}

		if (!strcmpi(this->_Name, "off"))
		{
			this->AutoStruct[aIndex]._Points = 0;
			this->AutoStruct[aIndex]._Strength = 0;
			this->AutoStruct[aIndex]._Dexterity = 0;
			this->AutoStruct[aIndex]._Vitality = 0;
			this->AutoStruct[aIndex]._Energy = 0;
			this->AutoStruct[aIndex]._Active = false;

			Func.MsgOutput(aIndex, 1, "[ Aviso ]: O sistema foi finalizado.");
			return;
		}

		if (this->AutoStruct[aIndex]._Active == true)
		{
			Func.MsgOutput(aIndex, 1, "[ Aviso ]: O sistema ja esta ativo.");
			return;
		}

		// AUTO RESET
		if (Count == 1)
		{
			this->AutoStruct[aIndex]._Strength = 0;
			this->AutoStruct[aIndex]._Dexterity = 0;
			this->AutoStruct[aIndex]._Vitality = 0;
			this->AutoStruct[aIndex]._Energy = 0;
		}
		// AUTO RESET + AUTO ADD
		else if (Count == 5)
		{
			if (this->AutoStruct[aIndex]._Strength <= 0 &&
				this->AutoStruct[aIndex]._Dexterity <= 0 &&
				this->AutoStruct[aIndex]._Vitality <= 0 &&
				this->AutoStruct[aIndex]._Energy <= 0)
			{
				Func.MsgOutput(aIndex, 1, "[ Aviso ]: Erro de sintaxe!");
				return;
			}
		}
		else
		{
			Func.MsgOutput(aIndex, 1, "[ Aviso ]: Erro de sintaxe!");
			return;
		}

		if (gObj[aIndex].Money < this->_Money)
		{
			Func.MsgOutput(aIndex, 1, "[ Aviso ]: E necessario %d de zen.", this->_Money);
			return;
		}

		this->AutoStruct[aIndex]._Active = true;

		GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Money);

		if (Count == 5)
			Func.MsgOutput(aIndex, 1, "[ Aviso ]: Auto Reset + Auto Add iniciado.");
		else
			Func.MsgOutput(aIndex, 1, "[ Aviso ]: Auto Reset iniciado.");
	}
}

void cAutoReset::Quit(LPOBJ lpObj)
{
	if (this->AutoStruct[lpObj->m_Index]._Active == true)
	{
		this->AutoStruct[lpObj->m_Index]._Points = 0;
		this->AutoStruct[lpObj->m_Index]._Strength = 0;
		this->AutoStruct[lpObj->m_Index]._Dexterity = 0;
		this->AutoStruct[lpObj->m_Index]._Vitality = 0;
		this->AutoStruct[lpObj->m_Index]._Energy = 0;

		this->AutoStruct[lpObj->m_Index]._Active = false;
	}
}

cAutoReset AutoReset;