#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stru.c"
#include "filefunc.c"
#include "morefunc.c"
int main(int argc, char *argv[])
{
	int choice;
	while(1)
	{
		fflush(stdin);
		system("clear");
		printf("Enter\n0:Exit\n1:Add\n2:View\n3:Delete\n4:Search\n");
		scanf("%d",&choice);
		switch (choice)
		{
			case 0:
			exit(0);
			break;
			case 1:
			addData();
			break;
			case 2:
			;
			drug* d=Read();
			FILE *fp;
			fp=fopen("database.csv","r");
			int Size=countlines(fp);
			fclose(fp);
			int chp=choose();
			sort(d,Size,chp);
			Print(d,Size);
			fflush(stdin);
			getchar();
			fflush(stdin);
			getchar();
			break;

			case 3: ;
				drug* d3 = Read();
				char name1[56];
				printf(" Input the drug you want to remove : ");
        		scanf("%s", name1);
				int lno = search(name1, d3);
				delete(lno);
				break;

			case 4: ;
				drug* d2 = Read();
				printf("Enter Drug name to search:");
				char name[56];
				scanf("%s", name);
				search(name, d2);
				fflush(stdin);
				getchar();
				fflush(stdin);
				getchar();
				break;
			default:
				printf(":/\n");
				fflush(stdin);
				getchar();
				fflush(stdin);
				getchar();
				
		}
	}
	
	return 0;
}
