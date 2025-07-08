#ifndef GRADING_SYSTEM_H
#define GRADING_SYSTEM_H

#include <string>
#include <vector>

struct studentInfo {
    int studentID;
    std::string answers;
    int score;
    float percent;
    char grade;
};

// Function prototypes
bool isNumeric(const std::string& s);
void calculateScoreAndGrade(studentInfo* student, const std::string& correctAnswers);
void writeErrorFile(const std::string& errorFileName, const std::string& errorMessage);
std::string readStudentData(const std::string& studentFileName, const std::string& errorFileName, std::vector<studentInfo*>& studentList);
void writeReportFile(const std::string& reportFileName, const std::vector<studentInfo*>& studentList, const std::string& correctAnswers);
void cleanUpMemory(std::vector<studentInfo*>& studentList);

#endif // GRADING_SYSTEM_H
