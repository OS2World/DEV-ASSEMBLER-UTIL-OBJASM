#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "o.h"

char *o_malloc( size )
    unsigned int    size;
{
    char    *result;

    result = (char *)calloc( 1, size );
    if( result == NULL ) {
        fprintf(stderr, "Out of memory\n" );
        exit(4);
    }
    return( result );
}
