/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey With work by Shane Skikne
License: Creative Commons Attribution-ShareAlike 3.0
Significant help from http://www.lemoda.net/c/unix-regex/index.html
and http://stackoverflow.com/questions/14577426/email-validation-in-c-using-glibc-regex-h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5
#define MAX_ERROR_MSG 0x1000

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
    	if (strstr(tracks[i], search_for)) {
	        printf("Track %i: '%s'\n", i, tracks[i]);
	   }
    }
}
// Sets up the regex object used for matching and confirms regex search is valid
int setup_regex(regex_t * r, const char * regex_text){
    //REG_ICASE ignores the case of 
    int confirm = regcomp(r, regex_text, REG_ICASE);
    //If the search text is invalid, will print error and return 1
    if (confirm != 0){
        char error_message[MAX_ERROR_MSG];
        regerror (confirm, r, error_message, MAX_ERROR_MSG);
        printf ("Regex error compiling '%s': %s\n", regex_text, error_message);
        return 1;
    }
    return 0;
}

//For each track, checks if it matches the search text using regular expressions
int run_regex(regex_t * r){
    int i;
    int res;
    for (i=0; i<NUM_TRACKS; i++) {
        res = regexec(r,tracks[i],0,NULL,0);
        if (!res){
            printf("Track %i: '%s'\n", i, tracks[i]);
        } 
    }
    return 0;


}
// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{
    
    regex_t r;
    const char * regex_text = pattern;
    if (!setup_regex(& r, regex_text)){
        run_regex(& r);
        regfree (& r);
    }

}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	*ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
