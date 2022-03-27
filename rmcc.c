/*
 *
 * REMOVE ALL COMMENTS FROM C FILE (rmcc)
 * ======================================
 *
 * Created by: RamPanic
 *
 * Usage: ./rmcc < file.c
 *
 * Note: This program will ignore the correct syntax
 *
 * */

#include <stdio.h>

// Symbolic Constants

#define FALSE 0
#define TRUE  1 
#define ARRAY_LENGTH 100000
#define EXIT_SUCCESS 0
#define EXIT_FAILED 1


// Prototypes

void write_string(char string[], int length);
int str_length(char string[]);
void remove_comments(char string[]);


int main(int argc, char *argv[]){

    if (argc > 1){

        printf("No arguments needed");

        return EXIT_FAILED;
    
    }

    char string[ARRAY_LENGTH];

    write_string(string, ARRAY_LENGTH);

    remove_comments(string);

    return EXIT_SUCCESS;

}

void write_string(char string[], int length){

    int i; char c;

    for (i = 0; i < length && (c = getchar()) != EOF; i++)
        string[i] =  c;

    string[i] = '\0';

}

int str_length(char string[]){

    int i;

    for (i = 0; string[i] != '\0'; i++);

    return i;

}

void remove_comments(char string[]){

    int index, str_len, quotes, simple_comment, block_comment;

    str_len = str_length(string); 
    
    quotes = FALSE;
    simple_comment = FALSE;
    block_comment = FALSE;

    index = 0;

    while (index < str_len){
    
        if (string[index] == '"' && !quotes){

            quotes = TRUE;

        } else if (string[index] == '"' && quotes){

            quotes = FALSE;

        }


        if (!quotes){

            if (string[index] == '/' && string[index + 1] == '/'){

                simple_comment = TRUE;

            } else if (string[index] == '/' && string[index + 1] == '*'){

                block_comment = TRUE;
                index = index + 2;

            } else if (string[index] == '*' && string[index + 1] == '/'){
    
                block_comment = FALSE;
                index = index + 2;

            } 
            
            if (simple_comment){

                for (index = index + 2; index < str_len && string[index] != '\n'; index++);
                
                simple_comment = FALSE;

            } else {
                
                if (block_comment){

                    index++;

                } else {

                    putchar(string[index++]);
                
                }
        
            }

        } else {

            putchar(string[index++]);

        }

    }       

}