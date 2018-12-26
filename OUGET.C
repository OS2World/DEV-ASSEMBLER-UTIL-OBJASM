#include <stdio.h>
#include <stdlib.h>
#include "o.h"

unsigned char get_byte()
{
    int     ch;

    ch = fgetc( o_file );
    if( ch == EOF ) {
        fprintf(stderr, "%s: Premature end of file\n");
        exit(3);
    }
    return( (unsigned char)ch );
}

int get_int()
{
    int    ch;

    ch = get_byte();
    ch += get_byte() << 8;

    return( ch );
}

unsigned int get_word()
{
    unsigned int    ch;

    ch = get_byte();
    ch += get_byte() << 8;

    return( ch );
}

unsigned long get_long()
{
    unsigned long   ch;

    ch = get_byte();
    ch += get_byte() << 8;
    ch += get_byte() << 16;
    ch += get_byte() << 24;
    return( ch );
}

void get_str( length, dest_string )
    int     length;
    char    *dest_string;
{
    int     count;

    count = length;

    while( count ) {
      *dest_string++ = get_byte();
      --count;
    }
    *dest_string = '\0';
}


int get_name( dest_string )
    char    *dest_string;
{
    int     length;

    length = get_byte();
    get_str( length, dest_string );

    return( length+1 );
}

int get_index( data )
    int     *data;
{
    unsigned int ch;

    ch = get_byte();
    if ( ch > 0x7F ) {
        ch = ((ch & 0x7F) << 8) + get_byte();
        *data = ch;
        return( 2 );
    } else {
        *data = ch;
        return( 1 );
    }
}

