#include <iostream>
#include <string>
#include <cmath>
#include <limits> // Required for numeric_limits

// Function Prototypes
void displayMainMenu();
void performArithmeticOperations();
void performNumberConversions();

// Arithmetic Functions
double add(double num1, double num2);
double subtract(double num1, double num2);
double multiply(double num1, double num2);
double divide(double num1, double num2);

// Number Conversion Functions
std::string decToBin(long long decimalNum);
std::string decToOct(long long decimalNum);
std::string decToHex(long long decimalNum);
long long binToDec(const std::string& binaryNumString);
long long octToDec(const std::string& octalNumString);
long long hexToDec(const std::string& hexNumString);

// Helper Functions for Validation
bool isValidBinary(const std::string& str);
bool isValidOctal(const std::string& str);
bool isValidHexadecimal(const std::string& str);
bool getDoubleInput(double& num);
bool getLongLongInput(long long& num);

int main() {
    int choice;
    do {
        displayMainMenu();
        std::cout << "Enter your choice: ";
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume the newline character

        switch (choice) {
        case 1:
            performArithmeticOperations();
            break;
        case 2:
            performNumberConversions();
            break;
        case 3:
            std::cout << "Exiting Calculator. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        std::cout << "\n"; // Add a newline for better readability between menu loops
    } while (choice != 3);

    return 0;
}

// Pseudocode for displayMainMenu():
//  Display the main menu options:
//  1. Arithmetic Operations
//  2. Number Base Conversions
//  3. Exit
void displayMainMenu() {
    std::cout << "---------- Calculator Menu ----------\n";
    std::cout << "1. Arithmetic Operations\n";
    std::cout << "2. Number Base Conversions\n";
    std::cout << "3. Exit\n";
    std::cout << "-------------------------------------\n";
}

// Pseudocode for performArithmeticOperations():
//  Loop until user chooses to return to main menu:
//      Prompt user to choose an arithmetic operation (add, subtract, multiply, divide).
//      Validate operation choice.
//      If valid:
//          Prompt user to enter two numbers.
//          Validate number inputs.
//          Perform the chosen operation using dedicated functions (add, subtract, multiply, divide).
//          Display the result.
//          Handle division by zero.
//      Offer user to perform another arithmetic operation or return to main menu.
void performArithmeticOperations() {
    int choice;
    double num1, num2;
    char operationChoice;

    do {
        std::cout << "\n--- Arithmetic Operations ---\n";
        std::cout << "a. Addition\n";
        std::cout << "s. Subtraction\n";
        std::cout << "m. Multiplication\n";
        std::cout << "d. Division\n";
        std::cout << "r. Return to Main Menu\n";
        std::cout << "Enter your operation choice (a, s, m, d, r): ";
        std::cin >> operationChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (operationChoice == 'r' || operationChoice == 'R') {
            break; // Exit the loop and return to main menu
        }

        std::cout << "Enter the first number (floating-point): ";
        if (!getDoubleInput(num1)) {
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        std::cout << "Enter the second number (floating-point): ";
        if (!getDoubleInput(num2)) {
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

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
            if (num2 != 0) {
                std::cout << "Result: " << num1 << " / " << num2 << " = " << divide(num1, num2) << std::endl;
            }
            else {
                std::cout << "Error: Division by zero is not allowed.\n";
            }
            break;
        default:
            std::cout << "Invalid operation choice. Please try again.\n";
            break;
        }
    } while (true);
}

// Pseudocode for performNumberConversions():
//  Loop until user chooses to return to main menu:
//      Display number base conversion sub-menu.
//      Prompt user for conversion choice.
//      Validate conversion choice.
//      If valid:
//          Prompt user to enter the number in the specified base (as a string for non-decimal).
//          Validate the input string for the given base.
//          Perform the conversion using dedicated functions (e.g., decToBin, binToDec).
//          Display the result.
//      Offer user to perform another conversion or return to main menu.
void performNumberConversions() {
    int choice;
    long long decimalNum;
    std::string numString;

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
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 7) {
            break; // Exit the loop and return to main menu
        }

        switch (choice) {
        case 1: // Decimal to Binary
            std::cout << "Enter a decimal number: ";
            if (getLongLongInput(decimalNum)) {
                std::cout << "Binary: " << decToBin(decimalNum) << std::endl;
            }
            else {
                std::cout << "Invalid decimal input.\n";
            }
            break;
        case 2: // Decimal to Octal
            std::cout << "Enter a decimal number: ";
            if (getLongLongInput(decimalNum)) {
                std::cout << "Octal: " << decToOct(decimalNum) << std::endl;
            }
            else {
                std::cout << "Invalid decimal input.\n";
            }
            break;
        case 3: // Decimal to Hexadecimal
            std::cout << "Enter a decimal number: ";
            if (getLongLongInput(decimalNum)) {
                std::cout << "Hexadecimal: " << decToHex(decimalNum) << std::endl;
            }
            else {
                std::cout << "Invalid decimal input.\n";
            }
            break;
        case 4: // Binary to Decimal
            std::cout << "Enter a binary number: ";
            std::getline(std::cin, numString);
            if (isValidBinary(numString)) {
                std::cout << "Decimal: " << binToDec(numString) << std::endl;
            }
            else {
                std::cout << "Invalid binary input. Only '0' and '1' are allowed.\n";
            }
            break;
        case 5: // Octal to Decimal
            std::cout << "Enter an octal number: ";
            std::getline(std::cin, numString);
            if (isValidOctal(numString)) {
                std::cout << "Decimal: " << octToDec(numString) << std::endl;
            }
            else {
                std::cout << "Invalid octal input. Only '0'-'7' are allowed.\n";
            }
            break;
        case 6: // Hexadecimal to Decimal
            std::cout << "Enter a hexadecimal number: ";
            std::getline(std::cin, numString);
            if (isValidHexadecimal(numString)) {
                std::cout << "Decimal: " << hexToDec(numString) << std::endl;
            }
            else {
                std::cout << "Invalid hexadecimal input. Only '0'-'9', 'A'-'F' (case-insensitive) are allowed.\n";
            }
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (true);
}

// Pseudocode for add(num1, num2):
//  Return num1 + num2.
double add(double num1, double num2) {
    return num1 + num2;
}

// Pseudocode for subtract(num1, num2):
//  Return num1 - num2.
double subtract(double num1, double num2) {
    return num1 - num2;
}

// Pseudocode for multiply(num1, num2):
//  Return num1 * num2.
double multiply(double num1, double num2) {
    return num1 * num2;
}

// Pseudocode for divide(num1, num2):
//  Return num1 / num2. (Caller handles division by zero).
double divide(double num1, double num2) {
    return num1 / num2;
}

// Pseudocode for decToBin(decimalNum):
//  If decimalNum is 0, return "0".
//  Initialize an empty string for binary result.
//  While decimalNum > 0:
//      Prepend decimalNum % 2 to the binary string.
//      Divide decimalNum by 2.
//  Return the binary string.
std::string decToBin(long long decimalNum) {
    if (decimalNum == 0) {
        return "0";
    }
    std::string binaryString = "";
    while (decimalNum > 0) {
        binaryString = (decimalNum % 2 == 0 ? "0" : "1") + binaryString;
        decimalNum /= 2;
    }
    return binaryString;
}

// Pseudocode for decToOct(decimalNum):
//  If decimalNum is 0, return "0".
//  Initialize an empty string for octal result.
//  While decimalNum > 0:
//      Prepend decimalNum % 8 (as a character) to the octal string.
//      Divide decimalNum by 8.
//  Return the octal string.
std::string decToOct(long long decimalNum) {
    if (decimalNum == 0) {
        return "0";
    }
    std::string octalString = "";
    while (decimalNum > 0) {
        octalString = std::to_string(decimalNum % 8) + octalString;
        decimalNum /= 8;
    }
    return octalString;
}

// Pseudocode for decToHex(decimalNum):
//  If decimalNum is 0, return "0".
//  Initialize an empty string for hexadecimal result.
//  Define a character array for hex digits (0-9, A-F).
//  While decimalNum > 0:
//      Get remainder (decimalNum % 16).
//      Prepend the corresponding hex digit to the hexadecimal string.
//      Divide decimalNum by 16.
//  Return the hexadecimal string.
std::string decToHex(long long decimalNum) {
    if (decimalNum == 0) {
        return "0";
    }
    std::string hexString = "";
    const char hexDigits[] = "0123456789ABCDEF";
    while (decimalNum > 0) {
        hexString = hexDigits[decimalNum % 16] + hexString;
        decimalNum /= 16;
    }
    return hexString;
}

// Pseudocode for binToDec(binaryNumString):
//  Initialize decimalResult to 0.
//  Initialize power to 0.
//  Iterate through binaryNumString from right to left:
//      If character is '1':
//          Add 2^power to decimalResult.
//      Increment power.
//  Return decimalResult.
long long binToDec(const std::string& binaryNumString) {
    long long decimalResult = 0;
    long long power = 1; // Represents 2^0, 2^1, 2^2, etc.
    for (int i = binaryNumString.length() - 1; i >= 0; --i) {
        if (binaryNumString[i] == '1') {
            decimalResult += power;
        }
        power *= 2;
    }
    return decimalResult;
}

// Pseudocode for octToDec(octalNumString):
//  Initialize decimalResult to 0.
//  Initialize power to 0.
//  Iterate through octalNumString from right to left:
//      Convert character to integer digit.
//      Add digit * 8^power to decimalResult.
//      Increment power.
//  Return decimalResult.
long long octToDec(const std::string& octalNumString) {
    long long decimalResult = 0;
    long long power = 1; // Represents 8^0, 8^1, 8^2, etc.
    for (int i = octalNumString.length() - 1; i >= 0; --i) {
        int digit = octalNumString[i] - '0';
        decimalResult += digit * power;
        power *= 8;
    }
    return decimalResult;
}

// Pseudocode for hexToDec(hexNumString):
//  Initialize decimalResult to 0.
//  Initialize power to 0.
//  Iterate through hexNumString from right to left:
//      Convert character to integer digit (A-F handled).
//      Add digit * 16^power to decimalResult.
//      Increment power.
//  Return decimalResult.
long long hexToDec(const std::string& hexNumString) {
    long long decimalResult = 0;
    long long power = 1; // Represents 16^0, 16^1, 16^2, etc.
    for (int i = hexNumString.length() - 1; i >= 0; --i) {
        char c = std::toupper(hexNumString[i]); // Convert to uppercase for consistent handling
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        }
        else if (c >= 'A' && c <= 'F') {
            digit = 10 + (c - 'A');
        }
        else {
            // This case should ideally be caught by isValidHexadecimal
            return -1; // Indicate error or throw an exception
        }
        decimalResult += digit * power;
        power *= 16;
    }
    return decimalResult;
}

// Pseudocode for isValidBinary(str):
//  For each character in str:
//      If character is not '0' and not '1':
//          Return false.
//  Return true.
bool isValidBinary(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (c != '0' && c != '1') {
            return false;
        }
    }
    return true;
}

// Pseudocode for isValidOctal(str):
//  For each character in str:
//      If character is not between '0' and '7':
//          Return false.
//  Return true.
bool isValidOctal(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (c < '0' || c > '7') {
            return false;
        }
    }
    return true;
}

// Pseudocode for isValidHexadecimal(str):
//  For each character in str:
//      If character is not between '0'-'9', 'A'-'F', or 'a'-'f':
//          Return false.
//  Return true.
bool isValidHexadecimal(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        c = std::toupper(c); // Convert to uppercase for validation
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))) {
            return false;
        }
    }
    return true;
}

// Pseudocode for getDoubleInput(num):
//  Attempt to read a double into num.
//  If input fails:
//      Clear error flag.
//      Discard invalid input.
//      Return false.
//  Return true.
bool getDoubleInput(double& num) {
    std::cin >> num;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume remaining newline
    return true;
}

// Pseudocode for getLongLongInput(num):
//  Attempt to read a long long into num.
//  If input fails:
//      Clear error flag.
//      Discard invalid input.
//      Return false.
//  Return true.
bool getLongLongInput(long long& num) {
    std::cin >> num;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume remaining newline
    return true;
}