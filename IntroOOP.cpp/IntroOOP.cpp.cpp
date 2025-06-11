// IntroOOP.cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
using namespace std;

class YouTubeChanel {

public:
	string Name;
	string OwnerName;
	int SubscriptionCount;
	list<string> PublischedVideoTitles;

};

int main()

{
	YouTubeChanel ytChannel;
	ytChannel.Name = "YouCode";
	ytChannel.OwnerName = "JakkeMath";
	ytChannel.SubscriptionCount = 1000;
	ytChannel.PublischedVideoTitles = { "C++ for begginners, HTML & CSS video, C++OPP VIDEO" };
	
	cout << "Name: " << ytChannel.Name << endl;
	cout << "Owner Name : " << ytChannel.OwnerName << endl;
	cout << "Subscription Count: " << ytChannel.SubscriptionCount << endl;
	cout << "Videos: " << endl;

	for (string videoTitle : ytChannel.PublischedVideoTitles) {
		cout << videoTitle << endl;
	}

	system("pause>0");

}

