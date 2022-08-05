#include "list.h"

void push(Node **head, int x, int y)
{
    Node *tmp = (Node*) malloc(sizeof(Node));

    tmp->x = x;
    tmp->y = y;

    (*head) = tmp;
}
