#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <time.h>
#include <fstream>

//Design speech manager class
class SpeechManager
{
public:

	//constructor
	SpeechManager();

	//menu function
	void showMenu();

	//exit system
	void exitSystem();

	//creat 12 player
	void creatSpeaker();

	//start game
	void startSpeech();

	//random draw
	void speechDraw();

	//contest
	void speechContest();

	//show scores
	void showScore();

	//save records
	void saveRecord();

	//read records
	void loadRecord();

	//show past record
	void showRecord();

	//delet record file
	void clearRecord();

	//judge file if empty
	bool fileIsEmpty;

	//store past records
	map<int, vector<string>>m_Record;

	//destructor
	~SpeechManager();

	//initial vector and values
	void initSpeech();

	//Save first players' info
	vector<int>v1;
	//Save second players' info
	vector<int>v2;
	//Save the first three player's info
	vector<int>vVictory;

	//Save index and info
	map<int, Speaker>m_Speaker;

	int m_Round;


private:

};

