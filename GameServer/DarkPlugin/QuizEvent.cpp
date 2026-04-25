#include "StdAfx.h"

bool cQuiz::Load()
{
	this->_Count[0] = 0; this->_Count[1] = 0;

	memset(this->QuizStruct, 0, sizeof(this->QuizStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/QuizEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(&this->_Syntax[0], sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(1)));
		this->_Interval = Section.Rows[0].GetInt(2);
		this->_Duration = Section.Rows[0].GetInt(3);
		this->_Reward = Section.Rows[0].GetInt(4);
		this->_Amount = Section.Rows[0].GetInt(5);
		strcpy_s(&this->_NameCoin[0], sizeof(this->_NameCoin), (Section.Rows[0].GetStringPtr(6)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			strcpy_s(&this->QuizStruct[this->_Count[0]]._Question[0], sizeof(this->QuizStruct[this->_Count[0]]._Question), (Section.Rows[i].GetStringPtr(0)));
			this->_Count[0]++;
		}
	}

	if (Group.GetSection(2, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->QuizStruct[this->_Count[1]]._Type = Section.Rows[i].GetInt(0);
			this->QuizStruct[this->_Count[1]]._Index = Section.Rows[i].GetInt(1);
			this->QuizStruct[this->_Count[1]]._Level = Section.Rows[i].GetInt(2);
			this->QuizStruct[this->_Count[1]]._Luck = Section.Rows[i].GetInt(3);
			this->QuizStruct[this->_Count[1]]._Skill = Section.Rows[i].GetInt(4);
			this->QuizStruct[this->_Count[1]]._Option = Section.Rows[i].GetInt(5);
			this->QuizStruct[this->_Count[1]]._Excelente = Section.Rows[i].GetInt(6);
			this->QuizStruct[this->_Count[1]]._Quantity = Section.Rows[i].GetInt(7);
			strcpy_s(&QuizStruct[this->_Count[1]]._Name[0], sizeof(QuizStruct[this->_Count[1]]._Name), (Section.Rows[i].GetStringPtr(8)));
			this->_Count[1]++;
		}
	}

	return true;
}

bool cQuiz::Check(int aIndex, const char* Text)
{
	if (!this->_Active)
	{
		Func.MsgOutput(aIndex, 1, "Comando desabilitado.");
		return false;
	}
	else if (strlen(this->_Question) < 1)
	{
		Func.MsgOutput(aIndex, 1, "Não há nenhum Quiz registrado no momento.");
		return false;
	}
	else if (this->_Sended == false)
	{
		Func.MsgOutput(aIndex, 1, "Aguarde o próximo Quiz ser registrado.");
		return false;
	}
	else
	{
		Func.MsgOutput(aIndex, 1, "O último Quiz registrado é:");
		Func.MsgOutput(aIndex, 1, "%s", this->_Question);
		return true;
	}

	return false;
}

void cQuiz::Run()
{
	if (!this->_Active)
	{
		return;
	}

	if (this->_Started == true)
	{
		this->Time();
	}
	else
	{
		srand(time(NULL));

		int Sortear = rand() % this->_Count[0];

		char Buffer[255], *Context = nullptr;

		strcpy_s(Buffer, this->QuizStruct[Sortear]._Question);

		char* Question = strtok_s(Buffer, "==", &Context);
		char* Answer = strtok_s(nullptr, "==", &Context);

		strcpy(this->_Question, Question);
		strcpy(this->_Answer, Answer);

		strcpy(this->_Author, "[    QUIZ    ]");

		this->_Started = true;
	}
}

void cQuiz::Winner(int aIndex, const char* Text)
{
	if (this->_Started == true)
	{
		if (strlen(Text) >= 1 && strlen(this->_Answer) >= 1)
		{
			if (!_stricmp(Text, this->_Answer))
			{
				Func.AllServerAnnounce("%s Acertou a resposta!", gObj[aIndex].Name);

				if (this->_Reward == 1)
				{
					Func.AllServerAnnounce("Prêmio: %d %s", this->_Amount, this->_NameCoin);

					Manager.ExecFormat(Query._Query[7], gObj[aIndex].Name);
					Manager.ExecFormat(Query._Query[8], this->_Amount, gObj[aIndex].AccountID);

					this->Finish();
				}
				else if (this->_Reward == 2)
				{
					srand(time(NULL));

					int Sortear = rand() % this->_Count[1];

					for (int i = 0; i < this->QuizStruct[Sortear]._Quantity; i++)
					{
						int Item = ITEMGET(this->QuizStruct[Sortear]._Type, this->QuizStruct[Sortear]._Index);
						ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->QuizStruct[Sortear]._Level, 0, this->QuizStruct[Sortear]._Skill, this->QuizStruct[Sortear]._Luck, this->QuizStruct[Sortear]._Option, aIndex, this->QuizStruct[Sortear]._Excelente);
					}

					Func.AllServerAnnounce("Prêmio: %s", this->QuizStruct[Sortear]._Name);

					Manager.ExecFormat(Query._Query[7], gObj[aIndex].Name);

					this->Finish();
				}
			}
		}
	}
}

void cQuiz::Finish()
{
	this->_Started = false;
	this->_Time = 0;
	this->_TimeLeft = 0;
	this->_Sended = false;
	strcpy(this->_Question, "");
	strcpy(this->_Answer, "");
	strcpy(this->_Author, "");
}

void cQuiz::Time()
{
	if (this->_Started == true)
	{
		if (this->_Time == (60 * this->_Interval))
		{
			Func.AllServerAnnounce("%s", this->_Author);
			Func.AllServerAnnounce("%s", this->_Question);

			this->_TimeLeft = 0;
			this->_Sended = true;
		}

		if (this->_TimeLeft == (60 * this->_Duration) && this->_Sended == true)
		{
			Func.AllServerAnnounce("O último Quiz registrado expirou!");

			this->Finish();
		}

		this->_Time++;
		this->_TimeLeft++;
	}
}

cQuiz QuizEvent;