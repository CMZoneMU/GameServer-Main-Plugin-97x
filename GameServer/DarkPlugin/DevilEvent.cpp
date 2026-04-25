#include "StdAfx.h"

bool cDevilEvent::Load()
{
	this->_Count = 0;

	memset(this->DevilStruct, 0, sizeof(this->DevilStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/DevilEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->DevilStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->DevilStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->DevilStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			this->DevilStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			this->DevilStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			this->DevilStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			this->DevilStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->_Count++;
		}
	}

	return true;
}

void Item(LPOBJ lpObj)
{
	for (int i = 0; i < DevilEvent._Count; i++)
	{
		int Item = ITEMGET(DevilEvent.DevilStruct[i]._Type, DevilEvent.DevilStruct[i]._Index);

		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, lpObj->X, lpObj->Y, Item, DevilEvent.DevilStruct[i]._Level, 0, DevilEvent.DevilStruct[i]._Skill, DevilEvent.DevilStruct[i]._Luck, DevilEvent.DevilStruct[i]._Option, lpObj->m_Index, DevilEvent.DevilStruct[i]._Excelente);
	}

	Manager.ExecFormat("UPDATE Character SET DevilEvent = DevilEvent + 1 WHERE Name = '%s'", lpObj->Name);
}

__declspec(naked) void cDevilEvent::SendRanking()
{
	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 8]
		PUSH EAX
		CALL Item
		MOV BYTE PTR SS : [EBP - 0x2C], 0x0C1
		MOV BYTE PTR SS : [EBP - 0x2A], 1
		MOV EDI, 0x432922
		JMP EDI

	}
}

cDevilEvent DevilEvent;