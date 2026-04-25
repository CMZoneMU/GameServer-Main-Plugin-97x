#pragma once

class cNews
{
public:
	cNews();

public:
	bool Load();
	void Run();

public:
	bool									_Active;
	int										_Interval;
	int										_Count;

	std::vector<std::array<std::string, 3>> _Notice;
	std::vector<std::array<std::string, 3>>::const_iterator _Last;
};

extern cNews News;