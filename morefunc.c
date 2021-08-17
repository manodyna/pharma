int choose()
{
	while(1)
	{
	printf("How do you want the data to be sorted?\n");
	printf("1:By name\n2:By Manufacturer\n3:By Cost\n4:By Expiration date\n");
	int c;
	scanf("%d",&c);
	if (c==1||c==2||c==3||c==4)
		return c;
	printf("Invalid Choice");
	}
}
void swap(drug *a,drug *b)
{
	drug temp=*a;
	*a=*b;
	*b=temp;
}

int date_cmp(char a[],char b[])
{
	int d1,m1,y1,d2,m2,y2;
	
	sscanf(a,"%d-%d-%d",&d1,&m1,&y1);
	sscanf(b,"%d-%d-%d",&d2,&m2,&y2);
	if(y1>y2)
	{
		//printf("Date1:%d-%d-%d\t>Date2:%d-%d-%d\n",d1,m1,y1,d2,m2,y2);
		return 1;
	}
	else if(y1<y2)
	{
		//printf("Date1:%d-%d-%d\t<Date2:%d-%d-%d\n",d1,m1,y1,d2,m2,y2);
		return -1;
	}
	else
	{
		if(m1>m2)
		{
			//printf("Date1:%d-%d-%d\t>Date2:%d-%d-%d\n",d1,m1,y1,d2,m2,y2);
			return 1;
		}
		else if(m1<m2)
		{
			//printf("Date1:%d-%d-%d\t<Date2:%d-%d-%d\n",d1,m1,y1,d2,m2,y2);
			return -1;
		}
		else{
			if(d1>d2)
			{
				//printf("Date1:%d-%d-%d\t>Date2:%d-%d-%d\n",d1,m1,y1,d2,m2,y2);
				return 1;
			}
			else if(d1<d2)
			{
				//printf("Date1:%d-%d-%d\t<Date2:%d-%d-%d\n",d1,m1,y1,d2,m2,y2);
				return -1;
			}
		}
	}
	return 0;
}
void freedom(drug *arr)
{
	free(arr);
	arr=NULL;
}
