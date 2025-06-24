//  Dice, Hangman, and Blackjack


#include <iostream> 
#include <string>   
#include <vector>   
#include <cstdlib>  
#include <ctime>    
#include <algorithm>
#include <numeric>  /
using namespace std;

// --- Dice Rolling Game Functions ---


int rollDice() {
    return (rand() % 6) + 1;
}

// Function to run the Dice Rolling Game
void playDiceGame() {
    char choice; // Variable to store user's choice to roll again

    cout << "\n--- Welcome to the Dice Rolling Game! ---\n";

    do {
        int dieRoll = rollDice(); // Roll the die
        cout << "\nYou rolled a: " << dieRoll << endl; // Display result

        cout << "Roll again? (y/n): "; // Ask to roll again
        cin >> choice;

        // Clear the input buffer to prevent issues with future inputs
        cin.ignore(10000, '\n');

    } while (choice == 'y' || choice == 'Y'); // Continue if user enters 'y' or 'Y'

    cout << "Thanks for playing the Dice Game!\n";
}

// --- Hangman Game Functions ---

// Function to display the Hangman gallows based on incorrect guesses
void displayHangmanGallows(int incorrectGuesses) {
    cout << "  +---+\n";
    cout << "  |   |\n";
    cout << "  " << (incorrectGuesses > 0 ? "O" : " ") << "   |\n";
    cout << " " << (incorrectGuesses > 2 ? "/" : " ") << (incorrectGuesses > 1 ? "|" : " ") << (incorrectGuesses > 3 ? "\\" : " ") << "  |\n";
    cout << " " << (incorrectGuesses > 4 ? "/" : " ") << " " << (incorrectGuesses > 5 ? "\\" : " ") << "  |\n";
    cout << "      |\n";
    cout << "=========\n";
}

// Function to run the Hangman Game
void playHangmanGame() {
    // List of words for the game
    vector<string> words = {
        "programming", "computer", "keyboard", "monitor", "algorithm",
        "developer", "language", "hardware", "software", "internet",
        "blackjack", "hangman", "dice", "cplusplus", "console"
    };

    // Choose a random word from the list
    string secretWord = words[rand() % words.size()];
    string guessedWord(secretWord.length(), '_'); // Initialize with underscores
    string guessedLetters = ""; // Stores letters already guessed
    int incorrectGuesses = 0; // Counter for incorrect guesses
    const int maxIncorrectGuesses = 6; // Maximum allowed incorrect guesses

    cout << "\n--- Welcome to Hangman! ---\n";
    cout << "Try to guess the word.\n";

    // Game loop
    while (incorrectGuesses < maxIncorrectGuesses && guessedWord != secretWord) {
        displayHangmanGallows(incorrectGuesses); // Display gallows state
        cout << "\nWord: " << guessedWord << endl;
        cout << "Guessed letters: " << guessedLetters << endl;
        cout << "Incorrect guesses remaining: " << (maxIncorrectGuesses - incorrectGuesses) << endl;
        cout << "Enter a letter: ";

        char guess;
        cin >> guess;
        // Convert guess to lowercase for case-insensitivity
        guess = static_cast<char>(tolower(static_cast<unsigned char>(guess)));

        // Clear the input buffer
        cin.ignore(10000, '\n');

        // Check if letter has already been guessed
        if (guessedLetters.find(guess) != string::npos) {
            cout << "You already guessed that letter. Try again.\n";
            continue;
        }

        guessedLetters += guess; // Add the guessed letter to the list

        bool found = false;
        // Check if the guessed letter is in the secret word
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (static_cast<char>(tolower(static_cast<unsigned char>(secretWord[i]))) == guess) {
                guessedWord[i] = secretWord[i]; // Reveal the letter
                found = true;
            }
        }

        if (!found) {
            cout << "Incorrect guess!\n";
            incorrectGuesses++; // Increment incorrect guess count
        }
        else {
            cout << "Good guess!\n";
        }
        cout << endl;
    }

    // Game end conditions
    displayHangmanGallows(incorrectGuesses); // Final gallows display
    if (guessedWord == secretWord) {
        cout << "Congratulations! You guessed the word: " << secretWord << endl;
    }
    else {
        cout << "You ran out of guesses! The word was: " << secretWord << endl;
        cout << "Better luck next time!\n";
    }

    cout << "Thanks for playing Hangman!\n";
}

// --- Blackjack Game Functions ---

// Card structure
struct Card {
    string rank; // e.g., "2", "King", "Ace"
    int value;        // Numeric value (e.g., 2, 10, 11 for Ace initially)
};

// Function to create a standard deck of 52 cards
vector<Card> createBlackjackDeck() {
    vector<Card> deck;
    vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
    vector<int> values = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

    // Create 4 suits of each card
    for (int i = 0; i < 4; ++i) {
        for (size_t j = 0; j < ranks.size(); ++j) {
            deck.push_back({ ranks[j], values[j] });
        }
    }
    return deck;
}

