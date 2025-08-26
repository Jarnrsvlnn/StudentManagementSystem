#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_functions.h"
#include <stdbool.h>

typedef struct {
    char name[20];
    int age;
    float gpa;
    int id;
}Student;

int main(void) {
    while (true) {
        int userMenuChoice = getUserMenuChoice();

        switch (userMenuChoice) {
            case 1:
                addStudent();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("\nThank you for using the program!");
                return 0;
            default:
                printf("Invalid Choice! Please try again.\n\n");
                break;
        }
    }
    return 0;
}