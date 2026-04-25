#include "StdAfx.h"

cSpeed::cSpeed() : _Active(false)
{
}

bool cSpeed::Load()
{
	this->_Count = 0;

	memset(this->SkillStruct, 0, sizeof(this->SkillStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Speed.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Attack = Section.Rows[0].GetInt(1);
		this->_Moviment = Section.Rows[0].GetInt(2);

		this->_Display[0] = Section.Rows[1].GetInt(0);
		this->_Display[1] = Section.Rows[1].GetInt(1);
		this->_Display[2] = Section.Rows[1].GetInt(2);
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->SkillStruct[this->_Count]._Magic = Section.Rows[i].GetInt(0);
			this->SkillStruct[this->_Count]._Velocity = Section.Rows[i].GetInt(1);
			this->SkillStruct[this->_Count]._Type = Section.Rows[i].GetInt(2);
			this->_Count++;
		}
	}

	return true;
}

void cSpeed::Connect(int aIndex)
{
	if (this->_Active)
	{
		this->SpeedStruct[aIndex]._Sended = false;

		this->SpeedStruct[aIndex]._Block = false;

		this->SpeedStruct[aIndex]._Attack = 0;

		this->SpeedStruct[aIndex]._Skill = 0;

		this->SpeedStruct[aIndex]._Moviment = 0;

		this->SpeedStruct[aIndex]._Time = 0;
	}
}

void cSpeed::Run(LPOBJ lpObj)
{
	if (this->_Active)
	{
		if (this->SpeedStruct[lpObj->m_Index]._Time >= 10)
		{
			this->SpeedStruct[lpObj->m_Index]._Sended = false;

			this->SpeedStruct[lpObj->m_Index]._Block = false;

			this->SpeedStruct[lpObj->m_Index]._Time = 0;
		}
		else if (this->SpeedStruct[lpObj->m_Index]._Block == true)
		{
			this->SpeedStruct[lpObj->m_Index]._Time++;
		}

		if (this->SpeedStruct[lpObj->m_Index]._Attack > this->_Attack && this->SpeedStruct[lpObj->m_Index]._Sended == false)
		{
			this->SpeedStruct[lpObj->m_Index]._Sended = true;

			Func.MsgOutput(lpObj->m_Index, 0, "Detectado alteração de velocidade: %s!", lpObj->Name);
			Func.MsgOutput(lpObj->m_Index, 0, "Desconectado por uso de speed hacker.");

			gObjCloseSet(lpObj->m_Index, 0);

			this->Log("Jogador: %s, Attack: %d", lpObj->Name, this->SpeedStruct[lpObj->m_Index]._Attack);
		}

		if (this->SpeedStruct[lpObj->m_Index]._Moviment > this->_Moviment && this->SpeedStruct[lpObj->m_Index]._Sended == false)
		{
			this->SpeedStruct[lpObj->m_Index]._Sended = true;

			Func.MsgOutput(lpObj->m_Index, 0, "Detectado alteração de velocidade: %s!", lpObj->Name);
			Func.MsgOutput(lpObj->m_Index, 0, "Desconectado por uso de speed hacker.");

			gObjCloseSet(lpObj->m_Index, 0);

			this->Log("Jogador: %s, Moviment: %d", lpObj->Name, this->SpeedStruct[lpObj->m_Index]._Moviment);
		}

		this->SpeedStruct[lpObj->m_Index]._Attack = 0;
		this->SpeedStruct[lpObj->m_Index]._Skill = 0;
		this->SpeedStruct[lpObj->m_Index]._Moviment = 0;
	}
}

bool cSpeed::Attack(LPOBJ lpObj, LPOBJ Target, class CMagicInf* lpMagic)
{
	if (this->_Active)
	{
		if (this->SpeedStruct[lpObj->m_Index]._Block == true)
		{
			return false;
		}

		if (lpObj->Type == PLAYER && Target->Type == PLAYER)
		{
			if (lpObj->m_Index != Target->m_Index && lpMagic == NULL)
			{
				if (this->SpeedStruct[lpObj->m_Index]._Attack > 0 && this->_Display[0] == 1)
				{
					Func.MsgOutput(lpObj->m_Index, 0, "Attack: %d", this->SpeedStruct[lpObj->m_Index]._Attack);
				}

				this->SpeedStruct[lpObj->m_Index]._Attack++;
			}
		}
	}

	return true;
}

