// Subhra

#include "stdio.h"
#include "stdlib.h"


typedef struct student{
    int age;
    char *name;
}stu;


void dispayInfo(stu stud){
    printf("\nName: %s", stud.name);
    printf("\nAge: %d", stud.age);
    printf("\n");
}


int main(){
    stu data;

    data.name = (char*) malloc(sizeof(char) * 10);

    printf("\nEnter name: ");
    scanf("%s", data.name);

    printf("\nEnter age: ");
    scanf("%d", &data.age);

    dispayInfo(data);

    return 0;
}
