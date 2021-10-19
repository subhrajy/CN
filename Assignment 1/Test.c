#include<stdio.h>
#include<stdlib.h>
struct stu_add
{
    char *city;
};
struct std_data
{
    char *name;
    struct stu_add addr;
};

int main(void)
{
    struct std_data *ptr;
    ptr = (struct std_data*) malloc(sizeof(struct std_data) * 2);

    int i;

    for(i=0;i<2;i++)
    {
        (ptr+i)->addr.city=malloc(sizeof(char)*12);
        (ptr+i)->name=(char*) malloc(sizeof(char)*12);
        printf("Enter name: ");
        scanf("%s",(ptr+i)->name);
        printf("Enter addr:");
        scanf("%s",(ptr+i)->addr.city);
    }

    printf("Print details\n");
        for(i=0;i<2;i++)
    {
        printf("Name: %s\n",(ptr+i)->name);
        printf("Addr: %s\n",(ptr+i)->addr.city);
    }
}
