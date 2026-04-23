#pragma once

struct VAngle
{
	float X;
	float Y;
	float Z;
};

struct HEALTH_BAR
{
	short Index;
	BYTE Rate;
};

class cHealthBar
{
public:
	void Clear();
	void Insert(short Index, BYTE Rate);
	HEALTH_BAR* Get(short Index);
	static void Draw();

private:
	char _Buffer[80];
};

extern cHealthBar HPBar;