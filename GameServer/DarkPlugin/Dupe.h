#pragma once

class cDupe
{
public:
	bool Serial(LPOBJ lpObj, DWORD Serial, int Local);
	void Run(LPOBJ lpObj);

private:
	bool                _Detected;
	int					_Count[2];
};

extern cDupe Dupe;