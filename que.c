#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

struct Component
{
	db_t details;
	int priority;
};
typedef struct Component compo_t;
struct node
{
	compo_t c;
	struct node *link;
};

typedef struct node node_t;
struct prio_queue
{
	node_t *head;
};
typedef struct prio_queue prio_t;
void init_queue(prio_t *p_queue);
void enque(prio_t* p_q,compo_t* c);
void deque(prio_t* p_q);
void disp(const prio_t* p_q);

void init_queue(prio_t *p_queue) 
{
	#if debug
	printf("init_queue_reached\n");
	#endif
	p_queue -> head = NULL;
	
	#if debug
	printf("inir_queue passed\n");
	#endif
}
void enque(prio_t* p_q,compo_t* com)
{
	#if debug
	printf("Enqueue reached\n");
	#endif
	node_t *temp = (node_t*)malloc(sizeof(node_t));
	strcpy(temp ->c.details.drug,com->details.drug);
	
	strcpy(temp ->c.details.type,com->details.type);
	strcpy(temp ->c.details.manufacturer,com->details.manufacturer);
	strcpy(temp->c.details.date,com->details.date);
	temp->c.details.isPrescription=com->details.isPrescription;
	temp->c.details.price=com->details.price;
	temp->c.details.quantity=com->details.quantity;
	
	temp->c.priority = com->priority;
	temp->link = p_q ->head;
	p_q ->head = temp;
}
/*
void deque(prio_t* p_q)
{
	if(p_q->head == NULL)
		printf("No elements in the Q to delete\n");
	else
	{
		node_t *present = p_q ->head; // present points to wherever head is pointing
		node_t *prev = NULL;
	// prev points to NULL initially. But later one before the present node
		int max = 0;
		node_t *prev_max = NULL; // link field of this points to the node with highest
		while(present != NULL)
		{
			if(present->c.priority >= max)
			{
				max = present->c.priority;
				prev_max = prev;
			}
			prev = present;
			present = present->link;
		}
		compo_t compo;// to store the details of removed node. Just for printing purpose
		if(prev_max != NULL)
		{
			node_t *temp = prev_max->link;
			prev_max->link = temp->link;
			strcpy(compo.details,temp->c.details);
			compo.priority = temp->c.priority;
			free(temp);
		}
		else
		{
			node_t *temp = p_q ->head;
			p_q->head = p_q ->head>link;
			strcpy(compo.details,temp->c.details);
			compo.priority = temp->c.priority;
			free(temp);
		}
		printf("Deleted component is %s with %d priority\n", compo.details, compo.priority);
	}
}
*/
void disp(const prio_t* p_q)
{
	node_t *p = p_q ->head;
	if(p == NULL)
	{
		printf("No elements in queue");
	}
	else
	{
		while(p != NULL)
		{
			printf("%s\t%s\t%s\t%s\t%d\t%.2f\t%d\n",p->c.details.drug,p->c.details.type,p->c.details.manufacturer,p->c.details.date,p->c.details.isPrescription,p->c.details.price,p->c.details.quantity);
			p = p->link;
		}
	}
}

struct Node
{
	db_t data;
	struct Node* next;
};

typedef struct Node node_t;
/* Function to insert a node at the beginning of a linked list */
void insertAtTheBegin(struct Node **start_ref, db_t data);
  
/* Function to bubble sort the given linked list */
void bubbleSort(struct Node *start);
  
/* Function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b);
  
/* Function to print nodes in a given linked list */
void printList(struct Node *start);
  
void getData(){
    FILE* fp = fopen("database.csv", "r");
	#if debug
	printf("\nFile Opens\n");
	#endif
	if (fp==NULL)
	{
		printf("File could not be opened\n");
		exit(1);
	}

    char line[100];
	while(fgets(line,100,fp)!=NULL)
	{
		#if debug
		printf("The while loop enters\n");
		#endif
		db_t c;
		char *drug=strtok(line,",");
		
		strcpy(c.drug,drug);
		char *type=strtok(NULL,",");
		strcpy(c.type,type);
		char *manufacturer=strtok(NULL,",");
		strcpy(c.manufacturer,manufacturer);
		char *date=strtok(NULL,",");
		strcpy(c.date,date);
		char *isPrescription=strtok(NULL,",");
		int isP=atoi(isPrescription);
		c.isPrescription=isP;
		char *cost=strtok(NULL,",");
		float price=strtof(cost,NULL);
		c.price=price;
		char *quan=strtok(NULL,",");
		int quantity=atoi(quan);
		c.quantity=quantity;
		}

}

void insertAtTheBegin(struct Node **start_ref, db_t data)
{
    struct Node *ptr1 = (struct Node*)malloc(sizeof(struct Node));
    ptr1->data = data;
    ptr1->next = *start_ref;
    *start_ref = ptr1;
}

void bubbleSort(struct Node *start)
{
    int swapped, i;
    struct Node *ptr1;
    struct Node *lptr = NULL;
  
    /* Checking for empty list */
    if (start == NULL)
        return;
  
    do
    {
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr)
        {
            if (ptr1->data.price > ptr1->next->data.price)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void swap(struct Node *a, struct Node *b)
{
    db_t temp = a->data;
    a->data = b->data;
    b->data = temp;
}