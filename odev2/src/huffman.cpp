//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Mehmet Furkan Çetiner  
//---Student Number: 150200073
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alphabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//

/*new function*/
//create new node, assign symbol and value, return the address
Node* createNode(string sym, int value){
    Node* myNode = new Node;                
    myNode->token.symbol = sym;
    myNode->token.val = value;
    myNode->next = NULL;
    return myNode;
}
/*new function*/

//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();
    //DO NOT CHANGE THIS
    unsigned int i = 0;
    int freq = 1;
    char c = sortedKey[i];                      //initialize c with the first char of sortedKey

    //i + 1 because we don't make comparison for the first char since we initialized c
    while(sortedKey.size() > i + 1 ) {                             
        while(c == sortedKey[i+1] && sortedKey.size() > i + 1 ) {   //keep iterating on the string until c and encountered character are different or it's the end of the string 
            freq++;
            i++;
        }
        //convert c to string, create new node and enqueue immediately
        queue.enque(createNode(string(1,c), freq));                                  
        c = sortedKey[i+1];
        freq = 1;                                                   //freq = 1 for the new character
        i++;
    }
    
    
    
    
    //TODO
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
//Find frequency takes care of creating the queue, we just need to dequeue twice and
//merge the nodes then enqueue the new node until queue has only one node, the top node that includes 
//all characters of the huffman tree. Then we dequeue one last time and assign it to root of the huffman tree.
void Huffman::createHuffmanTree(){
    //TODO
    findFrequency();       
    Node* temp;
    while(queue.head->next != NULL) {
        temp = huffmanTree.mergeNodes(queue.dequeue(), queue.dequeue());
        queue.enque(temp);
    }
    huffmanTree.root = queue.dequeue();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//

/*new function*/
//checks if given char is on the left or the right child
char peek(Node* peekRoot, char peekChar){
    
    string str = peekRoot->left->token.symbol;
    for(unsigned int i = 0; i < str.size(); i++) {  //search for peekChar on the left child, if it finds return 0 else return 1 
        if(peekChar == str[i]) 
            return '0';            
    }
    return '1';
}
/*new function*/

string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    //TODO
    string str = "";
    char ch;
    //concenate 0 if the left child contains the tokenChar or 1 if the right does, traverse to the appropriate child until null child encountered
    while(traverse->left != NULL && traverse->right != NULL) {  
        ch = peek(traverse, tokenChar);
        if(ch == '0')
            traverse = traverse->left;
        else if(ch == '1')
            traverse = traverse->right;
        str += ch;  
    }
    tokenBinary = str;
    return str;

    
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
//get token binary, concenate it to encodedBinaryPassword and 
//convert size to string and concenate to encodedValPassword
void Huffman::encodePassword(string password){
    //TODO
    string tokBin;
    encodedBinaryPassword = "";
    encodedValPassword = "";
    for(unsigned int i = 0; i < password.size(); i++) {
        tokBin = getTokenBinary(password[i], huffmanTree.root, tokBin);
        encodedBinaryPassword += tokBin;
        encodedValPassword += to_string(tokBin.size());
    }
    return; 
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
//for each token iterate until encodedValPassword[i] times, concenate the segment of the
//encodedBinaryPassword to "toDecode" and decode it with decodeToken function. decodeToken takes
//care of concenating the decoded char to the decodedPassword string 
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    //TODO
    decodedPassword = "";
    string toDecode = "";

    int i = 0;
    for(unsigned int n = 0; n < encodedValPassword.size(); n++) {
        for(int k = 0; k < (encodedValPassword[n] - '0'); k++, i++) {
            toDecode += encodedBinaryPassword[i];
        }
        decodeToken(toDecode);
        toDecode = "";
    }
    return;
    

    
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
//read encoded token char by char, traverse left if it's 0 and 1. repeat encodedToken.size() times.
//then concenate the found symbol to decodedPassword
void Huffman::decodeToken(string encodedToken){
    //TODO
    Node* temp = huffmanTree.root;
    for(unsigned int i = 0; i < encodedToken.size(); i++) {
        switch (encodedToken[i])
        {
        case '0':
            temp = temp->left;
            break;
        case '1':
            temp = temp->right;
            break;
        default:
            break;
        }
    }
    decodedPassword += temp->token.symbol;


};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};