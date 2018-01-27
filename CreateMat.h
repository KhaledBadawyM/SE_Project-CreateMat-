#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<vector>
#include <stdlib.h>
#include<queue>
#include<algorithm>
#include<exception>
using namespace std;

class CreateMat
{
private:
	string name;  //there was pointer to name
	string body;
	vector<vector<vector<string>>>matConcat;
	queue<char>semicolone_colon_queue;   /////////////////////was queue insted of vector this change to could use [order]
	vector<CreateMat>data;
	vector<int>ordering;
	int count;  // initialization in  separat_pracket() 
	int semicolon_count;
	vector<vector<char>>brackts;
	queue<char>colon;
	stack<int>indx; int n = 0;
public:
	vector<vector<string>>finalMatrix;
	CreateMat(string s, vector<CreateMat>input);
	~CreateMat();
	string getName();
private:	
	void separat_pracket(string S);
	void subMatrix(string subS);
	void concatenate();
	void match(vector<vector<string>> a, int flag);

	
	
};

