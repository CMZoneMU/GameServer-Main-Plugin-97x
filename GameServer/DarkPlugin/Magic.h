#pragma once

class CMagicInf
{
public:
	BYTE	m_Level;
	BYTE	m_Skill;
	int     m_DamageMin;
	int     m_DamageMax;

public:
	CMagicInf();
	virtual ~CMagicInf();

	BOOL IsMagic();
	void Clear();
	int  Set(BYTE Skill, BYTE Level);
	int  GetDamage();
};