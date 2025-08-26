#include <stdio.h>
#include "student_functions.h"
#include <stdlib.h>

typedef struct {
    char name[20];
    int age;
    float gpa;
}Student;

// declared globally so that all functions has access
Student * students = NULL;
int studentCount = 0;

int getUserMenuChoice() {
    int menuChoice;
    printf("\n<==== Student Management System ====>\n1. Add Student\n2. View All Students\n3. Update Student GPA\n4. Delete Student\n5. Exit\nEnter your choice: ");
    scanf("%d", &menuChoice);

    return menuChoice;
}

void addStudent() {
    studentCount++;
    students = realloc(students, studentCount * sizeof(Student)); //

    printf("Enter student name: ");
    scanf("%s", students[studentCount - 1].name);
    printf("Enter student age: ");
    scanf("%d", &students[studentCount - 1].age);
    printf("Enter student gpa: ");
    scanf("%f", &students[studentCount - 1].gpa);
    printf("\n");
}

void displayStudents() {
    printf("\nList of all students:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Student %d: %s | Age: %d | GPA: %.2f\n", i + 1, students[i].name, students[i].age, students[i].gpa);
    }
}

int selectStudentNumber() { // gets the student number for updateStudentGPA() to use
    int userChoice;
    printf("Select a student:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Student %d: %s | Age: %d | GPA: %.2f\n", i + 1, students[i].name, students[i].age, students[i].gpa);
    }
    printf("Enter student number: ");
    scanf("%d", &userChoice);

    return userChoice;
}

void updateStudentGPA() {
    int userChoice = selectStudentNumber();
    float newGPA;

    printf("Enter a new GPA: ");
    scanf("%f", &newGPA);
    students[userChoice - 1].gpa = newGPA;

    printf("Student %s GPA has been changed to %.2f!\n", students[userChoice - 1].name, newGPA);
}

