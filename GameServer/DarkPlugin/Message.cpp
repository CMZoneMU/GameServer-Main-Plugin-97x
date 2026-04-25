#include "StdAfx.h"
#include "Message.h"

bool cMessage::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Message.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		strcpy_s(&this->_Buffer[0][0], sizeof(this->_Buffer[0]), (Section.Rows[0].GetStringPtr(0)));
		strcpy_s(&this->_Buffer[1][0], sizeof(this->_Buffer[1]), (Section.Rows[1].GetStringPtr(0)));
		strcpy_s(&this->_Buffer[2][0], sizeof(this->_Buffer[2]), (Section.Rows[2].GetStringPtr(0)));
		strcpy_s(&this->_Buffer[3][0], sizeof(this->_Buffer[3]), (Section.Rows[3].GetStringPtr(0)));
		strcpy_s(&this->_Buffer[4][0], sizeof(this->_Buffer[4]), (Section.Rows[4].GetStringPtr(0)));
	}

	return true;
}

cMessage Message;