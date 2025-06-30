#include "Games.h" // Assuming this header would contain declarations if split into multiple files
#include <iostream> // For standard input/output operations (cout, cin)
#include <string>   // For std::string class (text manipulation)
#include <vector>   // For std::vector container (dynamic arrays)
#include <fstream>  // For std::ifstream (file input operations)
#include <algorithm> // For std::transform and std::shuffle algorithms
#include <random>   // For modern C++ random number generation (mt19937, uniform_int_distribution)
#include <unordered_set> // For std::unordered_set (efficient unique element storage and lookup)
#include <chrono>   // For std::chrono::system_clock (to get a time-based seed for RNG)
#include <iomanip>  // For std::fixed, std::setprecision (output formatting for numbers)
#include <limits>   // For std::numeric_limits (to clear input buffer robustly)
#include <cctype>   // For character classification and conversion (tolower, toupper, isalpha)

// Using namespace std; is common in smaller projects or competitive programming for brevity.
// In larger, professional projects, explicitly using 'std::' prefix (e.g., std::cout) is often preferred
// to avoid potential naming conflicts.
using namespace std;

// --- Global RNG setup ---
// Initialize a random number generator (Mersenne Twister engine).
// It's declared 'static' to limit its scope to this translation unit if this were part of a larger project,
// and to ensure it's initialized only once.
// The seed is obtained from the current system time, ensuring different random sequences each time the program runs.
static mt19937 rng(static_cast<unsigned>(
    chrono::system_clock::now().time_since_epoch().count()));

// === Helper Functions ===

// Get a validated character input from the user, only accepts characters from `valid` string
// This function demonstrates robust input handling and conversion.
char getValidatedChar(const string& prompt, const string& valid) {
    char ch;
    while (true) { // Loop indefinitely until valid input is received
        cout << prompt; // Display the prompt message to the user
        cin >> ch; // Attempt to read a single character

        // Clear the input buffer: This is crucial. When a user types 'Y' and presses Enter,
        // 'Y' is read, but '\n' (newline) remains in the buffer. Without clearing, the next
        // cin operation might immediately read this leftover '\n' and skip prompting the user.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        ch = toupper(static_cast<unsigned char>(ch)); // Convert the input character to uppercase.
        // static_cast<unsigned char> is used here for safety with `toupper`, as `char` can be signed
        // and might lead to undefined behavior for negative values.

        // Check if the uppercase character is found within the 'valid' string.
        // string::npos is a special value indicating "not found".
        if (valid.find(ch) != string::npos) return ch; // If found, return the valid character

        // If input is not valid, print an error message and loop again
        cout << "Invalid input. Choose one of [" << valid << "].\n";
    }
}

// Get a validated integer input from the user between minVal and maxVal (inclusive)
// This function handles non-numeric input and range validation.
int getValidatedInt(const string& prompt, int minVal, int maxVal) {
    int x;
    while (true) { // Loop indefinitely until valid integer input is received
        cout << prompt; // Display the prompt
        cin >> x; // Attempt to read an integer

        // Check for input failure (e.g., user typed text instead of a number) OR if the number is out of range.
        if (cin.fail() || x < minVal || x > maxVal) {
            cout << "Please enter a number between " << minVal
                << " and " << maxVal << ".\n";
            cin.clear(); // Clear the error flag on the cin stream (resets its state from 'fail')
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input from the buffer
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining characters (like '\n') from the buffer
            return x; // Return the validated integer
        }
    }
}

// === Craps Game ===

// Roll two six-sided dice and return their sum.
// Uses the global 'rng' and 'uniform_int_distribution' for fair and robust rolls.
static int rollTwoDice() {
    uniform_int_distribution<int> dist(1, 6); // Defines a distribution for integers from 1 to 6 (inclusive)
    return dist(rng) + dist(rng); // Calls the distribution twice to simulate two dice rolls and sums them
}

/**
 * @brief Play the Craps game with betting.
 *
 * The player starts with a balance and can bet each round.
 * Rules:
 * - Initial roll of 7 or 11 wins.
 * - Initial roll of 2, 3, or 12 loses (craps).
 * - Any other number becomes the "point".
 * - Keep rolling until you roll the point again (win) or roll a 7 (lose).
 * The player's balance is updated accordingly.
 *
 * @param playerBalance Reference to player's current balance, modified by game.
 */
