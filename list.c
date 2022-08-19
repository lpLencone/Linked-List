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
        // link the new node and the last node of the list
        node->prev = list->end;
        list->end->next = node;
        // update the pointer to the end of the list
        list->end = node;
    }

    list->length++;    
}

/** Add node to the beginning of the List
 * Arguments:
 * - list: LIST*: list to enqueue the node in
 * - node: NODE*: node to enqueue in the list
 * 
 * Procedure:
 * - Link the node's next to the first element of the list,
 * - Link the first element's prev to the node,
 * - Update start position of the list.
 * */
void enqueueNode(LIST *list, NODE *node)
{
    if (list->start == NULL)
    {
        // set both start and end of list to new node
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
    list->length++;   
}

/** Add node to list maintaining its sorted status
 * Arguments:
 * - list: LIST*: list to add node to
 * - node: NODE*: node to add to the list
 * 
 * Procedure:
 * - Use a temporary NODE* variable to compare the node's id with the list's node's ids
 * - When node's id comes ASCII-betically before the current tmp's id, insert the new node before tmp
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
        // node's id comes ASCIIbetically after all the other nodes in the list
        appendNode(list, node);
        return;
    }
    
    if (tmp == list->start)
    {
        // node's id comes ASCIIbetically before all the other nodes in the list
        enqueueNode(list, node);
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
NODE *locateNodeAt(LIST *list, int at)
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

/** Locates a node in a list given an id
 * Arguments:
 * - list: LIST*: list to locate the node in
 * - id: char*: id of the sought after node
 * 
 * Procedure:
 * - iterates through the list using a temporary NODE* variable
 * - returns the node if it's found, returns NULL otherwise
 * */
NODE *locateNodeById(LIST *list, char *id)
{
    if (list->length == 0)
    {
        // SIGERR
        return NULL;
    }

    NODE *tmp = list->start;
    while (tmp != NULL && strcmp(tmp->id, id) != 0)
    {
        tmp = tmp->next;
    }

    // Will return NULL if no node with such id exists
    return tmp;
}

/** Delete I'th element of the list, and free the memory associated with it
 * Arguments:
 * - list: LIST*: list to delete the item from
 * - at: int: position of the node
 * 
 * Procedure:
 * - Uses the locateNodeAt function to find the node, then connect the other nodes it's linked to
 * and finally frees its memory.
 * */
void deleteNodeAt(LIST *list, int at)
{
    NODE *popNode = locateNodeAt(list, at);

    if (popNode == NULL)
    {
        // SIGERR
        return;
    }

    if (popNode == list->start)
    {
        list->start = popNode->next;
    }

    deleteNode(popNode);
    list->length--;
}

/** Deletes a node from a list, given it's id
 * Arguments:
 * - list: LIST*: list to delete the node from
 * - id: char*: id of target node
 * 
 * Procedure:
 * - uses the locateNodeById function to locate the node
 * - uses the deleteNode function to delete the node correctly
 * */
void deleteNodeById(LIST *list, char *id)
{
    NODE *nptr = locateNodeById(list, id);

    if (nptr == NULL)
    {
        // SIGERR
        return;
    }

    if (nptr == list->start)
    {
        list->start = nptr->next;
    }

    deleteNode(nptr);
    list->length--;
}

/** Remove node from the beginning of the List
 * Arguments:
 * - list: LIST*: list to dequeue the node from
 * 
 * Procedure:
 * - Use deleteNodeAt(list, 0) to delete the first element;
 * */
void dequeueNode(LIST *list)
{
    deleteNodeAt(list, 0);
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

    NODE *copiedNode, *tmp = list->start;

    while (tmp != NULL)
    {
        copiedNode = createNode(tmp->id);
        appendNode(copiedList, copiedNode);
        tmp = tmp->next;       
    }
    copiedList->length = list->length;
    
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
    printf("List length: %i\n", list->length);
    NODE *nptr = list->start;
    int i = 0;
    while (nptr != NULL)
    {
        printf("%i | %s\n", i, nptr->id);
        nptr = nptr->next;
        i++;
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
    NODE *lNode = locateNodeAt(list, spos);
    NODE *rNode = locateNodeAt(list, mpos);
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
