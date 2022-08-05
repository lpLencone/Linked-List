#include <stdlib.h>
#include "node.c"

typedef struct
{
    NODE *start;
    NODE *end;
    int length;
}
LIST;

/** Initializes a linked list
 * -------------------------
 * Arguments:
 * - void
 * 
 * Procedure:
 * - Allocates memory to a new linked list, and set its start and end to NULL
 * 
 * Return:
 * - LIST *: A pointer to the initialized list
 * */
LIST *createList(void)
{
    LIST *list = (LIST *)malloc(sizeof(LIST));
    list->start = NULL;
    list->end = NULL;
    list->length = 0;

    return list;
}

/** Append node to the end of the List
 * -----------------------
 * Arguments:
 * - list: LIST*: list to append the node to
 * - node: NODE*: node to append to the list
 * 
 * Procedure:
 * - Append the node to the end of the list
 * 
 * Return: void
 * */
void appendNode(LIST *list, NODE *node)
{
    if (list->start == NULL)
    {
        // set both start and end of list to Node node
        list->start = node;
        list->end = node;
    }
    else
    {
        // link the node and the last node of the list
        node->prev = list->end;
        list->end->next = node;
        // update the pointer to the end of the list
        list->end = node;
    }

    list->length++;    
}

/** Add node to the beginning of the List
 * Arguments:
 * - list: LIST*: list to queue the node in
 * - node: NODE*: node to queue in the list
 * 
 * Procedure:
 * - Link the node's next to the first element of the list,
 * - Link the first element's prev to the node,
 * - Update start position of the list.
 * 
 * Return:
 * - void
 * */
void queueNode(LIST *list, NODE *node)
{
    if (list->start == NULL)
    {
        // set both start and end of list to Node node
        list->start = node;
        list->end = node;
    }
    else
    {
        // link the node and the last element of the list
        node->next = list->start;
        list->start->prev = node;
        // update the pointer to the end of the list
        list->start = node;
    }
    list->length += 1;   
}

/** Add node to list maintaining its sorted status
 * Arguments:
 * - list: LIST*: list to add node to
 * - node: NODE*: node to add to the list
 * 
 * Procedure:
 * - Use a temporary NODE* variable to compare the node's id with the list's node's ids
 * - When node's id is finally greater ASCII-betically than current tmp's id, insert it next to tmp
 * - But if reached the end of the list, append node
 */
void insertSorted(LIST *list, NODE *node)
{
    if (list->length == 0)
    {
        appendNode(list, node);
        return;
    }

    NODE *tmp = list->start;
    while (tmp != NULL && strcmp(tmp->id, node->id) < 0)
    {
        tmp = tmp->next;
    }

    if (tmp == NULL)
    {
        appendNode(list, node);
        return;
    }
    
    if (tmp == list->start)
    {
        tmp->prev = node;
        node->next = tmp;
        list->start = node;
    }
    else
    {
        node->prev = tmp->prev;
        tmp->prev->next = node;
        tmp->prev = node;
        node->next = tmp;
    }

    list->length++;
}

/** Locate I'th element of the list
 * Arguments:
 * - list: LIST *: list to search the element about
 * - I: int: the position of the element to search about (0 -> length - 1)
 * 
 * Procedure:
 * - Iterate through the list up till the I, unless I is bigger than the list's length
 * 
 * Return:
 * NODE *: Node at the I'th element
 * */
NODE *locateNode(LIST *list, int at)
{
    int len = list->length;
    if (at >= len) return NULL;
    if (at == len - 1) return list->end;

    NODE *nptr = list->start;
    for (int i = 0; i < at; i++)
    {
        nptr = nptr->next;
    }
    return nptr;
}

/** Create a copy of a List
 * Argument:
 * - list: LIST*: list from which the copy will be originated
 * 
 * Procedure:
 * - Iterate through the list,
 * - Create identical nodes,
 * - Append the nodes to the copying list
 * 
 * Return:
 * - LIST *: A pointer to the copied list
 * */
