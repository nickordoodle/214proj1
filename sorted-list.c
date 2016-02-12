#include <stdlib.h>
#include "sorted-list.h"


SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){

	return NULL;
}


void SLDestroy(SortedListPtr list){

	return;

}


int SLInsert(SortedListPtr list, void *newObj){

	return 0;
}


int SLRemove(SortedListPtr list, void *newObj){

	return 0;
}


SortedListIteratorPtr SLCreateIterator(SortedListPtr list){

	return NULL;

}


void SLDestroyIterator(SortedListIteratorPtr iter){

	return;

}


void * SLNextItem(SortedListIteratorPtr iter){

	return iter;


}

void * SLGetItem( SortedListIteratorPtr iter ){

	return iter;


}