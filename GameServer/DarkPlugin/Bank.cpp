#include "StdAfx.h"

bool cBank::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Bank.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Level = Section.Rows[0].GetInt(1);
		this->_Zen = Section.Rows[0].GetInt(2);
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(3)));
	}

	return true;
}

void cBank::Check(int aIndex, char* msg)
{
	if (!this->_Active)
	{
		Func.MsgOutput(aIndex, 1, "Comando desabilitado.");
		return;
	}
	else if (gObj[aIndex].Level < this->_Level)
	{
		Func.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level);
		return;
	}
	else if (gObj[aIndex].Money < this->_Zen)
	{
		Func.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen);
		return;
	}
	else if (gObj[aIndex].m_IfState.use != 0)
	{
		Func.MsgOutput(aIndex, 1, "Feche todas as janelas para usar o banco.");
		return;
	}

	this->_Jewel[0] = 0, this->_Trans[0] = 0;

	sscanf(msg, "%s %s %d", &this->_Trans, &this->_Jewel, &this->_Count);

	if (strlen(msg) < 3 || this->_Trans[0] == 0 || strcmpi(this->_Trans, "deposito") && strcmpi(this->_Trans, "saque") && strcmpi(this->_Trans, "saldo"))
	{
		Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
		Func.MsgOutput(aIndex, 1, "Digite: %s saldo ou deposito/saque.", this->_Syntax);
		return;
	}

	if (this->_Jewel[0] == 0 || strcmpi(this->_Jewel, "bless") && strcmpi(this->_Jewel, "soul") && strcmpi(this->_Jewel, "life") && strcmpi(this->_Jewel, "chaos") && strcmpi(this->_Jewel, "creation") && strcmpi(this->_Jewel, "Luck") && strcmpi(this->_Jewel, "skill") && strcmpi(this->_Jewel, "level") && strcmpi(this->_Jewel, "option"))
	{
		Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
		Func.MsgOutput(aIndex, 1, "Digite: %s saldo ou deposito/saque joia quantidade.", this->_Syntax);
		return;
	}

	int Item = !strcmpi(this->_Jewel, "bless") ? ITEMGET(14, 13) : !strcmpi(this->_Jewel, "soul") ? ITEMGET(14, 14) : !strcmpi(this->_Jewel, "life") ? ITEMGET(14, 16) : !strcmpi(this->_Jewel, "chaos") ? ITEMGET(12, 15) : !strcmpi(this->_Jewel, "creation") ? ITEMGET(14, 22) : !strcmpi(this->_Jewel, "luck") ? ITEMGET(15, 18) : !strcmpi(this->_Jewel, "skill") ? ITEMGET(15, 19) : !strcmpi(this->_Jewel, "level") ? ITEMGET(15, 20) : !strcmpi(this->_Jewel, "option") ? ITEMGET(15, 23) : -1;

	int Jewel = !strcmpi(this->_Jewel, "bless") ? this->Bless : !strcmpi(this->_Jewel, "soul") ? this->Soul : !strcmpi(this->_Jewel, "life") ? this->Life : !strcmpi(this->_Jewel, "chaos") ? this->Chaos : !strcmpi(this->_Jewel, "creation") ? this->Creation : !strcmpi(this->_Jewel, "luck") ? this->Luck : !strcmpi(this->_Jewel, "skill") ? this->Skill : !strcmpi(this->_Jewel, "level") ? this->Level : !strcmpi(this->_Jewel, "option") ? this->Option : -1;

	if (!strcmpi(this->_Trans, "saldo"))
	{
		Manager.JewelsCount(aIndex, gObj[aIndex].AccountID);

		Func.MsgOutput(aIndex, 1, "[ BANK ] Saldo de %d %s(s)", Custom[aIndex].Jewels[Jewel], this->_Jewel);
		return;
	}

	if (!strcmpi(this->_Trans, "deposito"))
	{
		int Total = Func.CheckInventory(aIndex, Item, 0);

		if (this->_Count <= 0)
		{
			Func.MsgOutput(aIndex, 1, "É preciso digitar o valor do depósito.");
			return;
		}
		else if (this->_Count > Total)
		{
			Func.MsgOutput(aIndex, 1, "Você só tem %d %s(s)", Total, this->_Jewel);
			return;
		}

		if (Total != 0)
		{
			Func.DeleteInventory(aIndex, Item, 0, this->_Count);

			Custom[aIndex].Jewels[Jewel] += this->_Count;

			char * Coluna = Jewel == this->Bless ? "Bless" : Jewel == this->Soul ? "Soul" : Jewel == this->Life ? "Life" : Jewel == this->Chaos ? "Chaos" : Jewel == this->Creation ? "Creation" : Jewel == this->Luck ? "Luck" : Jewel == this->Skill ? "Skill" : Jewel == this->Level ? "JLevel" : Jewel == this->Option ? "JOption" : "null";
			
			Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %d WHERE memb___id = '%s'",Coluna, Custom[aIndex].Jewels[Jewel], gObj[aIndex].AccountID);

			Func.MsgOutput(aIndex, 1, "Deposito de %d %s(s) efetuado!", this->_Count, this->_Jewel);
			Func.MsgOutput(aIndex, 1, "Saldo atual de %d %s(s)", Custom[aIndex].Jewels[Jewel], this->_Jewel);
		}

	}
	else if (!strcmpi(this->_Trans, "saque"))
	{
		if (this->_Count <= 0)
		{
			Func.MsgOutput(aIndex, 1, "É preciso digitar o valor do saque.");
			return;
		}
		else if (this->_Count > Custom[aIndex].Jewels[Jewel])
		{
			Func.MsgOutput(aIndex, 1, "Você só tem %d %s(s)", Custom[aIndex].Jewels[Jewel], this->_Jewel);
			return;
		}

		if (!Func.InventoryFullCheck(aIndex, Item))
		{
			Func.MsgOutput(aIndex, 1, "O inventário está cheio!");
			return;
		}

		int Check = Func.InventoryFullCheck(aIndex, Item);

		if (this->_Count > Check)
		{
			this->_Count = Check;
		}

		for (int i = 0; i < this->_Count; i++)
		{
			ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, 0, 0, 0, 0, 0, aIndex, 0);

			Custom[aIndex].Jewels[Jewel]--;
		}

		if (Custom[aIndex].Jewels[Jewel] < 0)
		{
			Custom[aIndex].Jewels[Jewel] = 0;
		}

		char * Coluna = Jewel == this->Bless ? "Bless" : Jewel == this->Soul ? "Soul" : Jewel == this->Life ? "Life" : Jewel == this->Chaos ? "Chaos" : Jewel == this->Creation ? "Creation" : Jewel == this->Luck ? "Luck" : Jewel == this->Skill ? "Skill" : Jewel == this->Level ? "JLevel" : Jewel == this->Option ? "JOption" : "null";

		Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %d WHERE memb___id = '%s'", Coluna, Custom[aIndex].Jewels[Jewel], gObj[aIndex].AccountID);
		
		Func.MsgOutput(aIndex, 1, "Saque de %d %s(s) efetuado!", this->_Count, this->_Jewel);
		Func.MsgOutput(aIndex, 1, "Saldo restante de %d %s(s)", Custom[aIndex].Jewels[Jewel], this->_Jewel);
	}
}

cBank Bank;