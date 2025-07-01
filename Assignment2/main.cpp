#include <iostream> // Includes the standard input/output stream library for console operations.
#include "Games.h"  // Includes the custom header file that declares all game functions and helper utilities.

// Using namespace std; is common in smaller projects. For larger projects,
// explicitly using 'std::' (e.g., std::cout) is often preferred to avoid naming conflicts.
using namespace std;

/**
 * @brief Main entry point for the multi-game program.
 *
 * Displays a menu to select between Craps, Hangman, Blackjack, or Quit.
 * Manages the player's balance for Craps across sessions.
 * Loops until the player chooses to quit.
 */
int main() {
    // Declares a variable to store the player's balance for the Craps game.
    // It's initialized here so its value persists across multiple Craps games
    // played within the same program session. This demonstrates variable scope.
    double playerBalance = 50.0;
    char choice; // Variable to store the user's menu selection.
    // This do-while loop creates the main program menu.
    // It ensures the menu is displayed at least once and continues to loop
    // until the user explicitly chooses to quit.
    do {
        // Display the main game menu options to the user.
        cout << "\n=== Game Menu ===\n";
        cout << "1. Craps\n";
        cout << "2. Hangman\n";
        cout << "3. Blackjack\n";
        cout << "Q. Quit\n";
        cout << "Choose a game (1-3 or Q): ";

        // Get user input for choice.
        cin >> choice;
        // Clear input buffer: This is crucial after `cin >> choice;` to remove the
        // newline character left by pressing Enter. If not cleared, it could interfere
        // with subsequent `cin` operations within the game functions.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Convert choice to uppercase for case-insensitive comparison.
        // `static_cast<unsigned char>(choice)` is used for safe conversion with `toupper`.
        choice = toupper(static_cast<unsigned char>(choice));

        // The switch statement handles different actions based on the user's menu choice.
        // Each 'case' corresponds to a specific game or the quit option.
        switch (choice) {
        case '1':
            // Call the Craps game function.
            // `playerBalance` is passed by reference (`double& playerBalance` in function signature),
            // meaning changes made to `playerBalance` inside `playCraps` will directly
            // affect this `playerBalance` variable in `main`.
            playCraps(playerBalance);
            break; // 'break' exits the switch statement.
        case '2':
            // Call the Hangman game function.
            // This game does not involve a persistent balance, so no specific parameters are passed.
            playHangman();
            break;
        case '3':
            // Call the Blackjack game function.
            // Similar to Hangman, this game does not track a persistent balance in this context.
            playBlackjack();
            break;
        case 'Q':
            // User chose to quit. Display an exit message.
            cout << "Exiting... Goodbye!\n";
            break;
        default:
            // Handles any input that is not '1', '2', '3', or 'Q'.
            cout << "Invalid option. Try again.\n";
            // No break needed here as it's the last case.
        }
    } while (choice != 'Q'); // The loop continues as long as the user has not chosen to 'Q'uit.
    // Return 0 indicates that the program executed successfully.
    return 0;
}
