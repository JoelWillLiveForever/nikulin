/* Условие задачи 3:
 * Выпуклый многоугольник задаётся координатами вершин при обходе по часовой или против часовой стрелки.
 * Контур многоугольника не имеет самопересечений.
 * Определить направление обхода.
 * Выполнить то же самое, но только в случае невыпуклого многоугольника. */

#include "foo.h"

#define EXIT_NODES_READ_FAILED 2
#define EXIT_NODE_X_READ_FAILED 3
#define EXIT_NODE_Y_READ_FAILED 4
#define EXIT_MALLOC_FAILED 5

int main( void )
{
    int nodes, i;
    printf( "Enter amount nodes of polygon: " );

    if ( scanf( "%d", &nodes ) != 1 )
        return EXIT_NODES_READ_FAILED;

    float *x_nodes = ( float * )malloc( nodes * sizeof( float ) );
    float *y_nodes = ( float * )malloc( nodes * sizeof( float ) );

    if ( !x_nodes || !y_nodes )
        return EXIT_MALLOC_FAILED;

    for ( i = 0; i < nodes; i++ )
    {
        printf( "Enter node #%d coordinates:\nX = ", ( i + 1 ) );

        if ( scanf( "%f", &x_nodes[i] ) != 1 )
            return EXIT_NODE_X_READ_FAILED;

        printf( "Y = " );

        if ( scanf( "%f", &y_nodes[i] ) != 1 )
            return EXIT_NODE_Y_READ_FAILED;
    }

    printf( "Nodes:\n" );

    for ( i = 0; i < nodes; i++ )
        printf( "X = %f; Y = %f;\n", *( x_nodes + i ), *( y_nodes + i ) );

    // получить реузультат
    int result = get_traversal_direction( x_nodes, y_nodes, nodes );
    result == -1
    ? printf( "Result = %d; (anti-clockwise)\n", result )
    : printf( "Result = %d; (clockwise)\n", result );

    // чистим память
    free( x_nodes );
    free( y_nodes );

    return EXIT_SUCCESS;
}