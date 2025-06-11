// Inheritance Oriented Object programming

#include <iostream>
#include <list>
using namespace std;

class YouTubeChannel {
private:
	string Name;	
	int SubscriptionCount = 0;
	list<string> PublishedVideoTitles;

protected:
	string OwnerName;

public:
	YouTubeChannel(string name, string ownerName)
	: Name(name), OwnerName(ownerName) { }

	void GetInfo() {
		cout << "Name: " << Name << endl;
		cout << "Owner Name : " << OwnerName << endl;
		cout << "Subscription Count: " << SubscriptionCount << endl;
		cout << "Videos: " << endl;
		for (string videoTitle : PublishedVideoTitles) {
			cout << "- " << videoTitle << endl;
		}

	}
	void Subscribe() { SubscriptionCount++; }

	void Unsubscribe() {
		if (SubscriptionCount > 0)
			SubscriptionCount--;
	}

	void PublishedVideo(string videoTitle) {
		PublishedVideoTitles.push_back(videoTitle);
	}

};
class CookingYoutubeChannel: public YouTubeChannel {
public:
	CookingYoutubeChannel(string name, string ownerName): YouTubeChannel(name, ownerName) {

	}
	void Practice() {
		cout << OwnerName <<"is practicing cooking, learnig new recipes, experimentig with spices..."<<endl;
	}

};

int main()

{
	CookingYoutubeChannel cookingYtChannel("Lisa's kitchen", "Lisa");
	cookingYtChannel.PublishedVideo("Apple pie");
	cookingYtChannel.PublishedVideo("Chocolate cake");
	cookingYtChannel.Subscribe();
	cookingYtChannel.GetInfo();
	cookingYtChannel.Practice();

	CookingYoutubeChannel cookingYtChannel2("Jhon's kitchen", "Jhon");
	
	cookingYtChannel2.Practice();

 
	system("pause>0");

}