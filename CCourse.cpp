////////////////////////////////////////////////////////////////////////////
// ELEX 4618 - Lab 2: Grading - CCourse.cpp file
// This file 
// Created Jan 22, 2021 
// By Laurel Kinahan
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <regex>
#include <fstream>
#include <iomanip>
#include "CCourse.h"
#include "CStudent.h"
using namespace std;

CStudent temp_student;

/////////////////////////////////////////////////////////////////////////////
//		PRINT_MENU FUNCTION
/////////////////////////////////////////////////////////////////////////////
void CCourse::print_menu(void)
{
    cout << "\n****************************************" << endl;
    cout << "\nELEX4618 Grade system, by Laurel Kinahan" << endl;
    cout << "\n****************************************" << endl;
    cout << "(A) Add student" << endl;
    cout << "(E) Edit student" << endl;
    cout << "(P) Print grades" << endl;
    cout << "(D) Delete student" << endl;
    cout << "(S) Save class" << endl;
    cout << "(L) Load class" << endl;
    cout << "(Q) Quit\n" << endl;
}

/////////////////////////////////////////////////////////////////////////////
//		ADD_STUDENT FUNCTION
/////////////////////////////////////////////////////////////////////////////
void CCourse::add_student(void)
{
    input_grades();
    students.push_back(temp_student);
}

// Student numbers must be entered as A0+0/1+6other numbers less than 10
regex check_student_number("[A][0][01][01][0-9][0-9][0-9][0-9][0-9]"); // help from (https://stackoverflow.com/questions/11185261/checking-strings-with-regex-in-c)
// Grades must exist before they are edited or deleted
// Grades must be entered as positive whole numbers
regex check_grade("((\\+)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?"); // help from (https://stackoverflow.com/questions/33520934/regex-with-only-numbers-in-a-string-c)
// Student edits and deletes must be confirmed
regex check_command("[[:digit:]]"); // help from (https://stackoverflow.com/questions/33520934/regex-with-only-numbers-in-a-string-c)

