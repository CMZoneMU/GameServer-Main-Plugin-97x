#include "StdAfx.h"

cNews::cNews() : _Active(false), _Notice(), _Count(0)
{
}

bool cNews::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/News.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Interval = Section.Rows[0].GetInt(1) * 60;
	}

	DWORD Index = 1;

	while (true)
	{
		if (!Group.GetSection(Index, Section))
		{
			break;
		}

		this->_Notice.push_back({
			Section.Rows[0].GetStringPtr(0),
			Section.Rows[1].GetStringPtr(0),
			Section.Rows[2].GetStringPtr(0)
			});

		++Index;
	}

	this->_Last = this->_Notice.cbegin();
	this->_Count = this->_Interval;

	return true;
}

void cNews::Run()
{
	if (this->_Active && this->_Notice.size() > 0)
	{
		if (this->_Count > 0)
		{
			--this->_Count;
		}
		else
		{
			this->_Count = this->_Interval;

			if (this->_Last == this->_Notice.cend())
			{
				this->_Last = this->_Notice.cbegin();
			}

			auto News = this->_Last->data();

			for (int i = OBJECT_MIN; i < OBJECT_MAX; ++i)
			{
				if (gObj[i].Connected == 3)
				{
					GCServerMsgStringSend((char*)(News[0].c_str()), i, 0);
					GCServerMsgStringSend((char*)(News[1].c_str()), i, 0);
					GCServerMsgStringSend((char*)(News[2].c_str()), i, 0);
				}
			}

			++this->_Last;
		}
	}
}

cNews News;