/ Program 5 – Grading Using Pointers
// Objective: Read student quiz data, calculate scores/grades, handle errors, output reports.

// 1. Define Data Structure:
STRUCT studentInfo
    INT studentID
    STRING answers
    INT score
    FLOAT percent
    CHAR grade
END STRUCT

// 2. Function: isNumeric(STRING s) -> BOOL
//    Purpose: Check if a given string contains only numeric digits.
//    Logic:
//      FOR each character in s
//          IF character is NOT a digit
//              RETURN FALSE
//      RETURN TRUE

// 3. Function: calculateScoreAndGrade(studentInfo* student, STRING correctAnswers)
//    Purpose: Calculate student's score, percentage, and assign a letter grade.
//    Logic:
//      score = 0
//      FOR i from 0 to 19 (for 20 questions)
//          IF student->answers[i] == correctAnswers[i]
//              score = score + 2 (Correct answer is 2 points)
//          ELSE IF student->answers[i] == ' ' (Blank answer)
//              score = score + 0 (Blank answer is 0 points)
//          ELSE
//              score = score + 1 (Incorrect answer is 1 point)
//      student->score = score
//      student->percent = (FLOAT)student->score / 40.0 * 100.0 (Quiz is 40 points total)
//      IF student->percent >= 90.0
//          student->grade = 'A'
//      ELSE IF student->percent >= 80.0
//          student->grade = 'B'
//      ELSE IF student->percent >= 70.0
//          student->grade = 'C'
//      ELSE IF student->percent >= 60.0
//          student->grade = 'D'
//      ELSE
//          student->grade = 'F'

// 4. Function: readStudentData(STRING studentFileName, STRING errorFileName, VECTOR<studentInfo*>* studentList) -> STRING correctAnswers
//    Purpose: Read student data from file, validate, calculate, and store.
//    Logic:
//      OPEN studentFileName for reading
//      IF file fails to open
//          PRINT error message and EXIT
//      OPEN errorFileName for writing
//      IF file fails to open
//          PRINT error message and EXIT
//      READ first line from studentFileName into correctAnswers STRING
//      LOOP while NOT end of studentFileName
//          READ next line from studentFileName as rawLine STRING
//          IF rawLine is empty, CONTINUE to next loop iteration
//          PARSE studentID_str from rawLine (before first space)
//          PARSE answers_str from rawLine (after first space)
//          IF isNumeric(studentID_str) is FALSE (or try-catch stoi fails)
//              WRITE "Error found in this line: " + rawLine to errorFileName
//              CONTINUE to next loop iteration (reject record)
//          CREATE new_student = new studentInfo
//          new_student->studentID = CONVERT studentID_str to INT
//          new_student->answers = answers_str
//          CALL calculateScoreAndGrade(new_student, correctAnswers)
//          ADD new_student to studentList (add pointer to vector)
//      CLOSE studentFileName
//      CLOSE errorFileName
//      RETURN correctAnswers (since it's needed by writeReportFile)

// 5. Function: writeReportFile(STRING reportFileName, VECTOR<studentInfo*>* studentList, STRING correctAnswers)
//    Purpose: Write processed student data to the report file.
//    Logic:
//      OPEN reportFileName for writing
//      IF file fails to open
//          PRINT error message and EXIT
//      WRITE Header to reportFileName: "STUD ID   STUDENT ANSWERS           SCORE/40           PERCENT         GRADE"
//      WRITE correctAnswers to reportFileName (optional, but good for context)
//      WRITE separator line
//      FOR each studentInfo* s_ptr in studentList
//          WRITE s_ptr->studentID to reportFileName
//          WRITE s_ptr->answers to reportFileName
//          WRITE s_ptr->score + "/40" to reportFileName
//          WRITE s_ptr->percent (formatted to 2 decimal places) to reportFileName
//          WRITE s_ptr->grade to reportFileName
//      CLOSE reportFileName

// 6. Function: cleanUpMemory(VECTOR<studentInfo*>* studentList)
//    Purpose: Delete dynamically allocated studentInfo objects to prevent memory leaks.
//    Logic:
//      FOR each studentInfo* s_ptr in studentList
//          DELETE s_ptr
//      CLEAR studentList

// 7. Main Program Flow (main function)
//    Logic:
//      DECLARE VECTOR<studentInfo*> studentRecords
//      DECLARE STRING correctAnswers
//      CALL readStudentData("student.txt", "error.txt", &studentRecords) to populate studentRecords and get correctAnswers
//      CALL writeReportFile("report.txt", &studentRecords, correctAnswers)
//      CALL cleanUpMemory(&studentRecords)
//      PRINT "Grading process complete. Check report.txt and error.txt."