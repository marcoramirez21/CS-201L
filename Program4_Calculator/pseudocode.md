# Calculator Program Pseudocode

## Main Program Flow

```pseudocode
START
    LOOP UNTIL user_choice IS 3 (Exit)
        CALL displayMainMenu()
        GET validated user_choice for main menu
        SWITCH user_choice
            CASE 1: CALL performArithmeticOperations()
            CASE 2: CALL performNumberConversions()
            CASE 3: DISPLAY "Exiting Calculator. Goodbye!"
            DEFAULT: DISPLAY "Invalid choice."
        END SWITCH
    END LOOP
END

PROCEDURE displayMainMenu()
    DISPLAY main menu options (Arithmetic, Conversions, Exit)
END PROCEDURE

PROCEDURE performArithmeticOperations()
    LOOP UNTIL user_chooses_to_return
        DISPLAY arithmetic sub-menu (Add, Subtract, Multiply, Divide, Return)
        GET operationChoice
        IF operationChoice IS 'r' THEN BREAK LOOP
        
        GET validated num1 (floating_point)
        GET validated num2 (floating_point)

        SWITCH operationChoice
            CASE 'a': DISPLAY num1 + num2
            CASE 's': DISPLAY num1 - num2
            CASE 'm': DISPLAY num1 * num2
            CASE 'd':
                IF num2 IS NOT 0 THEN DISPLAY num1 / num2
                ELSE DISPLAY "Error: Division by zero."
            DEFAULT: DISPLAY "Invalid operation."
        END SWITCH
    END LOOP
END PROCEDURE

PROCEDURE performNumberConversions()
    LOOP UNTIL user_chooses_to_return
        DISPLAY conversion sub-menu (Dec to Bin/Oct/Hex, Bin/Oct/Hex to Dec, Return)
        GET choice
        IF choice IS 7 THEN BREAK LOOP

        SWITCH choice
            CASE 1 (Dec to Bin):
                GET validated decimalNum
                DISPLAY CALL decToBin(decimalNum)
            CASE 2 (Dec to Oct):
                GET validated decimalNum
                DISPLAY CALL decToOct(decimalNum)
            CASE 3 (Dec to Hex):
                GET validated decimalNum
                DISPLAY CALL decToHex(decimalNum)
            CASE 4 (Bin to Dec):
                GET binaryNumString
                IF CALL isValidBinary(binaryNumString) THEN DISPLAY CALL binToDec(binaryNumString)
                ELSE DISPLAY "Invalid binary input."
            CASE 5 (Oct to Dec):
                GET octalNumString
                IF CALL isValidOctal(octalNumString) THEN DISPLAY CALL octToDec(octalNumString)
                ELSE DISPLAY "Invalid octal input."
            CASE 6 (Hex to Dec):
                GET hexNumString
                IF CALL isValidHexadecimal(hexNumString) THEN DISPLAY CALL hexToDec(hexNumString)
                ELSE DISPLAY "Invalid hexadecimal input."
            DEFAULT: DISPLAY "Invalid choice."
        END SWITCH
    END LOOP
END PROCEDURE

PROCEDURE add(num1, num2)
    RETURN num1 + num2
END PROCEDURE

PROCEDURE subtract(num1, num2)
    RETURN num1 - num2
END PROCEDURE

PROCEDURE multiply(num1, num2)
    RETURN num1 * num2
END PROCEDURE

PROCEDURE divide(num1, num2)
    RETURN num1 / num2
END PROCEDURE

PROCEDURE decToBin(decimalNum)
    IF decimalNum IS 0 THEN RETURN "0"
    DECLARE binaryString
    WHILE decimalNum > 0
        PREPEND (decimalNum MOD 2) to binaryString
        SET decimalNum = decimalNum / 2
    END WHILE
    RETURN binaryString
END PROCEDURE

PROCEDURE decToOct(decimalNum)
    IF decimalNum IS 0 THEN RETURN "0"
    DECLARE octalString
    WHILE decimalNum > 0
        PREPEND (decimalNum MOD 8) to octalString
        SET decimalNum = decimalNum / 8
    END WHILE
    RETURN octalString
END PROCEDURE

PROCEDURE decToHex(decimalNum)
    IF decimalNum IS 0 THEN RETURN "0"
    DECLARE hexString
    DECLARE hexDigits array
    WHILE decimalNum > 0
        SET remainder = decimalNum MOD 16
        PREPEND hexDigits[remainder] to hexString
        SET decimalNum = decimalNum / 16
    END WHILE
    RETURN hexString
END PROCEDURE

PROCEDURE binToDec(binaryNumString)
    DECLARE decimalResult = 0
    DECLARE power = 1
    FOR each char in binaryNumString from right to left
        IF char IS '1' THEN ADD power to decimalResult
        MULTIPLY power by 2
    END FOR
    RETURN decimalResult
END PROCEDURE

PROCEDURE octToDec(octalNumString)
    DECLARE decimalResult = 0
    DECLARE power = 1
    FOR each char in octalNumString from right to left
        SET digit = char to integer
        ADD (digit * power) to decimalResult
        MULTIPLY power by 8
    END FOR
    RETURN decimalResult
END PROCEDURE

PROCEDURE hexToDec(hexNumString)
    DECLARE decimalResult = 0
    DECLARE power = 1
    FOR each char in hexNumString from right to left
        SET digit = hexChar to integer (handle A-F)
        ADD (digit * power) to decimalResult
        MULTIPLY power by 16
    END FOR
    RETURN decimalResult
END PROCEDURE

PROCEDURE isValidBinary(str)
    IF str IS empty THEN RETURN false
    FOR each char in str
        IF char IS NOT '0' AND NOT '1' THEN RETURN false
    END FOR
    RETURN true
END PROCEDURE

PROCEDURE isValidOctal(str)
    IF str IS empty THEN RETURN false
    FOR each char in str
        IF char IS NOT BETWEEN '0' AND '7' THEN RETURN false
    END FOR
    RETURN true
END PROCEDURE

PROCEDURE isValidHexadecimal(str)
    IF str IS empty THEN RETURN false
    FOR each char in str
        IF char IS NOT '0'-'9' AND NOT 'A'-'F' (case-insensitive) THEN RETURN false
    END FOR
    RETURN true
END PROCEDURE

PROCEDURE getDoubleInput(num)
    ATTEMPT to read double into num
    IF read fails THEN
        CLEAR input error, DISCARD invalid input
        RETURN false
    END IF
    CONSUME newline
    RETURN true
END PROCEDURE

PROCEDURE getLongLongInput(num)
    ATTEMPT to read long long into num
    IF read fails THEN
        CLEAR input error, DISCARD invalid input
        RETURN false
    END IF
    CONSUME newline
    RETURN true
END PROCEDURE