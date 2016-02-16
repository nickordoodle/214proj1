#include <stdlib.h>
#include "sorted-list.h"


int compareInts(void* firstArg, void * secondArg){
        int *firstInt = (int*)firstArg;
        int *secondInt = (int*)secondArg;
        int value = *firstInt-*secondInt;

        return value;

}



int compareFloats(float first, float second){

	return 0;
}

int compareStrings(char *first, char *second){

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
        printf("%d\n", ptr);


}


int main(int argc, char const *argv[])
{

	int test = 1;
        int test2 = 5;
        int *value = NULL;
        int *value2 = NULL;
        int success = -1;
        value = &test;
        value2 = &test2;

        SortedListPtr SLPtr = SLCreate (compareInts, destroyFunc);
        //printf("%d\n",SLPtr->data);
        //success = SLInsert(SLPtr,value);

        change(SLPtr, "Insert", value);
        //printf("%d",SLInsert(SLPtr,value));
        change(SLPtr, "Insert", value2);
        change(SLPtr, "Remove", value);

	return 0;
}
