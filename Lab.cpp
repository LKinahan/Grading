////////////////////////////////////////////////////////////////////////////
// ELEX 4618 - Lab 2: Grading
// This program is an introductoory lab to C++ which is supposed to 
//    add, edit, print students to a grade sheet with error checking
// Created Jan 22, 2021 
// By Laurel Kinahan
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <regex>
#include "CCourse.h"
#include "CStudent.h"
using namespace std;

int main()
{
    CCourse classlist;

    while (1)
    {
        classlist.print_menu();
        string user_input;
        cout << "CMD> "; cin >> user_input;
        // if 'A' or 'a' selected then call function add_student
        if (user_input == "A" || user_input == "a")
            classlist.add_student();

        // if 'E' or 'e' selected then call function edit_student
        else if (user_input == "E" || user_input == "e")
            classlist.edit_student();

        // if 'P' or 'p' selected then call function print_grades
        else if (user_input == "P" || user_input == "p")
            classlist.print_grades();

        // if 'D' or 'd' selected then call function delete_student
        else if (user_input == "D" || user_input == "d")
            classlist.delete_student();

        // if 'S' or 's' selected then call function save_list
        else if (user_input == "S" || user_input == "s")
            classlist.save_list();

        // if 'L' or 'l' selected then call function load_list
        else if (user_input == "L" || user_input == "l")
            classlist.load_list();

        // if 'Q' or 'q' selected then exit program
        else if (user_input == "Q" || user_input == "q")
            break;

        // If incorrect selection, try again
        else
            cout << "ERROR! Invalid command, please try again..." << endl;
    }
    return 0;
}
