// Marco Ramirez 16370924
// Program 1 - Chocolate Factory

#include "Header.h"


const int SIZE_L = 5, SIZE_M = 3, SIZE_S = 1;
const double PRICE_L = 41.25, PRICE_M = 25.80, PRICE_S = 13.50;
const double TAX = 0.072;

static char getMenuChoice() {
    char c;
    cout << "\nChocolate Inventory\n";
    cout << " F: Fill order\nO: Order Inventory\nP: Print Inventory\nE: Exit\nEnter your choice: ";
    cin >> c; c = toupper(c);
    while (c != 'F' && c != 'P' && c != 'E') {
        cout << "WARNING: " << c << " is and invalid choice. Please try again. \nEnter your choice ";
        cin >> c; c = toupper(c);
    }

    return c;
    
}

static double shippingCost(int lbs) {
    if (lbs <= 10) return 8.25;
    if (lbs <= 20) return 12.75;
    if (lbs <= 500) return 15.25;
    return 19.75;
}

static void printReceipt(int l, int m, int s, int total_Lbs, int o) {
    double total_L = l * PRICE_L, total_M = m * PRICE_M, total_S = s * PRICE_S;
    double subtotal = total_L + total_M + total_S, tax = subtotal * TAX, ship = shippingCost(total_Lbs), total = subtotal + tax + ship;

    cout << fixed << setprecision(2) << setw(10);
    cout << "Chocolate Order #" << o << endl;
    cout << "Large Bars: " << setw(4) << l << setw(9) << l * SIZE_L << setw(12) << total_L << endl;
    cout << "Medium Bars: " << setw(4) << m << setw(9) << m * SIZE_M << setw(12) << total_M << endl;
    cout << "Small Bars: " << setw(4) << s << setw(9) << s * SIZE_S << setw(12) << total_S << endl;
    cout << "Sub Total: " << setw(13) << total_Lbs << setw(12) << subtotal << endl;
    cout << "\nTax Total: " << setw(25) << tax << endl;
    cout << "Shiping: " << setw(25) << ship << endl;
    cout << "Total Cost: " << setw(25) << total << endl << endl;
    }

static void fillOrder(int& l, int& m, int& s, int& o) {
    int req, L = 0, M = 0, S = 0;
    int available = l * SIZE_L + m * SIZE_M + s;
    cout << "Enter pounds of chocolate to order: ";
    cin >> req;


    if (req > available) {
        cout << "WARNING: Unable to fill order of " << req << " pounds. Wer are " << req - available << "pounds short. \n\n";
        return;

    }


    L = min(req / SIZE_L, l); req -= L * SIZE_L;
    M = min(req / SIZE_M, m); req -= M * SIZE_M;
    S = min(req, s);         req -= S;


    if (req > 0) {
        cout << " WARNING: Unable to fill order of " << req << " pounds. We are" << req << " pounds shor.\n\n";
        return;
    }


    l -= L; m -= M; s -= S;
    printReceipt(L, M, S, L * SIZE_L + S * SIZE_S, o++);
}

void orderInventory(int& l, int& m, int& s) {
    char type;
    int amount;
    cout << "Enter bar type (L/M/S): ";
    cin >> type;
    type = toupper(type);
    cout << "Enter number of bars to order: ";
    cin >> amount;

    switch (type) {
    case 'L': l += amount; break;
    case 'M': m += amount; break;
    case 'S': s += amount; break;
    default:
        cout << "WARNING: " << type << "is an invalid type. Command ingnored.\n\n ";
        return;
    }

    cout << "An Additional amount " << type << "type bars ordered. New total of" << type << " bars = " << (type == 'L' ? l : type == 'M' ? m : s) << "\n\n";
}

void printInventory (int l, int m, int s) {
            cout << "\nCurrent Inventory:\n";
            cout << "Large Bars: " << setw(4) << l << endl;
            cout << "Medium Bars: " << setw(4) << m << endl;
            cout << "Small Bars: " << setw(4) << s << endl << endl;
}

int main() {
            int l = 1500, m = 1200, s = 7000, o = 1;
            char choice;
            while ((choice = getMenuChoice()) != 'E') {

                if (choice == 'F') fillOrder(l, m, s,o);
                else if (choice == 'O') orderInventory(l, m, s);
                else if (choice == 'P') printInventory(l, m, s);
            }

            cout << "Thank you for using my program!\n";
        
    }
