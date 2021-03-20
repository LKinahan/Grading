////////////////////////////////////////////////////////////////////////////
// ELEX 4618 - Lab 2: Grading - CStudent.h file
// This file holds the data for one student in the class
// Created Jan 22, 2021 
// By Laurel Kinahan
////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
using namespace std;

// CStudent class stores variables for grades for one student
class CStudent
{
private:

public:
	// float to store final grade
	float final_grade;		
	// string to store student number 
	string student_number;
	// string to store lab grade
	string lab_grade;		
	// string to store quiz grade
	string quiz_grade;		
	// string to store midterm grade
	string midterm_grade;	
	// string to store final exam grade
	string final_exam_grade;
};
