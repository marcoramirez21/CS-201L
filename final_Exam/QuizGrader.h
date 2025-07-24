#ifndef QUIZ_GRADER_H
#define QUIZ_GRADER_H

#include <string>
#include <vector>

// Structure to hold information for each student's quiz results
struct StudentQuizInfo {
    int studentID;      // Unique identifier for the student
    std::string studentAnswers; // Student's answers to the quiz
    int correctCount;   // Number of correct answers for the student

    // Default constructor
    StudentQuizInfo() : studentID(0), studentAnswers(""), correctCount(0) {}

    // Parameterized constructor
    StudentQuizInfo(int id, const std::string& answers)
        : studentID(id), studentAnswers(answers), correctCount(0) {
    }
};

// Function to read quiz data from the input file
// Parameters:
//   filename: The name of the input file (e.g., "quiz_data.txt")
//   correctAnswers: Reference to a string to store the correct answers (output)
//   students: Reference to a vector of StudentQuizInfo pointers (output)
// Returns: True if file reading is successful, false otherwise.
bool readQuizData(const std::string& filename, std::string& correctAnswers,
    std::vector<StudentQuizInfo*>& students);

// Function to calculate the number of correct answers for a single student
// Parameters:
//   correctAnswers: The string containing the correct answers
//   studentPtr: Pointer to a StudentQuizInfo object whose score needs to be calculated
void calculateScores(const std::string& correctAnswers, StudentQuizInfo* studentPtr);

// Function to write the quiz results to the output file
// Parameters:
//   filename: The name of the output file (e.g., "quiz_results.txt")
//   students: Constant reference to a vector of StudentQuizInfo pointers (input)
// Returns: True if file writing is successful, false otherwise.
bool writeResults(const std::string& filename, const std::vector<StudentQuizInfo*>& students);

// Function to deallocate dynamically allocated memory for StudentQuizInfo objects
// Parameters:
//   students: Reference to a vector of StudentQuizInfo pointers (modified to clear)
void cleanUp(std::vector<StudentQuizInfo*>& students);

#endif // QUIZ_GRADER_H