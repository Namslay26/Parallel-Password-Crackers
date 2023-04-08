#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

int main() {
    //getting the input
    int count=0;
    printf("Enter your password:\n");
    char pass[MAX_WORD_LENGTH + 1];
    scanf("%s", &pass);
    //file 
    FILE* file;
    file = fopen("passlist.txt", "r");
    if (file == NULL) {
        printf("File not found :(\n");
        return 1;
    }
    //forming the word 
    char* word = (char*)malloc(MAX_WORD_LENGTH + 1);
    if (word == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }
    //comparing the words
    while (fgets(word, MAX_WORD_LENGTH, file)) {
        word[strlen(word)-1]='\0';
        //printf("Read word: %s\n", word);
        //printf("Im here");
        if (strcasecmp(word, pass) == 0) {
 	
            printf("Password found: %s in count %d\n", word,count);
            free(word);
            fclose(file);
            return 0;
        }
        count++;
    }

    free(word);
    fclose(file);

    printf("Password not found :(\n");
    return 0;
}