LIST *copyList(LIST *list)
{
    LIST *copiedList = createList();
    if (list->length == 0) return copiedList;

    NODE *copiedNode, *nptr = list->start;

    while (nptr != NULL)
    {
        copiedNode = createNode(nptr->id);
        appendNode(copiedList, copiedNode);
        nptr = nptr->next;       
    }
    
    return copiedList;
}

/** Free the memory from all the nodes in the list
 * ----------------------------------------------
 * Arguments:
 * - head: LIST*: the list to free memory from
 * 
 * Procedure:
 * - Deletes each node of the list, one after another, till the end of the list.
 * 
 * Return:
 * - void 
 * */
void freeList(LIST *list)
{
    NODE *tmp, *ptr = list->start;
    
    while (ptr != NULL)
    {
        tmp = ptr->next;
        free(ptr->id);
        free(ptr);
        ptr = tmp;
    }

    free(list);
}

/** Print linked list
 * -----------------
 * Arguments:
 * - list: LIST*
 * 
 * Procedure:
 * - Iterate through the list and print the nodes' ids
 * 
 * Return:
 * - void
 * */
void printList(LIST *list)
{
    NODE *nptr = list->start;
    while (nptr != NULL)
    {
        printf("%s\n", nptr->id);
        nptr = nptr->next;
    }   
}

/** Merge two sorted sided of a linked list into a single sorted list
 * Arguments:
 * - lNode: NODE *: node at the start of the left side of the list
 * - rNode: NODE*: node at the start of the right side of the list
 * 
 * Procedure:
 * - Iterate through the elements starting from the beginning of both the left and right side simultaneously,
 * - Compare the two elements and put the 'smaller' into the the sorting list,
 * - Advance the index of the side from which the element now in the sorting list came from,
 * - Keep doing that until one of the sides exhaust,
 * - Finally append the rest of the elements from whichever side onto the end of the list
 * 
 * Return:
 * - void: merge happens inplace
 * */
void mergeList(LIST *list, int spos, int llen, int mpos, int rlen)
{
    LIST *mergedList = createList();
    NODE *lNode = locateNode(list, spos);
    NODE *rNode = locateNode(list, mpos);
    NODE *nIterator = lNode;

    int li = 0, ri = 0;
    while (li < llen && ri < rlen)
    {
        if (strcmp(lNode->id, rNode->id) < 0)
        {
            appendNode(mergedList, createNode(lNode->id));
            lNode = lNode->next;
            li++;
        }
        else
        {
            appendNode(mergedList, createNode(rNode->id));
            rNode = rNode->next;
            ri++;
        }
    }

    while (li < llen)
    {
        appendNode(mergedList, createNode(lNode->id));
        lNode = lNode->next;
        li++;
    }
    while(ri < rlen)
    {
        appendNode(mergedList, createNode(rNode->id));
        rNode = rNode->next;
        ri++;
    }

    NODE *mgdNode = mergedList->start;

    int len = llen + rlen;
    for (int i = 0; i < len; i++)
    {

        nIterator->id = mgdNode->id;
        
        mgdNode = mgdNode->next;
        nIterator = nIterator->next;
    }   
}

/** Merge sort the List
 * Arguments:
 * - list: LIST*: list to be sorted
 * - startPos: int: from where to start sorting
 * - length: int: the length to sort from the start position
 * 
 * Procedure:
 * - Sort recursively the left side of the list
 * - Sort recursively the right side of the list
 * - Merge the two sides into a sorted list
 * 
 * Return:
 * - void; the sorting happens inplace
 * */
void mergeSortList(LIST *list, int startPos, int length)
{
    if (length == 1) return;

    int leftHalfLength = length / 2;
    int rightHalfLength = length - leftHalfLength;

    int midPos = startPos + leftHalfLength;

    mergeSortList(list, startPos, leftHalfLength);
    mergeSortList(list, midPos, rightHalfLength);

    mergeList(list, startPos, leftHalfLength, midPos, rightHalfLength);
}
