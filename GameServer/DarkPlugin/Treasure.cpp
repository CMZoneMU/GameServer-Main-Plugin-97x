#include "StdAfx.h"

char treasureMapName[][15] = { "Lorencia", "Dungeon", "Davias", "Noria" };
BYTE treasureMapNumber[] = { 0,			 1,			 2,        3 };

bool TREASURE_Custom::Load()
{
	ZeroMemory(this->_Winner, sizeof(this->_Winner));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/TreasureEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
			this->_TimeOpen = Section.Rows[0].GetInt(1) * 60;
			this->_TimeBuy = Section.Rows[0].GetInt(2);
			this->_TimeClose = Section.Rows[0].GetInt(3) * 60;
			strcpy_s(this->_Syntax[2], sizeof(this->_Syntax[2]), (Section.Rows[0].GetStringPtr(4)));
			strcpy_s(this->_Syntax[3], sizeof(this->_Syntax[3]), (Section.Rows[0].GetStringPtr(5)));
		}
	}

	this->_State = treasureOff;
	this->_TimeCount = this->_TimeOpen;
	this->_Index = -1;
	this->_ShopNumber = 11;

	return true;
}

void TREASURE_Custom::Check()
{
	if (!this->_Active)
	{
		return;
	}

	if (this->_TimeCount > 0)
	{
		this->_TimeCount--;
		return;
	}

	if (this->_State == treasureOff)
	{
		ZeroMemory(this->_Winner, sizeof(this->_Winner));

		this->_State = treasureOn;
		this->_TimeCount = this->_TimeClose;

		short X, Y; srand(time(NULL));

		BYTE Index = (BYTE)(rand() % sizeof(treasureMapNumber));
		BYTE Map = treasureMapNumber[Index];

		while (Func.GetBoxPosition(Map, 10, 10, 240, 240, X, Y) == 0) {}

		this->_Index = gObjAddCallMon();

		if (this->_Index >= 0 && this->_Index < OBJECT_MIN)
		{

			OBJECTSTRUCT* lpNpc = &gObj[this->_Index];

			lpNpc->Class = 201;
			lpNpc->MapNumber = Map;
			lpNpc->X = X;
			lpNpc->Y = Y;
			lpNpc->Dir = (rand() % 7);
			lpNpc->m_RecallMon = this->_Index;
			lpNpc->TargetNumber = -1;
			lpNpc->TX = lpNpc->X;
			lpNpc->TY = lpNpc->Y;
			lpNpc->MTX = lpNpc->X;
			lpNpc->MTY = lpNpc->Y;
			lpNpc->m_OldX = lpNpc->X;
			lpNpc->m_OldY = lpNpc->Y;
			lpNpc->StartX = (BYTE)(lpNpc->X);
			lpNpc->StartY = (BYTE)(lpNpc->Y);
			lpNpc->m_ActState.Emotion = 0;
			lpNpc->m_ActState.Attack = 0;
			lpNpc->m_ActState.EmotionCount = 0;
			lpNpc->PathCount = 0;
			lpNpc->m_MoveRange = 0;
			lpNpc->m_PosNum = -1;

			Functions::gObjSetMonsterEx(this->_Index, 201);
			gObjViewportListProtocolCreate(&gObj[this->_Index]);

			lpNpc->ShopNumber = this->_ShopNumber;

			sprintf_s(this->_Buffer[0], "O pirata Jack escondeu seu tesouro em %s", treasureMapName[Index]);

			for (int i = OBJECT_MIN; i != OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3)
				{
					GCServerMsgStringSend(this->_Buffer[0], i, 0);
					GCServerMsgStringSend("Procure-o e ganhe recompensas!", i, 0);
				}
			}
		}
		else
		{
			this->_TimeCount = this->_TimeOpen;
			this->_Index = -1;
			this->_State = treasureOff;
		}
	}
	else if (this->_State == treasureOn)
	{
		this->_State = treasureOff;
		this->_TimeCount = this->_TimeOpen;

		if (this->_Index != -1)
		{
			gObjDel(this->_Index);
		}

		if (this->_Winner[0] == 0)
		{
			for (int i = OBJECT_MIN; i != OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3)
				{
					GCServerMsgStringSend("O tesouro do pirata Jack foi destruído por monstros", i, 0);
					GCServerMsgStringSend("Tente ajudá-lo novamente na próxima vez", i, 0);
				}
			}
		}
		else
		{
			ZeroMemory(this->_Winner, sizeof(this->_Winner));
		}

		this->_Index = -1;
	}
}

void TREASURE_Custom::Talk(OBJECTSTRUCT* Npc, OBJECTSTRUCT* Player)
{
	if (!this->_Active)
	{
		ChatTargetSend(Npc, "Como eu parei aqui? Vixi! Acho que estou perdido", Player->m_Index);
		return;
	}

	if (this->_State == treasureOn)
	{
		if (this->_Winner[0] == 0)
		{
			this->_TimeCount = this->_TimeBuy;

			strcpy_s(this->_Winner, Player->Name);

			ChatTargetSend(Npc, "Obrigado por vir! O tesouro é todo seu!", Player->m_Index);

			sprintf_s(this->_Buffer[1], "O tesouro foi encontrado por %s", Player->Name);
			sprintf_s(this->_Buffer[2], "Localização: %s %02d/%02d", treasureMapName[Player->MapNumber], Npc->X, Npc->Y);

			for (int i = OBJECT_MIN; i != OBJECT_MAX; i++)
			{
				if (gObj[i].Connected == 3)
				{
					GCServerMsgStringSend(this->_Buffer[1], i, 0);
					GCServerMsgStringSend(this->_Buffer[2], i, 0);
				}
			}
		}
		else
		{
			if (_stricmp(this->_Winner, Player->Name))
			{
				ChatTargetSend(Npc, "Parece que você chegou meio tarde, não é?!", Player->m_Index);
			}
		}
	}
	else
	{
		ChatTargetSend(Npc, "Não tem doce no meu baú para você", Player->m_Index);
	}
}

BYTE TREASURE_Custom::ShopNumber() const
{
	return this->_ShopNumber;
}

const char* TREASURE_Custom::Winner() const
{
	return this->_Winner;
}


void TREASURE_Custom::StartManual()
{
	this->_State = treasureOff;
	this->_TimeCount = 0;
}
TREASURE_Custom Treasure;



