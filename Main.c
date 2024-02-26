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

char* getStringFromStdin()
{
    char word[MAX_STRING_SIZE];
    char* retValue = fgets(word, MAX_STRING_SIZE, stdin);
    if (retValue != NULL)
    { 
        // Remove the newline character if it's read by fgets
        retValue[strcspn(retValue, "\n")] = 0;
    }
    return retValue;
}

void populateStringList(StrList** strListPtr) {
    StrList* strList = *strListPtr;
    // deallocate the string list.
    freeList(strList);
     
    strList = StrList_alloc();                
    *strListPtr = strList;
    
    // read the number of words from stdin
    char* retValue = getStringFromStdin();
    if (retValue == NULL) {
        return; // EOF reached
    }
    int numOfWords = atoi(retValue);
    
    // read the line of words
    retValue = getStringFromStdin();
    if (retValue == NULL) {
        return; // EOF reached
    }

    const char *delimiters = " \n"; // Delimiter for tokenization
    // Use strtok to find the first token
    char *token = strtok(retValue, delimiters);        

    int count = 0;
    while (token != NULL && count < numOfWords) {                            
        StrList_insertLast(strList, token);	// add the current token to the list 				  
        token = strtok(NULL, delimiters); // Get the next token        
        count++;
    }        
}

void putStringAtIndex(StrList* strList) {
    if (strList != NULL) {
        char* retValue = getStringFromStdin();
        int index = atoi(retValue);        
        
        retValue = getStringFromStdin();

        StrList_insertAt(strList, retValue, index);    
    }
}

int main() {
    long command;    
    StrList* strList = NULL;
    int index;
    char* retValue;

    while (1) {        
        retValue = getStringFromStdin();        
        if (retValue == NULL) {
            freeList(strList);
            return 0;
        }
        
        command = atoi(retValue);

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
                if(strList == NULL){
                    printf("\n");
                }
                break;
            case 4:
                printf("%ld\n", StrList_size(strList));                
                break;
            case 5:                                
                retValue = getStringFromStdin();
                index = atoi(retValue);
                StrList_printAt(strList, index);                
                break;
            case 6:       
                printf("%d\n", StrList_printLen(strList));         
                break;
            case 7:                                            
                retValue = getStringFromStdin();
                printf("%d\n", StrList_count(strList, retValue));                                      
                break;
            case 8:                
                retValue = getStringFromStdin();
                StrList_remove(strList, retValue);
                if (StrList_size(strList) == 0) {
                    StrList_free(strList);
                    strList = NULL;
                }                                                     
                break;
            case 9:                
                retValue = getStringFromStdin();
                index = atoi(retValue);
                StrList_removeAt(strList, index);
                if (StrList_size(strList) == 0) {
                    StrList_free(strList);
                    strList = NULL;
                }                 
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
                    printf("true\n");
                } else {
                    printf("false\n");
                }              
                break;                            
            default:                
                printf("Invalid command.\n");
        }
    }
    return 0;
}
