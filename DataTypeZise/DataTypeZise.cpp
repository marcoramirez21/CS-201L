#include <iostream>
using namespace std;

int main()
{
	int YearOBirt = 1993;
	char gender = 'f';
	bool isOlderthan18 = true;
	float GPA = 4;
	double balance = 387985398;

	cout << "Size of int: " << sizeof(int) << "bytes\n";
	cout << "Int min value is: " << INT_MIN << endl; //-1,-2,-3,...-2147483648
	cout << "Int max value is: " << INT_MAX << endl; //0,1,2,3,...+2147483647

	cout << "Size of bool is: " << sizeof(bool) << " bytes\n";
	cout << "Size of char is: " << sizeof(char) << " bytes\n";
	cout << "Size of float is: " << sizeof(float) << " bytes\n";
	cout << "Size of double is: " << sizeof(double) << " bytes\n";


	system("pause>0");

}