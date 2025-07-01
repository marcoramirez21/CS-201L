#include <iostream>   // For input/output stream functionality (cin, cout)
#include <iomanip>    // For formatting output (e.g., setprecision)

using namespace std;  // Avoids needing to use std:: prefix throughout

int main() {
    // === Declaration and Initialization of Inventory and Constants ===
    int large = 620, medium = 500, small = 700;  // Current inventory
    const int LARGE_POUND = 5, MEDIUM_POUND = 3, SMALL_POUND = 1;  // Bar sizes in pounds
    const double PRICE_LARGE = 27.99, PRICE_MEDIUM = 21.99, PRICE_SMALL = 14.99;  // Sale prices

    int orderNumber = 1;   // Tracks number of orders sequentially
    char choice;           // User's decision to continue or stop

    // === Main Loop: Program keeps running until user chooses to exit ===
    do {
        int poundsRequested;  // Variable to store user input
        cout << "Order #" << orderNumber << " - Enter pounds of chocolate needed: ";
        cin >> poundsRequested;  // User enters how many pounds of chocolate they want

        // === Input Validation ===
        if (poundsRequested <= 0) {
            cout << "Invalid order amount. Please enter a positive number.\n";
            continue;  // Skip rest of loop if invalid
        }

        // === Begin Order Fulfillment: Try to use largest bars first ===
        int usedLarge = min(poundsRequested / LARGE_POUND, large);  // Use as many large bars as possible
        int remaining = poundsRequested - usedLarge * LARGE_POUND;  // Subtract large bar weight from total

        int usedMedium = min(remaining / MEDIUM_POUND, medium);     // Then use medium bars
        remaining -= usedMedium * MEDIUM_POUND;

        int usedSmall = min(remaining / SMALL_POUND, small);        // Finally, use small bars
        remaining -= usedSmall * SMALL_POUND;

        // === Check If Order Can Be Fulfilled ===
        if (remaining > 0) {
            // If not enough inventory to fulfill exact weight, do not process order
            cout << "Order cannot be fulfilled due to insufficient inventory.\n";
        }
        else {
            // === Update Inventory ===
            large -= usedLarge;
            medium -= usedMedium;
            small -= usedSmall;

            // === Calculate Total Cost of Order ===
            double cost = usedLarge * PRICE_LARGE + usedMedium * PRICE_MEDIUM + usedSmall * PRICE_SMALL;

            // === Print Order Summary and Inventory Report ===
            cout << fixed << setprecision(2);  // Ensures 2 decimal places for money formatting
            cout << "\nOrder #" << orderNumber << " fulfilled:\n";
            cout << "  Large bars used: " << usedLarge << "\n";
            cout << "  Medium bars used: " << usedMedium << "\n";
            cout << "  Small bars used: " << usedSmall << "\n";
            cout << "Total cost: $" << cost << "\n";

            cout << "Remaining inventory:\n";
            cout << "  Large bars: " << large << "\n";
            cout << "  Medium bars: " << medium << "\n";
            cout << "  Small bars: " << small << "\n";

            orderNumber++;  // Increase order number for next loop
        }

        // === Ask User to Continue or Quit ===
        cout << "\nWould you like to enter another order? (Y/N): ";
        cin >> choice;
        cout << endl;

    } while (choice == 'Y' || choice == 'y');  // Loop continues if user enters 'Y' or 'y'

    // === Program Ends Here ===
    cout << "Thank you for using the chocolate warehouse system.\n";
    return 0;  // Signals successful program termination
}