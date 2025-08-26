#include <stdio.h>
#include "student_functions.h"
#include <stdbool.h>

int main(void) {
    while (true) {
        int userMenuChoice = getUserMenuChoice();

        switch (userMenuChoice) {
            case 1: // add student to the struct array
                addStudent();
                break;
            case 2: // display all the students from the struct array
                displayStudents();
                break;
            case 3: // update a students gpa
                updateStudentGPA();
                break;
            case 4: // remove a student from the struct array
                break;
            case 5:
                printf("\nThank you for using the program!");
                return 0;
            default:
                printf("Invalid Choice! Please try again.\n\n");
                break;
        }
    }
}