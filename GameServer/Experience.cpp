#include "StdAfx.h"

bool cExperience::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Experience.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Experience[0] = Section.Rows[0].GetInt(1);
		this->_Experience[1] = Section.Rows[0].GetInt(2);
		this->_Experience[2] = Section.Rows[0].GetInt(3);
	}

	return true;
}

void cExperience::ExperienceSend(int aIndex, int TargetIndex, int Exp, int AttackDamage, int MSBFlag)
{
	if (!Func.gObjIsConnectedGP(aIndex))
	{
		return;
	}

	if (Exp < 0)
	{
		Exp = 0;
	}

	int ExpBase = Exp;
	__int64 ExpBonus = 0;

	if (Experience._Active == true)
	{
		if (Custom[aIndex].VipCount > 0) // Adicional para jogadores vip's.
		{
			ExpBonus += ((__int64)ExpBase * Experience._Experience[0]) / 100;
		}

		if (gObj[aIndex].MapNumber == 9) // Adicional no devil square.
		{
			ExpBonus += ((__int64)ExpBase * Experience._Experience[1]) / 100;
		}

		if (gObj[aIndex].MapNumber >= 11 && gObj[aIndex].MapNumber <= 16) // Adicional no blood castle.
		{
			ExpBonus += ((__int64)ExpBase * Experience._Experience[2]) / 100;
		}
	}

	if (HappyEvent._Active == true && HappyEvent._Event == true) // Happy event ativo.
	{
		if (HappyEvent._Experience > 0)
		{
			ExpBonus += ((__int64)ExpBase * HappyEvent._Experience) / 100;
		}
	}

	if (Custom[aIndex].Pet == true) // Bonus do pet ativo.
	{
		if (Pet._ExpPercent > 0)
		{
			ExpBonus += ((__int64)ExpBase * Pet._ExpPercent) / 100;
		}
	}

	if (ExpBonus < 0)
	{
		ExpBonus = 0;
	}

	__int64 ExpFinal = (__int64)ExpBase + ExpBonus;

	if (ExpFinal < 0)
	{
		ExpFinal = 0;
	}

	if (ExpFinal > 2147483647)
	{
		ExpFinal = 2147483647;
	}

	return GCKillPlayerExpSend(aIndex, TargetIndex, (int)ExpFinal, AttackDamage, MSBFlag);
}

cExperience Experience;