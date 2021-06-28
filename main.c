// including necessary library files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define debug 1
#define TRY(a)  if (!(a)) {perror(#a);exit(1);}

// defining database functionalities
#define DB "database.csv"


// defining a struct for the management system
typedef struct db
{
    char drug[56];
    char type[26];
    time_t dateOfExpiry;
    char manufacturer[56];
    int quantity;
    float price;
    bool isPrescription;
    struct db *next;
}
db_t,*pdb_t;



db_t* getData()
{
	FILE* fp = fopen("database.csv", "r");
	#if debug
	printf("\nFile Opens\n");
	#endif
	if (fp==NULL)
	{
		printf("File could not be opened\n");
		return NULL;
	}
	char line[100];
	db_t *head;
	while(fgets(line,100,fp)!=NULL)
	{
		#if debug
		//printf("%s",typeof(head));
		#endif
		char *drug=strtok(line,",");
		char *type=strtok(NULL,",");
		char *manufacturer=strtok(NULL,",");
		char *isPrescription=strtok(NULL,",");
		int isP=atoi(isPrescription);
		char *cost=strtok(NULL,",");
		float price=strtof(cost,NULL);
		char *quan=strtok(NULL,",");
		int quantity=atoi(quan);
		head->drug=drug;
		#if debug
		printf("line=%s\n",head->drug);
		#endif
	}
	return head;
}

// enum for commands
enum {ADD, PRINT, READLINE, READ, SORT, DESTROY};

// data access object(DAO)
static pdb_t dao (int cmd, FILE *f, pdb_t db);

int main(int argc,char** argv){
    char buf[100];
    #if debug
    printf("%s\n",argv[1]);
    #endif
    // defining the database commands
    const char *commands[] = {"-a", "-p", "-s", "-m", "-t" , "-d", NULL};
    // setting up the db and its locations
    db_t db;
    db.next = NULL;
    pdb_t dbList;
    int i;
    FILE *f;

    TRY (f=fopen(DB, "a+"));

// printing usage menu if the CL argument count is less than 2 ie. if the program is just launched
    if (argc<2){
        usage: printf("[commands]\n"
        "-a add to database\n"
        "-d delete record\n"
        "-s sort records by date of expiry\n"
        "-m sort records by manufacturer\n"
        "-t sort records by type\n"
        "-p find last added record \n");
        fclose (f);
        return 0;
    }

// defining cases for command line inputs
    for (i=0;commands[i]&&strcmp(argv[1],commands[i]);i++);
    switch (i) {
        case ADD:
            #if debug
            // printf("-a  Create a new entry.\n");
            #endif
            printf("Name           :");if((scanf(" %s[^\n]",db.drug     ))<0)break;
            printf("Type           :");if((scanf(" %s[^\n]",db.type))<0)break;
            printf("Manufacturer   :");if((scanf(" %s[^\n]",db.manufacturer ))<0)break;
            
			// printf("Date of expiry :");if((scanf(" %s[^\n]",buf          ))<0)break;
            printf("Is prescription(1/0):");if((scanf(" %d[^\n]",&db.isPrescription))<0)break;
            printf("Price          :");if((scanf(" %f[^\n]",&db.price))<0)break;
            printf("Quantity       :");if((scanf(" %d[^\n]",&db.quantity))<0)break;

            dao (ADD,f,&db);
            break;

        case PRINT:
            // printf ("-p  Print the latest entry.\n");
            while (!feof(f)){
                #if debug
                printf("This works loop enters\n Working on it\n");
                #endif

                 dao (PRINT,f,&db);
                 exit(0);
            }
            break;

        default: {
            printf ("Unknown command: %s.\n",(strlen(argv[1])<10?argv[1]:NULL));
            exit(0);
        }
    }

    fclose (f);
    return 0;

}

static pdb_t dao (int cmd, FILE *f, pdb_t in_db) {
pdb_t *pdb=NULL,rec=NULL,hd=NULL;
    int i=0, ret;
    char buf[100];
    switch (cmd) {
        case ADD:
            fprintf (f,"%s,",in_db->drug);
            fprintf (f,"%s,",in_db->type);
            fprintf (f,"%s,",in_db->manufacturer);
            // fprintf (f,"\"%s\",",time2str(&in_db->dateOfExpiry));
            fprintf(f, "%d,", in_db->isPrescription);
            fprintf (f,"%f,",in_db->price);
            fprintf (f,"%d\n",in_db->quantity);
            break;
			
            case PRINT:;
			#if debug
			printf ("Enters the print case\n");
			#endif
			db_t *node=getData();

            printf("%s %s %s %d %f %d\n",node->drug,node->type,node->manufacturer,node->isPrescription,node->price,node->quantity);
  
             
            break;


          default:
            printf("Case not implemented\n");
    }
    return rec;
}
