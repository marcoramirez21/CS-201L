#ifndef GAMES_H
#define GAMES_H

#include <string>
#include <vector>
#include <unordered_set>

/** @brief Play the Craps game with betting; modifies player's balance. */
void playCraps(double& playerBalance);

/** @brief Play Hangman, reading words from file, with ASCII gallows. */
void playHangman();

/** @brief Play Blackjack (single-player vs dealer). */
void playBlackjack();

#endif // GAMES_H