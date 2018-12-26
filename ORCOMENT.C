#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "o.h"
                                        /*----- Comment Record Types ------*/
#define MSLANG  0                       /* 00h - MS Language Name          */
#define MSDOSV  156                     /* BCh - MS DOS Level Number (?)   */
#define MSMODL  157                     /* BDh - MS Memory Model (+opts)   */
#define MSDSEG  158                     /* BEh - MS Forced 'DOSSEG' switch */
#define MSILIB  159                     /* A0h - MS INCLUDELIB directive   */
#define MSEXTN  161                     /* A1h - MS Extensions Enabled     */
#define UNKNWN  162                     /* A2h - (?)                       */
#define MSLNAM  163                     /* A3h - MS Library Module Name    */
#define PATIME  221                     /* DDh - Phoenix Time Stamp        */
#define PACMNT  255                     /* FFh - Phoenix Comment           */

void coment( length )
    unsigned int    length;
{
    char            comment[128];
    char            text[80];
    char            temp[80];
    int             type;
    int             class;
    char            cksum;
    unsigned char   *prt_char;

    type = get_byte();
    class = get_byte();
    length -= 3;

    get_str( length, comment );

    switch( class ) {
        case MSLANG:
            out_line( "", "; Compiler:", comment, "" );
            break;
        case MSMODL:
            processor_type_comment_occurred = TRUE;
            switch( comment[0] ) {
                case '3': 
                    out_line( "", ".386p", "", "" );
                    out_line( "", ".387", "", "" );
                    processor_mode = 386;
                    break;
                case '2': 
                    out_line( "", ".286p", "", "" );
                    out_line( "", ".287", "", "" );
                    processor_mode = 286;
                    break;
                case '1': 
                    out_line( "", ".186", "", "" );
                    out_line( "", ".187", "", "" );
                    processor_mode = 186;
                    break;
                case '0': 
                    out_line( "", ".8086", "", "" );
                    out_line( "", ".8087", "", "" );
                    processor_mode = 8086;
                    break;
                default:  
                    fmt_error( "Unknown Processor Type" );
                    break;
            }
            switch( comment[1] ) {
                case 'c': 
                    out_line( "", "; Compact Memory Model", "", "" );
                    break;
                case 's':
                    out_line( "", "; Small Memory Model", "", "" );
                    break;
                case 'm': 
                    out_line( "", "; Medium Memory Model", "", "" );
                    break;
                case 'l': 
                    out_line( "", "; Large Memory Model", "", "" );
                    break;
                case 'h': 
                    out_line( "", "; Huge Memory Model", "", "" );
                    break;
                default:  
                    fmt_error( "Unknown Model" );
                    break;
            }
            if ( comment[2] = 'O' ) {
                out_line( "", "; Optimizations Enabled", "", "" );
            }
            break;
        case MSDSEG:
            out_line( "", "; Force DOSSEG linker option", "", "" );
            break;
        case MSILIB:
            out_line( "", "includelib", comment, "" );
            break;
        case MSEXTN:
            if ( !strcmp( comment, "\001CV" ) ) {
                out_line( "", "; CodeView Enabled", "", "" );
            } else {
                fmt_error( "Unknown CodeView Option" );
            }
            break; 
        case UNKNWN:
            out_line( "", "; A2h (162) - Undocumented Comment Record Type", 
                                                                    "", "" );
            break;
        case PATIME:
            if ( comment[0] != 16 ) {
                fmt_error( "Unknown Phoenix Time Stamp Prefix" );
            }
            out_line( "", "; Time: ", &comment[1], "" );
            break;
        case PACMNT:
            out_line( "", ";", comment, "" );
            break;
        default:
            text[0] = '\0';
            prt_char = comment;
            while ( length ) {
                if ( isprint(*prt_char) ) {
                    sprintf( temp, "%c", *prt_char );
                } else {
                    sprintf( temp, "[%02X]", *prt_char );
                }
                strcat( text, temp );
                prt_char++;
                --length;
            }
            sprintf( temp, "; Unknown Comment Record (Class %d): '%s'", class, text );
            out_line( "", temp, "", "" );
            break;
    }

    out_newline();

    cksum = get_byte();
}
