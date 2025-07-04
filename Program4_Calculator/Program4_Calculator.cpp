#include <iostream>  // Required for standard input/output operations (cin, cout)
#include <string>    // Required for std::string type and string manipulation functions
#include <cmath>     // Required for mathematical functions (e.g., for power calculations, though custom implemented here)
#include <limits>    // Required for std::numeric_limits (used for clearing input buffer)
#include <cctype>    // Required for std::toupper (used in hexadecimal conversion/validation)

// --- Function Prototypes ---
// Declaring functions before their definitions allows for better code organization.

/**
 * @brief Displays the main menu of the calculator program.
 */
void displayMainMenu();

/**
 * @brief Manages the arithmetic operations module.
 *
 * This function handles user interaction for addition, subtraction,
 * multiplication, and division, including input of numbers, performing
 * calculations, and displaying results. It also manages the loop for
 * repeating arithmetic operations.
 */
void performArithmeticOperations();

/**
 * @brief Manages the number base conversion module.
 *
 * This function presents a sub-menu for various base conversions
 * (Decimal to Binary/Octal/Hex, Binary/Octal/Hex to Decimal). It prompts
 * for input, performs the conversion, displays the result, and validates
 * input for each base. It allows repeating conversions.
 */
void performNumberConversions();

// --- Arithmetic Functions ---
// Basic mathematical operations.

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
 * @param num1 The first factor.
 * @param num2 The second factor.
 * @return The product of num1 and num2.
 */
double multiply(double num1, double num2);

/**
 * @brief Performs division of two double numbers.
 * @param num1 The dividend.
 * @param num2 The divisor.
 * @return The quotient of num1 and num2. Note: Division by zero handling
 * is performed in the calling function (`performArithmeticOperations`).
 */
double divide(double num1, double num2);

// --- Number Conversion Functions ---
// Functions for converting numbers between different bases.

/**
 * @brief Converts a decimal integer to its binary string representation.
 * @param decimalNum The decimal integer to convert.
 * @return A string representing the binary equivalent. Returns "0" for input 0.
 */
std::string decToBin(long long decimalNum);

/**
 * @brief Converts a decimal integer to its octal string representation.
 * @param decimalNum The decimal integer to convert.
 * @return A string representing the octal equivalent. Returns "0" for input 0.
 */
std::string decToOct(long long decimalNum);

/**
 * @brief Converts a decimal integer to its hexadecimal string representation.
 * @param decimalNum The decimal integer to convert.
 * @return A string representing the hexadecimal equivalent (uppercase). Returns "0" for input 0.
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
 * @return The decimal integer equivalent. Returns -1 if an invalid hex character is encountered,
 * though `isValidHexadecimal` should prevent this in practice.
 */
long long hexToDec(const std::string& hexNumString);

// --- Helper Functions for Input Validation ---
// These functions provide robust ways to get validated input from the user.

/**
 * @brief Checks if a given string contains only valid binary digits ('0' or '1').
 * @param str The string to validate.
 * @return `true` if the string is a valid binary number, `false` otherwise.
 */
bool isValidBinary(const std::string& str);

/**
 * @brief Checks if a given string contains only valid octal digits ('0' through '7').
 * @param str The string to validate.
 * @return `true` if the string is a valid octal number, `false` otherwise.
 */
bool isValidOctal(const std::string& str);

/**
 * @brief Checks if a given string contains only valid hexadecimal digits ('0'-'9', 'A'-'F', case-insensitive).
 * @param str The string to validate.
 * @return `true` if the string is a valid hexadecimal number, `false` otherwise.
 */
bool isValidHexadecimal(const std::string& str);

/**
 * @brief Prompts the user for a double (floating-point) input and validates it.
 * @param num Reference to a double variable where the validated input will be stored.
 * @return `true` if a valid double was read, `false` otherwise. Handles input stream errors.
 */
bool getDoubleInput(double& num);

/**
 * @brief Prompts the user for a long long integer input and validates it.
 * @param num Reference to a long long variable where the validated input will be stored.
 * @return `true` if a valid long long was read, `false` otherwise. Handles input stream errors.
 */
bool getLongLongInput(long long& num);


