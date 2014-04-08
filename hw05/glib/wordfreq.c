#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


/* This function takes the key (String) and its value (int) and 
   prints them. It is used for printing the tables.*/


void printInput(char *key, int value){
    printf("Key: %s. Value: %d\n", key, value );
}

/* This function take the hashtable of words and their frequency 
   and prints out each key/value combo.*/

void printTable(GHashTable *table){
    g_hash_table_foreach(table, (GHFunc) printInput, NULL);
}

/* This function takes the hashtable and a word. If the word is 
   alread in the hashtable, it increments the freqency by 1. If 
   the word is not in the hashtable, it adds it  */

void addWord(GHashTable **table, char *word){
    size_t size = strlen(word);
    //check if the first letter is uppercase. Don't care about 
    //other letters, because they will be consistently uppercase
    // or lowercase (ie eBook is always eBook)
    if(isupper(word[0])){
        word[0] = tolower(word[0]);
    }
    //check if the last letter is punctuation. Don't check rest.
    //if punctuation is not the last letter, safe to assume it is specific 
    // to the word (ie the ' in don't. )
    if(ispunct(word[size-1])){
        word[size-1] = '\0';
    }

    //Look up the freq of the word.
    int freq = g_hash_table_lookup(*table, word);

    //if the freq is null, the word has not been added yet.
    if (freq == NULL){
        //add the word and a freq of 1
        freq = 1;
        g_hash_table_insert(*table, word, (gpointer) freq );
    } else {
        //update the freq for this word
        freq++;
        g_hash_table_replace(*table, word, (gpointer) freq);
    }
}

/* This function takes a FILE object and the hashtable. It parses
   the file and passes each word off to get added to the table. */

int parse(FILE *file, GHashTable **table){
    char word[30];
    
    
    puts("Parsing file");

    while (fscanf(file, "%s", word) != EOF) { 
        
        char *newWord = malloc(30);
        if (newWord == NULL){
            perror ("malloc failed");
            exit (-1);
        }
        strcpy(newWord,word );
        addWord(table, newWord);
 
    
    }
    return 0;
}

int main(int argc, char** argv) {

    //Open a FILE object for parsing.
    FILE *file = fopen("text.txt","r");
    if (file == NULL){
        perror ("fopen failed");
        exit (-1);
    }
    // create a GHashTable to store all our words/freqs
	GHashTable* table;
    table = g_hash_table_new(g_str_hash, g_str_equal);
    
    //Test code to try simple additions.
    // char key[] = "HELLO!";
    // int value = 5;
    // char key2[] = "Shane";
    // int value2 = 2;
    // char key3[] = "Ca4!";
    // int value3 = 6;
    
    // g_hash_table_insert(table, (gpointer) key, (gpointer) value);
    
    // g_hash_table_insert(table, (gpointer) key2, (gpointer) value2);
    // g_hash_table_insert(table, (gpointer) key3, (gpointer) value3);    
    
    parse(file, &table);
    int closed = fclose(file);

    if (closed != 0){
        perror ("fclose failed");
        exit (-1);    
    }

    printTable(table);

    return 0;
}   