#pragma once

typedef void(*pMapItemInit)(void);
extern pMapItemInit MapItemInit;
typedef void(*pLoadMapAttr)(const char*, int);
extern pLoadMapAttr LoadMapAttr;
typedef const char*(*pGetNewPath)(const char*, int);
extern pGetNewPath GetNewPath;

class cMaps
{
public:
	static bool Load();
	static bool LoadLimit();
	static bool LoadAtt();
	static void LoadMapAtt(unsigned int index, const char *name);
};

extern cMaps Maps;