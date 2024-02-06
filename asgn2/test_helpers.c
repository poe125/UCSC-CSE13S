//this tests all functions in hangman_helpers.c
#include <stdio.h>
#include <string.h>
#include "hangman_helpers.h"

int main(){
printf("<This is the test for hangman_helpers.c>\n");

//test for read_letter
char word = read_letter();
printf("Input:%s\n", &word);

//test for is_lowercase_letter
bool is_lowercase = is_lowercase_letter(word);
if(is_lowercase){
    printf("The input was lowercase\n");
} else {
    printf("The input was not lowercase\n");
}

char str[17] = {'t','h','i','s','-','i','s','-','t','h','e',' ','t','e','s','t', '\0'};
printf("[This is the string: %s]\n", str);

//test for validate_secret
bool not_validate = validate_secret(str);
if(!not_validate){
    printf("The secret is validate\n");
} else {
    printf("The secret is not validate\n");
}

//test for string_contains_character
bool string_contained = string_contains_character(str, word);
if(string_contained){
    printf("The input is contained in the secret\n");
} else {
    printf("The input is not contained in the secret\n");
}
printf("\n");

return 0;
}