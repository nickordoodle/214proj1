#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sorted-list.h"


int compareInts(void* firstArg, void * secondArg){
        int *firstInt = (int*)firstArg;
        int *secondInt = (int*)secondArg;

        if(*firstInt > *secondInt)
                return 1;
        else if(*firstInt < *secondInt)
                return -1;


        return 0;

}



int compareFloats(float first, float second){

	return 0;
}

int compareStrings(char *first, char *second){

        int compareVal = strcmp(first, second);

        if(compareVal > 0){
                return 1;
        } else if(compareVal < 0){
                return -1;
        } else {
                return 0;
        }

	return 0;
}

int compareStructs(int addressOne, int addressTwo){

	return 0;
}

void destroyFunc(){


	return;
}
/* helper function for easy insertion and deletion*/
void change(SortedListPtr SLPtr, char * type, int * ptr){
        int success  = -1;

        if(*type == 'i' || *type == 'I')//insert check
                success = SLInsert(SLPtr,ptr);
        if(*type == 'r' || *type == 'R')
                success = SLRemove(SLPtr,ptr);

        printf("%s", type);

        if(success == 1)
                printf(" successful: ");
        else if(success == -1)
                printf("error\n");
        else
                printf(" unsuccessful: ");
        printf("%d\n", *ptr);


}

/* Outputs values from tree */
void outputTree(SortedListIteratorPtr iter){


}

/* Used for testing integer values */
void testInts(){


        int integerValues[] = {10, 32, 12, 5, 643, 3,47, 56, 3, 554, 49, 6, 99, 5};
        int i, *ptr[13];

        SortedListPtr SLPtr = SLCreate (compareInts, destroyFunc);

        SortedListIteratorPtr iter = SLCreateIterator(SLPtr);
        iter->type = 'i';

        /* Add all integers to Sorted List */
        for ( i = 0; i < 13; i++) {
                ptr[i] = &integerValues[i]; /* assign the address of integer. */
                change(SLPtr, "Insert", ptr[i]);

        }

        /* Test removing specific elements */
        change(SLPtr, "Remove", ptr[i + 5]);
        change(SLPtr, "Remove", ptr[i + 8]);
        

        SLDestroy(SLPtr);


}

/* Used to test strings 
void testStrings(){

        char* stringValues = {"apple", "pineapple", "oranges", "tomatoes", "apple", "potato"};
        int i, *ptr[sizeof(integerValues)];

        SortedListPtr SLPtr = SLCreate (compareStrings, destroyFunc);

        SortedListIteratorPtr iter = SLCreateIterator(SLPtr);
        iter->type = 'i';
        */
        /* Add all integers to Sorted List 
        for ( i = 0; i < 5; i++) {
                ptr[i] = &integerValues[i]; 
                change(SLPtr, "Insert", ptr[i]);

        }*/

        /* Test removing specific elements */
        //change(SLPtr, "Remove", ptr[i + 5]);
        //change(SLPtr, "Remove", ptr[i + 8]);
        

        //SLDestroy(SLPtr);


//} 


int main(int argc, char const *argv[]) {


        testInts();


	return 0;
}
