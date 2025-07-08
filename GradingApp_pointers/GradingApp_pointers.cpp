// GradingSystem.cpp
// Implementation file for Program 5 - Grading Using Pointers

#include "GradingSystem.h" // Include our header file
#include <iostream>        // For console input/output
#include <fstream>         // For file input/output (ifstream, ofstream)
#include <string>          // For std::string manipulation
#include <vector>          // For std::vector
#include <iomanip>         // For std::fixed, std::setprecision
#include <limits>          // For std::numeric_limits
#include <algorithm>       // For std::remove, std::isspace (useful for trimming/cleaning strings)
#include <stdexcept>       // For std::stoi exceptions if chosen over isNumeric

// Pseudocode Note: Function: isNumeric(STRING s) -> BOOL
// Purpose: Check if a given string contains only numeric digits.
bool isNumeric(const std::string& s) {
    // An empty string is not considered numeric for an ID.
    if (s.empty()) {
        return false;
    }
    for (char c : s) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Pseudocode Note: Function: calculateScoreAndGrade(studentInfo* student, STRING correctAnswers)
// Purpose: Calculate student's score, percentage, and assign a letter grade.
void calculateScoreAndGrade(studentInfo* student, const std::string& correctAnswers) {
    student->score = 0; // Initialize score
    int numQuestions = correctAnswers.length(); // Assuming 20 questions based on input format

    // Iterate through each answer provided by the student
    for (int i = 0; i < numQuestions; ++i) {
        char studentAnswer = (i < student->answers.length()) ? student->answers[i] : ' '; // Handle potentially shorter answer strings or missing characters
        char correctAnswer = correctAnswers[i];

        if (studentAnswer == correctAnswer) {
            student->score += 2; // Correct answer is worth 2 points
        }
        else if (studentAnswer == ' ') {
            student->score += 0; // Blank answers are worth 0 points
        }
        else {
            student->score += 1; // Incorrect answer is worth 1 point
        }
    }

    // Calculate percentage, watching for integer division
    student->percent = static_cast<float>(student->score) / 40.0f * 100.0f;

    // Assign grade based on the scale
    if (student->percent >= 90.0f) {
        student->grade = 'A';
    }
    else if (student->percent >= 80.0f) {
        student->grade = 'B';
    }
    else if (student->percent >= 70.0f) {
        student->grade = 'C';
    }
    else if (student->percent >= 60.0f) {
        student->grade = 'D';
    }
    else {
        student->grade = 'F';
    }
}

// Pseudocode Note: Function: writeErrorFile(STRING errorFileName, STRING errorMessage)
// Purpose: Handles and logs invalid student records by appending to error.txt.
void writeErrorFile(const std::string& errorFileName, const std::string& errorMessage) {
    std::ofstream errorFile(errorFileName, std::ios::app); // Open in append mode
    if (!errorFile.is_open()) {
        std::cerr << "Error: Could not open error file for writing: " << errorFileName << std::endl;
        // In a real application, you might throw an exception or handle this more robustly.
        return;
    }
    errorFile << "Error found in this line: " << errorMessage << std::endl;
    errorFile.close();
}


// Pseudocode Note: Function: readStudentData(...)
// Purpose: Read student.txt, validate IDs, calculate scores/grades, populate vector of studentInfo pointers.
// Returns the correct answers string.
std::string readStudentData(const std::string& studentFileName, const std::string& errorFileName, std::vector<studentInfo*>& studentList) {
    std::ifstream studentFile(studentFileName);
    std::string correctAnswers;

    // Open student input file
    if (!studentFile.is_open()) {
        std::cerr << "Error: Could not open student data file: " << studentFileName << std::endl;
        exit(1); // Exit if essential input file cannot be opened
    }

    // Clear error.txt content from previous runs, then ensure it can be opened
    std::ofstream errorFileClear(errorFileName, std::ios::trunc); // Open in truncate mode to clear
    if (!errorFileClear.is_open()) {
        std::cerr << "Error: Could not clear/open error file: " << errorFileName << std::endl;
        exit(1); // Exit if essential error file cannot be opened
    }
    errorFileClear.close();

    // Read the first line which contains the correct answers
    if (std::getline(studentFile, correctAnswers)) {
        // Trim any trailing whitespace from correctAnswers
        correctAnswers.erase(std::remove_if(correctAnswers.begin(), correctAnswers.end(), ::isspace), correctAnswers.end());
    }
    else {
        std::cerr << "Error: Could not read correct answers from " << studentFileName << std::endl;
        studentFile.close();
        exit(1);
    }

    std::string line;
    // Read the remaining records containing student IDs and answers
    while (std::getline(studentFile, line)) {
        if (line.empty()) { // Skip empty lines
            continue;
        }

        std::string studentID_str;
        std::string answers_str;
        size_t firstSpacePos = line.find(' ');

        // Parse student ID and answers from the line
        if (firstSpacePos != std::string::npos) {
            studentID_str = line.substr(0, firstSpacePos);
            answers_str = line.substr(firstSpacePos + 1);
            // Trim leading/trailing whitespace from answers_str
            answers_str.erase(0, answers_str.find_first_not_of(" \t\n\r\f\v"));
            answers_str.erase(answers_str.find_last_not_of(" \t\n\r\f\v") + 1);
        }
        else {
            // Handle lines that might only have an ID or are malformed without a space
            studentID_str = line;
            answers_str = ""; // No answers provided
        }

        // Validate student ID
        if (!isNumeric(studentID_str)) {
            writeErrorFile(errorFileName, line); // Write the entire problematic line to error file
            continue; // Skip this record and move to the next
        }

        // Create a new studentInfo object dynamically
        studentInfo* newStudent = new studentInfo;
        try {
            newStudent->studentID = std::stoi(studentID_str); // Convert string ID to integer
        }
        catch (const std::out_of_range& oor) { // Catches too large/small numbers
            writeErrorFile(errorFileName, line + " (ID out of range)");
            delete newStudent; // Clean up memory for the failed object
            continue;
        }
        catch (const std::invalid_argument& ia) { // Catches non-numeric if isNumeric was not used/failed somehow
            writeErrorFile(errorFileName, line + " (ID invalid argument)");
            delete newStudent; // Clean up memory for the failed object
            continue;
        }

        newStudent->answers = answers_str;

        // Calculate score and grade for the student
        calculateScoreAndGrade(newStudent, correctAnswers);

        // Add the pointer to the studentInfo object to the vector
        studentList.push_back(newStudent);
    }

    studentFile.close();
    return correctAnswers;
}

// Pseudocode Note: Function: writeReportFile(...)
// Purpose: Formats and writes processed student data to report.txt.
void writeReportFile(const std::string& reportFileName, const std::vector<studentInfo*>& studentList, const std::string& correctAnswers) {
    std::ofstream reportFile(reportFileName);

    if (!reportFile.is_open()) {
        std::cerr << "Error: Could not open report file for writing: " << reportFileName << std::endl;
        exit(1); // Exit if essential output file cannot be opened
    }

    // Write header
    reportFile << std::left << std::setw(10) << "STUD ID"
        << std::setw(25) << "STUDENT ANSWERS"
        << std::setw(15) << "SCORE/40"
        << std::setw(15) << "PERCENT"
        << std::setw(5) << "GRADE" << std::endl;

    // Optional: Write correct answers and separator for context
    reportFile << "Correct Answers: " << correctAnswers << std::endl;
    reportFile << std::string(80, '-') << std::endl; // Separator line

    // Write each student's data
    for (const auto& studentPtr : studentList) { // Use const auto& for iteration over pointers
        reportFile << std::left << std::setw(10) << studentPtr->studentID
            << std::setw(25) << studentPtr->answers
            << std::setw(15) << std::to_string(studentPtr->score) + "/40"
            << std::fixed << std::setprecision(2) << std::setw(15) << studentPtr->percent
            << std::setw(5) << studentPtr->grade << std::endl;
    }

    reportFile.close();
}

// Pseudocode Note: Function: cleanUpMemory(...)
// Purpose: Delete dynamically allocated studentInfo objects to prevent memory leaks.
void cleanUpMemory(std::vector<studentInfo*>& studentList) {
    for (studentInfo* s_ptr : studentList) {
        delete s_ptr; // Delete the dynamically allocated studentInfo object
    }
    studentList.clear(); // Clear the pointers from the vector
}

// Pseudocode Note: Main Program Flow (main function)
int main() {
    std::string studentFileName = "student.txt";
    std::string errorFileName = "error.txt";
    std::string reportFileName = "report.txt";

    std::vector<studentInfo*> studentRecords; // Vector to store pointers to student data
    std::string correctAnswers;

    std::cout << "Starting quiz grading process..." << std::endl;

    // Read student data and process it
    correctAnswers = readStudentData(studentFileName, errorFileName, studentRecords);

    // Write the report file
    writeReportFile(reportFileName, studentRecords, correctAnswers);

    // Clean up dynamically allocated memory
    cleanUpMemory(studentRecords);

    std::cout << "Grading process complete. Check " << reportFileName << " and " << errorFileName << " for results." << std::endl;

    return 0; // Indicate successful execution
}