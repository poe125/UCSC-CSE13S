#include "hash.h"
#include "ll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 100

//create a program where it counts the number of unique words

void write_char(Hashtable *ht, char* text, int index){
    //put it in the hash table 
   // printf("write_char: starting...\n");
    hash_put(ht, text, index);
}

void clear_char(char* text){
    for(int i=0; i<16; i++){
        *(text+i) = '\0';
    }
}

int read_file(Hashtable *ht, int file_descriptor, char* text){
  //  printf("read_file: starting...\n");
    //create buffer inside here
    char buffer[BUFFER_SIZE];
    ssize_t is_read;
    int j=0;
    int index=0;
    int unique = 0;
    while((is_read = read(file_descriptor, buffer, sizeof(buffer)))){
        for(ssize_t i=0; i<is_read; i++){
            *(text+j) = buffer[i];
            j++;
            if(buffer[i] == '\n'){
 //               printf("read_file: enter key pressed\n");
                //text -> key, index -> id
                //check for unique lines
                int *ret = hash_get(ht, text);
                if(ret == NULL){
                    //unique line
                    unique++;
                } else {
                write_char(ht, text, index);
                }
                clear_char(text);
                index += j;
                j=0;
            }
        }
    }
    return unique;
}

int main(int argc, char *argv[]){
    static char *text;
    static int file_descriptor;

    Hashtable *h = hash_create();
  //  printf("main: Created the hash table\n");

    text = (char*)malloc(BUFFER_SIZE);
    if(text == NULL){
        perror("Memory allocation error\n");
        return 1;
    }
    //open file
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }
    file_descriptor = open(argv[1], O_RDONLY);
    if(file_descriptor < 0){ //handling errors for filenames
        perror("Error: This file does not exist.\n");
        free(text);
        return 1;
    }

    //read file
    int unique_num = read_file(h, file_descriptor, text);
    printf("Number of unique lines: %d \n", unique_num);
    //close file
    if(close(file_descriptor)<0){
        perror("Error closing file");
        free(text);
        return 1;
    }

    //free memories
    free(text);
    hash_destroy(&h);
    return 0;
}
