#include <stdio.h>
#include "student_functions.h"


void addStudent() {

}

int getUserMenuChoice() {
    int menuChoice;
    printf("<==== Student Management System ====>\n1. Add Student\n2. View All Students\n3. Update Student GPA\n4. Delete Student\n5. Exit\nEnter your choice: ");
    scanf("%d", &menuChoice);

    return menuChoice;
}