#ifndef GAMES_H // Include guard: Prevents the header file from being included multiple times in a single compilation unit.
#define GAMES_H // This ensures that declarations are processed only once, avoiding redefinition errors.

#include <string>        // Required for std::string type
#include <vector>        // Required for std::vector container
#include <unordered_set> // Required for std::unordered_set container
#include <random>        // Required for std::mt19937 (for the global RNG declaration)

// Forward declarations for standard library components used in function signatures,
// to avoid including full headers here if only types are needed.
// This is good practice for header files to minimize dependencies.
// However, the original .cpp includes all necessary headers directly, so these are
// implicitly covered there.

// --- Global Random Number Generator (RNG) Declaration ---
// Declared as 'extern' here because it's defined in the .cpp file.
// 'extern' tells the compiler that 'rng' exists elsewhere and will be linked later.
extern std::mt19937 rng;

// === Helper Functions Declarations ===
// These functions provide robust input validation and common utilities used across games.

/**
 * @brief Gets a validated character input from the user.
 *
 * Prompts the user and continuously asks for input until a single character
 * from the `valid` string is entered. Input is converted to uppercase.
 *
 * @param prompt The message displayed to the user.
 * @param valid A string containing all acceptable single characters (e.g., "YN", "HS").
 * @return The validated, uppercase character entered by the user.
 */
char getValidatedChar(const std::string& prompt, const std::string& valid);

/**
 * @brief Gets a validated integer input from the user within a specified range.
 *
 * Prompts the user and continuously asks for input until a valid integer
 * within the `minVal` and `maxVal` (inclusive) range is entered.
 * Handles non-numeric input gracefully.
 *
 * @param prompt The message displayed to the user.
 * @param minVal The minimum acceptable integer value.
 * @param maxVal The maximum acceptable integer value.
 * @return The validated integer entered by the user.
 */
int getValidatedInt(const std::string& prompt, int minVal, int maxVal);


// === Craps Game Declarations ===

/**
 * @brief Rolls two six-sided dice and returns their sum.
 * @return The sum of the two dice rolls (an integer between 2 and 12).
 */
static int rollTwoDice(); // Declared static as it's a helper for playCraps, typically not exposed externally.

/**
 * @brief Play the Craps game with betting.
 *
 * This function handles the game loop for Craps,
 * allowing the player to place bets and roll dice.
 * The player's balance is updated based on wins/losses.
 *
 * @param playerBalance Reference to the player's current balance, modified by the game.
 */
void playCraps(double& playerBalance);


// === Hangman Game Declarations ===

/**
 * @brief Displays the Hangman gallows ASCII art based on incorrect guesses.
 * @param wrong The current count of incorrect guesses.
 */
static void displayGallows(int wrong); // Declared static as it's a helper for playHangman.

/**
 * @brief Converts an entire string to lowercase.
 *
 * This utility function is useful for normalizing strings (e.g., words from a file)
 * for case-insensitive comparisons.
 *
 * @param s The input string to convert.
 * @return A new string with all characters converted to lowercase.
 */
static std::string toLower(std::string s); // Declared static as it's a helper for loadWords.

/**
 * @brief Loads words from a specified file into a vector of strings.
 *
 * Reads words line by line from the given file, converts them to lowercase,
 * and stores them in the provided vector.
 *
 * @param fname The name of the file to read words from.
 * @return A vector of strings containing the loaded and lowercased words.
 */
static std::vector<std::string> loadWords(const std::string& fname); // Declared static as it's a helper for playHangman.

/**
 * @brief Play the Hangman game.
 *
 * Loads a list of words from an external file ("words.txt").
 * The player guesses letters to reveal a hidden word.
 * The game displays ASCII gallows as the player makes wrong guesses.
 *
 * Uses a default word list if the file cannot be loaded.
 */
void playHangman();


// === Blackjack Game Declarations ===

/**
 * @brief Represents a playing card.
 *
 * Groups together the card's rank (e.g., "A", "K", "2") and its numerical value
 * for Blackjack calculations.
 */
struct Card {
    std::string rank; // The face value of the card (e.g., "Ace", "King", "5")
    int value;        // The numerical value of the card in Blackjack (e.g., 11 for Ace, 10 for King, 5 for 5)
};

/**
 * @brief Creates a standard 52-card deck and shuffles it.
 *
 * This function generates all 52 unique cards, assigns their Blackjack values,
 * and then shuffles them randomly using a modern C++ random engine.
 *
 * @return A std::vector of Card objects representing a newly created and shuffled deck.
 */
static std::vector<Card> makeShuffledDeck(); // Declared static as it's a helper for playBlackjack.

/**
 * @brief Calculates the total value of a Blackjack hand.
 *
 * Correctly handles the special rule for Aces, which can count as 11 or 1
 * depending on the hand's total to prevent busting.
 *
 * @param h A constant reference to the vector of Card objects in the hand.
 * @return The calculated numerical value of the hand.
 */
static int handValue(const std::vector<Card>& h); // Declared static as it's a helper for playBlackjack.

/**
 * @brief Prints the cards in a player's or dealer's hand to the console.
 *
 * Can optionally hide the first card, typically used for the dealer's initial hand.
 *
 * @param owner A string indicating whose hand is being displayed (e.g., "Player", "Dealer").
 * @param h A constant reference to the vector of Card objects in the hand.
 * @param hide A boolean flag; if true, the first card in the hand will be shown as "[hidden]".
 */
static void printHand(const std::string& owner, const std::vector<Card>& h, bool hide = false); // Declared static as it's a helper for playBlackjack.

/**
 * @brief Play the Blackjack game (single player vs dealer).
 *
 * Implements basic Blackjack rules:
 * - Player can hit or stand.
 * - Dealer hits until hand value is 17 or more.
 * - Aces count as 1 or 11 optimally.
 *
 * Uses a shuffled deck each round.
 */
void playBlackjack();

#endif // GAMES_H
