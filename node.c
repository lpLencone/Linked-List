#include <stdlib.h>

typedef struct Node
{
    struct Node *prev;
    struct Node *next;
    char *id;
}
NODE;

/** Create node with provided id
 * ---------------------------------
 * Arguments:
 * - id: char*: the id to assign to the node
 * 
 * Procedure:
 * - Dynamically alocate memory to a new Node,
 * - Dynamically alocate memory to the Node's id, given the id argument,
 * - Use cpystr to copy the id arg into the Node's id,
 * - It also sets the pointer to the previous and next Node to NULL.
 * 
 * Return:
 * - struct Node *: A pointer to the created node.
 * */
NODE *createNode(char *id)
{
    NODE *n = (NODE *)malloc(sizeof(NODE));
    n->prev = NULL;
    n->next = NULL;

    int len = strlen(id);
    n->id = (char *)malloc(len + 1);
    strcpy(n->id, id);

    return n;
}

/** Deletes a node regardless of the list it's in
 * Arguments:
 * - node: NODE*: node to be deleted from the list
 * 
 * Procedure:
 * - link the node's previous and next node pointers, if they exist, then free the memory of its id and itself
 * */
void deleteNode(NODE *node)
{
    // Connect previous node to the next node
    if (node->prev != NULL)
    {
        node->prev->next = node->next;
    }

    // Connect next node to the previous one
    if (node->next != NULL)
    {
        node->next->prev = node->prev;
    }

    free(node->id);
    free(node);
}
