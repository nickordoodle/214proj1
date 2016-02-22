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

void destroyFunc(void *data){	

        free(data);
	return;
}
/* helper function for easy insertion and deletion*/
void change(SortedListPtr SLPtr, char * type, int * ptr){
        int success  = -1;

        if(*type == 'i' || *type == 'I')
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


void testRegularTree(){

        int integerValues[] = {10, 5, 643, 40, 72, 100, 4320, 3, 54, 43, 9923};
        int i, *ptr[12];

        SortedListPtr SLPtr = SLCreate (compareInts, destroyFunc);

        SortedListIteratorPtr iter;

        /* Add all integers to Sorted List */
        for ( i = 0; i < 11; i++) {
                ptr[i] = &integerValues[i]; /* assign the address of integer. */
                change(SLPtr, "Insert", ptr[i]);

        }

        iter = SLCreateIterator(SLPtr);

        for(i = 0; i < 11; i++){
                printf("%d  ",*((int *)SLNextItem(iter)));

        }

        printf("\n");

        SLDestroy(SLPtr);
        SLDestroyIterator(iter);


}

void testTreeWithDuplicates(){


        int integerValues[] = {10, 9923, 5, 643, 40, 5, 72, 72, 100, 10, 4320, 3, 54, 43, 4320, 9923};
        int i, *ptr[17];

        SortedListPtr SLPtr = SLCreate (compareInts, destroyFunc);

        SortedListIteratorPtr iter;

        /* Add all integers to Sorted List */
        for ( i = 0; i < 16; i++) {
                ptr[i] = &integerValues[i]; /* assign the address of integer. */
                change(SLPtr, "Insert", ptr[i]);

        }

        iter = SLCreateIterator(SLPtr);

        for(i = 0; i < 11; i++){
                printf("%d  ",*((int *)SLNextItem(iter)));

        }

        printf("\n");

        SLDestroy(SLPtr);
        SLDestroyIterator(iter);
}

void testMultipleIterators(){

        int integerValues[] = {10, 5, 643, 40, 72, 100, 4320, 3, 54, 43, 9923};
        int i, *ptr[12];

        SortedListPtr SLPtr = SLCreate (compareInts, destroyFunc);

        SortedListIteratorPtr iter;
        SortedListIteratorPtr iterTwo;

        /* Add all integers to Sorted List */
        for ( i = 0; i < 11; i++) {
                ptr[i] = &integerValues[i]; /* assign the address of integer. */
                change(SLPtr, "Insert", ptr[i]);

        }

        iter = SLCreateIterator(SLPtr);
        iterTwo = SLCreateIterator(SLPtr);

        for(i = 0; i < 11; i++){
                printf("%d  ",*((int *)SLNextItem(iter)));
                printf("%d  ",*((int *)SLNextItem(iterTwo)));

        }

        printf("\n");

        SLDestroy(SLPtr);
        SLDestroyIterator(iter);
        SLDestroyIterator(iterTwo);

}

void testRemove(){

        int integerValues[] = {10, 5, 643, 40, 72, 100, 4320, 3, 54, 43, 9923};
        int i, *ptr[12];

        SortedListPtr SLPtr = SLCreate (compareInts, destroyFunc);

        SortedListIteratorPtr iter;

        /* Add all integers to Sorted List */
        for ( i = 0; i < 11; i++) {
                ptr[i] = &integerValues[i]; /* assign the address of integer. */
                change(SLPtr, "Insert", ptr[i]);

        }

        iter = SLCreateIterator(SLPtr);

        change(SLPtr, "Remove", ptr[10]);
        change(SLPtr, "Remove", ptr[4]);
        change(SLPtr, "Remove", ptr[9]);


        printf("%d  ",*((int *)SLNextItem(iter)));

        
        printf("\n");

        SLDestroy(SLPtr);
        SLDestroyIterator(iter);
}

void testInsertAndRemoveWithIterator(){


        int integerValues[] = {10, 5, 643, 40, 72, 100, 4320, 3, 54, 43, 9923};
        int i, *ptr[12];

        SortedListPtr SLPtr = SLCreate (compareInts, destroyFunc);

        SortedListIteratorPtr iter;

        /* Add all integers to Sorted List */
        for ( i = 0; i < 11; i++) {
                ptr[i] = &integerValues[i]; /* assign the address of integer. */
                change(SLPtr, "Insert", ptr[i]);

        }

        iter = SLCreateIterator(SLPtr);

        change(SLPtr, "Remove", ptr[10]);//Remove 9923
        change(SLPtr, "Remove", ptr[4]);//Remove 72
        change(SLPtr, "Remove", ptr[9]);// Remove 43


        printf("%d  ",*((int *)SLNextItem(iter)));

        change(SLPtr, "Remove", ptr[5]);//Remove 100
        printf("%d  ",*((int *)SLNextItem(iter)));

        change(SLPtr, "Insert", ptr[4]);//Insert 72

        printf("%d  ",*((int *)SLNextItem(iter)));
        printf("%d  ",*((int *)SLNextItem(iter)));


        printf("\n");

        SLDestroy(SLPtr);
        SLDestroyIterator(iter);
}
/* Used for testing integer values */
void testInts(){

        testRegularTree();

        testTreeWithDuplicates();

        testMultipleIterators();

        testRemove();

        testInsertAndRemoveWithIterator();
}


int main(int argc, char const *argv[]) {


        testInts();

	return 0;
}
