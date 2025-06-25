// Marco Ramirez 
// Program 1 - Chocolate Factory

#include "Header.h" // Includes a custom header file. 

// Constants representing bar sizes in pounds. 
// It encapsulates fixed values for chocolate weights and pricing to simplify updates  
const int SIZE_L = 5, SIZE_M = 3, SIZE_S = 1;
// Consttants representing bar prices. 
const double PRICE_L = 41.25, PRICE_M = 25.80, PRICE_S = 13.50;
const double TAX = 0.072; // Tax rate

// Function to diplay menu and get a valid user choice. 
//Prevents errors by allowing only valid commands.
//Keeps asking until a valid option(F, O, P, or E ) is chosen.
static char getMenuChoice() {
    char c;
    cout << "\nChocolate Inventory\n";
    cout << "F: Fill order\nO: Order Inventory\nP: Print Inventory\nE: Exit\nEnter your choice: ";
    cin >> c; c = toupper(c); // Convert choice to uppercase 
    // Loop until user enters a valid option. 
    while (c != 'F' && c != 'P' && c != 'E' && c != 'O') {
        cout << "WARNING: " << c << " is an invalid choice. Please try again. \nEnter your choice: ";
        cin >> c; c = toupper(c);
    }
     return c;
}
// Function to determine shipping cost based on weight
// Applies tiered flat rates that simulate real-worl shipping charges.
static double shippingCost(int lbs) {
    if (lbs <= 10) return 8.25;       // 1-10 pounds
    else if (lbs <= 20) return 12.75; // 11-20 pounds
    else if (lbs <= 50) return 15.25; // 21-50 pounds
    return 19.75; // Shipping cost for orders over 50 pounds. 
}
// Function to print a detailed receipt for an order.Uses formatting to generate an organized receipt. 
static void printReceipt(int l, int m, int s, int total_Lbs, int orderNumber) {
    // Calculate total cost per bar size 
    double total_L = l * PRICE_L, total_M = m * PRICE_M, total_S = s * PRICE_S;
    // Calculate subtotal, tax, shipping, and final total
    double subtotal = total_L + total_M + total_S;
    double tax = subtotal * TAX;
    double ship = shippingCost(total_Lbs);
    double total = subtotal + tax + ship;
    // Print a organized and formated receipt
    cout << fixed << setprecision(2) << setw(10);
    cout << "\nChocolate Order #" << orderNumber << endl;
    cout << "Large Bars:  " << setw(4) << l << setw(8) << l * SIZE_L << setw(8) << "$" << setw(10) << total_L << endl;
    cout << "Medium Bars: " << setw(4) << m << setw(8) << m * SIZE_M << setw(8) << "$" << setw(10) << total_M <<endl;
    cout << "Small Bars:  " << setw(4) << s << setw(8) << s * SIZE_S << setw(8) << "$" << setw(10) << total_S << endl;
    cout << "Sub Total:   " << setw(12) << total_Lbs << setw(8) << "$" << setw(10) << subtotal << endl;
    cout << "\nTax Total:   " << setw(37) << "$" << setw(10) << tax << endl;
    cout << "Shipping:    " << setw(37) << "$" << setw(10) << ship << endl;
    cout << "Total Cost:  " << setw(37) << "$" << setw(10) << total << endl << endl;
    }
// Function to process an order request. Fulfills a customer request based on available inventory. 
// Fulfills orders using large bars first, then smaller ones. Updates inventory only if the full order can be met. 
static void fillOrder(int& l, int& m, int& s, int& orderNumber) {
    // (req=requested), L=large, M=medium, S=small. 
    int req, L = 0, M = 0, S = 0;
    // Calculate total available chocolate in pounds
    int available = l * SIZE_L + m * SIZE_M + s * SIZE_S;
    cout << "Enter pounds of chocolate to order: ";
    cin >> req;
    // If the requested ammount exceed total available inventory, print warning and cancel order.
    if (req > available) {
        cout << "WARNING:  Unable to fill order of " << req << " pounds. We are " << req - available << " pounds short. \n\n";
        return;}
    /* Calculate max(L)arge bars to use : either how many fit in req(req / SIZE_L) or inventory(l), whichever is less.
    substract used (L)arge bars' weight from req. */
    L = min(req / SIZE_L, l); req -= L * SIZE_L;
    M = min(req / SIZE_M, m); req -= M * SIZE_M;
    /* For small bars, 1 bar = 1 pound, so use as many as required or as many as available (s), whichever is less.
    then substract used (S)mall bars from rmaining request*/
    S = min(req, s);          req -= S;
    
    if (req > 0) {// If we still can't fulfill the exact request 
        cout << "WARNING: Unable to fill order of " << req << " pounds. We are " 
             << req << " pounds short. We are sorry for the inconvenience.\n\n";
        return; 
    }
    l -= L; m -= M; s -= S;  // Update inventory
    // Print receipt and increment order number
    int total_Lbs = L * SIZE_L + M * SIZE_M + S * SIZE_S;
    printReceipt(L, M, S, total_Lbs ,orderNumber++); // o is order number
}
// Function to add inventory. Adds more chocolate bars to inventory.  
// Takes input for bar type and quantity, then updates inventory.
// Simulates restocking to keep the program running smoothly.
void orderInventory(int& l, int& m, int& s) { // & 
    char type;
    int amount;
    cout << "Enter bar type (L/M/S): ";
    cin >> type;
    type = toupper(type);
    cout << "Enter number of bars to order: ";
    cin >> amount;

    // Update the appropriate inventory based on type
    switch (type) {
    case 'L': l += amount; break;
    case 'M': m += amount; break;
    case 'S': s += amount; break;
    default:
        cout << "WARNING: " << type << " is an invalid type. Command ignored.\n\n ";
        return;
    }
    // Confirmation message 
    cout << "An additional amount " << type << " bars ordered. New total of " << type << " bars = "
         << (type == 'L' ? l : type == 'M' ? m : s) << endl << endl;
}

// Function to display current inventory levels (current number of each bar size).
// Helps user track inventory and plan orders.
void printInventory (int l, int m, int s) {
            cout << "\nCurrent Inventory:\n";
            cout << "Large Bars: " << setw(4) << l << endl;
            cout << "Medium Bars: " << setw(4) << m << endl;
            cout << "Small Bars: " << setw(4) << s << endl << endl;
}
// Main function acts as the main control center for the whole system.
// Set up inventory, runs the menu loop, handles actions, and exits cleanly.
int main() {
            // Initialize inventory and order number
            int l = 1500, m = 1200, s = 7000, orderNumber = 1;
            char choice;
            // Main loop for menu options
            while ((choice = getMenuChoice()) != 'E') {
                if (choice == 'F') fillOrder(l, m, s,orderNumber);
                else if (choice == 'O') orderInventory(l, m, s);
                else if (choice == 'P') printInventory(l, m, s);
            }
            // Exit message. 
            cout << "Thank you for using my program!\n";
            return 0;
        
    }
