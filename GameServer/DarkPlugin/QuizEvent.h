#pragma once

struct sQuiz
{
	BYTE					_Type;
	BYTE					_Index;
	BYTE					_Level;
	BYTE					_Skill;
	BYTE					_Luck;
	BYTE					_Option;
	BYTE					_Excelente;
	int                     _Quantity;
	char					_Question[255];
	char					_Name[255];
};

class cQuiz
{
public:
	char _Syntax[10][25];
	bool Load();
	bool Check(int aIndex, const char* Text);
	void Run();
	void Winner(int aIndex, const char* Text);
	void Finish();
	void Time();
	void StartManual();

public:
	bool					_Active;
	bool                    _Sended;
	
	
	int						_Interval;
	int						_Duration;
	char					_Question[255];
	char					_Answer[255];
	int						_Reward;
	int						_Amount;
	char                    _NameCoin[255];
	bool					_Started;
	int						_Time;
	int						_TimeLeft;
	int						_Count[2];
	char                    _Author[255];

private:
	sQuiz			        QuizStruct[1000];
};

extern cQuiz QuizEvent;


