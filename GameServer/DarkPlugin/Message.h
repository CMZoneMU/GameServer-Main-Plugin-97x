#pragma once

class cMessage
{
public:
	bool Load();

public:
	char _Buffer[5][255];
};

extern cMessage Message;