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

Node *createNode(void *newObj, Node *parent){


	Node *newNode = malloc(sizeof(Node));
	newNode->data = newObj;
	newNode->parent = parent;		
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

int insertNode(CompareFuncT cf, Node *node, Node *parent, void *data){

	Node *parent = parent;
	void *nodeData = node->data;
	int compareVal = cf(*data, *nodeData);

    /* Empty tree, build here and successful insertion*/
    if(node == NULL){
        createNode(data, parent);
        return 1;
    }

    /* Insert into left subtree */
    if(compareVal < 0){
    	parent = node;
    	insertElement(cf, node->left, parent, data);
    } 
    /* Insert into right subtree */
    else if (compareVal > 0){   
    	parent = node;    
    	insertElement(cf, node->right, parent, data);
    } 
    /* Duplicate found */
    else {
    	return 0;
    }
    

    return 0;
}

/* NOT COMPLETE */
int deleteNode(CompareFuncT cf, Node *node, void *data){


	void *nodeData = node->data;
	int compareVal = cf(*data, *nodeData);

    /* Empty tree, build here and successful insertion*/
    if(node == NULL){
        createNode(data);
        return 1;
    }

    /* Insert into left subtree */
    if(compareVal < 0){
       insertElement(cf, node->left, data);
    } 
    /* Insert into right subtree */
    else if (compareVal > 0){       
    	insertElement(cf, node->right, data);
    } 
    /* Duplicate found */
    else {
    	return 0;
    }
    

    return 0;
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

	int returnVal = 0;

	/* Empty tree, make new one */
	if(list->head == NULL){
		list->head = createNode(newObj);
		return 1;
	} 

	returnVal = insertNode(list->compare, list->head, newObj);

	return returnVal;
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


	SortedListIteratorPtr listPtr = (SortedListIteratorPtr) malloc(sizeof(struct SortedListIterator));

	listPtr->curr = list->head;

	if(list->head == NULL)
		listPtr->isFinished = 1;
	else
		listPtr->isFinished = 0;

	return listPtr;

}


void SLDestroyIterator(SortedListIteratorPtr iter){

	iter->curr = NULL;
	free(iter->curr);
	free(iter);
	
}

/* Given the iterators current Node, traverse
   right if possible, then left, or return current value */

void * SLNextItem(SortedListIteratorPtr iter){

	void *data = NULL;

	/* Visit current */
	if(curr->right == NULL && curr->left == NULL)
		data = iter->curr->data;
	/* Visit right */
	else if (curr->left == NULL)
		data = iter->curr->right->data;
	/* Visit left */
	else
		data = iter->curr->left->data;

	return data;


}

void * SLGetItem( SortedListIteratorPtr iter ){

	void *data = iter->curr->data;
	return data;

}