void playCraps(double& playerBalance) { // playerBalance is passed by reference, so changes persist outside this function
    cout << "\n--- Craps ---\n";

    // Reset balance to starting amount if the player's balance is zero or less.
    // This ensures a fresh start if they previously went broke.
    if (playerBalance <= 0.0) {
        playerBalance = 50.0;
        cout << "Starting fresh with $50.00\n";
    }

    // Main game loop for Craps rounds. Continues as long as player has money.
    while (playerBalance > 0.0) {
        // Set output formatting for currency: fixed decimal notation with 2 digits after the decimal point.
        cout << fixed << setprecision(2);

        // Ask player for bet amount. The prompt is dynamically created using to_string for current balance.
        // The bet is validated to be between $1 and the player's current balance.
        double bet = getValidatedInt(
            "You have $" + to_string(static_cast<int>(playerBalance)) // Convert double to int for string conversion (for prompt display)
            + ". Enter bet [$1-$" + to_string(static_cast<int>(playerBalance)) + "]: ",
            1, static_cast<int>(playerBalance)); // Cast playerBalance to int for min/max range validation

        cout << "Betting $" << bet << "\n";

        // First roll (come-out roll)
        int roll = rollTwoDice();
        cout << "Rolled a " << roll << "\n";
        bool roundOver = false; // Flag to indicate if the current round has ended
        int point = 0;          // Stores the point if established

        // Immediate win/lose conditions based on the first roll
        if (roll == 7 || roll == 11) {
            cout << "You win!\n";
            playerBalance += bet; // Add bet to balance
            roundOver = true;
        }
        else if (roll == 2 || roll == 3 || roll == 12) {
            cout << "Craps - you lose!\n";
            playerBalance -= bet; // Subtract bet from balance
            roundOver = true;
        }
        else {
            // If not an immediate win/lose, the roll becomes the "point"
            point = roll;
            cout << "Point is " << point << ". Continue rolling...\n";
        }

        // Continue rolling loop: runs only if the round is not yet over (i.e., a point was established)
        while (!roundOver) {
            roll = rollTwoDice(); // Roll again
            cout << "Rolled a " << roll << "\n";
            if (roll == point) {
                cout << "Hit the point - you win!\n";
                playerBalance += bet; // Add bet to balance
                roundOver = true;
            }
            else if (roll == 7) {
                cout << "Seven out – you lose!\n";
                playerBalance -= bet; // Subtract bet from balance
                roundOver = true;
            }
        }

        cout << "Balance now: $" << playerBalance << "\n";

        // Check if player is broke after the round
        if (playerBalance <= 0) {
            cout << "You're broke – game over.\n";
            break; // Exit the main Craps game loop
        }

        // Ask if player wants to play another round of Craps.
        // If 'N' is chosen, break out of the game loop.
        if (getValidatedChar("Play again? (Y/N): ", "YN") == 'N') break;
    }

    cout << "Leaving Craps with $" << playerBalance << "\n";
}

// === Hangman Game ===

// Display ASCII gallows depending on the number of wrong guesses.
// This provides visual feedback on the player's progress.
static void displayGallows(int wrong) {
    cout << "  +---+\n  |   |\n";
    cout << "  " << (wrong > 0 ? 'O' : ' ') << "   |\n"; // Head appears after 1 wrong guess
    cout << " " << (wrong > 2 ? "/" : " ") << (wrong > 1 ? "|" : " ") // Left arm (3rd), Body (2nd)
        << (wrong > 3 ? "\\" : " ") << "  |\n"; // Right arm (4th)
    cout << " " << (wrong > 4 ? "/" : " ") << " " << (wrong > 5 ? "\\" : " ") << "  |\n"; // Left leg (5th), Right leg (6th)
    cout << "      |\n=========\n";
}

// Convert entire string to lowercase (used for word normalization).
// This ensures case-insensitive matching in Hangman.
static string toLower(string s) { // Passed by value, so a copy is made and modified
    // std::transform applies a function (here, a lambda that converts char to lowercase)
    // to each character in the string's range.
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return tolower(c); }); // Lambda function for character conversion
    return s; // Return the new lowercase string
}

// Load words from a file, returning a vector of lowercase words.
// This function fulfills the "File Input" requirement for Hangman.
static vector<string> loadWords(const string& fname) { // fname is passed by const reference for efficiency
    vector<string> v; // Vector to store the loaded words
    ifstream fin(fname); // Open the file for reading (fin is an input file stream object)
    string w; // Temporary string to hold each word read from the file
    while (fin >> w) { // Read words one by one until the end of the file
        v.push_back(toLower(w)); // Convert word to lowercase and add to the vector
    }
    return v; // Return the vector of loaded words
}

/**
 * @brief Play Hangman game.
 *
 * Loads a word list from file or uses a default list.
 * Player guesses letters; each wrong guess draws part of the gallows.
 * The player wins if the full word is guessed before 6 wrong guesses.
 */
