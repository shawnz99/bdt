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
bool arrcomp(char a[], char b[]);

int main (int argc, char **argv)
{
    /*
     *  Checking number of arguments
     */
    if ( argc < 2 ){
        fprintf(stderr, "Invalid number of Arguments");
        exit(1);
    }

    // file pointers
    FILE *fptr1     = NULL;
    FILE *fptr2     = NULL;
    // file bytes
//    int *f1         = NULL;
//    int *f2         = NULL;

    char bytearr1[BYTEPL];
    char bytearr2[BYTEPL];

    int byteOffset = 0;

    /*
     *  If the number of args is correct then get some file ptrs
     */

    fptr1 = fopen(*(argv + 1), "r");
    fptr2 = fopen(*(argv + 2), "r");


    /*
     *  Getting some stuff to read the bytes into
     */

    //f1 = (int*) malloc(sizeof(char));
    //f2 = (int*) malloc(sizeof(char));
    

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


        if ( byteOffset == BYTEPL && arrcomp(bytearr1, bytearr2) == true ) {
            fprintf(stdout, "hello? \n");
            
        }
        else if ( arrcomp(bytearr1, bytearr2) == false ) {
            fprintf(stdout, "not the same \n");
            exit(1);
        }
    }

    return 0;
}


/*
 *  function to go through each element of the arrays
 *  and compare them if theyre differnt return false
 */
bool arrcomp(char a[], char b[]) {
    
    for (int i = 0; i < BYTEPL; i++ ) {
        if ( a[i] != b[i] )
            return false;
    }

    return true;
}
