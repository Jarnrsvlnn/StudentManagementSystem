#include <stdio.h>
#include "student_functions.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char name[20];
    int age;
    float gpa;
    int id;
}Student;

// declared globally so that all functions has access
Student * students = NULL;
int studentCount = 0;

int getUserMenuChoice() {
    int menuChoice;
    bool isValid = false;

    while (!isValid) {
        printf("\n<==== Student Management System ====>\n1. Add Student\n2. View All Students\n3. Update Student GPA\n4. Delete Student\n5. Exit\nEnter your choice: ");

        if (scanf("%d", &menuChoice) == 1) { // if the user inputs a valid data type then scanf returns 1
            if (menuChoice >= 1 && menuChoice <= 5) {
                isValid = true;
            }
            else {
                printf("Invalid Input! Please enter a number between 1 and 5.");
            }
        }
        else {
            printf("\nInvalid Input! Please enter a number.\n");
            while (getchar() != '\n'); // discards the leftover string from the scanf
        }
    }

    return menuChoice;
}

int menuInterface(int menuChoice) {
    switch (menuChoice) {
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
            deleteStudent();
            break;
        case 5:
            printf("\nThank you for using the program!");
            return 0;
        default:
            printf("Invalid Choice! Please try again.\n\n");
            break;
    }
}

void generateStudentID(Student * students) {
    static int studentID = 202400000;
    students->id = studentID;
    ++studentID;
}

void addStudent() {
    bool isValid = false;
    studentCount++;
    students = realloc(students, studentCount * sizeof(Student)); //
    generateStudentID(&students[studentCount - 1]);

    while (!isValid) {
        printf("Enter student name: ");
        scanf("%s", students[studentCount - 1].name);

        isValid = true;
        // checks if the entered name is all leters
        for (int i = 0; i < strlen(students[studentCount - 1].name); ++i) {
            if (!isalpha(students[studentCount - 1].name[i])) {
                printf("Invalid Name! Enter letters only.\n");
                isValid = false;
                break;
            }
        }

        if (!isValid) {
            continue;
        }

        printf("Enter student age: ");
        if (scanf("%d", &students[studentCount - 1].age) == 0 || students[studentCount - 1].age <= 0) {
            printf("\nInvalid Input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Enter student gpa: ");
        if (scanf("%f", &students[studentCount - 1].gpa) == 0 || students[studentCount - 1].gpa < 1.00 || students[studentCount - 1].gpa > 5.00) {
            printf("\nInvalid Input! Please enter a valid GPA.\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    printf("\n");
}

void displayStudents() {
    printf("\nList of all students:\n");

    if (studentCount == 0) {
        printf("There are no current student.\n");
    }
    else {
        for (int i = 0; i < studentCount; i++) {
            printf("Student %d: %s | Age: %d | GPA: %.2f | ID: %d\n", i + 1, students[i].name, students[i].age, students[i].gpa, students[i].id);
        }
    }
}

int selectStudentFromID() { // gets the student number for updateStudentGPA() to use
    int studentID;
    int selectedStudent;

    printf("Select a student:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Student %d: %s | Age: %d | GPA: %.2f | ID: %d\n", i + 1, students[i].name, students[i].age, students[i].gpa, students[i].id);
    }
    printf("Enter student ID: ");
    if (scanf("%d", &studentID) == 0) {
        while (getchar() != '\n');
        return 1;
    }
    for (int i = 0; i < studentCount; i++) {
        if (studentID == students[i].id) {
            selectedStudent = i;
            return selectedStudent;
        }
    }
    return 1;
}

void updateStudentGPA() {
    int selectedStudent = selectStudentFromID();

    if (selectedStudent == 1) {
        printf("\nInvalid Input! Please enter a valid ID.\n");
    }
    else {
        float newGPA;

        printf("Enter a new GPA: ");
        scanf("%f", &newGPA);
        students[selectedStudent].gpa = newGPA;
        printf("Student %s with the ID %d GPA has been changed to %.2f!\n", students[selectedStudent].name, students[selectedStudent].id, students[selectedStudent].gpa);
    }

}

void deleteStudent() {
    int studentToDelete;
    int studentIndex = -1;

    printf("\nEnter the ID of the student: ");

    if (scanf("%d", &studentToDelete) == 0) {
        printf("\nPlease enter a valid student ID.\n");
        while (getchar() != '\n');
    }
    else {
        for (int i = 0; i < studentCount; i++) {
            if (studentToDelete == students[i].id) {
                studentIndex = i;
            }
        }

        if (studentIndex == -1) {
            printf("Student not found!\n");
        }

        for (int i = studentIndex; i < studentCount - 1; i++) { // this will shift the student at index student[i] which starts at selected studentIndex to the left
            students[i] = students[i + 1]; // this will make it so that the student we want to delete is at the last index
        }

        studentCount--; // this reduces the size of the student struct array, and works because of the code in line 126
        students = realloc(students, studentCount * sizeof(Student));
        printf("\nStudent with the ID %d has been deleted!\n", studentToDelete);
    }
}