// Function to shuffle the deck (using random_shuffle)
void shuffleBlackjackDeck(vector<Card>& deck) {
    random_shuffle(deck.begin(), deck.end());
}

// Function to calculate the total value of a hand, handling Aces (1 or 11)
int calculateBlackjackHandValue(const vector<Card>& hand) {
    int value = 0;
    int aceCount = 0;

    for (const auto& card : hand) {
        value += card.value;
        if (card.rank == "Ace") {
            aceCount++;
        }
    }

    // Adjust for Aces if hand value exceeds 21
    while (value > 21 && aceCount > 0) {
        value -= 10; // Change Ace from 11 to 1
        aceCount--;
    }
    return value;
}

// Function to display a hand
void displayBlackjackHand(const string& owner, const vector<Card>& hand, bool hideDealerCard = false) {
    cout << owner << "'s hand: ";
    for (size_t i = 0; i < hand.size(); ++i) {
        if (hideDealerCard && i == 0) {
            cout << "[Hidden Card] ";
        }
        else {
            cout << hand[i].rank << " ";
        }
    }
    if (!hideDealerCard) {
        cout << "(Value: " << calculateBlackjackHandValue(hand) << ")";
    }
    cout << endl;
}

// Function to run the Blackjack Game
void playBlackjackGame() {
    char playAgain;
    cout << "\n--- Welcome to Blackjack! ---\n";

    do {
        vector<Card> deck = createBlackjackDeck();
        shuffleBlackjackDeck(deck);

        vector<Card> playerHand;
        vector<Card> dealerHand;

        int deckIndex = 0; // To keep track of current card in the deck

        // Deal initial cards
        playerHand.push_back(deck[deckIndex++]);
        dealerHand.push_back(deck[deckIndex++]); // Dealer's first card (hidden)
        playerHand.push_back(deck[deckIndex++]);
        dealerHand.push_back(deck[deckIndex++]);

        displayBlackjackHand("Player", playerHand);
        displayBlackjackHand("Dealer", dealerHand, true); // Hide dealer's first card

        // Player's turn
        char choice;
        while (true) {
            int playerValue = calculateBlackjackHandValue(playerHand);
            if (playerValue > 21) {
                cout << "Player busts!\n";
                break;
            }
            if (playerValue == 21) {
                cout << "Player has Blackjack!\n";
                break;
            }

            cout << "Do you want to (H)it or (S)tand? ";
            cin >> choice;
            choice = static_cast<char>(tolower(static_cast<unsigned char>(choice)));

            // Clear the input buffer
            cin.ignore(10000, '\n');

            if (choice == 'h') {
                playerHand.push_back(deck[deckIndex++]);
                displayBlackjackHand("Player", playerHand);
            }
            else if (choice == 's') {
                cout << "Player stands.\n";
                break;
            }
            else {
                cout << "Invalid choice. Please enter 'H' or 'S'.\n";
            }
        }

        // Dealer's turn (only if player hasn't busted)
        int playerFinalValue = calculateBlackjackHandValue(playerHand);
        if (playerFinalValue <= 21) {
            cout << "\nDealer's turn:\n";
            displayBlackjackHand("Dealer", dealerHand); // Reveal dealer's hidden card

            while (calculateBlackjackHandValue(dealerHand) < 17) {
                cout << "Dealer hits.\n";
                dealerHand.push_back(deck[deckIndex++]);
                displayBlackjackHand("Dealer", dealerHand);
            }
            int dealerValue = calculateBlackjackHandValue(dealerHand);
            if (dealerValue > 21) {
                cout << "Dealer busts! Player wins!\n";
            }
            else if (dealerValue > playerFinalValue) {
                cout << "Dealer wins!\n";
            }
            else if (playerFinalValue > dealerValue) {
                cout << "Player wins!\n";
            }
            else {
                cout << "It's a push (tie)!\n";
            }
        }

        cout << "Play again? (y/n): ";
        cin >> playAgain;
        playAgain = static_cast<char>(tolower(static_cast<unsigned char>(playAgain)));
        cin.ignore(10000, '\n'); // Clear input buffer
        cout << endl;

    } while (playAgain == 'y');

    cout << "Thanks for playing Blackjack!\n";
}

// --- Main Program ---

int main() {
    // Seed the random number generator once at the beginning of the program
    srand(static_cast<unsigned int>(time(0)));

    int choice;

    do {
        cout << "\n--- Welcome to the C++ Game Collection! ---\n";
        cout << "1. Play Dice Rolling Game\n";
        cout << "2. Play Hangman Game\n";
        cout << "3. Play Blackjack Game\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear the input buffer
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1:
            playDiceGame();
            break;
        case 2:
            playHangmanGame();
            break;
        case 3:
            playBlackjackGame();
            break;
        case 4:
            cout << "Exiting the game collection. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            break;
        }
        cout << endl; // Add a newline for spacing after each game
    } while (choice != 4); // Continue until the user chooses to exit

    return 0; // Indicate successful program execution
}

