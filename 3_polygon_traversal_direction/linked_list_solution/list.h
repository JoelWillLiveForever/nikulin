// определяем данные, которые будут храниться в самом узле списка
typedef struct Node
{
    int x;
    int y;
    struct Node *next;
} Node;

// определяем сам список
typedef Node *List;

//void push(Node **head, int x, int y);
