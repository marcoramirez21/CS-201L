#include <iostream>
#include <vector>
#include <string>
#include "QuizGrader.h" // Now includes both StudentQuizInfo and the function declarations

int main() {
    std::string correctAnswers;
    std::vector<StudentQuizInfo*> students; // Vector to hold pointers to student data

    const std::string inputFileName = "quiz_data.txt";
    const std::string outputFileName = "quiz_results.txt";

    // Step 1: Read quiz data from the input file
    if (!readQuizData(inputFileName, correctAnswers, students)) {
        // Error already reported by readQuizData
        cleanUp(students); // Clean up any potentially allocated memory before exiting
        return 1; // Indicate an error
    }

    // Step 2: Calculate scores for each student
    for (StudentQuizInfo* studentPtr : students) {
        calculateScores(correctAnswers, studentPtr);
    }

    // Step 3: Write results to the output file
    if (!writeResults(outputFileName, students)) {
        // Error already reported by writeResults
        cleanUp(students); // Clean up allocated memory before exiting
        return 1; // Indicate an error
    }

    std::cout << "Quiz grading complete. Results written to " << outputFileName << std::endl;

    // Step 4: Clean up dynamically allocated memory
    cleanUp(students);

    return 0; // Indicate successful execution
}