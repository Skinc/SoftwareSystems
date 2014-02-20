/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns a heap-allocated string with length n, with
// the given string in the middle, surrounded by fillchar.
//
// For example, if s is allen, n is 10 and fillchar is .
// the result is ..allen... 

char *center(char *s, int n,  char fillchar)
{
    int slen = strlen(s);
    int tlen = slen + 2*n +1 ;
    char *whole = malloc( tlen * sizeof(char) );
    char *filler1 = malloc(2*n+1);
    char *filler2 = malloc(2*n+1);
    

    int i;
    for (i =0; i<n; i++){
         strcat(filler1, &fillchar);

         strcat(filler2, &fillchar);
    } 

    strcat(whole, filler1);

    strcat(whole, s);

    strcat(whole, filler2);
    
    return whole;
}


int main (int argc, char *argv[])
{
    char *s = center("Software", 30, '.');
    printf("%s\n", s);

    char *s2 = center("Systems", 31, '-');
    printf("%s\n", s2);

    char *s3 = center("Spring 2014", 32, '*');
    printf("%s\n", s3);

    char *s4 = center("Exam 1", 33, '^');
    printf("%s\n", s4);

    return 0;
}
