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

void destroyTree(Node *node){

	if (node == NULL) return;
 
    /* first delete both subtrees */
    destroyTree(node->left);
    destroyTree(node->right);
   
    /* then delete the node */
    free(node);

}
/* Do null check on list, if not null then iterate
   through the list */
void SLDestroy(SortedListPtr list){

	destroyTree(list->head);
	
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

	Node *nodeParent = parent;
	void *nodeData = node->data;
	int compareVal = cf(data, nodeData);

    /* Empty tree, build here and successful insertion*/
    if(node == NULL){
        createNode(data, nodeParent);
        return 1;
    }

    /* Insert into left subtree */
    if(compareVal < 0){
    	nodeParent = node;
    	insertNode(cf, node->left, nodeParent, data);
    } 
    /* Insert into right subtree */
    else if (compareVal > 0){   
    	nodeParent = node;    
    	insertNode(cf, node->right, nodeParent, data);
    } 
    /* Duplicate found */
    else {
    	return 0;
    }
    

    return 0;
}

Node *minValueNode(Node* node)
{
    Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

/* Must evaluate all three cases when there is no children,
   one child or the most complex - two children */
int deleteNode(CompareFuncT cf, Node *root, void *data){

	int compareVal = cf(data, root->data);

    // base case
    if (root == NULL) return 0;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (compareVal < 0)
        deleteNode(cf, root->left, data);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (compareVal > 0)
        deleteNode(cf, root->right, data);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            Node *temp = root->right;
            temp->parent = root->parent;
            root->parent->left = temp;
            free(root);
            return 1;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            temp->parent = root->parent;
            root->parent->right = temp;
            free(root);
            return 1;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        Node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        
        root->data = temp->data;
 
        // Delete the inorder successor
        deleteNode(cf, root->right, temp->data);
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
		list->head = createNode(newObj, NULL);
		return 1;
	} 

	returnVal = insertNode(list->compare, list->head, list->head, newObj);

	return returnVal;
}


int SLRemove(SortedListPtr list, void *newObj){

	/* Look for node and delete, return 1 on success or 0 otherwise */	
	int returnVal = deleteNode(list->compare, list->head, newObj);

	return returnVal;
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
	Node *curr = iter->curr;

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