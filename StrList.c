#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

/********************************************************************************
 *
 * A StrList library implementation.
 *struct _StrListpredictable ways when the system memory runs
 * out.
 *
 ********************************************************************************/

struct _StrList {
    char* data;             // Data part of the node, can store a string word.
    struct _StrList* next;  // Pointer to the next node in the list
};

/* helper functions*/
void freeNodeData(StrList* strList) {
    if (strList != NULL) {
        free(strList->data);
        strList->data = NULL;         
    }
}

void freeTheWholeList(StrList* strList) {
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

void removeNode(StrList** prevNode, StrList** currNode, int size) {
    StrList* prev = *prevNode;
    StrList* strList = *currNode;

    if (prev != NULL) {
        prev->next = strList->next;
        if (size == 1) {
            freeNodeData(strList); // instead of free memory of the last one.            
        } else {                   
            StrList_free(strList);        
        }
        *currNode = prev; // strList = prev;
    } else {
        // we should remove the first element.        
        if (size == 1) {
            freeNodeData(strList); // instead of free memory of the last one.            
        } else {
            // keep the current list head.
            // set the list head data to be the next node data.
            // then, free the next node data.                        
            StrList* nextNode = strList->next;
            char* swapValue = strList->data;
            strList->data = nextNode->data;
            strList->next = nextNode->next;
            nextNode->data = swapValue; // swap pointers, needed to free memory correctly.
            StrList_free(nextNode);
        }
    }
}

char* getMinimumOfStrList(StrList* strList)
{
    if (strList == NULL || strList->data == NULL) {
        return NULL;
    }
    
    StrList* head = strList;
    char *minValue = strList->data;
    int index = 0;
    int count = 0;
    while (strList->next != NULL)
    {
        strList = strList->next;
        count++;
        if (strcmp(strList->data, minValue) < 0)
        {
            minValue = strList->data;
            index = count;
        }
    }
    minValue = strdup(minValue); // the previous minValue will be freed by the next command.
    StrList_removeAt(head, index);
    return minValue;
}

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_alloc() {
    StrList* strList = (StrList*)malloc(sizeof(StrList));
    strList->data = NULL;
    strList->next = NULL;
    return strList;
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* strList) {
    if (strList != NULL) {                 
        // free data and then node itself.
        free(strList->data);
        free(strList);       
    }
}

size_t StrList_size(const StrList* strList) {
    int count = 0;
    while (strList != NULL && strList->data != NULL) {
        strList = strList->next;            
        count++;        
    }
    return count;
}

/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* strList,
					  const char* data) {
    if (strList != NULL) {
        // check the first node data
        // if it is null, then init its data.
        if (strList->data == NULL) {
            strList->data = strdup(data);
        } else {
            StrList_insertAt(strList, data, StrList_size(strList));            
        }
    }    
}

/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList* strList, 
	const char* data,int index) {

    // Check if the index is valid
    int size = StrList_size(strList);
    if (index < 0 || index > size) {
        return;
    }
    
    // special case: the very first insertion.
    if (size == 0 && strList != NULL) {
        strList->data = strdup(data);
        return;
    }

    int count = 0;
    StrList* prev = NULL;
    
    while (strList != NULL) {
        if (index == 0) {
            StrList* newNode = StrList_alloc();
            newNode->data = strList->data;
            newNode->next = strList->next;
            strList->next = newNode;
            strList->data = strdup(data);
            break;
        }

        if (index == count) {
            StrList* newNode = StrList_alloc();
            newNode->next = strList;
            newNode->data = strdup(data);
            prev->next = newNode;
            break;
        }

        prev = strList;
        strList = strList->next;    
        count++;
    }
    // a special case: we add a node to the end of the list.
    if (index == size && prev != NULL) {
        StrList* newNode = StrList_alloc();
        newNode->next = NULL;
        newNode->data = strdup(data);
        prev->next = newNode;
    }    
}

/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* StrList) {
    if (StrList != NULL) {
        return StrList->data;
    }
    return NULL;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* strList) {
    if (strList != NULL) {
        // go to the last node.
        while (strList != NULL) {
            if (strList->data != NULL) {
                printf("%s\n", strList->data);
            }
            strList = strList->next;            
        }
    }
}
/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList* strList,int index) {
    // Check if the index is valid
    int size = StrList_size(strList);
    if (index < 0 || index >= size) {
        return;
    }
    
    int count = 0;    

    while (strList != NULL) {
        if (index == count) {
            printf("%s\n", strList->data);
            break;
        }

        strList = strList->next;    
        count++;
    }
}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* strList) {
    int charsLen = 0;
    while (strList != NULL) {
        charsLen += strlen(strList->data);
        strList = strList->next;            
    }
    return charsLen;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* strList, const char* data) {
    int shows = 0;
    if (data != NULL) {
        while (strList != NULL) {
            if (strcmp(strList->data, data) == 0) {
                shows++;
            }
            strList = strList->next;            
        }
    }
    return shows;
}

