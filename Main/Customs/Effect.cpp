#include "StdAfx.h"

bool cEffect::Load()
{
	this->_Count = 0;

	memset(this->EffectStruct, 0, sizeof(this->EffectStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Local\\Effect.bmd"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->EffectStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->EffectStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->EffectStruct[this->_Count]._Dynamic = Section.Rows[i].GetInt(2);
			this->EffectStruct[this->_Count]._Size[0] = Section.Rows[i].GetFloat(3);
			this->EffectStruct[this->_Count]._Static = Section.Rows[i].GetInt(4);
			this->EffectStruct[this->_Count]._Size[1] = Section.Rows[i].GetFloat(5);
			this->EffectStruct[this->_Count]._Bone = Section.Rows[i].GetInt(6);
			this->EffectStruct[this->_Count]._Color[0] = Section.Rows[i].GetFloat(7);
			this->EffectStruct[this->_Count]._Color[1] = Section.Rows[i].GetFloat(8);
			this->EffectStruct[this->_Count]._Color[2] = Section.Rows[i].GetFloat(9);
			this->_Count++;
		}
	}

	HookCall(0x454B2C, this->Run);
	HookCall(0x500B8D, this->Run);

	return true;
}


void cEffect::Run(int lpModel, int ItemModel, int a3, GLfloat alpha, int a5, int a6, int a7, int a8, int a9)
{
	for (int i = 0; i <= Effect._Count; i++)
	{
		sEffect* Result = &Effect.EffectStruct[i];

		if (ItemModel == ITEM(Result->_Type, Result->_Index))
		{
			vec3_t Bone;
			float Unknow = 0;

			DWORD Model = 188 * ItemModel + *(DWORD*)0x5D9D3BC;

			DWORD* ItemTransform = (DWORD*)(0x6EE5100);

			AllowStaticEffect((LPDWORD)Model, &ItemTransform[12 * Result->_Bone], &Unknow, &Bone, 1);

			DynamicEffect(Result->_Dynamic, (DWORD*)&Bone, lpModel + 28, Result->_Color, 3, Result->_Size[0], 0);

			StaticEffect(Model, Result->_Static, Result->_Bone, 0x40000000, Result->_Color, Result->_Size[1]);
		}
	}

	DrawItemEffect(lpModel, ItemModel, a3, alpha, a5, a6, a7, a8, a9);
}

cEffect Effect;