// --- Main Program Entry Point ---
int main() {
    int choice; // Variable to store the user's main menu choice

    // Main program loop: Continues until the user chooses to exit (option 3)
    do {
        displayMainMenu(); // Display the main menu options
        std::cout << "Enter your choice: ";

        // Input validation loop for main menu choice
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear(); // Clear the error flag on std::cin
            // Discard invalid input from the buffer up to the newline character
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        // Consume the remaining newline character after a successful integer read
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Handle user's main menu choice using a switch statement
        switch (choice) {
        case 1:
            performArithmeticOperations(); // Call the arithmetic module
            break;
        case 2:
            performNumberConversions();  // Call the number conversion module
            break;
        case 3:
            std::cout << "Exiting Calculator. Goodbye!\n"; // Exit message
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n"; // Handle out-of-range choices
            break;
        }
        std::cout << "\n"; // Add a newline for better readability between menu loops
    } while (choice != 3); // Loop condition: Continue as long as user doesn't choose to exit

    return 0; // Indicate successful program execution
}

/**
 * @brief Displays the main menu options to the console.
 *
 * This function simply prints the main menu header and options to `std::cout`.
 */
void displayMainMenu() {
    std::cout << "---------- Calculator Menu ----------\n";
    std::cout << "1. Arithmetic Operations\n";
    std::cout << "2. Number Base Conversions\n";
    std::cout << "3. Exit\n";
    std::cout << "-------------------------------------\n";
}

/**
 * @brief Manages the arithmetic operations sub-menu and logic.
 *
 * This function allows the user to perform repeated arithmetic operations
 * (addition, subtraction, multiplication, division) until they choose
 * to return to the main menu. It prompts for operands, calls the appropriate
 * arithmetic function, and displays the result. It includes division-by-zero
 * handling and robust input validation for numbers.
 */
void performArithmeticOperations() {
    double num1, num2;      // Variables to store the two numbers for arithmetic
    char operationChoice;   // Variable to store the user's operation choice (e.g., 'a', 's')

    // Loop for arithmetic operations: Continues until user chooses to return ('r')
    do {
        std::cout << "\n--- Arithmetic Operations ---\n";
        std::cout << "a. Addition\n";
        std::cout << "s. Subtraction\n";
        std::cout << "m. Multiplication\n";
        std::cout << "d. Division\n";
        std::cout << "r. Return to Main Menu\n";
        std::cout << "Enter your operation choice (a, s, m, d, r): ";
        std::cin >> operationChoice; // Get operation choice
        // Consume the remaining newline character
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Check if the user wants to return to the main menu
        if (operationChoice == 'r' || operationChoice == 'R') {
            break; // Exit the arithmetic operations loop
        }

        // Prompt and validate input for the first number
        std::cout << "Enter the first number (floating-point): ";
        if (!getDoubleInput(num1)) { // Call helper for robust double input
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue; // Skip to the next iteration of the loop
        }

        std::cout << "Enter the second number (floating-point): ";
        if (!getDoubleInput(num2)) { // Call helper for robust double input
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue; // Skip to the next iteration of the loop
        }

        // Perform the chosen arithmetic operation
        switch (operationChoice) {
        case 'a':
        case 'A':
            std::cout << "Result: " << num1 << " + " << num2 << " = " << add(num1, num2) << std::endl;
            break;
        case 's':
        case 'S':
            std::cout << "Result: " << num1 << " - " << num2 << " = " << subtract(num1, num2) << std::endl;
            break;
        case 'm':
        case 'M':
            std::cout << "Result: " << num1 << " * " << num2 << " = " << multiply(num1, num2) << std::endl;
            break;
        case 'd':
        case 'D':
            // Handle division by zero
            if (num2 != 0) {
                std::cout << "Result: " << num1 << " / " << num2 << " = " << divide(num1, num2) << std::endl;
            }
            else {
                std::cout << "Error: Division by zero is not allowed.\n";
            }
            break;
        default:
            std::cout << "Invalid operation choice. Please try again.\n"; // Handle invalid operation character
            break;
        }
    } while (true); // Loop indefinitely until 'r' is entered
}

