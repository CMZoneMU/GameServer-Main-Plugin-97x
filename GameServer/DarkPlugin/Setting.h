#pragma once

class cSetting
{
public:
	bool Load();

public:
	int  _Type;
	int  _MaxReset;
	int  _PvP;
	int  _CheckSum;
	int  _Personal;
	int  _Reflect;
	int  _Mapas;
	int  _Announce[0];
};

extern cSetting Setting;