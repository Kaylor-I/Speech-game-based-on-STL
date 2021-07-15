#include <iostream>
using namespace std;
#include "speechManager.h"

int main() {

	//cout << "Hello world!" << endl;
	//rand number seed
	srand((unsigned)time(NULL));

	//Creat manager object
	SpeechManager sm;

	//test
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "player number: " << it->first << " player name: " << it->second.m_Name
	//		<< " score: " << it->second.m_Score[0] << endl;
	//}

	int choice = 0;


	while (true) {
		sm.showMenu();

		cout << "Please input your choice:" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://start game
			sm.startSpeech(); 
			break;
		case 2:// view past game record
			sm.showRecord();
			break;
		case 3://clean game record
			sm.clearRecord();
			break;
		case 0://exit the system
			sm.exitSystem();
			break;
		default:
			system("cls");//clean screen
			break;
		}
	}

	system("pause");
	return 0;

}