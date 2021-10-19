// Subhra

#include "stdio.h"
#include "stdlib.h"

typedef struct record{
    char subject[10];
    int marks;
} record;

int main() {
    int i, n;
    record *records;

    printf("\nEnter number of records: ");
    scanf("%d", &n);

    records = (record*) malloc(n * sizeof(record));

    for (i = 0; i < n; i++){
        printf("\nEnter subject and marks respectively-\n");
        scanf("%s", (records+i)->subject);
        scanf("%d", &(records+i)->marks);
    }

    printf("\nDisplaying information:");
    for (i = 0; i < n; i++)
        printf("\n%s\t\t%d", (records+i)->subject, (records+i)->marks);

    return 0;
}
