#include <stdio.h>
#include "student_functions.h"
#include <stdlib.h>

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
    printf("\n<==== Student Management System ====>\n1. Add Student\n2. View All Students\n3. Update Student GPA\n4. Delete Student\n5. Exit\nEnter your choice: ");
    scanf("%d", &menuChoice);

    return menuChoice;
}

void generateStudentID(Student * students) {
    static int studentID = 202400000;
    students->id = studentID;
    ++studentID;
}

void addStudent() {
    studentCount++;
    students = realloc(students, studentCount * sizeof(Student)); //
    generateStudentID(&students[studentCount - 1]);

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
        printf("Student %d: %s | Age: %d | GPA: %.2f | ID: %d\n", i + 1, students[i].name, students[i].age, students[i].gpa, students[i].id);
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
    scanf("%d", &studentID);

    for (int i = 0; i < studentCount; i++) {
        if (studentID == students[i].id) {
            selectedStudent = i;
            return selectedStudent;
        }
    }

    printf("Student not found!\n");
}

void updateStudentGPA() {
    int selectedStudent = selectStudentFromID();
    float newGPA;

    printf("Enter a new GPA: ");
    scanf("%f", &newGPA);
    students[selectedStudent].gpa = newGPA;

    printf("Student %s with the ID %d GPA has been changed to %.2f!\n", students[selectedStudent].name, students[selectedStudent].id, students[selectedStudent].gpa);
}

