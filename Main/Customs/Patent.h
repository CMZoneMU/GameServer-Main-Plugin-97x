#pragma once

class cPatent
{
public:
	static void LoadImagesEx();
	static void Image(int Type, char * Folder, int Id);
	void GCReqRankLevelUser(PMSG_CUSTOM_RANKUSER * aRecv);
	void Run();

public:
	CUSTOM_RANKUSER_DATA RankStruct[10000];
};

extern cPatent Patent;