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

Node *createNode(void *newObj){


	Node *newNode = malloc(sizeof(Node));
	newNode->data = newObj;
	newNode->next = NULL;
	newNode->prev = NULL;

	return newNode;
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

	Node *temp = list->head;
	Node *prev = temp->prev;
	Node *next = temp->next;

	void *data = temp->data;

	int compareVal = list->compare(newObj, data);

	Node *newNode = createNode(newObj);

	/* Front of list */
	if(temp == NULL){
		list->head = newNode;
		return 1;
	} else if(next == NULL && compareVal >= 0){
		list->head = newNode;
		newNode->next = temp;
		temp->prev = newNode;
		return 1;
	}

	while(temp != NULL){

		/* New object found right place */
		if(compareVal >= 0){
			newNode->next = temp;
			prev->next = newNode;
			temp->prev = newNode;
			newNode->prev = prev;
			return 1;
		}

		temp = next;
		next = temp->next;
	}


	return 0;
}


int SLRemove(SortedListPtr list, void *newObj){

	Node *temp = list->head;
	Node *prev = temp->prev;
	Node *next = temp->next;

	void *data = temp->data;

	int compareVal = list->compare(newObj, data);
	
	/* Front of list */
	if(temp == NULL){
		return 1;
	} else if(next == NULL && !compareVal){
		list->head = NULL;
		free(temp);
		return 1;
	}

	while(temp != NULL){

		/* Object data found, delete here */
		if(!compareVal){
			prev->next = next;
			next->prev = prev;
			free(temp);
			return 1;
		}

		temp = next;
		next = temp->next;
	}

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