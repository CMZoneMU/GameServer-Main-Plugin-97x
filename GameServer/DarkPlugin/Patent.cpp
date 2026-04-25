#include "StdAfx.h"

bool cPatent::Load()
{
	this->_Count = 0;

	memset(this->PatentStruct, 0, sizeof(this->PatentStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Patent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->PatentStruct[this->_Count].Min = Section.Rows[i].GetInt(0);
			this->PatentStruct[this->_Count].Max = Section.Rows[i].GetInt(1);
			this->_Count++;
		}
	}

	return true;
}

void cPatent::GCReqRankLevelUser(int aIndex, int Target)
{
	PMSG_CUSTOM_RANKUSER Result = { 0 };

	int Rank = this->GetRankIndex(Target);

	Result.h.set(0xF3, 0xE5, sizeof(Result));

	Result.Index = Target;

	if (gObj[Target].Authority > 1)
	{
		Result.Rank = -1;
		Result.Type = 2;
	}
	else if (gObj[Target].Type == MONSTER)
	{
		Result.Type = 0;
	}
	else if (Custom[Target].Rei > 0)
	{
		Result.Rank = -1;
		Result.Type = 3;
	}
	else
	{
		Result.Rank = Rank;
		Result.Type = 1;
	}

	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
}

int cPatent::GetRankIndex(int aIndex)
{
	int Value = Custom[aIndex].Patent;

	for (int i = 0; i < this->_Count; i++)
	{
		if (Value >= this->PatentStruct[i].Min && Value <= this->PatentStruct[i].Max ||
			Value >= this->PatentStruct[i].Min && this->PatentStruct[i].Max == -1)
		{
			return i;
		}
	}

	return -1;
}

cPatent Patent;