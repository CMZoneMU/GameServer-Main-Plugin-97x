#include "StdAfx.h"

bool cAttribute::Load()
{
	this->_Count = 0;

	memset(this->AttributeStruct, 0, sizeof(this->AttributeStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string("./Data/Attribute.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->AttributeStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->AttributeStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->AttributeStruct[this->_Count]._Defense = Section.Rows[i].GetInt(2);
			this->AttributeStruct[this->_Count]._Attack = Section.Rows[i].GetInt(3);
			this->_Count++;
		}
	}

	return true;
}

void cAttribute::Run(int aIndex)
{
	CItem * Right = &gObj[aIndex].pInventory[0];
	CItem * Left = &gObj[aIndex].pInventory[1];
	CItem * Helm = &gObj[aIndex].pInventory[2];
	CItem * Armor = &gObj[aIndex].pInventory[3];
	CItem * Pants = &gObj[aIndex].pInventory[4];
	CItem * Gloves = &gObj[aIndex].pInventory[5];
	CItem * Boots = &gObj[aIndex].pInventory[6];

	for (int i = 0; i < this->_Count; i++)
	{
		if (this->AttributeStruct[i]._Attack > 0)
		{
			if (Right->m_Type == ITEMGET(this->AttributeStruct[i]._Type, this->AttributeStruct[i]._Index))
			{
				gObj[aIndex].m_AttackDamageMinRight = gObj[aIndex].m_AttackDamageMinRight * this->AttributeStruct[i]._Attack / 100;
				gObj[aIndex].m_AttackDamageMaxRight = gObj[aIndex].m_AttackDamageMaxRight * this->AttributeStruct[i]._Attack / 100;
			}

			if (Left->m_Type == ITEMGET(this->AttributeStruct[i]._Type, this->AttributeStruct[i]._Index))
			{
				gObj[aIndex].m_AttackDamageMinLeft = gObj[aIndex].m_AttackDamageMinLeft * this->AttributeStruct[i]._Attack / 100;
				gObj[aIndex].m_AttackDamageMaxLeft = gObj[aIndex].m_AttackDamageMaxLeft * this->AttributeStruct[i]._Attack / 100;
			}
		}

		if (this->AttributeStruct[i]._Defense > 0)
		{
			if (Helm->m_Type == ITEMGET(this->AttributeStruct[i]._Type, this->AttributeStruct[i]._Index))
			{
				gObj[aIndex].m_Defense += this->AttributeStruct[i]._Defense;
			}

			if (Armor->m_Type == ITEMGET(this->AttributeStruct[i]._Type, this->AttributeStruct[i]._Index))
			{
				gObj[aIndex].m_Defense += this->AttributeStruct[i]._Defense;
			}

			if (Pants->m_Type == ITEMGET(this->AttributeStruct[i]._Type, this->AttributeStruct[i]._Index))
			{
				gObj[aIndex].m_Defense += this->AttributeStruct[i]._Defense;
			}

			if (Gloves->m_Type == ITEMGET(this->AttributeStruct[i]._Type, this->AttributeStruct[i]._Index))
			{
				gObj[aIndex].m_Defense += this->AttributeStruct[i]._Defense;
			}

			if (Boots->m_Type == ITEMGET(this->AttributeStruct[i]._Type, this->AttributeStruct[i]._Index))
			{
				gObj[aIndex].m_Defense += this->AttributeStruct[i]._Defense;
			}
		}
	}
}

cAttribute Attribute;