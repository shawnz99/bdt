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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define BYTEPL 16


#define ANSI_RESET  "\x1b[0m"
#define ANSI_FG_RED "\x1b[31m"
#define ANSI_FG_GREEN "\x1b[32m"
#define ANSI_FG_WHITE "\x1b[37m"
#define ANSI_BOLD "\x1b[1m"

void printBytes(char a[], char b[], int offset, char f1[], char f2[]);
bool arrcomp(char a[], char b[]); 

int main (int argc, char *argv[])
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
    char f1[50]; strcpy (f1, *(argv + 1));
    char f2[50]; strcpy (f2, *(argv + 2));

    int byteOffset = 0;
    int arrElement = 0;
    /*
     *  If the number of args is correct then get some file ptrs
     */
    fptr1 = fopen(*(argv + 1), "r");
    fptr2 = fopen(*(argv + 2), "r");

    /*
     *  Snagging the first byte first because
     *  if we dont if the files empty eof will be unchecked
     */
    bytearr1[arrElement] = fgetc(fptr1);
    bytearr2[arrElement] = fgetc(fptr2);

    arrElement++;
    byteOffset++;


    // TODO: Make it grab more bytes after the fist 16
    while ( !feof(fptr1) && !feof(fptr2) ) {

        bytearr1[arrElement] = fgetc(fptr1);
        bytearr2[arrElement] = fgetc(fptr2);

        if ( !feof(fptr1) && !feof(fptr2) ) {

            byteOffset++;
            arrElement++;
        }
        if ( arrElement == BYTEPL ) {
           arrElement = 0; 
        }

    }

    if ( byteOffset == BYTEPL && arrcomp(bytearr1, bytearr2) == true ) {
        fprintf(stdout, "hello? \n");
    }
    else if ( arrcomp(bytearr1, bytearr2) == false ) {
        printBytes(bytearr1, bytearr2, byteOffset - BYTEPL, f1, f2);
        exit(1);
    }

    return 0;
}

/*
 *  function to go through each element of the arrays
 *  and compare them if theyre differnt return false
 */
bool arrcomp(char a[], char b[]) {
    
    for (int i = 0; i < BYTEPL; i++ ) {
        if ( a[i] != b[i] ) {
            return false;
        }
    }

    return true;
}


/*
 *  Function to print the 16 byte chunk where the error resides
 */
void printBytes(char a[], char b[], int offset, char f1[], char f2[]) {
    
    /* 
     *  For First file
     */
    fprintf(stdout, "[");
    fprintf(stdout, ANSI_FG_GREEN);
    fprintf(stdout, "%s", f1);
    fprintf(stdout, ANSI_RESET);
    fprintf(stdout, "]");
    fprintf(stdout, ANSI_FG_GREEN);
    fprintf(stdout, " < ");
    fprintf(stdout, ANSI_RESET);
    fprintf(stdout, ANSI_FG_WHITE);
    fprintf(stdout, ANSI_BOLD);
    fprintf(stdout, "%08x", offset);
    fprintf(stdout, ANSI_RESET);
    fprintf(stdout, ": ");

    for ( int i = 0; i < BYTEPL; i++ ) {
        if ( a[i] != b[i]  ) {
            fprintf(stdout, ANSI_FG_GREEN);
            fprintf(stdout, "%02x", a[i]);
            fprintf(stdout, ANSI_RESET);
        }
        else {
            fprintf(stdout, "%02x", a[i]);
        }

        if ( i % 2 == 1 ) {
            fprintf(stdout, " ");
        }
        if ( i == offset % BYTEPL - 1) {
            fprintf(stdout, "\n");
            i = BYTEPL;
        }
    }
    fprintf(stdout, "\n");

    /* 
     *  For second file
     */
    fprintf(stdout, "[");
    fprintf(stdout, ANSI_FG_RED);
    fprintf(stdout, "%s", f1);
    fprintf(stdout, ANSI_RESET);
    fprintf(stdout, "]");
    fprintf(stdout, ANSI_FG_RED);
    fprintf(stdout, " > ");
    fprintf(stdout, ANSI_RESET);
    fprintf(stdout, ANSI_FG_WHITE);
    fprintf(stdout, ANSI_BOLD);
    fprintf(stdout, "%08x", offset);
    fprintf(stdout, ANSI_RESET);
    fprintf(stdout, ": ");

    for ( int i = 0; i < BYTEPL; i++ ) {
        if ( a[i] != b[i]  ) {
            fprintf(stdout, ANSI_FG_RED);
            fprintf(stdout, "%02x", b[i]);
            fprintf(stdout, ANSI_RESET);
        }
        else {
            fprintf(stdout, "%02x", b[i]);
        }

        if ( i % 2 == 1 ) {
            fprintf(stdout, " ");
        }

        if ( i == offset % BYTEPL - 1) {
            fprintf(stdout, "\n");
            i = BYTEPL;
        }
    }
    fprintf(stdout, "\n");

}
