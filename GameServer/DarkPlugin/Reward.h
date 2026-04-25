#pragma once

struct sReward
{
	int                 _Day;
	int                 _Amount;
	char                _Column[255];
	char                _Coin[255];
};

class cReward
{
public:
	cReward();

public:
	bool Load();
	void Connect(int aIndex);
	void Run(LPOBJ lpobj);

private:
	bool                _Active;
	int                 _Count;

private:
	sReward             RewardStruct[7];
};

extern cReward Reward;