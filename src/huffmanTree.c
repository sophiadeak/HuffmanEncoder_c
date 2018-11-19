/*
 * @file huffmanTree.c
 * @author Sophia Deak
 * @date Nov 17th 2018
 * @brief wrapper functions for building huffman tree and generating codebook
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffmanTree.h"
#include "nodeQueue.h"
#include "helpers.h"


Node * createTree(Queue **leafQueue){

    Queue *middleQueue = initializeEmptyQueue();


    while((*leafQueue)->head != NULL || middleQueue->head->next != NULL){

        Node *A; 
        Node *B;

        newnewAssignLowestNodes(&A, &B, *leafQueue, middleQueue);

        Node *M = createMiddleNode(A, B);
        enqueue(middleQueue, M);

        printf("loop happened\n");
        printQueue(*leafQueue);
        printf("mid queue\n");
        printQueue(middleQueue);

    }

    printf("printing final midqueue\n");
    printQueue(middleQueue);

    Node *x  = copyNode(middleQueue->head);

    printf("test %c %c %c\n", x->left->character, x->right->character, x->left->left->character); 



    deleteQueue(middleQueue);
    free(middleQueue);


    return x;
}



void printTree(Node *root){

    Node *theNode = root;

    if(theNode->character != '*'){
        printf("Node %c : %d \n", theNode->character, theNode->frequency);
        return;
    }

        printTree(theNode->left);
        printTree(theNode->right);
}


void grabEncoding(Node *root, int height, int *code){

    Node *theNode = root;

    if(theNode->character != '*'){
        printf("Node %c : %d \n", theNode->character, theNode->frequency);
        for(int j = 0; j < height ; j++){
            printf("%d", code[j]);
        }
        printf("\n");
        return;
    }

    code[height - 1] = 1;
    grabEncoding(theNode->right, height + 1, code);


    code[height - 1] = 0;
   grabEncoding(theNode->left, height + 1, code);
}

void createCodebook(Node *root, int height){

    Node *theNode = root;

    if(theNode->character != '*'){
        printf("Node %c : %d \n", theNode->character, theNode->frequency);
        return;
    }


    int leftCode[height + 1];
    leftCode[height - 1] = 0;
 
    int rightCode[height + 1];
    rightCode[height - 1] = 1;  


    grabEncoding(theNode->left, height+1, leftCode);

    grabEncoding(theNode->right, height + 1, rightCode); 

}


void deleteTree(Node *root){

    Node *theNode = root;

    if(theNode == NULL){
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    free(theNode);
    return;
}
