// Subhra

#include "stdio.h"
#include "stdlib.h"


typedef struct student{
    char *name;
    int roll;
}stud;


struct student input(){
    stud data;

    data.name = (char*) malloc(sizeof(char) * 10);

    printf("\nEnter name: ");
    scanf("%s", data.name);

    printf("\nEnter roll: ");
    scanf("%d", &data.roll);

    return data;
}


void displayInfo(stud stu){
    printf("\nName: %s", stu.name);
    printf("\nRoll: %d", stu.roll);
}


int main(){
    displayInfo(input());
}
