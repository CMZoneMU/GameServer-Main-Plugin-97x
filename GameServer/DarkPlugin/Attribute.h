#pragma once

struct sAttribute
{
	int 		     _Type;
	int 			 _Index;
	int 			 _Defense;
	int 		 	 _Attack;
};

class cAttribute
{
public:
	bool Load();
	void Run(int aIndex);

public:
	bool             _Active;
	int              _Count;

public:
	sAttribute		 AttributeStruct[1000];
};

extern cAttribute Attribute;