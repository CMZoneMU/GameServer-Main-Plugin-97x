#pragma once

struct sEffect
{
	int          _Type;
	int          _Index;
	int          _Static;
	int          _Dynamic;
	int          _Bone;
	float        _Color[3];
	float        _Size[2];
};

class cEffect
{
public:
	bool Load();
	static void Run(int lpModel, int ItemModel, int a3, GLfloat alpha, int a5, int a6, int a7, int a8, int a9);

public:
	int          _Count;

private:
	sEffect      EffectStruct[3000];
};

extern cEffect Effect;