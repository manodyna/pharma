int Print(drug *lst,int size);
void swap(drug *a,drug *b)
{
	drug temp=*a;
	*a=*b;
	*b=temp;
}
void freedom(drug *arr)
{
	free(arr);
	arr=NULL;
}
void sort(drug arr[],int size,int type)
{
	size=size-1;
	int i,j,pos;
	// for(i=0;i<size;i++)
	// {
	// 	pos=i;
	// 	for(j=i+i;j<size;j++)
	// 	{
	// 		switch(type)
	// 		{
	// 			case 0:			//cost
	// 				if(arr[i].price>arr[j].price);
	// 				{
	// 					pos=j;
	// 				}
	// 			break;
	// 			case 1:			//name
	// 			//printf("%s\t%s\t%d\n",arr[i].name,arr[j].name,strcmp(arr[i].name,arr[j].name));
	// 				if(strcmp(arr[i].name,arr[j].name));
	// 				{
	// 					pos=j;
	// 				}
	// 			break;
	// 			// case 2:		//manufacturer

	// 		}
	// 	}
	// 	if(pos!=i)
	// 		swap(&arr[pos],&arr[i]);
	// }
	switch (type)
	{
	case 0:
	printf("entered case");
		for(i=0; i<size-1; i++){
			for (j = 0; j < size-i-1; j++)
			{
				printf("into the loop");
				if(arr[j].price>arr[j+1].price){
					// drug temp;
					// temp = arr[j];
					// arr[j] = arr[j+1];
					// arr[j+1] = temp;
					swap(&arr[j], &arr[j+1]);
				}

			}
			
		}
		break;

	case 1:
		for(i=0; i<size; i++){
			for (j = 0; j < size; j++)
			{
				if(strcmp(arr[j].name,arr[j+1].name)){
					drug temp;
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}

			}
			
		}
		break;
	
	case 2:
		for(i=0; i<size; i++){
			for (j = 0; j < size; j++)
			{
				if(strcmp(arr[j].manufac,arr[j+1].manufac)){
					drug temp;
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}

			}
			
		}
		break;

	case 3:
		for(i=0; i<size; i++){
			for (j = 0; j < size; j++)
			{
				if(arr[j].quantity>arr[j+1].quantity){
					drug temp;
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}

			}
			
		}
		break;
	
	default:
		break;
	}
}

int countlines(FILE *fp)
{
	char c;
	int l=0;
	c=getc(fp);
	while(c!=EOF)
	{
		if(c=='\n')
		{
			l++;
		}
	c=getc(fp);
	}
	return l;
}

drug* read()
{
	FILE *fp;
	fp=fopen("database.csv","r");
	int Size=countlines(fp),i;
	drug *drugs=(drug*)calloc(Size,sizeof(drug));
	rewind(fp);
	for(i=0;i<Size;i++)
	{
		fscanf(fp,"%[^,],%[^,],%[^,],%d,%lf,%d,%[^\n]\n",drugs[i].name,drugs[i].manufac,drugs[i].date,&drugs[i].prescription,&drugs[i].price,&drugs[i].quantity,drugs[i].details);
	}
	fclose(fp);
	return drugs;
}


int Print(drug *lst,int size)
{
	size=size-1;
	int i;
	for(i=0;i<size;i++)
	{
		printf("Name:%s\tCost:%lf\n",lst[i].name,lst[i].price);
	}
}

int addData()
{
	char name[100];
	char manufac[100];
	char date[50];
	int prescription;
	double price;
	int quantity;
	char details[200];
	printf("Enter name of medicine:");
	scanf("%s",name);
	printf("Enter name of manufacturer:");
	scanf("%s",manufac);
	printf("Enter expiration date of medicine:");
	scanf("%s",date);
	printf("Enter if prescription(1/0):");
	scanf("%d",&prescription);
	printf("Enter price:");
	scanf("%lf",&price);
	printf("Enter quantity:");
	scanf("%d",&quantity);
	fflush(stdin);
	printf("Enter details about the medicine:");
	fflush(stdin);
	getchar();
	fgets(details,200,stdin);
	FILE *fp=fopen("database.csv","a");
	fprintf(fp,"%sS,%s,%s,%d,%lf,%d,%s\n",name,manufac,date,prescription,price,quantity,details);
	fclose(fp);
	fp=NULL;
	
	return 0;
}

char name[56];
drug search(name){
	for (int i = 0; i < countlines; i++)
	{
		if (strcmp(name, drugs[i].name))
		{
			return(drugs[i]);
		}
	}
	
}