/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList* strList, const char* data) {  
    StrList* head = strList;    
    StrList* prev = NULL;
    if (data != NULL) {
        while (strList != NULL) {        
            if (strcmp(strList->data, data) == 0) {
                removeNode(&prev, &strList, StrList_size(head));                
                if (strList->data == NULL) {
                    // this is the indication the linked list is empty
                    return;
                }
            }
            prev = strList;
            strList = strList->next;            
        }
        // special case: strList={"aa","aa"}, data="aa"
        if (prev != NULL && strcmp(prev->data, data) == 0) {
            removeNode(&prev, &prev, StrList_size(head));
        }
    }
}

/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* strList, int index) {
    StrList* prev = NULL;

    // Check if the index is valid
    int size = StrList_size(strList);
    if (index < 0 || index >= size) {
        return;
    }
    
    int count = 0;    

    while (strList != NULL) {
        if (index == count) {
            removeNode(&prev, &strList, size);            
            break;
        }
        prev = strList;
        strList = strList->next;    
        count++;
    }
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2) {
    // Iterate over both lists simultaneously
    while (StrList1 != NULL && StrList2 != NULL) {
        // Compare the data of the two nodes
        if (strcmp(StrList1->data, StrList2->data) != 0) {
            // Data is not equal, return 0
            return 0;
        }
        // Move to the next node in both lists
        StrList1 = StrList1->next;
        StrList2 = StrList2->next;
    }

    // If both pointers are NULL, lists are of the same length and all elements matched
    if (StrList1 == NULL && StrList2 == NULL) {
        return 1; // Lists are equal
    } else {
        return 0; // One list is longer than the other
    }
}

/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* strList) {
    if (strList != NULL) {
        StrList* clone = StrList_alloc();
        while (strList != NULL) {
            StrList_insertLast(clone, strList->data);
            strList = strList->next;
        }
        return clone;
    }
    return NULL;
}

/*
 * Reverces the given StrList. 
 */
void StrList_reverse(StrList* strList) {
    StrList* head = strList;
    if (strList == NULL) {
        return;
    }
    // create a new list with reverted order.
    StrList* newList = StrList_alloc();
    StrList* newListHead = newList;
    while (strList != NULL) {
        StrList_insertAt(newList, strList->data, 0);
        strList = strList->next;
    }
    strList = head;
    // copy values from one list to another.
    // Iterate over both lists simultaneously
    while (strList != NULL && newList != NULL) {
        freeNodeData(strList);
        strList->data = strdup(newList->data);
        // Move to the next node in both lists
        strList = strList->next;
        newList = newList->next;
    }
    // free the new list memory.
    freeTheWholeList(newListHead);
}

/*
 * Sort the given list in lexicographical order 
 */
void StrList_sort(StrList* strList) {
    // we clone the list.
    // we create a new list.
    // as long as the cloned list is not null,
    // we find the minimum value in the cloned list
    // remove its node from there and append its value to the new list        
    if (strList == NULL) {
        return;
    }    
    StrList* cloned = StrList_clone(strList);

    // create a new list and insert values in a sorted manner by ascending order.
    StrList* newList = StrList_alloc();
    StrList* newListHead = newList;

    while (cloned != NULL && cloned->data != NULL) {
        char* minValue = getMinimumOfStrList(cloned);
        StrList_insertLast(newList, minValue);
        free(minValue);
    }
    StrList_free(cloned);    

    // copy values from one list to another.
    // Iterate over both lists simultaneously
    while (strList != NULL && newList != NULL) {
        freeNodeData(strList);
        strList->data = strdup(newList->data);
        // Move to the next node in both lists
        strList = strList->next;
        newList = newList->next;
    }
    // free the new list memory.
    freeTheWholeList(newListHead);
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* strList) {
    // clone the list and sort it
    // compare the cloned with the original
    // if they are the same, return 1.
    // otherwise, 0.
    if (strList == NULL) {
        return 0;
    }    
    StrList* cloned = StrList_clone(strList);
    StrList_sort(cloned);
    int result = StrList_isEqual(strList, cloned);
    // free the cloned list memory.
    freeTheWholeList(cloned);
    return result;
}

