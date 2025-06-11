// Contructor and class methods

#include <iostream>
#include <list>
using namespace std;

class YouTubeChanel {
public:
	string Name;
	string OwnerName;
	int SubscriptionCount;
	list<string> PublischedVideoTitles;

	YouTubeChanel(string name, string ownerName) {
		Name = name;
		OwnerName = ownerName;
		SubscriptionCount = 0;

}
	void Getinfo() {
		cout << "Name: " << Name << endl;
		cout << "Owner Name : " << OwnerName << endl;
		cout << "Subscription Count: " << SubscriptionCount << endl;
		cout << "Videos: " << endl;

		for (string videoTitle : PublischedVideoTitles) {
			cout << videoTitle << endl;

		}

	}
};

	int main()

	{
		YouTubeChanel ytChannel1("YouCode", "JakkeMath");
		ytChannel1.PublischedVideoTitles.push_back("C++ f0r begginers");
		ytChannel1.PublischedVideoTitles.push_back("HTML & CSS for begginers");
		ytChannel1.PublischedVideoTitles.push_back("C++ OOP");
		YouTubeChanel ytChannel2("Typing_Codexs", "JaxBlue");

		ytChannel1.Getinfo();
		ytChannel2.Getinfo();


		system("pause>0");

	}