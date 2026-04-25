#pragma once

class Commands
{
public:
	bool Load();
	bool Management(LPBYTE Protocolo, int aIndex);
	void Post(int aIndex, char* msg);
	void Add(int aIndex, char* msg, int Status);
	void ReAdd(int aIndex);
	void Clear(int aIndex);
	void Killer(int aIndex);
	void Ware(int aIndex, char* msg);
	static void Change(int aIndex);
	void Money(int aIndex);
	void Premiar(int aIndex, char* msg);
	void MoveAll(int aIndex, char* msg);
	void Skin(int aIndex, char* msg);
	void Move(int aIndex, char* msg);
	void FireWork(int aIndex);
	void Evento(int aIndex, char* msg);
	void Register(int aIndex);
	static void Run(void * lpParam);
	void Disconnect(int aIndex, char* msg);
	void Drop(int aIndex, char* msg);
	bool War(int aIndex, char* msg);
	void Track(int aIndex, char* msg);
	void Trace(int aIndex, char* msg);
	void Class(int aIndex, int Type);
	void Information(int aIndex);
	void Nick(int aIndex, char* msg);
	void Rei(int aIndex, char* msg);
	void Finish(int aIndex);
	void OpenWare(int aIndex);

public:
	bool					_Active[16];
	bool					_Vip[7];
	bool                    _Event;
	int					    _Color;
	int                     _Type;
	int					    _Ware[4];
	int					    _Level[8];
	int					    _Zen[8];
	int                     _Number;
	int                     _MapNumber[2];
	int                     _X[2];
	int                     _Y[2];
	int                     _Count;
	DWORD		            _Delay;
	char					_Syntax[19][25];
	char					_Formato[255];
	char                    _Notice[255];
	char                    _Buffer[255];
	char                    _Name[2][255];
};

extern Commands Command;