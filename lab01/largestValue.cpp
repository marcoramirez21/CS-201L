#include <iostream>
using namespace std;
int main() {
	int a, b, c,d;

	char again = 'Y';
	while (again == 'Y') {
		cout << "Enter 4 integers: ";
		cin >> a >> b >> c >> d;
		int large = a;
		if (b > large)
			large = b;
		if (c > large)
			large = c;
		if (d > large)
			large = d;

		//Find the smallest number
		int smallest = a;
		if (b < smallest)
			smallest = b;
		if (c < smallest)
			smallest = c;
		if (d < smallest)
			smallest = d;
		
		//print in increasing order 
		
		//print in increasing order 
		

		cout <<"The largest number is: " << large << endl;
		cout << "The smallest number is: " << smallest << endl;

		double avg = (a + b + c + d) / 4;
		cout << "The averge is: " << avg << endl;

	
		cout << "Again ?";
		cin >> again;
	}

}