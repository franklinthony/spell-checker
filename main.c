#include <time.h>
#include "hashTable_sll.h"

int main() {
    FILE *input = fopen("input_texts/Harry_Potter_and_the_Order_of_Phoenix.txt", "r");
    FILE *output = fopen("log.txt", "w");
    FILE *dictionary = fopen("ascii_noaccent_noduplicates_FIXED_v2_1.txt","r");
    
    char dictionaryStr[MAX_STRING], inputStr[MAX_STRING];
    char space[] = " ";
    char *token = NULL;
    clock_t time[2] = {0,0};
    int notFound = 0;
    int numWords = 0;

    HashTable *hashTable = CreateHashTable(hashTable);

    while (fgets(dictionaryStr, MAX_STRING, dictionary)){       //Insert dictionary in HashTable
        if(dictionaryStr[strlen(dictionaryStr) - 1] == '\n')
            dictionaryStr[strlen(dictionaryStr) - 1] = '\0';
        Insert(hashTable, dictionaryStr);
    }
    
    while (fgets(inputStr, MAX_STRING, input)){                 //Search words from input text
        RemovePunctAndMakeLowerCase(inputStr);

        if(inputStr[strlen(inputStr) - 1] == '\n')
            inputStr[strlen(inputStr) - 1] = '\0';

        time[0] += clock();        
        token = strtok(inputStr, space);
        
        while( token != NULL ) {
            numWords++;
            
            if(!Search(hashTable, token))
                notFound++;
    
            token = strtok(NULL, space);
        }
        time[1] += clock();
    }

    fprintf(output, "Numero total de palavras do texto: %d.\n", numWords);
    fprintf(output, "Tempo total da verificacao: %.2lf ms.\n", (double) (time[1] - time[0]) * 1000.0 / CLOCKS_PER_SEC);
    fprintf(output, "Numero total de palavras que falharam no spell check: %d.\n", notFound);

    fclose(input);
    fclose(output);
    fclose(dictionary);
    return 0;
}

/*
                                                                //Uncomment and put in your main if you want to 
                                                                //check the elements per bucket distribution 
#define MAX 20
    
FILE *data = fopen("data.txt", "w");
int elementsPerBucket[MAX] = {0};

for (int i = 0; i < MAX; i++){
    for (int j = 0; j < MAX_BUCKETS; j++){
        if(i == 0){
            fprintf(data,"%d;", h->numElements[j]); 
        }
        if(h->numElements[j] == i){
            //printf("%d[%d]\n", h->numElements[j], i);
            elementsPerBucket[i]++;
        }
    }
    printf("Buckets com %d = %d, (%.2lf%%)\n", i, elementsPerBucket[i], (double) (elementsPerBucket[i] * 100)/MAX_BUCKETS);
}
    
fclose(data);
*/