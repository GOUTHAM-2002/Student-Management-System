#include <stdio.h>
#include "stdlib.h"

struct Student {
    char name[50];
    int rollNumber;
    int age;
    float marks;
};
void inputStudent(struct Student *student);
void displayStudent(struct Student student);
int sumOfAges(struct Student *students, int n);

void addStudent(struct Student **students,int *size,int  *capacity){
    if(*size==*capacity){
        *capacity*=2;
        struct Student *temp = realloc(*students,*capacity * sizeof(struct Student));
        if(temp==NULL){
            printf("Meomory Allocation");
            return;
        }
        *students = temp;
    }
    inputStudent(&(*students)[*size]);
    (*size)++;
}
struct Student *searchSudent(struct Student *students,int size,int rollNumber){
    for(int i=0;i<size;i++){
        if(students[i].rollNumber == rollNumber){
            return &students[i];
        }
    }
    return NULL;
}
int sumOfAges(struct Student *students,int n){
    if(n <= 0){
        return 0;
    }else {
        return students[n-1].age+ sumOfAges(students,n-1);
    }
}

void inputStudent(struct Student* student){
    printf("Enter student name");
    scanf("%s",student->name);
    printf("Enter roll number: ");
    scanf("%d",&student->rollNumber);
    printf("Enter age: ");
    scanf("%d",&student->age);
    printf("Enter marks");
    scanf("%f",&student->marks);

}
void displayStudent(struct Student student){
    printf("\nName: %s\n",student.name);
    printf("Roll Number: %d\n",student.rollNumber);
    printf("Age: %d\n",student.age);
    printf("Marks %.2f",student.marks);
}

int main(){
    int capacity = 5;
    struct Student *students = (struct Student *)malloc(capacity * sizeof (struct Student));
    int size=0;
    if(students==NULL){
        printf("Memory Allocation failed.\n");
        return 1;
    }
    int choice,roll;
    do{
        printf("\nStudent Management System\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Student By Roll Number\n");
        printf("4. Calculate Sum of All Ages\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent(&students, &size, &capacity);
                break;
            case 2:
                if (size == 0) {
                    printf("No records to display.\n");
                } else {
                    printf("\n--- All Student Records ---\n");
                    for (int i = 0; i < size; i++) {
                        displayStudent(students[i]);
                    }
                    printf("\n");
                }
                break;
            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &roll);
                struct Student *found = searchSudent(students, size, roll);
                if (found != NULL) {
                    displayStudent(*found);
                } else {
                    printf("Student with roll number %d not found.\n", roll);
                }
                break;
            case 4:
                printf("Sum of all students' ages: %d\n", sumOfAges(students, size));
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 5);
    free(students);
    return 0;
}