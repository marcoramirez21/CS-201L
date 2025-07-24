#include "QuizGrader.h" // Includes both the struct and function declarations now
#include <fstream>   // For file operations
#include <iostream>  // For error output
#include <iomanip>   // For std::setw and std::left/right

// Function to read quiz data from the input file
bool readQuizData(const std::string& filename, std::string& correctAnswers,
    std::vector<StudentQuizInfo*>& students) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file " << filename << std::endl;
        return false;
    }

    // Read the first line (correct answers)
    if (!std::getline(inputFile, correctAnswers)) {
        std::cerr << "Error: Could not read correct answers from " << filename << std::endl;
        inputFile.close();
        return false;
    }

    // Read student IDs and their answers
    int studentID;
    std::string studentAnswers;
    while (inputFile >> studentID >> studentAnswers) {
        // Dynamically allocate memory for a new StudentQuizInfo object
        StudentQuizInfo* newStudent = new StudentQuizInfo(studentID, studentAnswers);
        students.push_back(newStudent); // Store the pointer in the vector
    }

    inputFile.close();
    return true;
}

// Function to calculate the number of correct answers for a single student
void calculateScores(const std::string& correctAnswers, StudentQuizInfo* studentPtr) {
    if (!studentPtr) {
        // Handle null pointer case, though typically shouldn't happen with proper usage
        return;
    }

    studentPtr->correctCount = 0; // Initialize correct count
    // Assuming both correctAnswers and studentAnswers have 5 characters
    for (size_t i = 0; i < correctAnswers.length() && i < studentPtr->studentAnswers.length(); ++i) {
        if (studentPtr->studentAnswers[i] == correctAnswers[i]) {
            studentPtr->correctCount++;
        }
    }
}

// Function to write the quiz results to the output file
bool writeResults(const std::string& filename, const std::vector<StudentQuizInfo*>& students) {
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file " << filename << std::endl;
        return false;
    }

    // Write header
    outputFile << std::left << std::setw(10) << "STUD ID" << "CORRECT" << std::endl;

    // Write each student's ID and correct count
    for (const auto& studentPtr : students) {
        if (studentPtr) { // Ensure the pointer is not null
            outputFile << std::left << std::setw(10) << studentPtr->studentID
                << studentPtr->correctCount << std::endl;
        }
    }

    outputFile.close();
    return true;
}

// Function to deallocate dynamically allocated memory for StudentQuizInfo objects
void cleanUp(std::vector<StudentQuizInfo*>& students) {
    for (StudentQuizInfo* studentPtr : students) {
        delete studentPtr; // Deallocate memory for each object
        studentPtr = nullptr; // Set pointer to nullptr to avoid dangling pointers
    }
    students.clear(); // Clear the vector itself
    std::cout << "Memory deallocated and vector cleared." << std::endl;
}