/**
 * @brief Manages the number base conversion sub-menu and logic.
 *
 * This function allows the user to perform repeated number base conversions
 * until they choose to return to the main menu. It presents a sub-menu,
 * prompts for numbers in the specified base, validates the input for correctness
 * within that base, performs the conversion, and displays the result.
 */
void performNumberConversions() {
    int choice;             // Variable to store the user's conversion choice
    long long decimalNum;   // Used for decimal input for conversions from decimal
    std::string numString;  // Used for string input for conversions to decimal (e.g., binary, hex strings)

    // Loop for number conversions: Continues until user chooses to return (option 7)
    do {
        std::cout << "\n--- Number Base Conversion ---\n";
        std::cout << "1. Decimal to Binary\n";
        std::cout << "2. Decimal to Octal\n";
        std::cout << "3. Decimal to Hexadecimal\n";
        std::cout << "4. Binary to Decimal\n";
        std::cout << "5. Octal to Decimal\n";
        std::cout << "6. Hexadecimal to Decimal\n";
        std::cout << "7. Return to Main Menu\n";
        std::cout << "Enter your conversion choice: ";

        // Input validation loop for conversion choice
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        // Consume the remaining newline character
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Check if the user wants to return to the main menu
        if (choice == 7) {
            break; // Exit the conversion loop
        }

        // Perform the chosen number base conversion
        switch (choice) {
        case 1: // Decimal to Binary
            std::cout << "Enter a decimal number: ";
            if (getLongLongInput(decimalNum)) { // Get and validate decimal input
                std::cout << "Binary: " << decToBin(decimalNum) << std::endl;
            }
            else {
                std::cout << "Invalid decimal input.\n";
            }
            break;
        case 2: // Decimal to Octal
            std::cout << "Enter a decimal number: ";
            if (getLongLongInput(decimalNum)) { // Get and validate decimal input
                std::cout << "Octal: " << decToOct(decimalNum) << std::endl;
            }
            else {
                std::cout << "Invalid decimal input.\n";
            }
            break;
        case 3: // Decimal to Hexadecimal
            std::cout << "Enter a decimal number: ";
            if (getLongLongInput(decimalNum)) { // Get and validate decimal input
                std::cout << "Hexadecimal: " << decToHex(decimalNum) << std::endl;
            }
            else {
                std::cout << "Invalid decimal input.\n";
            }
            break;
        case 4: // Binary to Decimal
            std::cout << "Enter a binary number: ";
            std::getline(std::cin, numString); // Read binary as a string
            if (isValidBinary(numString)) {    // Validate the binary string
                std::cout << "Decimal: " << binToDec(numString) << std::endl;
            }
            else {
                std::cout << "Invalid binary input. Only '0' and '1' are allowed.\n";
            }
            break;
        case 5: // Octal to Decimal
            std::cout << "Enter an octal number: ";
            std::getline(std::cin, numString); // Read octal as a string
            if (isValidOctal(numString)) {     // Validate the octal string
                std::cout << "Decimal: " << octToDec(numString) << std::endl;
            }
            else {
                std::cout << "Invalid octal input. Only '0'-'7' are allowed.\n";
            }
            break;
        case 6: // Hexadecimal to Decimal
            std::cout << "Enter a hexadecimal number: ";
            std::getline(std::cin, numString); // Read hexadecimal as a string
            if (isValidHexadecimal(numString)) { // Validate the hexadecimal string
                std::cout << "Decimal: " << hexToDec(numString) << std::endl;
            }
            else {
                std::cout << "Invalid hexadecimal input. Only '0'-'9', 'A'-'F' (case-insensitive) are allowed.\n";
            }
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n"; // Handle invalid conversion choice
            break;
        }
    } while (true); // Loop indefinitely until '7' is entered
}

/**
 * @brief Adds two double-precision floating-point numbers.
 * @param num1 The first number.
 * @param num2 The second number.
 * @return The sum of `num1` and `num2`.
 */
double add(double num1, double num2) {
    return num1 + num2;
}

/**
 * @brief Subtracts the second double from the first.
 * @param num1 The number to subtract from (minuend).
 * @param num2 The number to subtract (subtrahend).
 * @return The difference `num1 - num2`.
 */
double subtract(double num1, double num2) {
    return num1 - num2;
}

