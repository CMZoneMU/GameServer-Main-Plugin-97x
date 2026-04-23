#pragma once

class cDescription
{
public:
	static void Load();
	static void Text(char * Text, int Color, int Weight, ...);

private:
	char Buffer[255];

private:
	enum TextColor
	{
		White          = 0x00,
		Blue           = 0x01,
		Red            = 0x02,
		Gold           = 0x03,
		Green          = 0x04,
		WhiteRed       = 0x05,
		Violet         = 0x06,
	};
};

extern cDescription Description;