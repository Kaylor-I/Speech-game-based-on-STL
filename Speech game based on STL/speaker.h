#pragma once
#include<iostream>
using namespace std;

class Speaker
{
public:
	Speaker();

	string m_Name;
	double m_Score[2];

	~Speaker();

private:

};
inline Speaker::Speaker()
{
}

inline Speaker::~Speaker()
{
}

