#include "StdAfx.h"

bool Querys::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Querys.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		strcpy_s(this->_Query[0], sizeof(this->_Query[0]), (Section.Rows[0].GetStringPtr(0)));
		strcpy_s(this->_Query[1], sizeof(this->_Query[1]), (Section.Rows[1].GetStringPtr(0)));
		strcpy_s(this->_Query[2], sizeof(this->_Query[2]), (Section.Rows[2].GetStringPtr(0)));
		strcpy_s(this->_Query[3], sizeof(this->_Query[3]), (Section.Rows[3].GetStringPtr(0)));
		strcpy_s(this->_Query[4], sizeof(this->_Query[4]), (Section.Rows[4].GetStringPtr(0)));
		strcpy_s(this->_Query[5], sizeof(this->_Query[5]), (Section.Rows[5].GetStringPtr(0)));
		strcpy_s(this->_Query[6], sizeof(this->_Query[6]), (Section.Rows[6].GetStringPtr(0)));
		strcpy_s(this->_Query[7], sizeof(this->_Query[7]), (Section.Rows[7].GetStringPtr(0)));
		strcpy_s(this->_Query[8], sizeof(this->_Query[8]), (Section.Rows[8].GetStringPtr(0)));
		strcpy_s(this->_Query[9], sizeof(this->_Query[9]), (Section.Rows[9].GetStringPtr(0)));
		strcpy_s(this->_Query[10], sizeof(this->_Query[10]), (Section.Rows[10].GetStringPtr(0)));
		strcpy_s(this->_Query[11], sizeof(this->_Query[11]), (Section.Rows[11].GetStringPtr(0)));
		strcpy_s(this->_Query[12], sizeof(this->_Query[12]), (Section.Rows[12].GetStringPtr(0)));
		strcpy_s(this->_Query[13], sizeof(this->_Query[13]), (Section.Rows[13].GetStringPtr(0)));
		strcpy_s(this->_Query[14], sizeof(this->_Query[14]), (Section.Rows[14].GetStringPtr(0)));
		strcpy_s(this->_Query[15], sizeof(this->_Query[15]), (Section.Rows[15].GetStringPtr(0)));
		strcpy_s(this->_Query[16], sizeof(this->_Query[16]), (Section.Rows[16].GetStringPtr(0)));
		strcpy_s(this->_Query[17], sizeof(this->_Query[17]), (Section.Rows[17].GetStringPtr(0)));
		strcpy_s(this->_Query[18], sizeof(this->_Query[18]), (Section.Rows[18].GetStringPtr(0)));
		strcpy_s(this->_Query[19], sizeof(this->_Query[19]), (Section.Rows[19].GetStringPtr(0))); // Query Referente da moeda Cash
		strcpy_s(this->_Query[20], sizeof(this->_Query[20]), (Section.Rows[20].GetStringPtr(0)));
		strcpy_s(this->_Query[21], sizeof(this->_Query[21]), (Section.Rows[21].GetStringPtr(0)));
		strcpy_s(this->_Query[22], sizeof(this->_Query[22]), (Section.Rows[22].GetStringPtr(0)));
		strcpy_s(this->_Query[23], sizeof(this->_Query[23]), (Section.Rows[23].GetStringPtr(0)));
		strcpy_s(this->_Query[24], sizeof(this->_Query[24]), (Section.Rows[24].GetStringPtr(0)));
		strcpy_s(this->_Query[25], sizeof(this->_Query[25]), (Section.Rows[25].GetStringPtr(0)));
		strcpy_s(this->_Query[26], sizeof(this->_Query[26]), (Section.Rows[26].GetStringPtr(0)));
		strcpy_s(this->_Query[27], sizeof(this->_Query[27]), (Section.Rows[27].GetStringPtr(0)));
		strcpy_s(this->_Query[28], sizeof(this->_Query[28]), (Section.Rows[28].GetStringPtr(0)));
		strcpy_s(this->_Query[29], sizeof(this->_Query[29]), (Section.Rows[29].GetStringPtr(0)));
		strcpy_s(this->_Query[30], sizeof(this->_Query[30]), (Section.Rows[30].GetStringPtr(0)));
		strcpy_s(this->_Query[31], sizeof(this->_Query[31]), (Section.Rows[31].GetStringPtr(0)));
		strcpy_s(this->_Query[32], sizeof(this->_Query[32]), (Section.Rows[32].GetStringPtr(0)));
		strcpy_s(this->_Query[33], sizeof(this->_Query[33]), (Section.Rows[33].GetStringPtr(0)));
		strcpy_s(this->_Query[34], sizeof(this->_Query[34]), (Section.Rows[34].GetStringPtr(0)));
		strcpy_s(this->_Query[35], sizeof(this->_Query[35]), (Section.Rows[35].GetStringPtr(0)));
		strcpy_s(this->_Query[36], sizeof(this->_Query[36]), (Section.Rows[36].GetStringPtr(0)));
		strcpy_s(this->_Query[37], sizeof(this->_Query[37]), (Section.Rows[37].GetStringPtr(0)));
		strcpy_s(this->_Query[38], sizeof(this->_Query[38]), (Section.Rows[38].GetStringPtr(0)));
		strcpy_s(this->_Query[39], sizeof(this->_Query[39]), (Section.Rows[39].GetStringPtr(0)));
		strcpy_s(this->_Query[40], sizeof(this->_Query[40]), (Section.Rows[40].GetStringPtr(0)));
		strcpy_s(this->_Query[41], sizeof(this->_Query[40]), (Section.Rows[41].GetStringPtr(0)));
	}

	return true;
}

Querys Query;