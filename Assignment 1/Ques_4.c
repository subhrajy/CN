// Subhra

#include "stdio.h"
#include "stdlib.h"

struct stu_address{
    int street;
    char *state;
    char *city;
    char *country;
};

typedef struct stu_data{
    int stu_id;
    int stu_age;
    char *stu_name;
    struct stu_address stuAddress;
}stud;

int main(){
    stud stud;

    stud.stu_name = (char*) malloc(sizeof(char) * 10);
    stud.stuAddress.state = (char*) malloc(sizeof(char) * 10);
    stud.stuAddress.country = (char*) malloc(sizeof(char) * 10);
    stud.stuAddress.city = (char*) malloc(sizeof(char) * 10);

    printf("\nEnter student id: ");
    scanf("%d", &stud.stu_id);

    printf("\nEnter student age: ");
    scanf("%d", &stud.stu_age);

    printf("\nEnter student name: ");
    scanf("%s", stud.stu_name);

    printf("\nEnter address.");
    printf("\nEnter street number: ");
    scanf("%d", &stud.stuAddress.street);

    printf("\nEnter state: ");
    scanf("%s", stud.stuAddress.state);

    printf("\nEnter city: ");
    scanf("%s", stud.stuAddress.city);

    printf("\nEnter country: ");
    scanf("%s", stud.stuAddress.country);

    printf("\nDisplaying information: ");
    printf("\nStudent name: %s", stud.stu_name);
    printf("\nStudent id: %d", stud.stu_id);
    printf("\nStudent age: %d", stud.stu_age);

    printf("\nAddress: ");
    printf("\nStreet number: %d", stud.stuAddress.street);
    printf("\nState: %s", stud.stuAddress.state);
    printf("\nCity: %s", stud.stuAddress.city);
    printf("\nCountry: %s", stud.stuAddress.country);

    return 0;
}
