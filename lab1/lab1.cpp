//Marco Ramirez
//Program 2 - Distance
//This program compares the distances of two points from the origin and repeats until user quits.

#include <iostream> // allow input/output using cin and cout.
#include <math.h> // Provides math fuctions.
#include <cstdlib> // Used for rand() and srand() for generating random numbers.
#include <ctime> // Required for time() to get the current system as a seed for randomness.
#include <iomanip> // Allows setting output precision.

using namespace std;// Avoids prefixing std:: to standar fuctions.

// Function to generate a random integer between -10 and 10.
static int randomCoordinate() {
	return rand() % 21 - 10; // rand() % 21 gives 0-20, substract 10 to get -10 to 10.
}

//Function to calculate the distance of a point from the origen
static double distanceToOrigen(int x, int y) {
	return sqrt(x * x + y * y);// Pythagorean theorem to find the distance
}

// Function to get validated user input between -10 to 10 
//const means the function cannot modify the original string passed in. 
static int getValidatedInput(const string& prompt) { // string& means the function will work with the original object via REFERENCE "&". 
	int value;
	while (true) { // Repeats until valid input is entered. 
		cout << prompt; // Displays the input prombp
		cin >> value; // Take user input.

		if (cin.fail() || value < -10 || value > 10) { // invalid input check ( non-integer or out of range)
			cin.clear(); // clears input error
			cin.ignore(1000, '\n'); // Discard invalid characters
			cout << "Invalid input. Please enter an integer between -10 to 10.\n"; // Output error message
		}
		else
		{
			return value; // If input is valid, returns it to the caller "main()".
		}
	}
}

int main() //Controlos the program flow, handles user input, calculates distances and reapeats based on user choice.
{
	srand(static_cast <unsigned int> (time(0))); // Seeds random number generator with current the system time.
	/* static_cast <unsigned int> converts the result to an unsigned int, which is requiared by srand().
	Seeding refers to initializing the random number generator with unique value from time(0) (current system time), 
	ensuring that srand() generates a different sequence of numbers each time the program runs, preventing predictability*/
	
	char again; // Holds user's choice to repeat the program.

	do {// The loop runs at least once, then repeats if 'again' is 'Y' or 'y', otherwise it exits the loop. 
		int x1,y1,x2,y2; // Coordinates of two points.
		char choice; // User choice for input mode.

		cout << "Type 'E' to Enter the values manualy, or Type any other letter to 'Generate randomly': "; // Prompt to choose input method (manual or random). 
		cin >> choice; // Read choice.

		if (choice == 'E' || choice == 'e') {// The statement is checking if the input "choice" is 'E' or 'e' (case-insensitive). 
			// Call getValidadtedInput() to ensure coordinates are between -10 and 10.
			x1 = getValidatedInput("Enter x1 (-10 to 10): ");
			y1 = getValidatedInput("Enter y1 (-10 to 10): ");
			x2 = getValidatedInput("Enter x2 (-10 to 10): ");
			y2 = getValidatedInput("Enter y2 (-10 to 10): ");
		} else {// If the user chooses to generate random values
			//Generate random values of: x1/y1/x2/y2 between -10 and 10
			x1 = randomCoordinate();
			y1 = randomCoordinate();
			x2 = randomCoordinate();
			y2 = randomCoordinate();
			cout << "Random values generated.\n"; // Let user know that random values have been generated.
		}

		double dist1 = distanceToOrigen(x1, y1); // Calculates the distance of point 1 from the origin.
		double dist2 = distanceToOrigen(x2, y2); // Calculates the distance of point 2 from the origin.

		cout << fixed << setprecision(2); // Set decimal precision to 2 places.
		
		// Display points and their distances.
		cout << "Point 1: ( " << x1 << ", " << y1 << " ); -> Distance to origen " << dist1 << endl;
		cout << "Point 2: ( " << x2 << ", " << y2 << " ); -> Distance to origen " << dist2 << endl;

		// Compare and display which point is closer
		if (dist1 < dist2) // If point 1 is closer to the origin. 
			cout << " Point 1 is closer to the origin.\n";
		else if (dist2 < dist1) // If point 2 is closer to the origin.
			cout << "Point 2 is closer to the origin.\n";
		else // If both points are equally distant grom the origin.
			cout << "Both points are equally close to the origen.\n";

		cout << "Type 'Y' to RUN again. Type any other letter to END the program: "; // Ask user to repeat.
		cin >> again; // Read the user's choice.
	}
	while (again == 'Y' || again == 'y'); // Continue if 'Y' or 'y' entered.
		cout << "Program ended.\n"; // End message. 

			return 0; // End of program! The main fuction return 0 for succesfull execution.

	}





