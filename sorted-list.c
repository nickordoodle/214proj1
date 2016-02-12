#include <stdlib.h>
#include "sorted-list.h"

/* Allocate memory, set data fields to appropriate values*/
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){

	SortedListPtr SLPtr = (SortedListPtr) malloc(sizeof(struct SortedList));

	if(SLPtr == NULL) {
		return NULL;
	}

	SLPtr->head = NULL;
	SLPtr->compare = cf;
	SLPtr->destroy = df;

	
	return SLPtr;
}

/* Do null check on list, if not null then iterate
   through the list */
void SLDestroy(SortedListPtr list){

	Node *temp = list->head;
	Node *next = temp->next;

	if(list == NULL){
		return;
	} 

	while(temp != NULL){
		free(temp);
		temp = next;
	}

}

/* Uses the compare functions to determine where
   to place the data 

   MEAT OF THE PROGRAM.  Need to determine how to
   sort the list while inserting new items.  We
   could just iterate through each time but that is
   inefficient.  Problem is that sorting algorithms
   are harder to do with linked lists. So either
   regular iteration or change implementation to use
   linked lists. */
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