/**
 * @brief Multiplies two double-precision floating-point numbers.
 * @param num1 The first factor.
 * @param num2 The second factor.
 * @return The product of `num1` and `num2`.
 */
double multiply(double num1, double num2) {
    return num1 * num2;
}

/**
 * @brief Divides the first double by the second.
 * @param num1 The dividend.
 * @param num2 The divisor.
 * @return The quotient `num1 / num2`. Caller is responsible for checking `num2 != 0`.
 */
double divide(double num1, double num2) {
    return num1 / num2;
}

/**
 * @brief Converts a decimal (base-10) long long integer to its binary (base-2) string representation.
 * @param decimalNum The decimal number to convert.
 * @return A `std::string` containing the binary representation.
 */
std::string decToBin(long long decimalNum) {
    if (decimalNum == 0) {
        return "0"; // Special case for 0
    }
    std::string binaryString = "";
    // Repeatedly divide by 2 and prepend the remainder
    while (decimalNum > 0) {
        binaryString = (decimalNum % 2 == 0 ? "0" : "1") + binaryString;
        decimalNum /= 2;
    }
    return binaryString;
}

/**
 * @brief Converts a decimal (base-10) long long integer to its octal (base-8) string representation.
 * @param decimalNum The decimal number to convert.
 * @return A `std::string` containing the octal representation.
 */
std::string decToOct(long long decimalNum) {
    if (decimalNum == 0) {
        return "0"; // Special case for 0
    }
    std::string octalString = "";
    // Repeatedly divide by 8 and prepend the remainder
    while (decimalNum > 0) {
        octalString = std::to_string(decimalNum % 8) + octalString;
        decimalNum /= 8;
    }
    return octalString;
}

/**
 * @brief Converts a decimal (base-10) long long integer to its hexadecimal (base-16) string representation.
 * @param decimalNum The decimal number to convert.
 * @return A `std::string` containing the hexadecimal representation (uppercase A-F).
 */
std::string decToHex(long long decimalNum) {
    if (decimalNum == 0) {
        return "0"; // Special case for 0
    }
    std::string hexString = "";
    // Character array for hexadecimal digits (0-9 and A-F)
    const char hexDigits[] = "0123456789ABCDEF";
    // Repeatedly divide by 16 and prepend the corresponding hex digit
    while (decimalNum > 0) {
        hexString = hexDigits[decimalNum % 16] + hexString;
        decimalNum /= 16;
    }
    return hexString;
}

/**
 * @brief Converts a binary (base-2) string representation to its decimal (base-10) long long integer.
 * @param binaryNumString The binary number as a `std::string` (e.g., "10110").
 * @return The decimal long long integer equivalent.
 */
long long binToDec(const std::string& binaryNumString) {
    long long decimalResult = 0;
    long long power = 1; // Represents 2^0, 2^1, 2^2, etc., for position value

    // Iterate through the binary string from right to left (least significant bit to most significant)
    for (int i = binaryNumString.length() - 1; i >= 0; --i) {
        if (binaryNumString[i] == '1') {
            decimalResult += power; // Add the power of 2 if the digit is '1'
        }
        power *= 2; // Move to the next power of 2 for the next digit
    }
    return decimalResult;
}

/**
 * @brief Converts an octal (base-8) string representation to its decimal (base-10) long long integer.
 * @param octalNumString The octal number as a `std::string` (e.g., "754").
 * @return The decimal long long integer equivalent.
 */
long long octToDec(const std::string& octalNumString) {
    long long decimalResult = 0;
    long long power = 1; // Represents 8^0, 8^1, 8^2, etc.

    // Iterate through the octal string from right to left
    for (int i = octalNumString.length() - 1; i >= 0; --i) {
        int digit = octalNumString[i] - '0'; // Convert character digit to integer value
        decimalResult += digit * power;      // Add (digit * power of 8) to the result
        power *= 8;                          // Move to the next power of 8
    }
    return decimalResult;
}

/**
 * @brief Converts a hexadecimal (base-16) string representation to its decimal (base-10) long long integer.
 * @param hexNumString The hexadecimal number as a `std::string` (e.g., "A3F"). Case-insensitive.
 * @return The decimal long long integer equivalent.
 */
