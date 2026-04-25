#include "StdAfx.h"

bool cParty::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Party.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_VipCount = Section.Rows[0].GetInt(1);
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(2)));
	}

	return true;
}

void cParty::Command(int aIndex, char* msg)
{
	if (this->_Active == true)
	{
		if (Custom[aIndex].VipCount < this->_VipCount)
		{
			Func.MsgOutput(aIndex, 1, "Você não possui o plano vip necessário!");
			return;
		}

		memset(this->_Name, 0, sizeof(this->_Name));

		sscanf(msg, "%s", &this->_Name);

		if (strlen(msg) < 2 || this->_Name[0] == 0 || strcmpi(this->_Name, "on") && strcmpi(this->_Name, "off"))
		{
			Func.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Func.MsgOutput(aIndex, 1, "Digite: %s on ou off.", this->_Syntax);
			return;
		}

		if (!strcmpi(this->_Name, "on"))
		{
			if (this->PlayerStruct[aIndex]._Active == false)
			{
				this->PlayerStruct[aIndex]._Active = true;

				Func.MsgOutput(aIndex, 1, "Auto party ativado.");
			}
		}

		if (!strcmpi(this->_Name, "off"))
		{
			if (this->PlayerStruct[aIndex]._Active == true)
			{
				this->PlayerStruct[aIndex]._Active = false;

				Func.MsgOutput(aIndex, 1, "Auto party desativado.");
			}
		}
	}
}

void cParty::Quit(LPOBJ lpObj)
{
	if (this->PlayerStruct[lpObj->m_Index]._Active == true)
	{
		this->PlayerStruct[lpObj->m_Index]._Active = false;
	}
}

int cParty::Create(int usernumber, int dbnumber, int level)
{
	_asm
	{
		PUSH level
		PUSH dbnumber
		PUSH usernumber
		MOV ECX, 0x6301080;
		MOV EDI, 0x4500A0;
		CALL EDI;
	}
}

void cParty::Paint(int party_number)
{
	_asm
	{
		PUSH party_number
		MOV ECX, 0x6301080;
		MOV EDI, 0x450790;
		CALL EDI;
	}
}

int cParty::Add(int party_number, int usernumber, int dbnumber, int level)
{
	_asm
	{
		PUSH level
		PUSH dbnumber
		PUSH usernumber
		PUSH party_number
		MOV ECX, 0x6301080;
		MOV EDI, 0x450400;
		CALL EDI;
	}
}

void cParty::GCResultSend(int aIndex, BYTE headcode, BYTE result)
{
	PMSG_DEFRESULT Result;

	PHeadSetB((LPBYTE)&Result, headcode, sizeof(Result));
	Result.result = result;

	DataSend(aIndex, (UCHAR*)&Result, Result.h.size);
}

bool cParty::Accept(int Number, int aIndex)
{
	if (Party.PlayerStruct[Number]._Active == true)
	{
		if (gObj[Number].PartyNumber < 0)
		{
			gObj[Number].PartyNumber = this->Create(Number, gObj[Number].DBNumber, gObj[Number].Level);
		}

		int Party = gObj[Number].PartyNumber;

		if (gObj[Number].PartyNumber >= 0)
		{
			int iPartyPos = this->Add(gObj[Number].PartyNumber, aIndex, gObj[aIndex].DBNumber, gObj[aIndex].Level);

			if (iPartyPos >= 0)
			{
				gObj[aIndex].PartyNumber = gObj[Number].PartyNumber;

				Func.MsgOutput(Number, 1, "Party formada com %s", gObj[aIndex].Name);
				Func.MsgOutput(aIndex, 1, "Party formada com %s", gObj[Number].Name);

				this->Paint(Party);
			}
			else if (iPartyPos == -1)
			{
				this->GCResultSend(Number, 0x41, 2);
				this->GCResultSend(aIndex, 0x41, 2);
				return false;
			}
		}

		if (gObj[aIndex].m_IfState.use != 0 && gObj[aIndex].m_IfState.type == 2)
		{
			gObj[aIndex].m_IfState.use = 0;
			gObj[aIndex].PartyTargetUser = -1;
		}

		if (gObj[Number].m_IfState.use != 0 && gObj[Number].m_IfState.type == 2)
		{
			gObj[Number].m_IfState.use = 0;
			gObj[Number].PartyTargetUser = -1;
		}

		if (Party >= 0)
		{
			CGPartyListAll(Party);
		}

		return false;
	}
	else
	{
		return true;
	}
}

void cParty::CGPartyRequestRecvEx(PMSG_PARTYREQUEST * lpMsg, int aIndex)
{
	int number = MAKE_NUMBER(lpMsg->NumberH, lpMsg->NumberL);

	if (number < 0 || number > OBJECT_MAX - 1)
		return;

	if (gObj[aIndex].CloseCount >= 0 || gObj[number].CloseCount >= 0)
	{
		Party.GCResultSend(aIndex, 0x41, 0x00);
		return;
	}

	if (gObj[aIndex].m_IfState.use > 0)
	{
		Party.GCResultSend(aIndex, 0x41, 0x00);
		return;
	}

	if (gObj[number].m_IfState.use > 0)
	{
		Party.GCResultSend(aIndex, 0x41, 0x00);
		return;
	}

	if (Party.Accept(number, aIndex) == false)
	{
		return;
	}

	return CGPartyRequestRecv(lpMsg, aIndex);
}

cParty Party;