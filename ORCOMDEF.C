#include <stdio.h>
#include "o.h"

unsigned int get_val( unsigned long * );

unsigned int get_val( value )
    unsigned long   *value;
{   
    unsigned int    byte;
    unsigned int    result;

    byte = get_byte();

    switch( byte ) {
        case 0x81:
            *value = (unsigned long)get_word();
            result = 3;
            break;
        case 0x84:
            *value = (unsigned long)get_word() 
                     + ((unsigned long)get_byte() << 8);
            result = 4;
            break;
        case 0x88:
            *value = get_long();
            result = 5;
            break;
        default:
            *value = (unsigned long)byte;
            result = 1;
            break;
    }
    return( result );
}

void comdef( length, scope )
    unsigned int    length;
    int             scope;
{
    char            name[41];
    int             typ_idx;
    int             var_type;
    unsigned long   num_elements;
    unsigned long   element_size;
    char            cksum;

    --length;
    while( length ) {
        length -= get_name( name );
        length -= get_index( &typ_idx );
        --length;
        var_type = get_byte();
        if ( var_type == 0x61 ) {
            /* MSC v4.0 actually has these values reversed, so you may
               have to reverse the two lines below to generate resonable
               .asm code */
            length -= get_val( &num_elements );
            length -= get_val( &element_size );
        } else {
            length -= get_val( &element_size );
            num_elements = 1L;
        }
        ext_insert( name, 1, var_type, num_elements, 
                                        (unsigned int)element_size, scope );
    }
    cksum = get_byte();
}



