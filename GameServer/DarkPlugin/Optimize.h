#pragma once

class cOptimize
{
public:
	void Load();
	bool Memory();

private:
	DWORD  _Id;
	HANDLE _Thread;
};

extern cOptimize Optimize;