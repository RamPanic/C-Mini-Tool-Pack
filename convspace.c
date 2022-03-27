/*
 *
 *
 * TABS TO SPACES CONVERTER (convspace)
 * ====================================
 *
 * Created by: RamPanic
 *
 * Usage: ./convspace <total spaces> < input_file > output_file 
 *
 *
 * */


#include <stdio.h>

// Symbolic Constants

#define EXIT_SUCCESS 0
#define EXIT_FAILED 1
#define DEFAULT_SPACES_LENGTH 4

// Prototypes

int atoi(const char *str);
void conv_to_spaces(int spaces_length);


int main(int argc, char *argv[]){
    
    int spaces_length;

    if (argc > 2) {

        printf("Many arguments, only one allowed");

        return EXIT_FAILED;
    
    }
    
    if (argv[1] == NULL){

        spaces_length = DEFAULT_SPACES_LENGTH;
    
    } else {

        spaces_length = atoi(argv[1]);
    
    }

    conv_to_spaces(spaces_length);
    
    return EXIT_SUCCESS;

}

void conv_to_spaces(int spaces_length){

    int i, c;

    while ((c = getchar()) != EOF){

        if (c == '\t'){

            for (i = 0; i < spaces_length; i++){
            
                putchar(' ');

            }

        } else {

            putchar(c);

        }

    }

}
