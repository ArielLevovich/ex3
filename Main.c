#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

#define MAX_STRING_SIZE 1024

void freeList(StrList* strList) {
    if (strList != NULL) {
        int size = StrList_size(strList);
        if (size > 0) {
            for (int i=size-1; i>=0; i--) {
                StrList_removeAt(strList, i);
            }
            StrList_free(strList);
        }        
    }
}

void populateStringList(StrList** strListPtr) {
    StrList* strList = *strListPtr;
    // deallocate the string list.
    freeList(strList);
     
    strList = StrList_alloc();                
    *strListPtr = strList;

    int numOfWords;
    scanf(" %d", &numOfWords);    

    // Dynamically allocate a buffer for the input line
    // char *line = NULL;
    // size_t bufsize = 0;
    // getline(&line, &bufsize, stdin); // Read the entire line of words

    // const char *delimiters = " \n"; // Delimiter for tokenization
    // // Use strtok to find the first token
    // char *token = strtok(line, delimiters);        

    // int count = 0;
    // while (token != NULL && count < numOfWords) {                            
    //     StrList_insertLast(strList, token);	// add the current token to the list 				  
    //     token = strtok(NULL, delimiters); // Get the next token        
    //     count++;
    // }
    // free(line);
    int count = 0;
    while (count < numOfWords) {
        char word[MAX_STRING_SIZE];                            
        scanf("%1023s", word);
        StrList_insertLast(strList, word);					          
        count++;
    }
}

void putStringAtIndex(StrList* strList) {
    if (strList != NULL) {
        int index;
        scanf(" %d", &index);
        
        char word[MAX_STRING_SIZE];                            
        scanf("%1023s", word);

        StrList_insertAt(strList, word, index);    
    }
}

int main() {
    int command;    
    StrList* strList = NULL;
    char word[MAX_STRING_SIZE];
    int index;

    while (1) {
        // printf("Enter command in the range [0,13]: ");
        int retValue = scanf(" %d", &command); // Note the space before %c to consume any newline characters left in the input buffer
        if (retValue == EOF) {
            if (strList != NULL) {
                freeList(strList);
            }
            return 0;
        }
        switch (command) {
            case 0:
                if (strList != NULL) {
                    freeList(strList);
                }
                return 0;                            
            case 1:
                populateStringList(&strList);                
                break;
            case 2:
                putStringAtIndex(strList);             
                break;
            case 3:  
                StrList_print(strList);              
                break;
            case 4:
                printf("%ld\n", StrList_size(strList));                
                break;
            case 5:                
                scanf(" %d", &index);
                StrList_printAt(strList, index);                
                break;
            case 6:       
                printf("%d\n", StrList_printLen(strList));         
                break;
            case 7:                                            
                scanf("%1023s", word);
                printf("%d\n", StrList_count(strList, word));                                      
                break;
            case 8:                
                scanf("%1023s", word);
                StrList_remove(strList, word);
                if (StrList_size(strList) == 0) {
                    StrList_free(strList);
                    strList = NULL;
                }                                                     
                break;
            case 9:                
                scanf(" %d", &index);
                StrList_removeAt(strList, index);                
                break; 
            case 10:
                StrList_reverse(strList);     
                break;
            case 11:
                freeList(strList);
                strList = NULL;
                break;
            case 12:    
                StrList_sort(strList);           
                break;
            case 13:
                int sorted = StrList_isSorted(strList);
                if (sorted == 1) {
                    printf("Sorted.\n");
                } else {
                    printf("Not sorted.\n");
                }              
                break;                            
            default:                
                printf("Invalid command.\n");
        }
    }
}