/////////////////////////////////////////////////////////////////////////////
//		EDIT_STUDENT FUNCTION
/////////////////////////////////////////////////////////////////////////////
void CCourse::edit_student(void)
{
    // If no student in list there is no student to edit. Return to main menu
    if (students.size() == 0)
        cout << "\t\tERROR!!\nNo students registered to be edited, please make another selection" << endl;
    else
    {
        cout << "Student to edit: ";
        string s_edit_student;
        int edit_student = 0;
        // User inputs number of student to be edited
        cin >> s_edit_student; 
        // Check if student number is in list
        if (regex_match(s_edit_student, check_command))
            edit_student = stoi(s_edit_student);
        // Compare integer to see if it is a positive number less than the size of the vector
        // Fill existing student grades with edited grades using same function as to add a student
        if ((edit_student > 0) && (edit_student <= students.size()))
        {
            input_grades();
            students[edit_student - 1] = temp_student;
            cout << "Student edited!" << endl;
        }
        else
            cout << "\tERROR!!\nThat student is not in list. Returning to main menu" << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////
//		PRINT_GRADES FUNCTION
/////////////////////////////////////////////////////////////////////////////
void CCourse::print_grades(void)
{
    float grade_int = 0;

    cout << "\n#\tStudent\t\tLab\tQuiz\tMidterm\t\tFinal Exam\tFinal Grade" << endl;
    for (int student_count = 0; student_count < students.size(); student_count += 1) 
    {
        cout << student_count + 1; // + 1 to correct for offset
        cout << "\t" << students[student_count].student_number;
        grade_int = stof(students[student_count].lab_grade);
        cout << "\t" << grade_int;
        grade_int = stof(students[student_count].quiz_grade);
        cout << "\t" << grade_int;
        grade_int = stof(students[student_count].midterm_grade);
        cout << "\t" << grade_int;
        grade_int = stof(students[student_count].final_exam_grade);
        cout << "\t\t" << grade_int;
        cout << "\t\t" << students[student_count].final_grade << endl;
    }
}


/////////////////////////////////////////////////////////////////////////////
//		DELETE_STUDENT FUNCTION
/////////////////////////////////////////////////////////////////////////////
void CCourse::delete_student(void)
{
    // If no student in list there is no student to delete. Return to main menu
    if (students.size() == 0)
        cout << "No students registered to be deleted, please make another selection" << endl;
    else
    {
        cout << "Student to delete: " << endl;
        string s_delete_student;
        int delete_student = 0;
        // User inputs number of student to be deleted
        cin >> s_delete_student; 
        // Check if number is in list
        if (regex_match(s_delete_student, check_command))
            // Convert string to integer
            delete_student = std::stoi(s_delete_student); 
        // Compare integer to see if it is a positive number less than the size of the vector
        if ((delete_student > 0) && (delete_student <= students.size()))
        {
            students.erase(students.begin() + (delete_student - 1));
            cout << "\nStudent deleted" << endl;
        }
        else
            cout << "\tERROR!!\nThat student does not exist. Returning to main menu" << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////
//		INPUT_GRADES FUNCTION
/////////////////////////////////////////////////////////////////////////////
void CCourse::input_grades(void)
{
    float grade_int = 0;
    temp_student.final_grade = 0;

    while (1)
    {
        cout << "Student Number: "; cin >> temp_student.student_number;
        // Student numbers must be entered as A0+0/1+6other numbers less than 10
        // Check input for validity
        if (regex_match(temp_student.student_number, check_student_number))
            break;
        else
            cout << "\n\tERROR!\nInvalid input, Student Number must be entered as 'A001#####' or 'A010#####' please try again\n" << endl;
    }

    while (1)
    {
        cout << "Lab Grade: "; cin >> temp_student.lab_grade;
        // Grades must be entered as a positive integer with one decimal
        // Check input for validity
        if (regex_match(temp_student.lab_grade, check_grade))
        {
            // Convert string to float
            grade_int = stof(temp_student.lab_grade);
            // Verify float is a whole number between 0 and 100
            if (grade_int >= 0.0 && grade_int <= 100.0)
                break; // Exit loop
            else
                cout << "\n\tERROR!\nInvalid input, Grade must be entered as a positive number, please try again\n" << endl;
        }
        else
            cout << "\n\tERROR!\nInvalid input, Grade must be entered as a positive number, please try again\n" << endl;
    }
    temp_student.final_grade += 0.4 * grade_int;

    while (1)
    {
        cout << "Quiz Grade: "; cin >> temp_student.quiz_grade;
        // Grades must be entered as a positive integer with one decimal
        // Check input for validity
        if (regex_match(temp_student.quiz_grade, check_grade))
        {
            // Convert string to float
            grade_int = stof(temp_student.quiz_grade);
            // Verify float is a whole number between 0 and 100
            if (grade_int >= 0.0 && grade_int <= 100.0)
                break;
            else
                cout << "\n\tERROR!\nInvalid input, Grade must be entered as a positive number, please try again\n" << endl;
        }
        else
            cout << "\n\tERROR!\nInvalid input, Grade must be entered as a positive number, please try again\n" << endl;
    }
    temp_student.final_grade += 0.1 * grade_int;

    while (1)
    {
        cout << "Midterm Grade: "; cin >> temp_student.midterm_grade;
        // Grades must be entered as a positive integer with one decimal
        // Check input for validity
        if (regex_match(temp_student.midterm_grade, check_grade))
        {
            // Convert string to float
            grade_int = stof(temp_student.midterm_grade);
            // Verify float is a whole number between 0 and 100
            if (grade_int >= 0.0 && grade_int <= 100.0)
                break;
            else
                cout << "\n\tERROR!\nInvalid input, Grade must be entered as a positive number, please try again\n" << endl;
        }
        else
            cout << "\n\tERROR!\nInvalid input, Grade must be entered as a positive number, please try again\n" << endl;
    }
    temp_student.final_grade += 0.2 * grade_int;

    while (1)
    {
        cout << "Final Exam Grade: "; cin >> temp_student.final_exam_grade;
        // Grades must be entered as a positive integer with one decimal
        // Check input for validity
        if (regex_match(temp_student.final_exam_grade, check_grade))
        {
            // Convert string to float
            grade_int = stof(temp_student.final_exam_grade);
            // Verify float is a whole number between 0 and 100
            if (grade_int >= 0.0 && grade_int <= 100.0)
                break;
            else
                cout << "\n\tERROR!\nInvalid input, Grade must be entered as a positive number, please try again\n" << endl;
        }
        else
            cout << "\n\tERROR!\nInvalid input, Grade must be entered as a positive number, please try again\n" << endl;
    }
    temp_student.final_grade += 0.3 * grade_int;
}

/////////////////////////////////////////////////////////////////////////////
//		SAVE_LIST FUNCTION
/////////////////////////////////////////////////////////////////////////////
void CCourse::save_list(void)
{
    if (students.size() == 0)
        cout << "\tNo students available to be saved!\nPlease try again" << endl;
    else
    {
        string file_name;
        cout << "Enter file name: "; cin >> file_name;
        ofstream outfile;
        outfile.open(file_name, ios::out | ios::trunc);

        if (outfile.is_open())
        {
            for (int student_counter = 0; student_counter < students.size(); student_counter += 1) // Increment through every student to save grades
            {
                outfile << students[student_counter].student_number << " " << students[student_counter].lab_grade << " " << students[student_counter].quiz_grade << " " << students[student_counter].midterm_grade << " " << students[student_counter].final_exam_grade << " " << students[student_counter].final_grade << std::endl;
            }
            outfile.close();
            cout << "\nFile saved!" << endl;
        }
        else
            cout << "\tERROR!\nFile did not save properly! Please try again" << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////
//		LOAD_LIST FUNCTION
/////////////////////////////////////////////////////////////////////////////
void CCourse::load_list(void)
{
    string file_name;
    cout << "Enter file name: ";
    cin >> file_name;
    ifstream infile;
    infile.open(file_name);

    if (infile.is_open())
    {
        students.clear();
        while (infile >> temp_student.student_number >> temp_student.lab_grade >> temp_student.quiz_grade >> temp_student.midterm_grade >> temp_student.final_exam_grade >> temp_student.final_grade)
            students.push_back(temp_student);
        infile.close();
        cout << "\nFile loaded" << endl;
    }
    else
        cout << "\n\tERROR!!\nFile failed to load or file does not exist!" << endl;
}

