#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct Key {
    int number;
    char letter;
} Key;

int chek(int num, char s, Key **keys, int len){
    for(int j = 0; j < len; j++){
        if (keys[j]->number == num && keys[j]->letter == s){
            return 1;
        }
    }
    return 0;
}

int compare(Key* word_1, Key* word_2){
    if (word_1->letter > word_2->letter ){
        return 1;
    }
    else if (word_1->letter == word_2->letter){
        if (word_1->number > word_2->number){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int main(void){
    char letter_line[] = "ABCDIFGHJKLMONPQRSTUVWXYZ";
    int choice;
    printf("Enter type of sort: 1)Random oder keys 2)Forverd oder keys  3)Revers oder keys\n");
    scanf("%d", &choice);
    int id_letter;
    int id_number;
    if (choice == 2){
        id_letter = 0;
        id_number = 1;
    }else if (choice == 3){
        id_letter = 24;
        id_number = 10;
    }
    srand(time(NULL));
    FILE *fp = fopen("Example.txt", "r");
    if (fp == NULL) {
        printf("Error of read file\n");
        return 1;
    }
    Key **keys = NULL;
    char line[256];
    char **word = NULL;
    int i = 0;
    
    while(fscanf(fp, "%255s", line) == 1){
        Key **new_keys = realloc(keys, (i+1)*sizeof(Key*));
        if (new_keys == NULL){
            if (i > 0){
                for (int j = 0; j < i; j++){
                    free(keys[j]);
                    free(word[j]);
                }
                free(word);
            }
            free(keys);
            free(new_keys);
            fclose(fp);
            printf("Memory error\n");
            return 1;
        }
        keys = new_keys;
        keys[i] = malloc(sizeof(Key));
        if (keys[i] == NULL){
            if (i > 0){
                for (int j = 0; j < i; j++){
                    free(keys[j]);
                    free(word[j]);
                }
                free(word);
            }
            free(new_keys);
            free(keys[i]);
            free(keys);
            fclose(fp);
            printf("Memory error\n");
            return 1;
        }
        char **new_word = realloc(word, (i+1)*sizeof(char*));
        if (new_word == NULL){
            if (i >0){
                for (int j = 0; j < i; j++){
                    free(keys[j]);
                    free(word[j]);
                }
            }
            free(keys[i]);
            free(new_keys);
            free(new_word);
            free(word);
            free(keys);
            fclose(fp);
            printf("Memory error\n");
            return 1;
        }
        word = new_word;
        word[i] = malloc(sizeof(char*)*255);
        if(word[i] == NULL){
            if (i >0){
                for (int j = 0; j < i; j++){
                    free(keys[j]);
                    free(word[j]);
                }
            }
            free(keys[i]);
            free(word[i]);
            free(new_keys);
            free(new_word);
            free(word);
            free(keys);
            fclose(fp);
            printf("Memory error\n");
            return 1;
        }
        strcpy(word[i], line);
        if (choice == 1){
            int num = 1 + rand() % 11;
            char s = 'A' + rand() % ('Z' - 'A' + 1);
            while (chek(num, s, keys, i-1) == 1){
                num++;
            }
            keys[i]->letter = s;
            keys[i]->number = num;
        }
        else if(choice == 2){
            keys[i]->letter = letter_line[id_letter];
            keys[i]->number = id_number;
            if (id_number == 10 && id_letter != 24){
                id_letter++;
                id_number = 1;
            }else if(id_letter == 24 && id_number == 10){
                id_letter = 0;
                id_number = 1;
            }
            else{
                id_number++;
            }
        }else if(choice == 3){
            keys[i]->letter = letter_line[id_letter];
            keys[i]->number = id_number;
            if (id_number == 1 && id_letter != 0){
                id_letter = id_letter -1;
                id_number = 10;
            }else if(id_number == 1 && id_letter == 0){
                id_letter = 24;
                id_number = 10;
            }
            else{
                id_number = id_number -1;
            }
        }
        printf("%d%c :%s\n", keys[i]->number,keys[i]->letter, word[i]);
        i++;
    }
    fclose(fp);
    for(int j = 0; j < i; j++){
        int idx = j;
        for(int k = j; k < i; k++){
            if (compare(keys[idx], keys[k]) == 1){
                idx = k;
            }
        }
        Key* new_key = keys[idx];
        char *new_word = word[idx];
        keys[idx] = keys[j];
        word[idx] = word[j];
        keys[j] = new_key;
        word[j] = new_word;
    }
    printf("\nSorted:\n");
    for (int j = 0; j < i; j++){
        printf("%d%c :%s\n", keys[j]->number,keys[j]->letter, word[j]);
    }
    int key_n;
    char key_s;
    printf("\nEnter key:\n");
    scanf("%d%c", &key_n, &key_s);
    int f = 0;
    for (int j = 0; j < i; j++){
        if (keys[j]->letter == key_s && keys[j]->number == key_n){
            printf("%s\n", word[j]);
            f = 1;
        }
    }
    if(f == 0){
        printf("Error: no such key");
    }
    for(int j = 0; j < i; j++){
        free(word[j]);
        free(keys[j]);
    }
    free(keys);
    free(word);
    return 0;
}