void cSpeed::Skill(LPOBJ lpObj, int Magic)
{
	if (this->_Active)
	{
		CMagicInf * lpMagic = { 0 };

		lpMagic = new CMagicInf();

		lpMagic->Set(Magic, 0);

		if (lpMagic != NULL && this->SpeedStruct[lpObj->m_Index]._Block == false)
		{
			for (int i = 0; i < this->_Count; i++)
			{
				if (Magic == this->SkillStruct[i]._Magic)
				{
					this->SpeedStruct[lpObj->m_Index]._Skill++;

					if (this->SpeedStruct[lpObj->m_Index]._Skill > 0 && this->_Display[1] == 1)
					{
						Func.MsgOutput(lpObj->m_Index, 0, "Skill: %d", this->SpeedStruct[lpObj->m_Index]._Skill);
					}

					if (this->SpeedStruct[lpObj->m_Index]._Skill > this->SkillStruct[i]._Velocity && this->SkillStruct[i]._Type == 1)
					{
						if (this->SpeedStruct[lpObj->m_Index]._Sended == false)
						{
							this->SpeedStruct[lpObj->m_Index]._Sended = true;

							Func.MsgOutput(lpObj->m_Index, 0, "Detectado alteração de velocidade: %s!", lpObj->Name);
							Func.MsgOutput(lpObj->m_Index, 0, "Desconectado por uso de speed hacker.");

							gObjCloseSet(lpObj->m_Index, 0);

							this->Log("Jogador: %s, Skill: %d", lpObj->Name, this->SpeedStruct[lpObj->m_Index]._Skill);
						}
					}
					else if (this->SpeedStruct[lpObj->m_Index]._Skill > this->SkillStruct[i]._Velocity && this->SkillStruct[i]._Type == 0)
					{
						if (this->SpeedStruct[lpObj->m_Index]._Sended == false)
						{
							Func.MsgOutput(lpObj->m_Index, 0, "Detectado alteração de velocidade: %s!", lpObj->Name);
							Func.MsgOutput(lpObj->m_Index, 0, "Ataque bloqueado por 10 segundos.");

							this->SpeedStruct[lpObj->m_Index]._Block = true;

							this->Log("Jogador: %s, Skill: %d", lpObj->Name, this->SpeedStruct[lpObj->m_Index]._Skill);
						}
					}
				}
			}
		}
	}
}

void cSpeed::PMoveProcEx(PMSG_MOVE* Move, int aIndex)
{
	if (Speed._Active)
	{
		if (Speed.SpeedStruct[aIndex]._Moviment > 0 && Speed._Display[2] == 1)
		{
			Func.MsgOutput(aIndex, 0, "Moviment: %d", Speed.SpeedStruct[aIndex]._Moviment);
		}

		Speed.SpeedStruct[aIndex]._Moviment++;
	}

	return PMoveProc(Move, aIndex);
}

void cSpeed::Log(char * Text, ...)
{
	char Buffer[250];
	va_list pArguments;

	va_start(pArguments, Text);
	vsprintf(&Buffer[0], Text, pArguments);
	va_end(pArguments);

	SYSTEMTIME t;
	GetLocalTime(&t);

	FILE * stream;

	TCHAR String[512];

	wsprintf(String, "SPEED_LOG\\%02d-%02d-%02d_SPEED.txt", t.wYear, t.wMonth, t.wDay);

	stream = fopen(String, "a+");

	fprintf(stream, "%02d:%02d:%02d - %s\n", t.wHour, t.wMinute, t.wSecond, Buffer);

	fclose(stream);
}

cSpeed Speed;