long long hexToDec(const std::string& hexNumString) {
    long long decimalResult = 0;
    long long power = 1; // Represents 16^0, 16^1, 16^2, etc.

    // Iterate through the hexadecimal string from right to left
    for (int i = hexNumString.length() - 1; i >= 0; --i) {
        char c = std::toupper(hexNumString[i]); // Convert character to uppercase for consistent handling
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0'; // '0'-'9' characters
        }
        else if (c >= 'A' && c <= 'F') {
            digit = 10 + (c - 'A'); // 'A'-'F' characters (A=10, B=11, etc.)
        }
        else {
            // This case should ideally not be reached if isValidHexadecimal is used before calling this.
            // Returning -1 as an error indicator, but proper error handling might involve exceptions.
            return -1;
        }
        decimalResult += digit * power; // Add (digit * power of 16) to the result
        power *= 16;                    // Move to the next power of 16
    }
    return decimalResult;
}

/**
 * @brief Validates if a given string consists solely of '0' and '1' characters, making it a valid binary string.
 * @param str The `std::string` to be validated.
 * @return `true` if the string is a valid binary representation (not empty and contains only '0' or '1'), `false` otherwise.
 */
bool isValidBinary(const std::string& str) {
    if (str.empty()) return false; // An empty string is not a valid binary number
    for (char c : str) {
        if (c != '0' && c != '1') {
            return false; // Found a character that is not '0' or '1'
        }
    }
    return true; // All characters are valid binary digits
}

/**
 * @brief Validates if a given string consists solely of digits from '0' to '7', making it a valid octal string.
 * @param str The `std::string` to be validated.
 * @return `true` if the string is a valid octal representation (not empty and contains only '0'-'7'), `false` otherwise.
 */
bool isValidOctal(const std::string& str) {
    if (str.empty()) return false; // An empty string is not a valid octal number
    for (char c : str) {
        if (c < '0' || c > '7') {
            return false; // Found a character outside the octal range
        }
    }
    return true; // All characters are valid octal digits
}

/**
 * @brief Validates if a given string consists solely of valid hexadecimal digits ('0'-'9', 'A'-'F', case-insensitive).
 * @param str The `std::string` to be validated.
 * @return `true` if the string is a valid hexadecimal representation (not empty and contains valid hex chars), `false` otherwise.
 */
bool isValidHexadecimal(const std::string& str) {
    if (str.empty()) return false; // An empty string is not a valid hexadecimal number
    for (char c : str) {
        c = std::toupper(c); // Convert character to uppercase for easier comparison
        // Check if the character is a digit (0-9) or a hex letter (A-F)
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))) {
            return false; // Found an invalid hexadecimal character
        }
    }
    return true; // All characters are valid hexadecimal digits
}

/**
 * @brief Attempts to read a double-precision floating-point number from standard input.
 *
 * This function handles potential input errors (e.g., user enters text instead of a number)
 * by clearing the error flags and discarding invalid input.
 * @param num A reference to the `double` variable where the input will be stored.
 * @return `true` if a valid `double` was successfully read and stored, `false` otherwise.
 */
bool getDoubleInput(double& num) {
    std::cin >> num; // Attempt to read the double
    if (std::cin.fail()) { // Check if the input operation failed
        std::cin.clear(); // Clear the error flag on `std::cin`
        // Discard all characters in the input buffer until a newline is found
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false; // Indicate that input was invalid
    }
    // Consume the remaining newline character from the buffer after successful read
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true; // Indicate that input was valid
}

/**
 * @brief Attempts to read a long long integer from standard input.
 *
 * This function handles potential input errors (e.g., user enters text instead of a number)
 * by clearing the error flags and discarding invalid input.
 * @param num A reference to the `long long` variable where the input will be stored.
 * @return `true` if a valid `long long` was successfully read and stored, `false` otherwise.
 */
bool getLongLongInput(long long& num) {
    std::cin >> num; // Attempt to read the long long
    if (std::cin.fail()) { // Check if the input operation failed
        std::cin.clear(); // Clear the error flag on `std::cin`
        // Discard all characters in the input buffer until a newline is found
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false; // Indicate that input was invalid
    }
    // Consume the remaining newline character from the buffer after successful read
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true; // Indicate that input was valid
}