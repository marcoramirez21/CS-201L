
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Inventory counts
    int large = 620, medium = 500, small = 700;
    const int LARGE_POUND = 5, MEDIUM_POUND = 3, SMALL_POUND = 1;
    const double PRICE_LARGE = 27.99, PRICE_MEDIUM = 21.99, PRICE_SMALL = 14.99;

    int orderNumber = 1;
    char choice;

    do {
        int poundsRequested;
        cout << "Order #" << orderNumber << " - Enter pounds of chocolate needed: ";
        cin >> poundsRequested;

        if (poundsRequested <= 0) {
            cout << "Invalid order amount. Please enter a positive number.\n";
            continue; // ask again without incrementing order number
        }

        // Calculate bars needed using largest bars first
        int usedLarge = min(poundsRequested / LARGE_POUND, large);
        int remaining = poundsRequested - usedLarge * LARGE_POUND;

        int usedMedium = min(remaining / MEDIUM_POUND, medium);
        remaining -= usedMedium * MEDIUM_POUND;

        int usedSmall = min(remaining / SMALL_POUND, small);
        remaining -= usedSmall * SMALL_POUND;

        // Check if order can be fulfilled
        if (remaining > 0) {
            cout << "Order cannot be fulfilled due to insufficient inventory.\n";
        }
        else {
            // Update inventory
            large -= usedLarge;
            medium -= usedMedium;
            small -= usedSmall;

            // Calculate cost
            double cost = usedLarge * PRICE_LARGE + usedMedium * PRICE_MEDIUM + usedSmall * PRICE_SMALL;

            // Display order summary
            cout << fixed << setprecision(2);
            cout << "\nOrder #" << orderNumber << " fulfilled:\n";
            cout << "  Large bars used: " << usedLarge << "\n";
            cout << "  Medium bars used: " << usedMedium << "\n";
            cout << "  Small bars used: " << usedSmall << "\n";
            cout << "Total cost: $" << cost << "\n";

            // Display remaining inventory
            cout << "Remaining inventory:\n";
            cout << "  Large bars: " << large << "\n";
            cout << "  Medium bars: " << medium << "\n";
            cout << "  Small bars: " << small << "\n";

            orderNumber++;
        }

        cout << "\nWould you like to enter another order? (Y/N): ";
        cin >> choice;
        cout << endl;

    } while (choice == 'Y' || choice == 'y');

    cout << "Thank you for using the chocolate warehouse system.\n";
    return 0;
}


