#include "Games.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <chrono>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

// --- Global RNG ---
static mt19937 rng(static_cast<unsigned>(
    chrono::system_clock::now().time_since_epoch().count()));

// === Helper Functions ===

// Changed string_view to const string& for compatibility
char getValidatedChar(const string& prompt, const string& valid) {
    char ch;
    while (true) {
        cout << prompt;
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        ch = toupper(static_cast<unsigned char>(ch));
        if (valid.find(ch) != string::npos) return ch;
        cout << "Invalid input. Choose one of [" << valid << "].\n";
    }
}

int getValidatedInt(const string& prompt, int minVal, int maxVal) {
    int x;
    while (true) {
        cout << prompt;
        cin >> x;
        if (cin.fail() || x < minVal || x > maxVal) {
            cout << "Please enter a number between " << minVal
                << " and " << maxVal << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
    }
}

// === Craps ===

static int rollTwoDice() {
    uniform_int_distribution<int> dist(1, 6);
    return dist(rng) + dist(rng);
}

void playCraps(double& playerBalance) {
    cout << "\n--- Craps ---\n";
    if (playerBalance <= 0.0) {
        playerBalance = 50.0;
        cout << "Starting fresh with $50.00\n";
    }


    while (playerBalance > 0.0) {
        cout << fixed << setprecision(2);
        
        double bet = getValidatedInt(
            "You have $" + to_string((int)playerBalance)
            + ". Enter bet [$1-$" + to_string((int)playerBalance) + "]: ",
            1, static_cast<int>(playerBalance));
        cout << "Betting $" << bet << "\n";


        int roll = rollTwoDice();
        cout << "Rolled a " << roll << "\n";
        bool roundOver = false;
        int point = 0;

        if (roll == 7 || roll == 11) {
            cout << "You win!\n";
            playerBalance += bet;
            roundOver = true;
        }
        else if (roll == 2 || roll == 3 || roll == 12) {
            cout << "Craps – you lose!\n";
            playerBalance -= bet;
            roundOver = true;
        }
        else {
            point = roll;
            cout << "Point is " << point << ". Continue rolling...\n";
        }

        while (!roundOver) {
            roll = rollTwoDice();
            cout << "Rolled a " << roll << "\n";
            if (roll == point) {
                cout << "Hit the point – you win!\n";
                playerBalance += bet;
                roundOver = true;
            }
            else if (roll == 7) {
                cout << "Seven out – you lose!\n";
                playerBalance -= bet;
                roundOver = true;
            }
        }

        cout << "Balance now: $" << playerBalance << "\n";
        if (playerBalance <= 0) {
            cout << "You're broke – game over.\n";
            break;
        }
        if (getValidatedChar("Play again? (Y/N): ", "YN") == 'N') break;
    }

    cout << "Leaving Craps with $" << playerBalance << "\n";
}

// === Hangman ===

static void displayGallows(int wrong) {
    cout << "  +---+\n  |   |\n";
    cout << "  " << (wrong > 0 ? 'O' : ' ') << "   |\n";
    cout << " " << (wrong > 2 ? "/" : " ") << (wrong > 1 ? "|" : " ")
        << (wrong > 3 ? "\\" : " ") << "  |\n";
    cout << " " << (wrong > 4 ? "/" : " ") << " " << (wrong > 5 ? "\\" : " ") << "  |\n";
    cout << "      |\n=========\n";
}

static string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return tolower(c); });
    return s;
}

static vector<string> loadWords(const string& fname) {
    vector<string> v;
    ifstream fin(fname);
    string w;
    while (fin >> w) v.push_back(toLower(w));
    return v;
}

