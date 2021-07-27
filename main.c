#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stru.c"
#include "filefunc.c"
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
			drug* d=read();
			Print(d,sizeof(d));
			break;
		}
	}
	
	return 0;
}
