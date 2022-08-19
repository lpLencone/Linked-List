#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "list.c"
#include "helpers.c"

int main(void)
{
    srand(time(0));
    LIST *list = createList();

    char id[15];
    NODE *tmp;
    for (int i = 0; i < 10; i++)
    {
        randomString(id, 1);
        tmp = createNode(id);
        queueNode(list, tmp);
    }
    printList(list);

    LIST *sortedList = copyList(list);
    mergeSortList(sortedList, 0, sortedList->length);
    
    printf("\n\nSORTED:\n\n");

    printList(sortedList);

    printf("\n\nINSERTED:\n\n");


    for (int i = 0; i < 10; i++)
    {
        randomString(id, 1);
        tmp = createNode(id);
        insertSorted(sortedList, tmp);
    }
    printList(sortedList);


    randomString(id, 1);
    deleteNodeById(sortedList, id);
    deleteNodeAt(sortedList, 1);
    deleteNodeAt(sortedList, 2);

    printf("\n\nDELETED:\n\n");
    printList(sortedList);

    freeList(list);
    freeList(sortedList);

    return 0;
}