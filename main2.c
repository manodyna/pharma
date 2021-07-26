// including necessary library files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#define debug 0
#include "que.c"

// defining database functionalities
#define DB "database.csv"

#define FREE(a) if(a) {free(a);a=NULL;}
#define TRY(a)  if (!(a)) {perror(#a);exit(1);}
#define TRY2(a) if((a)<0) {perror(#a);exit(1);}
#define sort_by(foo) \
static int by_##foo (const void*p1, const void*p2) { \
    return strcmp ((*(const pdb_t*)p1)->foo, (*(const pdb_t*)p2)->foo); }


// defining a struct for the management system

typedef int (sort)(const void*, const void*);

prio_t getData()
{
	FILE* fp = fopen("database.csv", "r");
	#if debug
	printf("\nFile Opens\n");
	#endif
	if (fp==NULL)
	{
		printf("File could not be opened\n");
		exit(1);
	}
	prio_t queue;
	init_queue(&queue);
	
	
	char line[100];
	while(fgets(line,100,fp)!=NULL)
	{
		#if debug
		printf("The while loop enters\n");
		#endif
		compo_t c;
		char *drug=strtok(line,",");
		
		strcpy(c.details.drug,drug);
		char *type=strtok(NULL,",");
		strcpy(c.details.type,type);
		char *manufacturer=strtok(NULL,",");
		strcpy(c.details.manufacturer,manufacturer);
		char *date=strtok(NULL,",");
		strcpy(c.details.date,date);
		char *isPrescription=strtok(NULL,",");
		int isP=atoi(isPrescription);
		c.details.isPrescription=isP;
		char *cost=strtok(NULL,",");
		float price=strtof(cost,NULL);
		c.details.price=price;
		char *quan=strtok(NULL,",");
		int quantity=atoi(quan);
		c.details.quantity=quantity;
		enque(&queue,&c);
		#if debug
		printf("price=%.2f\n",c.details.price);
		#endif
	}
	return queue;
}

// enum for commands
enum {ADD, PRINT, DRUG, MANUFACTURER, TYPE, READLINE, READ, SORT, DESTROY};

// data access object(DAO)
static pdb_t dao (int cmd, FILE *f, pdb_t db, sort sort_by);

sort_by(drug);
sort_by(manufacturer);
sort_by(type);


int main(int argc,char **argv){
    char buf[100];
    // #if debug
    // printf("%s\n",argv[1]);
    // #endif
    // defining the database commands
    const char *commands[] = {"-a", "-p", "-n", "-m", "-t", NULL};  
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
        "-n sort records by name\n"
        "-m sort records by manufacturer\n"
        "-t sort records by type\n"
        "-p print all records \n");
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
            
			printf("Date of expiry(dd-mm-yyyy) :");if((scanf(" %s[^\n]",db.date))<0)break;
            printf("Is prescription(1/0):");if((scanf(" %d[^\n]",&db.isPrescription))<0)break;
            printf("Price          :");if((scanf(" %f[^\n]",&db.price))<0)break;
            printf("Quantity       :");if((scanf(" %d[^\n]",&db.quantity))<0)break;

            dao (ADD,f,&db,NULL);
            break;

        case PRINT:
            // printf ("-p  Print the latest entry.\n");
            while (!feof(f)){
                #if debug
                printf("This works loop enters\n Working on it\n");
                #endif

                 dao (PRINT,f,&db,NULL);
                 exit(0);
            }
            break;

        case DRUG:
            dbList = dao (READ,f,&db,NULL);
            dbList = dao (SORT,f,dbList,by_drug);
            dao (PRINT,f,dbList,NULL);
            dao (DESTROY,f,dbList,NULL);
            break;
        
        case MANUFACTURER:
            dbList = dao (READ,f,&db,NULL);
            dbList = dao (SORT,f,dbList,by_manufacturer);
            dao (PRINT,f,dbList,NULL);
            dao (DESTROY,f,dbList,NULL);
            break;

        case TYPE:
            dbList = dao (READ,f,&db,NULL);
            dbList = dao (SORT,f,dbList,by_type);
            dao (PRINT,f,dbList,NULL);
            dao (DESTROY,f,dbList,NULL);
            break;


        default: {
            printf ("Unknown command: %s.\n",(strlen(argv[1])<10?argv[1]:NULL));
            exit(0);
        }
    }

    fclose (f);
    return 0;

}

static pdb_t dao (int cmd, FILE *f, pdb_t in_db, sort sort_by) {
pdb_t *pdb=NULL,rec=NULL,hd=NULL;
    int i=0, ret;
    char buf[200];
    switch (cmd) {
        case ADD:
            fprintf (f,"%s,",in_db->drug);
            fprintf (f,"%s,",in_db->type);
            fprintf (f,"%s,",in_db->manufacturer);
            fprintf (f,"%s,",in_db->date);
			fprintf (f,"%d,", in_db->isPrescription);
            fprintf (f,"%f,",in_db->price);
            fprintf (f,"%d\n",in_db->quantity);
            break;
			
        case PRINT:;
			
			prio_t node=getData();
			
			#if debug
			printf ("GetData Successfully returned\n");
			#endif
			
			disp(&node);
             
            break;

        case READLINE:
            if((fscanf(f," \"%[^\"]\",",in_db->drug     ))<0)break;
            if((fscanf(f," \"%[^\"]\",",in_db->type))<0)break;
            if((fscanf(f," \"%[^\"]\",",in_db->manufacturer ))<0)break;
			if((fscanf(f,"\"%[^\"]\",",in_db->date))<0)break;
            if((fscanf(f," \"%[^\"]\" ",in_db->price      ))<0)break;
            if((fscanf(f," \"%[^\"]\" ",in_db->quantity      ))<0)break;
            if((fscanf(f," \"%[^\"]\" ",in_db->isPrescription      ))<0)break;
            // in_db->date=str2time (buf);
            break;

        case READ:
            while (!feof(f)) {
                dao (READLINE,f,in_db,NULL);
                TRY (rec=malloc(sizeof(db_t)));
                *rec=*in_db; /* copy contents */
                rec->next=hd;/* to linked list */
                hd=rec;i++;
            }
            if (i<2) {
                puts ("Empty database. Please create some entries.");
                fclose (f);
                exit (0);
            }
            break;

        case SORT:
            rec = in_db;
            for (;in_db;i++) in_db=in_db->next;
            TRY (pdb=malloc(i*sizeof(pdb_t)));
                in_db=rec;
                for (i=0;in_db;i++) {
                    pdb[i]=in_db;
                    in_db=in_db->next;
                }
                qsort (pdb,i,sizeof in_db,sort_by);
               
                pdb[i-1]->next=NULL;
                for (i=i-1;i;i--) {
                    pdb[i-1]->next=pdb[i];
                }

                rec=pdb[0];
            FREE (pdb);
            pdb=NULL;
            break;
            
            case DESTROY: 
            while ((rec=in_db)) {
                in_db=in_db->next;
                FREE (rec);
            }   
            
          default:
            printf("Case not implemented\n");
    }
    return rec;
}