void playHangman() {
    cout << "\n--- Hangman ---\n";

    // Load words from an external file ("words.txt").
    // If the file is empty or cannot be opened, a default list is used.
    auto words = loadWords("words.txt"); // 'auto' deduces the type as vector<string>
    if (words.empty()) {
        // Fallback to a hardcoded list if file loading fails or the file is empty.
        words = { "computer", "wizard", "hangman", "puzzle", "banana", "elephant" };
        cout << "(Using default word list.)\n";
    }

    // Pick a random secret word from the loaded list.
    // size_t is an unsigned integer type used for sizes and indices.
    uniform_int_distribution<size_t> dist(0, words.size() - 1);
    string secret = words[dist(rng)]; // The word the player needs to guess
    string guessed(secret.size(), '_'); // The player's current progress, initialized with underscores

    // unordered_set is used for 'used' letters because it provides very fast (average O(1))
    // lookup (`.count()`) and insertion (`.insert()`) of unique elements.
    unordered_set<char> used; // Stores letters that have already been guessed

    int wrong = 0, maxWrong = 6; // 'wrong' tracks incorrect guesses, 'maxWrong' is the limit

    // Main game loop: Continues as long as the player has guesses left AND hasn't guessed the word completely.
    while (wrong < maxWrong && guessed != secret) {
        displayGallows(wrong); // Show the current state of the Hangman gallows

        // Display game information to the player
        cout << "Word: " << guessed << "\nWrong guesses left: "
            << (maxWrong - wrong) << "\nUsed letters: ";
        for (char c : used) cout << c << ' '; // Iterate and print all already guessed letters
        cout << "\nGuess a letter: ";

        char g; // Variable to store the player's guess
        cin >> g; // Read the guessed character
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        g = tolower(static_cast<unsigned char>(g)); // Convert guess to lowercase for case-insensitive checking

        // Validate the guess: must be an alphabet character and not already used
        if (!isalpha(static_cast<unsigned char>(g)) || used.count(g)) { // isalpha checks if it's an alphabet letter
            cout << "Invalid or repeated guess.\n";
            continue; // Skip the rest of the loop and ask for input again
        }

        used.insert(g); // Add the valid, new guess to the set of used letters

        // Check if the guessed letter is in the secret word
        int found = 0; // Counter for how many times the letter appears in the word
        for (size_t i = 0; i < secret.size(); ++i) {
            if (secret[i] == g) { // If the letter matches a character in the secret word
                guessed[i] = g; // Reveal the letter in the 'guessed' word
                ++found; // Increment the found count
            }
        }

        // Provide feedback to the player based on the guess
        if (found)
            cout << "Good guess! '" << g << "' appears " << found << " time(s).\n";
        else {
            cout << "Wrong guess.\n";
            ++wrong; // Increment incorrect guess count
        }
    }

    displayGallows(wrong); // Display the final state of the gallows

    // Determine and announce the game outcome
    if (guessed == secret)
        cout << "Congrats! You guessed the word: '" << secret << "'.\n";
    else
        cout << "Out of guesses! The word was: '" << secret << "'.\n";

    // Ask if player wants to play again (this is handled by the main menu loop,
    // so this specific prompt is for within Hangman if it were standalone, or just for immediate feedback)
    // The main loop will re-prompt for game selection.
    // Removed the nested play again loop from previous versions to simplify main menu flow.
}

// === Blackjack Game ===

// Represents a playing card with rank (e.g., "A", "K", "2") and numerical value.
struct Card {
    string rank;
    int value;
};

// Create a standard 52-card deck and shuffle it.
// This function is called at the beginning of each Blackjack game round.
static vector<Card> makeShuffledDeck() {
    vector<Card> d; // Vector to hold the deck of cards

    // 'static const' vectors for ranks and values.
    // 'static' means they are initialized only once across all calls to this function.
    // 'const' means their content cannot be changed. This is efficient as they don't need to be recreated.
    static const vector<string> ranks = {
        "2","3","4","5","6","7","8","9","10","J","Q","K","A"
    };
    static const vector<int> vals = {
        2,3,4,5,6,7,8,9,10,10,10,10,11 // Ace's initial value is 11
    };

    // Populate the deck with 4 suits of each rank.
    for (int i = 0; i < 4; ++i) // Loop for each of the four suits
        for (size_t j = 0; j < ranks.size(); ++j) // Loop for each rank
            d.push_back({ ranks[j], vals[j] }); // Create a Card object and add it to the deck

    // Shuffle the deck using the global random number generator 'rng'.
    // std::shuffle is the modern and preferred way to randomize elements in a container.
    shuffle(d.begin(), d.end(), rng);
    return d; // Return the newly created and shuffled deck
}

