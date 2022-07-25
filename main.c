#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "list.c"
#include "helpers.c"

int main(void)
{
    srand(time(0));
    struct List *list = createList();

    char id[15];
    struct Node *tmp;
    for (int i = 0; i < 100; i++)
    {
        randomString(id, 5);
        tmp = createNode(id);
        queueNode(list, tmp);
    }
    printList(list);

    struct List *sortedList = copyList(list);
    mergeSortList(sortedList, 0, sortedList->length);
    
    printf("\n\nSORTED:\n\n");

    printList(sortedList);

    freeList(list);
    freeList(sortedList);

    return 0;
}