#include<stdio.h>
#include<stdlib.h>
  
/* structure for a node */
typedef struct db
{
    char drug[56];
    char type[26];
    //time_t dateOfExpiry;
    char manufacturer[56];
	char date[50];
    int quantity;
    float price;
    int isPrescription;
    struct db *next;
}
db_t,*pdb_t;

struct Node
{
	db_t data;
	struct Node* next;
};

typedef struct node node_t;
/* Function to insert a node at the beginning of a linked list */
void insertAtTheBegin(struct Node **start_ref, int data);
  
/* Function to bubble sort the given linked list */
void bubbleSort(struct Node *start);
  
/* Function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b);
  
/* Function to print nodes in a given linked list */
void printList(struct Node *start);
  
