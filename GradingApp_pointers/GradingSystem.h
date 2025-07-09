/**
 * @file GradingSystem.h
 * @brief Header for the Grading System.
 *
 * Defines student data structure and declares all grading system functions.
 */

#ifndef GRADING_SYSTEM_H
#define GRADING_SYSTEM_H

#include <string>  // For std::string
#include <vector>  // For std::vector

 /**
  * @struct studentInfo
  * @brief Holds a single student's quiz data.
  *
  * Encapsulates ID, answers, score, percentage, and grade.
  */
struct studentInfo {
    int studentID;      ///< @brief Student ID.
    std::string answers; ///< @brief Student's 20 answers.
    int score;          ///< @brief Score out of 40.
    float percent;      ///< @brief Percentage score.
    char grade;         ///< @brief Assigned letter grade.
};

/**
 * @brief Checks if a string is purely numeric.
 * @param s The string to check.
 * @return True if numeric, false otherwise.
 */
bool isNumeric(const std::string& s);

/**
 * @brief Calculates student's score, percentage, and grade.
 * @param student Pointer to studentInfo to update.
 * @param correctAnswers String of correct answers.
 */
void calculateScoreAndGrade(studentInfo* student, const std::string& correctAnswers);

/**
 * @brief Logs an error message to the error file.
 * @param errorFileName Name of the error log file.
 * @param errorMessage The message to log.
 */
void writeErrorFile(const std::string& errorFileName, const std::string& errorMessage);

/**
 * @brief Reads student data, processes it, and populates student list.
 * @param studentFileName Input file name.
 * @param errorFileName Error log file name.
 * @param studentList Vector to store studentInfo pointers.
 * @return The correct answers string.
 */
std::string readStudentData(const std::string& studentFileName, const std::string& errorFileName, std::vector<studentInfo*>& studentList);

/**
 * @brief Formats and writes processed student data to a report file.
 * @param reportFileName Output report file name.
 * @param studentList Vector of studentInfo pointers.
 * @param correctAnswers String of correct answers for report context.
 */
void writeReportFile(const std::string& reportFileName, const std::vector<studentInfo*>& studentList, const std::string& correctAnswers);

/**
 * @brief Deletes dynamically allocated studentInfo objects to prevent memory leaks.
 * @param studentList Vector of studentInfo pointers to clean up.
 */
void cleanUpMemory(std::vector<studentInfo*>& studentList);

#endif // GRADING_SYSTEM_H