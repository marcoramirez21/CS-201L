//Marco Ramirez
//Program 2 - Distance
//Calculate the distance of each pit to the origen

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a ramdom integer between -10 and 10

int randomCoordinate() {
	return rand() % 21 - 10; // Generate a number between -10 to 10


}

int main()
{
	srand(time(0)); // Ensures randomness byr setting a seed based on the current time
	cout << " Random coordinate: " << randomCoordinate() << endl;
	return 0;

}



