#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 100


void write_char(char* text, int index){
    printf("%08X: ", index);
    for(int i=0; i<16; i++){
        if(*(text+i) == '\0'){
            printf("  ");
        } else {
            printf("%02X", (unsigned char)*(text+i));
        }
        if((i+1)%2==0){
            printf(" ");
        } 
    }
    printf(" ");
    for(int i=0; i<16; i++){
        if(32<=(int)*(text+i) && (int)*(text+i)<=126 && *(text+i)!= '\0'){
            printf("%c",*(text+i));
        } else if (*(text+i)== '\0'){
            break;            
        }else {
            printf(".");
        }
    }
    printf("\n");
}

void clear_char(char* text){
    for(int i=0; i<16; i++){
        *(text+i) = '\0';
    }
}

void read_file(int file_descriptor, char* text){
    //create buffer inside here
    char buffer[BUFFER_SIZE];
    ssize_t is_read;
    int j=0;
    int index=0;
    while((is_read = read(file_descriptor, buffer, sizeof(buffer)))){
        for(ssize_t i=0; i<is_read; i++){
            *(text+j) = buffer[i];
            j++;
            if((i+1)%16 == 0 || i==(is_read-1)){
                write_char(text, index);
                clear_char(text);
                index += j;
                j=0;
            }
        }
    }
}

int main(){
    static char *text;
    static int file_descriptor;

    text = (char*)malloc(BUFFER_SIZE);
    if(text == NULL){
        perror("Memory allocation error");
        return 1;
    }

    //open file
    file_descriptor = open("foo.txt", O_RDONLY);
    if(file_descriptor < 0){ //handling errors for filenames
        perror("Error: This file does not exist.");
        free(text);
        return 1;
    }

    //read file
    read_file(file_descriptor, text);

    //close file
    if(close(file_descriptor)<0){
        perror("Error closing file");
        free(text);
        return 1;
    }

    //free memories
    free(text);
    return 0;
}