void playHangman() {
    cout << "\n--- Hangman ---\n";
    auto words = loadWords("words.txt");
    if (words.empty()) {
        words = { "computer","wizard","hangman","puzzle","banana","elephant" };
        cout << "(Using default word list.)\n";
    }

    uniform_int_distribution<size_t> dist(0, words.size() - 1);
    string secret = words[dist(rng)];
    string guessed(secret.size(), '_');
    unordered_set<char> used;
    int wrong = 0, maxWrong = 6;

    while (wrong < maxWrong && guessed != secret) {
        displayGallows(wrong);
        cout << "Word: " << guessed << "\nWrong guesses left: "
            << (maxWrong - wrong) << "\nUsed: ";
        for (char c : used) cout << c << ' ';
        cout << "\nGuess a letter: ";

        char g;
        cin >> g;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        g = tolower(static_cast<unsigned char>(g));
        if (!isalpha(g) || used.count(g)) {
            cout << "Invalid or repeated guess.\n";
            continue;
        }

        used.insert(g);
        int found = 0;
        for (size_t i = 0; i < secret.size(); ++i) {
            if (secret[i] == g) { guessed[i] = g; ++found; }
        }
        if (found) cout << "Good guess! '" << g << "' appears " << found << " time(s).\n";
        else { cout << "Wrong guess.\n"; ++wrong; }
    }

    displayGallows(wrong);
    if (guessed == secret)
        cout << "Congrats! Word was '" << secret << "'.\n";
    else
        cout << "Out of guesses! Word was '" << secret << "'.\n";
}

// === Blackjack ===

struct Card { string rank; int value; };

static vector<Card> makeShuffledDeck() {
    vector<Card> d;
    static const vector<string> ranks = {
        "2","3","4","5","6","7","8","9","10","J","Q","K","A"
    };
    static const vector<int> vals = {
        2,3,4,5,6,7,8,9,10,10,10,10,11
    };
    for (int i = 0; i < 4; ++i)
        for (size_t j = 0; j < ranks.size(); ++j)
            d.push_back({ ranks[j], vals[j] });
    shuffle(d.begin(), d.end(), rng);
    return d;
}

static int handValue(const vector<Card>& h) {
    int sum = 0, aces = 0;
    for (auto& c : h) {
        sum += c.value;
        if (c.rank == "A") ++aces;
    }
    while (sum > 21 && aces > 0) { sum -= 10; --aces; }
    return sum;
}

static void printHand(const string& owner, const vector<Card>& h, bool hide = false) {
    cout << owner << ": ";
    for (size_t i = 0; i < h.size(); ++i) {
        if (hide && i == 0) cout << "[hidden] ";
        else cout << h[i].rank << ' ';
    }
    if (!hide) cout << "(Total: " << handValue(h) << ")";
    cout << "\n";
}

void playBlackjack() {
    cout << "\n--- Blackjack ---\n";
    char again;
    do {
        auto deck = makeShuffledDeck();
        vector<Card> player, dealer;

        player.push_back(deck.back()); deck.pop_back();
        dealer.push_back(deck.back()); deck.pop_back();
        player.push_back(deck.back()); deck.pop_back();
        dealer.push_back(deck.back()); deck.pop_back();

        printHand("Dealer", dealer, true);
        printHand("Player", player);

        while (handValue(player) < 21) {
            char ch = getValidatedChar("(H)it or (S)tand? ", "HS");
            if (ch == 'H') {
                player.push_back(deck.back()); deck.pop_back();
                printHand("Player", player);
            }
            else break;
        }

        if (handValue(player) > 21) {
            cout << "Bust! You lose.\n";
        }
        else {
            printHand("Dealer", dealer);
            while (handValue(dealer) < 17) {
                dealer.push_back(deck.back()); deck.pop_back();
                printHand("Dealer", dealer);
            }
            int pv = handValue(player), dv = handValue(dealer);
            if (dv > 21) cout << "Dealer busts! You win!\n";
            else if (pv > dv) cout << "You win!\n";
            else if (pv < dv) cout << "Dealer wins.\n";
            else cout << "Push (tie).\n";
        }

        again = getValidatedChar("Play again? (Y/N): ", "YN");
        cout << "\n";
    } while (again == 'Y');
}
