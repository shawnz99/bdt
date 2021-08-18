//
// Design specs:
//  - take in two files as cli arguments, if not two files then error
//
//  - read the files in 16 byte chunks, compare those chunks,
//    if the chunks differ then output the line of diffence for both chunks
//
// For later:
//  - Display the address/offset on the left just as xxd does
//
/////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define BYTEPL 16


#define ANSI_RESET  "/x1b[0m"
#define ANSI_FG_RED "/x1b[31m"

bool arrcomp(char a[], char b[]);
void printBytes(char a[], char b[], int offset);

int main (int argc, char **argv)
{
    /*
     *  Checking number of arguments
     */
    if ( argc < 2 ){
        fprintf(stderr, "Invalid number of Arguments");
        exit(1);
    }

    /*
     * file pointers
     */
    FILE *fptr1     = NULL;
    FILE *fptr2     = NULL;

    /*
     *  + 1 because if not it overwrites the 
     *  first byte when it hits 16
     */ 
    char bytearr1[BYTEPL + 1];
    char bytearr2[BYTEPL + 1];

    int byteOffset = 0;
    int diffByte   = 0;

    /*
     *  If the number of args is correct then get some file ptrs
     */
    fptr1 = fopen(*(argv + 1), "r");
    fptr2 = fopen(*(argv + 2), "r");

    /*
     *  Snagging the first byte first because
     *  if we dont if the files empty eof will be unchecked
     */
    bytearr1[byteOffset] = fgetc(fptr1);
    bytearr2[byteOffset] = fgetc(fptr2);

    byteOffset++;


    // TODO: Make it grab more bytes after the fist 16
    while ( !feof(fptr1) && !feof(fptr2) ) {

        bytearr1[byteOffset] = fgetc(fptr1);
        bytearr2[byteOffset] = fgetc(fptr2);

        byteOffset++;

    }
    if ( byteOffset == BYTEPL && arrcomp(bytearr1, bytearr2) == true ) {
        fprintf(stdout, "hello? \n");
    }
    else if ( arrcomp(bytearr1, bytearr2) == false ) {
        printBytes(bytearr1, bytearr2, byteOffset);
        exit(1);
    }

    return 0;
}


/*
 *  function to go through each element of the arrays
 *  and compare them if theyre differnt return false
 */

// TODO: have it put the actual byte where the difference is 
bool arrcomp(char a[], char b[]) {
    
    for (int i = 0; i < BYTEPL; i++ ) {
        if ( a[i] != b[i] )
            return false;
    }

    return true;
}


/*
 *  Function to print the 16 byte chunk where the error resides
 */
void printBytes(char a[], char b[], int offset) {
    
    fprintf(stdout, "%08x:  ", offset);
    for ( int i = 0; i < BYTEPL; i++ ) {
        fprintf(stdout, "%02x", a[i]);
        if ( i % 2 == 1 ) {
            fprintf(stdout, " ");
        }
    }
    fprintf(stdout, "| ");
    for ( int i = 0; i < BYTEPL; i++ ) {
        fprintf(stdout, "%02x", b[i]);
        if ( i % 2 == 1 ) {
            fprintf(stdout, " ");
        }
    }
    fprintf(stdout, "\n");
    
}
