#include <stdio.h>
#include <string.h>
#include "hangman_helpers.h"


//checks if the string (char*) contains the character (char). If it does, it returns true
bool string_contains_character(const char *s, char c) {
    int s_len = (int)strlen(s);
    for(int i=0; i<s_len; i++){
        if((int)s[i] == (int)c){
            return true;
        }
    }
    return false;
}

//revised: reads the user input and returns only the right input
char read_letter(void) {
    char one_char;
    bool right_input = false;
    do{
        //printf("Enter a lowercase character:");
        scanf(" %c", &one_char);//only take the first letter of the input
        if(is_lowercase_letter(one_char)){//is a lowercase alphabet
            right_input = true;
        } else {
            printf("Invalid input, enter a lowercase character.\n");
        }
    } while (!right_input);
    return one_char;
    }

//This function checks if the given character is lowercase. If it is not a lowercase, it returns false
bool is_lowercase_letter(char c) {
    char a = 'a';
    char z = 'z';
    if((int)a <= (int)c && (int)c <= (int)z){//it is lowercase
        return true;
    } else {
        return false;
    }
}

//checks if the given character is a valid hangman secret
bool validate_secret(const char *secret) {
    int length = (int)strlen(secret);
    char hyphen = '-';
    char apostrophe = '\'';
    char space = ' ';
    for(int i=0; i<length; i++){
       if(!is_lowercase_letter(secret[i]) || 
       secret[i] != (int)hyphen ||
       secret[i] != (int)apostrophe ||
       secret[i] != (int)space){
        return false;
       } 
    }
    return true;
}