// Calculate the total value of a hand, accounting for Aces as 1 or 11.
// This is crucial for Blackjack logic.
static int handValue(const vector<Card>& h) { // Hand 'h' is passed by const reference for efficiency
    int sum = 0, aces = 0; // 'sum' for total value, 'aces' to count Aces for adjustment
    for (auto& c : h) { // Iterate through each card in the hand
        sum += c.value; // Add card's value to sum
        if (c.rank == "A") ++aces; // Count Aces
    }
    // Adjust for aces: If the sum exceeds 21 and there are Aces (which are currently 11),
    // reduce an Ace's value from 11 to 1 (by subtracting 10) until sum is <= 21 or no more Aces.
    while (sum > 21 && aces > 0) {
        sum -= 10; // Change 11 to 1
        --aces; // Decrement Ace count
    }
    return sum; // Return the final calculated hand value
}

// Print the cards in a hand; optionally hide dealer's first card.
static void printHand(const string& owner, const vector<Card>& h, bool hide = false) {
    cout << owner << ": "; // Print the owner's name
    for (size_t i = 0; i < h.size(); ++i) { // Iterate through the cards in the hand
        if (hide && i == 0) cout << "[hidden] "; // If hiding and it's the first card, print "[hidden]"
        else cout << h[i].rank << ' '; // Otherwise, print the card's rank
    }
    if (!hide) cout << "(Total: " << handValue(h) << ")"; // If not hiding, print the hand's total value
    cout << "\n"; // Newline after printing the hand
}

/**
 * @brief Play Blackjack game.
 *
 * Player plays against dealer with standard Blackjack rules.
 * Player can hit or stand.
 * Dealer hits until reaching 17 or more.
 * Results and busts are announced.
 */
void playBlackjack() {
    cout << "\n--- Blackjack ---\n";
    char again; // Variable to control playing multiple rounds of Blackjack

    do { // Loop for playing multiple rounds of Blackjack
        auto deck = makeShuffledDeck(); // Create a new, shuffled deck for each game round
        vector<Card> player, dealer; // Initialize empty hands for player and dealer

        // Initial deal: 2 cards each, alternating.
        // `deck.back()` gets the last element (top card), `deck.pop_back()` removes it.
        player.push_back(deck.back()); deck.pop_back();
        dealer.push_back(deck.back()); deck.pop_back();
        player.push_back(deck.back()); deck.pop_back();
        dealer.push_back(deck.back()); deck.pop_back();

        printHand("Dealer", dealer, true); // Display dealer's hand with the first card hidden
        printHand("Player", player); // Display player's hand

        // Player turn: Loop until player busts (total > 21) or chooses to stand.
        while (handValue(player) < 21) {
            // Get player's choice to Hit or Stand using the validated input helper.
            char ch = getValidatedChar("(H)it or (S)tand? ", "HS");
            if (ch == 'H') {
                player.push_back(deck.back()); deck.pop_back(); // Deal another card to player
                printHand("Player", player); // Show updated player hand
            }
            else break; // Player chose to stand, exit loop
        }

        // Check if player busted
        if (handValue(player) > 21) {
            cout << "Bust! You lose.\n";
        }
        else {
            // Dealer turn: Only proceeds if the player has not busted.
            cout << "\nDealer's turn:\n";
            printHand("Dealer", dealer); // Reveal dealer's hidden card and show full hand

            // Dealer hits until their hand value is 17 or more.
            while (handValue(dealer) < 17) {
                cout << "Dealer hits.\n";
                dealer.push_back(deck.back()); deck.pop_back(); // Dealer deals themselves a card
                printHand("Dealer", dealer); // Show updated dealer hand
            }

            int pv = handValue(player); // Player's final hand value
            int dv = handValue(dealer); // Dealer's final hand value

            // Determine the winner based on Blackjack rules
            if (dv > 21) cout << "Dealer busts! You win!\n"; // Dealer busted, player wins
            else if (pv > dv) cout << "You win!\n"; // Player has higher score without busting
            else if (pv < dv) cout << "Dealer wins.\n"; // Dealer has higher score without busting
            else cout << "Push (tie).\n"; // Scores are equal
        }

        // Ask if player wants to play another round of Blackjack.
        again = getValidatedChar("Play again? (Y/N): ", "YN");
        cout << "\n"; // Add a newline for better spacing between game rounds

    } while (again == 'Y'); // Continue loop if player chooses 'Y'
}
