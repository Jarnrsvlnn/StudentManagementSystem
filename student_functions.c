#include <stdio.h>
#include "student_functions.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
    int id;
}Student;

// declared globally so that all functions has access
Student * students = NULL;
int studentCount = 0;
FILE * filePointer;
int nextStudentID = 202400000;

int getUserMenuChoice() {
    int menuChoice;
    bool isValid = false;

    while (!isValid) {
        printf("\n<==== Student Management System ====>\n1. Add Student\n2. View All Students\n3. Update Student GPA\n4. Delete Student\n5. Save Changes\n6. Exit\nEnter your choice: ");

        if (scanf("%d", &menuChoice) == 1) { // if the user inputs a valid data type then scanf returns 1
            while (getchar() != '\n'); // flush newline
            if (menuChoice >= 1 && menuChoice <= 6) {
                isValid = true;
            }
            else {
                printf("\nInvalid Input! Please enter a number between 1 and 5.\n");
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
            (studentCount <= 0) ? printf("\nThere are no current students.\n") : deleteStudent();
            break;
        case 5: // save changes
            saveToFile();
            break;
        case 6:
            printf("\nThank you for using the program!");
            return 0;
        default:
            printf("Invalid Choice! Please try again.\n\n");
            break;
    }
    return 1;
}

void generateStudentID(Student * students) {
    students->id = nextStudentID++;
    nextStudentID++;
}

void addStudent() {
    bool isValid = false;
    char validChars[52] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    char buffer[100];
    char *endPtr;

    studentCount++;
    students = realloc(students, studentCount * sizeof(Student));
    generateStudentID(&students[studentCount - 1]);

    // NAME
    while (true) {
        printf("\nEnter student name: ");
        fgets(students[studentCount - 1].name, sizeof(students[studentCount - 1].name), stdin);
        students[studentCount - 1].name[strcspn(students[studentCount - 1].name, "\n")] = '\0';

        if (strspn(students[studentCount - 1].name, validChars) == strlen(students[studentCount - 1].name) &&
            strlen(students[studentCount - 1].name) > 0) {
            break; // valid
            }
        printf("\nInvalid Name! Try again.\n");
    }

    // AGE
    while (true) {
        printf("Enter student age: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        int tempAge = strtol(buffer, &endPtr, 10);

        if (*endPtr == '\0' && tempAge > 0 && tempAge <= 100) {
            students[studentCount - 1].age = tempAge;
            break;
        }
        printf("\nInvalid Age! Try again.\n");
    }

    // GPA
    while (true) {
        printf("Enter student gpa: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        float tempGPA = strtof(buffer, &endPtr);

        if (*endPtr == '\0' && tempGPA >= 1.00 && tempGPA <= 5.00) {
            students[studentCount - 1].gpa = tempGPA;
            break;
        }
        printf("\nInvalid GPA! Try again.\n");
    }

    printf("\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("\nThere are no current student.\n");
    }
    else {
        printf("\nList of all students:\n");

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

int deleteStudent() {
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
            return 1;
        }

        for (int i = studentIndex; i < studentCount - 1; i++) { // this will shift the student at index student[i] which starts at selected studentIndex to the left
            students[i] = students[i + 1]; // this will make it so that the student we want to delete is at the last index
        }

        studentCount--; // this reduces the size of the student struct array, and works because of the code in line 126
        students = realloc(students, studentCount * sizeof(Student));
        printf("\nStudent with the ID %d has been deleted!\n", studentToDelete);

    }
    return 1;
}

void saveToFile() {
    filePointer = fopen("student_records.txt", "w");

    if (filePointer == NULL) {
        printf("\nError saving file!\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(filePointer, "%s,%d,%d,%.2f\n", students[i].name, students[i].id, students[i].age, students[i].gpa);
    }

    fclose(filePointer);
    printf("\nFile saved successfully!\n");
}

void loadFromFile() {
    char studentLine[100];
    filePointer = fopen("student_records.txt", "r");

    if (filePointer == NULL) {
        printf("\nNo existing records found. Starting fresh.\n");
        return;
    }

    while (fgets(studentLine, sizeof(studentLine), filePointer) != NULL) {
        students = realloc(students, (studentCount + 1) * sizeof(Student));
        studentLine[strcspn(studentLine, "\n")] = '\0';

        char *token = strtok(studentLine, ",");
        if (!token) continue;  // skip malformed line
        strcpy(students[studentCount].name, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        students[studentCount].id = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        students[studentCount].age = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        students[studentCount].gpa = atof(token);

        if (students[studentCount].id >= nextStudentID) {
            nextStudentID = students[studentCount].id + 1;
        }

        studentCount++;
    }

    fclose(filePointer);
    printf("\nRecords loaded successfully!\n");
}