#include <stdio.h>
#include <stdlib.h>
#include "polygon_traversal_direction.h"

int main()
{
    int nodes, i;
    printf("Enter amount nodes of polygon: ");
    scanf("%d", &nodes);

    float *x_nodes = (float *) malloc(nodes * sizeof(float));
    float *y_nodes = (float *) malloc(nodes * sizeof(float));

    for (i = 0; i < nodes; i++)
    {
        printf("Enter node #%d coordinates:\nX = ", (i + 1));
        scanf("%f", &x_nodes[i]);
        printf("Y = ");
        scanf("%f", &y_nodes[i]);
    }

    printf("Nodes:\n");
    for (i = 0; i < nodes; i++)
    {
        printf("X = %f; Y = %f;\n", x_nodes[i], y_nodes[i]);
    }

    // получить реузультат
    int result = get_traversal_direction(x_nodes, y_nodes, nodes);
    result == -1 
        ? printf("Result = %d; (anti-clockwise)\n", result) 
        : printf("Result = %d; (clockwise)\n", result);
    
    // чистим память
    free(x_nodes);
    free(y_nodes);

    return 0;
}
