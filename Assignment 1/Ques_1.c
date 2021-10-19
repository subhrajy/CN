// Subhra

#include "stdio.h"

typedef struct student{
    char name[20];
    int roll_number;
    float marks;
} stud;

int main() {
    stud s1;

    printf("Enter information: \n");
    printf("Enter name: ");
    scanf("%[^\n]", s1.name);

    printf("Enter roll number: ");
    scanf("%d", &s1.roll_number);

    printf("Enter marks: ");
    scanf("%f", &s1.marks);

    printf("\nDisplaying information: \n");
    printf("name: %s\n", s1.name);
    printf("roll number: %d\n", s1.roll_number);
    printf("marks: %f\n", s1.marks);

    return 0;
}
