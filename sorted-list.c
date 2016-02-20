#include <stdlib.h>
#include <stdio.h>
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

void printTree(Node *node){/*created for testing purposes only*/
        if(node->left != NULL)
                printTree(node->left);
        if(node -> right != NULL)
                 printTree(node->right);
        return;
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
    newNode->visited = 0;
	newNode->parent = parent;		
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}
/*What is the purpose of parent here?*/
int insertNode(CompareFuncT cf, Node *node, Node *parent, void *data){

	Node *nodeParent = parent;
	void *nodeData = node->data;
	int compareVal = cf(data, nodeData);

    int returnVal = 0;

    /* Empty tree, build here and successful insertion*/
    if(node == NULL){ /*don't think this is needed anymore*/
        node = createNode(data, nodeParent);
        return 1;
    }

    /* Insert into left subtree */
    if(compareVal < 0){
    	/*nodeParent = node;*/
    	if(node -> left  == NULL){
                node -> left = createNode(data, nodeParent);
                returnVal = 1;
        } else{
            returnVal = insertNode(cf, node->left, nodeParent, data);

        }
	
    } 
    /* Insert into right subtree */
    else if (compareVal > 0){   
    	/*nodeParent = node;   */
    	if(node -> right == NULL){
                node -> right = createNode(data, nodeParent);
                returnVal = 1;
        } else{
           returnVal = insertNode(cf, node->right, nodeParent, data);
 
        }
    	
    } 
    /* Duplicate found */
    else {
    	returnVal = 0;
    }
    

    /* CAUSING UNWANTED BEHAVIOR BECAUSE OF RECURSION CALLS */
    return returnVal;
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
   one child or the most complex - two children
   direction is negative if it came from the left side of its part and positive if it came from the right side*/
int deleteNode(CompareFuncT cf, Node *root, void *data, int direction){
    /* base case*/
    if (root == NULL) return 0;
    
    int compareVal = cf(data, root->data);
    int returnVal = 0;
 
    /* If the key to be deleted is smaller than the root's key,
     then it lies in left subtree*/
    if (compareVal < 0)
        returnVal = deleteNode(cf, root->left, data, compareVal);
 
    /* If the key to be deleted is greater than the root's key,
     then it lies in right subtree*/
    else if (compareVal > 0)
        returnVal = deleteNode(cf, root->right, data, compareVal);
 
    /*if key is same as root's key, then This is the node
     to be deleted*/
    else
    {
        /*node with only one child or no child*/
        if (root->left == NULL)
        {
            if(root->right != NULL){
                if(direction < 0){
                        Node *temp = root->right;
                        temp->parent = root->parent;
                        root->parent->left = temp;
                }
                else if(direction > 0){
                        Node *temp = root->right;
                        temp->parent = root->parent;
                        root->parent->left = temp;
                }else{
                        Node *temp = minValueNode(root->right);

                        root->data = temp->data;

                        returnVal = deleteNode(cf, root->right, temp->data, 0);
                }
            }
            free(root);
            return 1;
        }
        else if (root->right == NULL)
        {
            if(root->left != NULL){
                       if(direction < 0){
                               Node *temp = root->left;
                               temp->parent = root->parent;
                               root->parent->left = temp;
                        }
                        else if(direction > 0){
                                Node *temp = root->left;
                                temp->parent = root->parent;
                                root->parent->left = temp;
                        }else{
                                Node *temp = root->left; /*maxValueNode(root->left);*/
                                while(temp->right != NULL){
                                        temp = temp->right;
                                }

                                root->data = temp->data;

                                returnVal = deleteNode(cf, root->right, temp->data, 0);
                        }
                }
            free(root);
            return 1;
        }
 
        /* node with two children: Get the inorder successor (smallest
         in the right subtree)*/
        Node* temp = minValueNode(root->right);
 
        /* Copy the inorder successor's content to this node*/
        
        root->data = temp->data;
 
        /*Delete the inorder successor*/
        returnVal = deleteNode(cf, root->right, temp->data, 0);
    }
    

    return returnVal;
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
	
	printTree(list-> head);
        printf("\n");

	return returnVal;
}


int SLRemove(SortedListPtr list, void *newObj){

	/* Look for node and delete, return 1 on success or 0 otherwise */	
	int returnVal = deleteNode(list->compare, list->head, newObj, 0);

	return returnVal;
}


SortedListIteratorPtr SLCreateIterator(SortedListPtr list){


	SortedListIteratorPtr listPtr = (SortedListIteratorPtr) malloc(sizeof(struct SortedListIterator));

	listPtr->head = list->head;
    listPtr->curr = list->head;
    listPtr->type = 0;

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

    Node *head = iter->head;
	Node *curr = iter->curr;
    void *dataOutput = iter->curr->data;

    /* Need a NULL check here */

    /*Visit Right */
    if(curr->right != NULL){

        if(!curr->right->visited && 
            (curr->right->left != NULL 
                &&
            !curr->right->left->visited)){
        
            curr = curr->right;
            iter->curr = curr;
            dataOutput = SLNextItem(iter);
        } 
    } 
    /*Visit Current */
    else if(!curr->visited){
        dataOutput = SLGetItem(iter);

    } 
    /*Visit Left */
    else if(curr->left != NULL){

        if(!curr->left->visited){
            curr = curr->left;
            iter->curr = curr;
            dataOutput = SLNextItem(iter);           
        }

    }


    /*Reset current for future operations */
    iter->curr = head;
	return dataOutput;
}

/* Used as helper function in SLNextItem */ 
void * SLGetItem( SortedListIteratorPtr iter ){

    /* Account for NULL values */

    iter->curr->visited = 1;
	return iter->curr->data;

}
