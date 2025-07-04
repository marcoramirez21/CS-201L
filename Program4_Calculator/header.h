// Program4_Calculator.cpp 
//

#ifndef CALCULATOR_H // Include guard to prevent multiple inclusions of this header file.
#define CALCULATOR_H // Defines the macro for the include guard.

#include <string>   // Required for std::string type and string manipulation functions.
#include <iostream> // Required for standard input/output operations (cin, cout).
#include <cmath>    // Required for mathematical functions like pow (used in base conversions).
#include <limits>   // Required for std::numeric_limits (used for clearing input buffer).
#include <algorithm> // Required for std::reverse (used in decimal to other base conversions).
#include <iomanip>  // Required for std::fixed and std::setprecision (for output formatting).
#include <cctype>   // Required for toupper and isxdigit (for character manipulation and validation).
#include <sstream>  // Required for std::stringstream (useful for hexadecimal conversions).

// --- Helper Functions for Input Validation ---
// These functions provide robust ways to get validated input from the user.

/**
 * @brief Gets a validated character input from the user.
 *
 * Prompts the user and continuously asks for input until a single character
 * from the 'valid_chars' string is entered. Input is converted to uppercase
 * for case-insensitive comparison.
 *
 * @param prompt The message displayed to the user.
 * @param valid_chars A string containing all acceptable single characters (e.g., "ASMDQ" for arithmetic options).
 * @return The validated, uppercase character entered by the user.
 */
char getValidatedChar(const std::string& prompt, const std::string& valid_chars);

/**
 * @brief Gets a validated double (floating-point) number input from the user.
 *
 * Prompts the user and continuously asks for input until a valid numeric
 * double value is entered. Handles non-numeric input gracefully.
 *
 * @param prompt The message displayed to the user.
 * @return The validated double value entered by the user.
 */
double getValidatedDouble(const std::string& prompt);

/**
 * @brief Gets a validated string input for number base conversion.
 *
 * Prompts the user to enter a number string and validates it against the
 * rules of the specified base (e.g., binary only '0' and '1', hexadecimal
 * '0'-'9' and 'A'-'F').
 *
 * @param prompt The message displayed to the user.
 * @param base The numerical base to validate against (e.g., 2 for binary, 16 for hexadecimal).
 * @return The validated number string in uppercase for hexadecimal.
 */
std::string getValidatedBaseInput(const std::string& prompt, int base);

// --- Arithmetic Operations Functions ---
// These functions perform basic mathematical operations.

/**
 * @brief Performs addition of two double numbers.
 * @param num1 The first operand.
 * @param num2 The second operand.
 * @return The sum of num1 and num2.
 */
double add(double num1, double num2);

/**
 * @brief Performs subtraction of two double numbers.
 * @param num1 The first operand.
 * @param num2 The second operand.
 * @return The difference of num1 and num2.
 */
double subtract(double num1, double num2);

/**
 * @brief Performs multiplication of two double numbers.
 * @param num1 The first operand.
 * @param num2 The second operand.
 * @return The product of num1 and num2.
 */
double multiply(double num1, double num2);

/**
 * @brief Performs division of two double numbers.
 *
 * @param num1 The dividend.
 * @param num2 The divisor.
 * @return The quotient of num1 and num2. Returns a special value (e.g., NaN or a large number)
 * or handles error if division by zero is attempted; actual error handling is in `performArithmeticOperations`.
 */
double divide(double num1, double num2);

/**
 * @brief Manages the arithmetic operations module.
 *
 * Presents a sub-menu for addition, subtraction, multiplication, and division.
 * Prompts for two numbers, performs the chosen operation, and displays the result.
 * Handles division by zero. Allows repeating arithmetic operations or returning
 * to the main menu.
 */
void performArithmeticOperations();


// --- Number Base Conversion Functions ---
// These functions handle conversions between decimal, binary, octal, and hexadecimal.

/**
 * @brief Converts a decimal integer to its binary string representation.
 * @param decimalNum The decimal integer to convert.
 * @return A string representing the binary equivalent.
 */
std::string decToBin(long long decimalNum);

/**
 * @brief Converts a decimal integer to its octal string representation.
 * @param decimalNum The decimal integer to convert.
 * @return A string representing the octal equivalent.
 */
std::string decToOct(long long decimalNum);

/**
 * @brief Converts a decimal integer to its hexadecimal string representation.
 * @param decimalNum The decimal integer to convert.
 * @return A string representing the hexadecimal equivalent (uppercase).
 */
std::string decToHex(long long decimalNum);

/**
 * @brief Converts a binary string representation to its decimal integer.
 * @param binaryNumString The binary number as a string (e.g., "10110").
 * @return The decimal integer equivalent.
 */
long long binToDec(const std::string& binaryNumString);

/**
 * @brief Converts an octal string representation to its decimal integer.
 * @param octalNumString The octal number as a string (e.g., "754").
 * @return The decimal integer equivalent.
 */
long long octToDec(const std::string& octalNumString);

/**
 * @brief Converts a hexadecimal string representation to its decimal integer.
 * @param hexNumString The hexadecimal number as a string (e.g., "A3F").
 * @return The decimal integer equivalent.
 */
long long hexToDec(const std::string& hexNumString);

/**
 * @brief Converts a single hexadecimal character to its decimal integer value.
 * @param hexChar The hexadecimal character ('0'-'9', 'A'-'F', 'a'-'f').
 * @return The decimal integer value (0-15).
 */
int hexCharToDec(char hexChar);

/**
 * @brief Converts a decimal integer value (0-15) to its hexadecimal character.
 * @param decValue The decimal integer value (0-15).
 * @return The hexadecimal character ('0'-'9', 'A'-'F').
 */
char decToHexChar(int decValue);

/**
 * @brief Manages the number base conversion module.
 *
 * Presents a sub-menu for various base conversions (Decimal to Binary/Octal/Hex,
 * Binary/Octal/Hex to Decimal). Prompts for input, performs the conversion,
 * and displays the result. Validates input for each base. Allows repeating
 * conversions or returning to the main menu.
 */
void performNumberConversions();

// --- Main Menu Display Function ---

/**
 * @brief Displays the main menu of the calculator program.
 * @return The user's validated choice (A, C, or E).
 */
char displayMainMenu();

#endif // CALCULATOR_H

