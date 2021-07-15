#include "speechManager.h"

//constructor
SpeechManager::SpeechManager()
{
	//initial vector and attribute
	this->initSpeech();

	//creat 12 players
	this->creatSpeaker();

	//load the past recoed
	this->loadRecord();
}

//menu function
void SpeechManager::showMenu() 
{
	cout << "********************************************" << endl;
	cout << "*******Welcome atten the speech game!*******" << endl;
	cout << "*******   1. Start speech game       *******" << endl;
	cout << "*******   2. View past game record   *******" << endl;
	cout << "*******   3. Clean game record       *******" << endl;
	cout << "*******   0. Exit the system         *******" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//exit system
void SpeechManager::exitSystem() 
{
	cout << "Welcome to use it next time." << endl;
	system("pause");
	exit(0);
}

//initial vector and values
void SpeechManager::initSpeech() 
{
	//clean vector
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//initial the game round
	this->m_Round = 1;

	//clear record vector
	this->m_Record.clear();
}

//creat 12 player
void SpeechManager::creatSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "player";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//creat players' index
		this->v1.push_back(i + 10001);

		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//start game
void SpeechManager::startSpeech()
{
	//first round

	//1.random draw
	this->speechDraw();

	//2.start game
	this->speechContest();

	//3.show the result of winers
	this->showScore();
	//second round
	this->m_Round++;

	//1.random draw
	this->speechDraw();

	//2.start game
	this->speechContest();

	//3.show the result of winers
	this->showScore();

	//4.save the result to file
	this->saveRecord();
	//reset game
	//initial vector and attribute
	this->initSpeech();
	//creat 12 players
	this->creatSpeaker();

	//load the past recoed
	this->loadRecord();

	cout << "The end of the competition." << endl;
	system("pause");
	system("cls");
}

//random draw
void SpeechManager::speechDraw()
{
	cout << "The number: " << this->m_Round << " round" 
		<< " players are drawing lots" << endl;
	cout << "-------------------------------" << endl;
	cout << "The order is:" << endl;

	if (this->m_Round == 1)
	{
		//first round
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		// second round
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------------------" << endl;
	system("pause");
	cout << endl;

}

//contest
void SpeechManager::speechContest()
{
	cout << "The round number: " << this->m_Round << endl;

	//A tempprary vector to save group's grade
	multimap<double, int, greater<double>>groupScore;

	//record the number of players, 6 is a group
	int num = 0;

	//players vector
	vector<int>v_Src;
	if (this->m_Round == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//iterate all players
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//Judges scoring
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; //600~1000
			//cout << score << " ";
			d.push_back(score);			
		}
		//cout << endl;

		sort(d.begin(), d.end(), greater<double>()); //sort scores
		d.pop_front(); //remove the highest score
		d.pop_back();// remove the lowest score

		double sum = accumulate(d.begin(), d.end(), 0.0f); // the totle scores
		double avg = sum / (double)d.size(); // average score

		//print average score
		/*cout << "Index:" << *it << " name: " << this->m_Speaker[*it].m_Name
			<< " the average score is : " << avg << endl;	*/

		//move average scores to map
		this->m_Speaker[*it].m_Score[this->m_Round - 1] = avg;

		//put the scores to temporary vector
		groupScore.insert(make_pair(avg, *it)); //key is score, value is the number of player
		//Each 6 player get the top 3
		if (num % 6 ==0)
		{
			cout << "The grades of round " << num / 6 << " is: " << endl;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "Index: " << it->second << " name: " << this->m_Speaker[it->second].m_Name
					<< " grade: " << this->m_Speaker[it->second].m_Score[this->m_Round - 1] << endl;
			}
			// get the top 3 grades players
			int count = 0;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Round == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			cout << endl;
			groupScore.clear(); // clear the group 
		}
	}
	cout << "The round " << this->m_Round << " has completed." << endl;
	cout << "-------------------------------" << endl;
	system("pause");
}

//show scores
void SpeechManager::showScore()
{
	cout << "---------Round " << this->m_Round << " ,the advance players info are: " << "--------" << endl;

	vector<int> v;
	if (this->m_Round == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "The index of player: " << *it << " name:" << this->m_Speaker[*it].m_Name
			<< " score" << this->m_Speaker[*it].m_Score[this->m_Round - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showMenu();
}


//save records
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //write file in append mode

	//write each player's info to file
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";

	}
	ofs << endl;

	ofs.close();
	cout << "Records have saved." << endl;

	this->fileIsEmpty = false;

}

//read records
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//read file
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "file is not exist" << endl;
		ifs.close();
		return;
	}

	//file is empty
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "file is empty" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//file is not empty
	this->fileIsEmpty = false;

	ifs.putback(ch);//put back the data that we read previously

	string data;
	int index =0;

	while (ifs >> data)
	{
		//cout << data << endl;
		//
		vector<string>v;//store the 6 string

		int pos = -1; // search the postion of ','
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//do not find out
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);

			start = pos + 1;
		}

		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	//for (map<int,vector<string>>::iterator it = m_Record.begin(); it !=m_Record.end(); it++)
	//{
	//	cout << it->first << "The champion index" << it->second[0] << " score:" << it->second[1] << endl;
	//}
}

//show past record
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "file is empty of not exist." << endl;

	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "The number " << i + 1 << " competition "
				<< "the champion index: " << this->m_Record[i][0] 
				<< " score: " << this->m_Record[i][1] << "\t"
				<< "the second is: " << this->m_Record[i][2] 
				<< " score: " << this->m_Record[i][3] << "\t"
				<< "the third is: " << this->m_Record[i][4] 
				<< " score: " << this->m_Record[i][5] << "\t" << endl;
		}
	}
	
	system("pause");
	system("cls");
}

//delet record file
void SpeechManager::clearRecord()
{
	cout << " Are you sure to clear the recode?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//To clear
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//initial vector and attribute
		this->initSpeech();

		//creat 12 players
		this->creatSpeaker();

		//load the past recoed
		this->loadRecord();

		cout << "Successed clear record." << endl;

	}

	system("pause");
	system("cls");

}

//destructor
SpeechManager::~SpeechManager()
{
}

