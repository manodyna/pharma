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
	for(i=0;i<size;i++)
	{
		pos=i;
		for(j=i+i;j<size;j++)
		{
			switch(type)
			{
				case 0:			//cost
				if(arr[i].price>arr[j].price);
				{
					pos=j;
				}
				break;
				case 1:			//name
				//printf("%s\t%s\t%d\n",arr[i].name,arr[j].name,strcmp(arr[i].name,arr[j].name));
				if(strcmp(arr[i].name,arr[j].name)>0);
				{
					pos=j;
				}
				break;
			}
		}
		if(pos!=i)
			swap(&arr[pos],&arr[i]);
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
	printf("Enter details about the medicine:");
	scanf("%[^\n]",details);
	FILE *fp=fopen("database.csv","a");
	fprintf(fp,"%s,%s,%s,%d,%lf,%d,%s\n",name,manufac,date,prescription,price,quantity,details);
	fclose(fp);
	fp=NULL;
	return 0;
}