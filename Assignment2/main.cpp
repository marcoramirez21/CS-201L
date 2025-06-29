#include <iostream>
#include "Games.h"

using namespace std;

int main() {
    double playerBalance = 50.0;
    char choice;

    do {
        cout << "\n=== Game Menu ===\n";
        cout << "1. Craps\n";
        cout << "2. Hangman\n";
        cout << "3. Blackjack\n";
        cout << "Q. Quit\n";
        cout << "Choose a game (1-3 or Q): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = toupper(choice);

        switch (choice) {
        case '1':
            playCraps(playerBalance);
            break;
        case '2':
            playHangman();
            break;
        case '3':
            playBlackjack();
            break;
        case 'Q':
            cout << "Exiting... Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 'Q');

    return 0;
}