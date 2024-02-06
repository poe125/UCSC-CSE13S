#include "hangman_helpers.h"
#include <stdio.h>
#include <string.h>

//checks for alphabets and put it in an array called array alphabet
void get_alphabet(const char* secret, char* alphabet, int length){
    int array_count = 0;
    for(int i=0; i<length; i++){
        if(is_lowercase_letter(secret[i])){
            alphabet[array_count] = secret[i];
            array_count++;
        }
    }   
    alphabet[array_count] = '\0';
}

void get_original_secret(const char* secret, char* original, int length){
    for(int i = 0; i < length && secret[i] != '\0'; i++){
        original[i] = secret[i];
    }
    original[length] = '\0';  // Ensure null termination
}



void get_hidden_secret(char* secret, char* alphabet, char* original, int length){
    int array_count = 0;
    for(int i=0; i<length; i++){
        if(is_lowercase_letter(original[i])){
            if(alphabet[array_count] != '0'){
                secret[i] = '_';
            } else {
                secret[i] = original[i];
            }
        array_count++;
        } //if it's not lowercase, skip
    }
}

//checks for the alphabet given by c and deletes it from array alphabet if it is found
void delete_alphabet(char* alphabet, char word){
    int alph_len = (int)strlen(alphabet);
    for(int i=0; i<alph_len && alphabet[i] != '\0'; i++){
        if((int)alphabet[i] == (int)word){
            alphabet[i]='0';
        }
    }
}

//return the array of characters that was wrong
void get_wrong_char(char* wrong_letters, char c, int i){
    wrong_letters[i] = c;
}

void get_secret(char *secret, int max_length) {
    printf("Enter a secret: ");
    //fgets(secret, max_length, stdin);
    scanf(" %99[^\n]", secret);
    secret[max_length -1] = '\0';
}

bool check_alphabet(char *alphabet){
    int al_leng = (int)strlen(alphabet);
    for(int i=0; i<al_leng && alphabet[i] != '\0'; i++){
        if(alphabet[i]!='0'){
            return false;
        }
    }
    return true;
}

void reorder_str(char *str) {
    int str_len = (int)strlen(str);
    char temp;

    for (int i = 0; i < str_len - 1; i++) {
        for (int j = i + 1; j < str_len; j++) {
            if ((int)str[j] < (int)str[i]) {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

//runs the game itself, and decides if the player wins or not
bool hangman_game(char *secret, char *wrong_alphabet, char *alphabet, char * original, int length){
    bool win = false;
    bool exit = false;
    bool is_included = false;

    char word;
    
    int mistake = 0;
    
    do{
        //the original is the correct secret, secret will be changed
        get_hidden_secret(secret, alphabet, original, length);
        
        printf("Phrase: %s\n", secret);
        printf("Eliminated: %s\n", wrong_alphabet);
        printf("%s\n", arts[mistake]);
        printf("Guess a letter:");

        word = read_letter();
        
        //check if the word is included in the given secret
        is_included = string_contains_character(alphabet, word);
        if(is_included == 1){
            delete_alphabet(alphabet, word);
        } else {
            get_wrong_char(wrong_alphabet, word, mistake);
            reorder_str(wrong_alphabet);
            mistake++;
        }
        if(check_alphabet(alphabet)){
            win = true;
            exit = true;
        }
        if(mistake == LOSING_MISTAKE){
            exit = true;
        }
        printf("%s", CLEAR_SCREEN);
    } while (!exit);

    if(win){
        return true;
    } else {
        return false;
    }
}

int main(){
    bool win = false;
    bool inside_loop = false;
    char secret[MAX_LENGTH]; //make an array for secret of length MAX_LENGTH

    do{
        get_secret(secret, MAX_LENGTH);
        if(validate_secret(secret) == 1){
            printf("wrong number of arguments\n");
        } else {
            inside_loop = true;
        }
    }while(!inside_loop);
    printf("%s", CLEAR_SCREEN);

    int length = (int)strlen(secret);
    
    char original[length+1];
    get_original_secret(secret, original, length);
    //only take the alphabet from the secret
    char alphabet[length];
    get_alphabet(secret, alphabet, length);

    //only the mistaken alphabet by the user
    char wrong_alphabet[LOSING_MISTAKE];

    win = hangman_game(secret, wrong_alphabet, alphabet, original, length);

    if(win){
        printf("You win! The secret phrase was: %s\n", original);
    } else {
        printf("You lose! The secret phrase was: %s\n", original);
    }

    return 0;
}
