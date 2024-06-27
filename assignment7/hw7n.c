// name: Yao Chong Chow
// email: chow.ya@northeastern.edu

// Hash table with doubly linked list for chaning/
#include <stdio.h>
#include <stdlib.h> 

struct bucket* hashTable = NULL; 
int BUCKET_SIZE = 10; 

// node struct
struct node {

    // Add your code here
    int key;
    int value;
    struct node* next;

};

// bucket struct
struct bucket{

    // Add your code here
    struct node* head;
    int count; 

};

// create a new node
struct node* createNode(int key, int value){

    // Add your code here
    struct node* newNode;

    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

//  hash function with %
int hashFunction(int key){
    return key % BUCKET_SIZE;
}

//  insert a new key
void add(int key, int value){
    int hashIndex = hashFunction(key);
    
    // Add your code here
    struct node* newNode = createNode(key, value);
    // when node is empty
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode; 
    }
    // when node has a key
    else{
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }

}

// remove a key
void remove_key(int key){
    int hashIndex = hashFunction(key);

    // Add your code here

    struct node* node;
    struct node* before;

    node = hashTable[hashIndex].head;

    if (node == NULL){
        printf("\nno key found");
        return;
    }
    while (node != NULL)
    {
        if (node->key == key){
            // change a pointer
            if (node == hashTable[hashIndex].head){
                hashTable[hashIndex].head = node->next;
            }
            else{
                before->next = node->next;
            }
            hashTable[hashIndex].count--;
            free(node);
            printf("\n[ %d ] is removed. \n", key);
            return;
        }
        before = node;
        node = node->next;
    }
    printf("\n[ %d ] is not found.\n", key);
    return;


}

// search a value using a key
void search(int key){
    int hashIndex = hashFunction(key);
    struct node* node = hashTable[hashIndex].head;

    // Add your code here
    if(node == NULL){
        printf("\nno key found. \n");
        return;
    }
    while (node != NULL)
    {
        if (node->key == key){
            printf("\nkey = [ %d ], value = [ %d ].\n", node->key, node->value);
            return;
        }
        node = node->next;
    }
    printf("\nno key found. \n");
    return;

}

void display(){
    struct node* iterator;

    printf("\n========= display start ========= \n");
    for (int i = 0; i<BUCKET_SIZE; i++){
        iterator = hashTable[i].head;
        printf("Bucket[%d] : ", i);
        while (iterator != NULL)
        {
            printf("(key: %d, val: %d)  <-> ", iterator->key, iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n========= display complete ========= \n");
}

int main(){
    hashTable = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));
    
    add(0, 1);
    add(1, 10);
    add(11, 12);
    add(21, 14);
    add(31, 16);
    add(5, 18);
    add(7, 19);

    display();

    remove_key(31);
    remove_key(11);

    display();

    search(11);
    search(1);
}
