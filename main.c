#include <stdlib.h>
#include "sorted-list.h"


int compareInts(int first, int second){

	return 0;

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


int main(int argc, char const *argv[])
{

	SortedListPtr SLPtr = SLCreate (compareInts, destroyFunc);
       
        SLInsert(SLPtr,value);
     


        printf("%d\n",SLRemove(SLPtr,value));



	return 0;
}
