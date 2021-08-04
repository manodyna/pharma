	int Print(drug *lst,int size);
	void swap(drug *a,drug *b);
	int date_cmp(char *a,char *b);
	void sort(drug arr[],int size,int type)
	{
		int i,j,pos;
		for(i=0;i<size;i++)
		{
			pos=i;
			for(j=0;j<size;j++)
			{
				if(type==3)
				{
					if(arr[i].price<arr[j].price)
					{
						swap(&arr[pos],&arr[j]);
					}
				}
				else if(type==1)
				{
					if(strcmp(arr[i].name,arr[j].name)<0)
					{
						swap(&arr[pos],&arr[j]);
					}
				}
				else if(type==2)
				{
					if(strcmp(arr[i].manufac,arr[j].manufac)<0)
					{
						swap(&arr[pos],&arr[j]);
					}
				}
				else if(type==4)
				{
					if(date_cmp(arr[i].date,arr[j].date)<0)
					{
						swap(&arr[pos],&arr[j]);
					}
				}
				
			}
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

	drug* Read()
	{
		FILE *fp;
		fp=fopen("database.csv","r");
		int Size=countlines(fp),i;
		drug *drugs=(drug*)calloc(Size,sizeof(drug));
		rewind(fp);
		//printf("Size:%d\n",Size);
		for(i=0;i<Size;i++)
		{
			fscanf(fp,"%[^,],%[^,],%[^,],%d,%lf,%d,%[^\n]\n",drugs[i].name,drugs[i].manufac,drugs[i].date,&drugs[i].prescription,&drugs[i].price,&drugs[i].quantity,drugs[i].details);
		}
		fclose(fp);
		return drugs;
	}


	int Print(drug *lst,int size)
	{
		//printf("Size:%d\n",size);
		int i;
		for(i=0;i<size;i++)
		{
			printf("Name:%12s\tCost:%12.2lf\tManufacturer:%14s\tExpiration Date:%14s\tDetails:%29s\n",lst[i].name,lst[i].price,lst[i].manufac,lst[i].date,lst[i].details);
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
		fprintf(fp,"%s,%s,%s,%d,%lf,%d,%s",name,manufac,date,prescription,price,quantity,details);
		fclose(fp);
		fp=NULL;
		
		return 0;
	}
