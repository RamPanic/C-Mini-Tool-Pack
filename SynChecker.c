/*
 *
 * SynChecker (Syntax Checker)
 * ===========================
 *
 * Created by: RamPanic
 *
 * Usage: ./SynChecker < test.c
 *
 * Description: 
 * ------------
 *
 * This is a basic C syntax checker. It is programmed with the language's 
 * standard library. It was made from the exercises in the book 
 * "The C Programming Language" by Brian W. Kernighan and Dennis M. Ritchie, 
 * so no other ways of simplifying the code were used. Also, note that it 
 * doesn't check all syntax, just braces, parentheses, brackets, escape 
 * sequences, quotes, and comments. If you see that it can be improved more, 
 * go ahead. 
 *
 *
 * */

#include <stdio.h>

// Symbolic Constants

#define TRUE 1
#define FALSE 0
#define LENGTH 10000
#define EXIT_SUCCESS 0
#define EXIT_FAILED 1

// Prototypes

void get_string(char string[], int length);
void syntax_checker(char string[]);
int get_string_length(char string[]);


int main(){ 
    
    char string[LENGTH];

    get_string(string, LENGTH);

    syntax_checker(string);

    return EXIT_SUCCESS;

}

void get_string(char string[], int length){

    char c; int i;

    for (i = 0; i < length && (c = getchar()) != EOF; i++)
        string[i] = c;

    string[i] = '\0';

}

void syntax_checker(char string[]){

    int string_length, line; // General
    
    // Syntax

    int double_quotes, simple_comment, 
        block_comment, escape_sequence_error, 
        curly_brackets_error, round_brackets_error, 
        square_brackets_error, apostrophe;

    int index, errors, current_line; // Counters

    string_length = get_string_length(string);

    // Flags

    simple_comment = FALSE;
    block_comment = FALSE;
    double_quotes = FALSE;
    apostrophe = FALSE;
    escape_sequence_error = FALSE;

    // Syntax Counters

    curly_brackets_error = 0;
    round_brackets_error = 0;
    square_brackets_error = 0;

    // General Counters

    current_line = 1;
    errors = 0;
    index = 0;

    while (index < string_length){

        // ------- Validate line number -------

        if (string[index] == '\n'){

            current_line++;
        
        }

        // ------- Validate double quotes -------

        if (string[index] == '"' && !double_quotes){
        
            double_quotes = TRUE;

        } else if (string[index] == '"' && double_quotes){

            double_quotes = FALSE;

        } else if (string[index] == '\'' && !apostrophe && !double_quotes){

            apostrophe = TRUE;

        } else if (string[index] == '\'' && apostrophe && !double_quotes){

            apostrophe = FALSE;

        }


        if (!double_quotes && !apostrophe){

            // ------- Validate block comment -------

            if (string[index] == '/' && string[index + 1] == '*'){

                block_comment = TRUE;

            } else if (string[index] == '*' && string[index + 1] == '/'){
    
                block_comment = FALSE;

            // ------- Validate simple comment -------

            } else if (string[index] == '/' && string[index + 1] == '/' && !block_comment){

                simple_comment = TRUE;

            } else if (string[index] == '\n' && !block_comment){

                simple_comment = FALSE;

            } 


            if (!block_comment && !simple_comment){

                // ------- Validate curly brackets -------

                if (string[index] == '{'){

                    curly_brackets_error++;

                } else if (string[index] == '}'){

                    curly_brackets_error--;

                }

                // ------- Validate round brackets -------

                else if (string[index] == '('){

                    round_brackets_error++;

                }

                else if (string[index] == ')'){

                    round_brackets_error--;

                }

                // ------- Validate square brackets -------

                else if (string[index] == '['){

                    square_brackets_error++;

                }

                else if (string[index] == ']'){

                    square_brackets_error--;

                }

            }
            

        } else {

            // ------- Validate escape sequences within a string -------

            if (string[index] == '\\' && (string[index + 1] != 'n' && string[index + 1] != 't' && string[index + 1] != 'r' && string[index + 1] != 'a' && string[index + 1] != 'b' && string[index + 1] != 'f' && string[index + 1] != 'v' && string[index + 1] != '\'' && string[index + 1] != '"' && string[index + 1] != '?' && string[index + 1] != '0')){

                escape_sequence_error = TRUE;
    
                errors++;

            }

        }

        index++;

    }

    printf("\nLines: %d\n", current_line - 1);

    if (block_comment){
        printf("Error: block comment was not closed\n"); 
        errors++;
    }

    if (escape_sequence_error){
        printf("Error: Escape sequence or null character are incorrect\n");  
        errors++;
    } 

    if (curly_brackets_error != 0){
        printf("Error: curly brackets are not aligned\n");
        errors++;
    }

    if (round_brackets_error != 0){
        printf("Error: round brackets are not aligned\n");
        errors++;
    }

    if (square_brackets_error != 0){
        printf("Error: square brackets are not aligned\n");
        errors++;
    }

    if (errors > 0) {
        printf("Errores de sintaxis: %d\n", errors);
        return;
    }

    printf("No hay errores de sintaxis");

}

int get_string_length(char string[]){

    int i;

    for (i = 0; string[i] != '\0'; i++);

    return i;

}