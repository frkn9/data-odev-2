//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Mehmet Furkan Çetiner
//---Student Number: 150200073
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    //TODO
    this->head = NULL;                                      //initialize head to null
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    //TODO
    Node* curr = head;
    //if queue empty, newnode is head
    if(head == NULL) {                                      
        head = newnode;                               
        head->next = NULL;
    }
    //if newnode's value is  lower than head's value, newnode is the new head
    else if(head->token.val > newnode->token.val) {         
        head = newnode;
        newnode->next = curr;
    }
    //iterate until current position's next pointer is either null or larger than newnode
    //when iteration has stopped, place new node after the current position.
    else {
        while((curr->next != NULL) && (newnode->token.val >= curr->next->token.val)) {  
            curr = curr->next;                                                              
        }
        newnode->next = curr->next;             
        curr->next = newnode;                   
    }
    
    return;

};

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    //TODO    
    Node* curr = head;                           //use curr as temporary pointer for head node
    head = head->next;                           //head's next is the new head

    curr->next = NULL;                           //set the now old head's next to null, just in case
    return curr;                                 //return old head
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    //TODO
    root = NULL;                                                //initialize root to null
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    //TODO
    deleteTree(root);                                            //call deleteTree 
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    if(node == NULL)
        return;

    deleteTree(node->left);             //calls deleteTree recursively and traverses until a null child is 
    deleteTree(node->right);            //encountered, then deletes the node, after that moves on to the right  
    delete node;                        //sibling, traverses until null child is encountered, deletes the node
    return;                             //and then deletes the parent and repeats this process until everything
}                                       //is removed

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* curr1, Node* curr2){
   //TODO
   Node* par = new Node;
   par->next = NULL;
   
   if(curr1->token.val >= curr2->token.val){        //if curr1's val greater or equal curr1 is the right node of the parent
        par->right = curr1;
        par->left = curr2;
   }
   else if(curr2->token.val > curr1->token.val){    //if curr1's val is smaller curr1 is the left node of the parent
        par->right = curr2;
        par->left = curr1;
   }
    
   par->token.symbol = curr1->token.symbol + curr2->token.symbol;   //merging the nodes into a parent node
   par->token.val = curr1->token.val + curr2->token.val;
   return par;
   
};

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};