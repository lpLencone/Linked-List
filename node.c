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
struct Node *createNode(char *id)
{
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->prev = NULL;
    n->next = NULL;

    int len = strlen(id);
    n->id = (char *)malloc(len + 1);
    strcpy(n->id, id);

    return n;
}

