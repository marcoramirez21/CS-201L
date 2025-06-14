//Marco Ramirez
//Program 1 - Numbers
//Analyze 4 input numbers to output the largest, smallest, average, and sort them. 

#include <iostream>// library for standar input/output
#include<algorithm>// Provides std::swap, a simple way to exchange values
#include<cctype>// Provides toupper(), which helps handle both 'y' and 'Y'
using namespace std;// So we don't need to prefix std:: everywhere

int main() {
	int a, b, c,d; // variables to hold user's input numbers
	char again = 'Y'; // controls whether the user wants to repeat the program
	
		//while loop continues as long as user enter 'Y' or 'y'
	while (again == 'Y') {
		cout << "Enter four integers: "; //prompt user to enter four integers
		cin >> a >> b >> c >> d; // input four integers from user

		// Copy original values to sort without affecting the original input
		int n1 = a, n2 = b, n3 = c, n4 = d;
		
		/* Sorting using bubble sort logic with swap
		bubble sort repeatedly compares adjacent values and swaps them 
		to bubble larger values toward the end (ascending order) */

		
		if (n1 > n2) swap(n1, n2); // compare and swap if out of order
		if (n2 > n3) swap(n2, n3);
		if (n3 > n4) swap(n3, n4);

		if (n1 > n2) swap(n1, n2); // second pass to fully sort middle values
		if (n2 > n3) swap(n2, n3);

		if (n1 > n2) swap(n1, n2); // final check to make sure smallest is first 
		// Now n1 to n4 are sorted in increasing order

		//Since it's already sorted, largest is last(n4), smallest is first(n1)
		cout <<"The largest number is: " << n4 << endl; // print largest number
		cout << "The smallest number is: " << n1 << endl;// print smallest number

		// Calculate average using original values.
		double avg = (a + b + c + d) / 4.0; // Use "double" to ensure floating-point division
		cout << "The averge is: " << avg << endl;

		//Display sorted numbers 
		cout << "Numbers in increasing order: "; 
		cout << n1 << "," << n2 << "," << n3 << "," << n4 << endl; // print increasing order

		cout << "Numbers in decreasing order: ";
		cout << n4 << "," << n3 << "," << n2 << "," << n1 << endl; // print decreasing order
	
		//Ask user if they want to reapeat
		cout << "Again (Y/N)?";
		cin >> again;
		again = toupper(again); // normalize input 'y' or 'Y' both work
		cout << endl; // add spacing beforer next loop
	}

}