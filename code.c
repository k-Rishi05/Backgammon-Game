#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct moves
{
	int initial1;
	int final1;
	int initial2;
	int final2;
	int pos[30];
	int dead;
	int antidead;
	int count;
	int flag;
	int pairs;
	int defencivepairs;
	int attackpairs;
	int homeblockingpairs;
	int rank;

	int dead1;
	int dead2;

}moves;

moves chat[1000];
void getmoves(int count1,int count2);
void evaluation(int count,int flag);
int bareval(int count,int flag);
int movecount=0;
int position[100];
int dead=0;
int antidead=0;
int givenresult=0;
int givenpairs=0;
int bearingflag=0;

int comparator(const void *p,const void *q)
{
	const moves* p1=p;
	const moves* p2=q;
	if(p1->flag < p2->flag)
	{
		return -1;
	}
	else if(p1->rank > p2 -> rank)
	{
		return -1;
	}


}

int main()
{
	char name[100];
	int clockflag=1;
	int fillcount=0;

	int i=0;
	while(i<24)
	{
		scanf("%d",&position[i]);
		i++;
	}
	int count1=0;
	int count2=0;
	char s[10];
	/*dead=atoi(s);
	scanf("%s",s);
	antidead=atoi(s);*/
	char c=getchar();
	while(1)
	{
		c=getchar();
		if(c=='\n')
			break;
		if(c=='a')
		{
			dead++;
		}
		else if(c=='b')
		{
			antidead++;
		}
		c=getchar();
	}
	scanf("%d%d",&count1,&count2);
	movecount=0;

	getmoves(count1,count2);
	getmoves(count2,count1);

	i=0;

	while(i<movecount)
	{
		int ik=1;
		int fff=0;
		while(ik<=18)
		{
			if(chat[i].pos[ik]>0)
			{
				fff=1;
				break;

			}
			ik++;
		}


		if(fff==0 && chat[i].dead==0 && chat[i].antidead==0)
		{
		//	printf("asd\n");
			bearingflag=1;

		}
		if(fff==0 && chat[i].antidead>0 && chat[i].dead==0)
		{
			bearingflag=2;
		}

		int answer=0;
		if(bearingflag==0)
		{
			answer=answer+homeboard(i,1);
			answer=answer+quard3(i,1);
			answer=answer+quard2(i,1);
			answer=answer+quard1(i,1);
			answer=answer+anchor(i,1);
		}
		else
		{
			answer=answer+bareval(i,bearingflag);
		}
		chat[i].rank=answer;
		i++;
	}

//	printf("%d\n",movecount);
	qsort((void*)chat,movecount,sizeof(moves),comparator);
	i=0;
	while(i<movecount)
	{
		int k=0;
		while(k<=25)
		{
	//		printf("%d ",chat[i].pos[k]);
			k++;
		}
	//	printf("\n%d -> %d %d ->  %d  %d %d %d\n ",chat[i].initial1,chat[i].final1,chat[i].initial2,chat[i].final2,chat[i].dead,chat[i].antidead,chat[i].rank );
		i++;
	}


	if(movecount>0)
	{
		i=0;
		int k=1;
		while(k<=25)
		{
			//	printf("%d ",chat[i].pos[k]);
			k++;
		}
		//	printf("%d -> %d %d ->  %d  %d %d %d \n",chat[i].initial1,chat[i].final1,chat[i].initial2,chat[i].final2,chat[i].dead,chat[i].antidead , chat[i].rank);

		if(chat[i].initial1!=-1 && chat[i].final1!=-1)
		{
			if(chat[i].initial1==0)
				printf("Z");
			else
			{
				int s1=printf("%d",chat[i].initial1);
			}
			printf(" ");
			if(chat[i].final1>=25)
				printf("O");
			else
			{
				int f1=printf("%d",chat[i].final1);
			}
			printf("\n");
		}
		else
		{
			printf("pass\n");
		}
		if(chat[i].initial2!=-1 && chat[i].final2!=-1)
		{
			if(chat[i].initial2==0)
				printf("Z");
			else
			{
				int s2=printf("%d",chat[i].initial2);
			}
			printf(" ");
			if(chat[i].final2>=25)
				printf("O");
			else
			{
				int f2=printf("%d",chat[i].final2);
			}
			printf("\n");
		}
		else
		{
			printf("pass\n");
		}

	}
	else
	{
		printf("pass\n");
	}


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int anchor(int i , int flag)
{
	int ans=0;
	if(chat[i].pos[19] >=2)
	{
		ans=ans+10;
	}
	if(chat[i].pos[6] >=2)
	{
		ans=ans+10;
	}
	return ans;

}

int bareval(int count,int flag)
{

	if(flag==1)
	{
		int temp[100];
		int ii=0;
		int i=count;
		while(ii<=24)
		{
			temp[ii]=chat[i].pos[ii];
			ii++;
		}
		ii=19;
		int ans=0;

		while(ii<=24)
		{
			if(temp[ii] > 0)
			{
				ans=ans+(temp[ii]*(ii));
			}
			ii++;
		}
		int suc=0;

		// calculating pairs

		int pairscount=0;
		int single=0;

		ii=19;
		int kills=0;
		int note=0;
		while(ii<=24)
		{
			if(temp[ii]>=2)
			{
				pairscount++;

			}
			if(temp[ii]==1)
			{
				single++;
				if(note==0)
				{
					note=ii;
				}
			}
			if(ii==chat[i].dead1 || ii==chat[i].dead2)
			{
				kills++;
			}
			ii++;
		}

		int retval=0;
		retval=(  (pairscount)*150   )+ ans + (( kills )*50)+ (note)  ;
		
		return ans;
	}
	else
	{
		int temp[100];
		int i=count;
		int ii=0;
		int homepoints=chat[i].pos[25];
		while(ii<=24)
		{
			temp[ii]=chat[i].pos[ii];
			ii++;
		}
		int suc=0;

		// calculating pairs

		int pairscount=0;
		int single=0;

		ii=19;
		int kills=0;
		int note=0;
		while(ii<=24)
		{
			if(temp[ii]>=2)
			{
				pairscount++;

			}
			if(temp[ii]==1)
			{
				single++;
				if(note==0)
				{
					note=ii;
				}


			}
			if(ii==chat[i].dead1 || ii==chat[i].dead2)
			{
				kills++;
			}
			ii++;
		}

		int retval=0;
		retval=(  (pairscount)*150   )+( (single)*(-100) ) + (( kills )*50)+ (note)  ;
		return retval;


	}
}









///////////////////////////////////////////////////// HomeBoard evaluation ////////////////////////////////////////////////////////////






int homeboard(int count,int flag)
{

	if(flag==1)
	{

		int temp[100];
		int i=count;
		int ii=0;
		//	int homepoints=chat[i].pos[25];
		while(ii<=24)
		{
			temp[ii]=chat[i].pos[ii];
			ii++;
		}
		int suc=0;

		// calculating pairs

		int pairscount=0;
		int single=0;

		ii=19;
		int kills=0;
		while(ii<=24)
		{
			if(temp[ii]>=2)
			{
				pairscount++;

			}
			if(temp[ii]==1)
			{
				single++;
			}
			if(ii==chat[i].dead1 || ii==chat[i].dead2)
			{
				kills++;
			}
			ii++;
		}

		int retval=0;
		retval=(  (pairscount)*150   )+( (single)*(-100) ) + (( kills )*50)  ;
		return retval;

	}
	return -1;
}

/////////////////////////////////////////////////////////    quard 3 //////////////////////////////////////////////////////////////////




int quard3(int count,int flag)
{

	if(flag==1)
	{

		int temp[100];
		int i=count;
		int ii=0;
		while(ii<=24)
		{
			temp[ii]=chat[i].pos[ii];
			ii++;
		}
		int suc=0;

		// calculating pairs

		int pairscount=0;
		int single=0;

		ii=13;
		int kills=0;
		while(ii<=18)
		{
			if(temp[ii]>=2)
			{
				pairscount++;

			}
			if(temp[ii]==1)
			{
				single++;
			}
			if(ii==chat[i].dead1 || ii==chat[i].dead2)
			{
				kills++;
			}
			ii++;
		}

		int retval=0;
		retval=(  (pairscount)*100  )+( (single)*(-40) ) + (( kills )*70);
		return retval;

	}
	return -1;
}

//////////////////////////////////////////////////////////////// quard2 ///////////////////////////////////////////////////////////////



int quard2(int count,int flag)
{

	if(flag==1)
	{

		int temp[100];
		int i=count;
		int ii=0;
		while(ii<=24)
		{
			temp[ii]=chat[i].pos[ii];
			ii++;
		}
		int suc=0;
		int pairscount=0;
		int single=0;
		ii=7;
		int kills=0;
		while(ii<=12)
		{
			if(temp[ii]>=2)
			{
				pairscount++;

			}
			if(temp[ii]==1)
			{
				single++;
			}
			if(ii==chat[i].dead1 || ii==chat[i].dead2)
			{
				kills++;
			}
			ii++;
		}

		int retval=0;
		retval=(  (pairscount)*70  )+( (single)*(-10) ) + (( kills )*100);
		return retval;

	}
	return -1;
}

//////////////////////////////////////////////////////////////        quard 1 ////////////////////////////////////////////////////////

int quard1(int count,int flag)
{

	if(flag==1)
	{

		int temp[100];
		int i=count;
		int ii=0;
		while(ii<=24)
		{
			temp[ii]=chat[i].pos[ii];
			ii++;
		}
		int suc=0;
		int pairscount=0;
		int single=0;
		ii=1;
		int kills=0;
		while(ii<=6)
		{
			if(temp[ii]>=2)
			{
				pairscount++;

			}
			if(temp[ii]==1)
			{
				single++;
			}
			if(ii==chat[i].dead1 || ii==chat[i].dead2)
			{
				kills++;
			}
			ii++;
		}

		int retval=0;
		retval=(  (pairscount)* 50 ) + (( kills )*150);
		return retval;

	}
	return -1;
}



void bearevaluation()
{

}


///////////////////////////////////////////////////////////////////// Phase1 evaluation //////////////////////////////////////////////////

void evaluation(int count ,int flag)
{
	if(flag==1)
	{
		int temp[100];
		int i=count;
		int ii=0;
		while(ii<=24)
		{
			temp[ii]=chat[i].pos[ii];
			ii++;
		}
		int suc=0;

		// calculating pairs

		int pairs[30];
		int pairscount=0;
		int defc=0;
		int attc=0;
		int homeblock=0;
		int success=chat[i].pos[25];
		int killed=chat[i].antidead;
		int otherblock=0;
		int lefthomepairs=0;
		int leftanchorpairs=0;
		int leftanchorpairsbottom=0;
		int anchorsleft=0;
		int singleleft=0;
		ii=1;
		while(ii<=24)
		{
			if(temp[ii] >= 2)
			{
				pairs[pairscount]=i;
				pairscount++;
				if(ii>=17 && ii<=20)
				{
					defc++;
				}
				if(ii>=5 && ii<=8)
				{
					attc++;
				}
				if(ii>=1 && ii<=6)
				{
					homeblock++;
				}
				if(ii>=19 && ii<=24)
				{
					otherblock++;
				}
			}
			if(temp[ii]==1)
			{
				if(ii>=19 && ii<=24)
				{
					lefthomepairs++;
				}
				if(ii>=17 && ii<=20)
				{
					leftanchorpairs++;
				}
				if(ii>=5 && ii<=8)
				{
					leftanchorpairsbottom++;
				}
				if(ii>=9 && ii <= 16)
				{
					singleleft++;	
				}			
				if(ii>=1 && ii <=4)
				{
					singleleft++;	
				}			
			}
			ii++;
		}
		int yy=1;
		int pip=0;
		while(yy<19)
		{
			if(temp[yy]>0)
			{
				pip=pip+(temp[yy])*(yy);
				break;
			}
			yy++;
		}

		int evalblock = (30*otherblock) +(20*defc)+(25 *attc)+(20 *homeblock) - (3 *lefthomepairs) - 2*(leftanchorpairs+leftanchorpairsbottom) -singleleft; 
		int finaleval = ( 70 * killed ) + evalblock  ;
		chat[i].rank=finaleval;

	}

}


////////////////////////////////////////////////////////////////////////// Moves /////////////////////////////////////////////////////////



void getmoves(int count1,int count2)
{
	int i=0;
	i=0;

	while(i<=24)
	{
		int temp[100]={0};
		temp[0]=dead;
		int p=0;

		//printf("%d\n",dead);

		int dead1=0;
		while(p<24)
		{
			temp[p+1]=position[p];
			p++;
		}


		int flag1=0;
		if(temp[0] > 0)
		{
			flag1=1;
		}

		int semiflag1=0;
		int yy=0;
		int ll=0;
		while(yy<19)
		{
			if(temp[yy]>0) 
			{
				semiflag1=1;
				break;
			}
			yy++;
		}
		if(i+count1 <25 )
		{
			semiflag1=0;

		}

		if(temp[i]>0 && temp[i+count1]>=-1  && semiflag1==0)
		{



			int passflag=0;
			int j=0;
			int opd=antidead;
			temp[i]--;
			if(temp[i+count1]==-1)
			{
				temp[i+count1]=0;
				opd++;
				dead1=i+count1;
			}
			else
			{
				dead1=0;
			}
			if(i+count1 > 25 )
			{
				temp[25]++;
			}
			else
			{
				temp[i+count1]++;
			}
			j=0;


			while(j<=24)
			{
				int dead2=0;
				int temp1[100]={0};
				int yy=0;
				while(yy<=25)
				{
					temp1[yy]=temp[yy];
					yy++;
				}
				int flag2=0;
				int opd2=opd;

				if(temp1[0]>0)
				{
					flag2=1;
				}

				int semiflag2=0;
				yy=1;
				while(yy<19)
				{
					if(temp1[yy]>0)
					{
						semiflag2=1;
						break;
					}
					yy++;
				}

				if(j+count2 <25 )
				{
					semiflag2=0;

				}


				if(temp1[j]>0 && temp1[j+count2]>=-1   && semiflag2==0)
				{
					temp1[j]--;
					if(temp1[j+count2]==-1)
					{
						opd2++;
						temp1[j+count2]=0;
						dead2=j+count2;
					}
					else
					{
						dead2=0;
					}
					if(j+count2 > 25)
					{
						temp1[25]++;
					}
					else
					{
						temp1[j+count2]++;
					}
					int k=0;
					passflag=1;
					while(k<=25)
					{
						if(k==0)
						{
							chat[movecount].dead=temp1[0];
							chat[movecount].antidead=opd2;	
							chat[movecount].initial1=i;	
							chat[movecount].final1=i+count1;	
							chat[movecount].initial2=j;	
							chat[movecount].final2=j+count2;	
							chat[movecount].flag=1;	
							chat[movecount].dead1=dead1;	
							chat[movecount].dead2=dead2;	
						}
						else
						{
							chat[movecount].pos[k]=temp1[k];	

						}
						k++;
					}
					movecount++;


				}
				if(flag2==1)
				{
					break;
				}
				j++;
			}

			if(passflag==0)
			{
				int k=0;
				while(k<=25)
				{
					if(k==0)
					{
						chat[movecount].dead=temp[k];
						chat[movecount].antidead=opd;	
						chat[movecount].initial1=i;	
						chat[movecount].final1=i+count1;	
						chat[movecount].initial2=-1;	
						chat[movecount].final2=-1;	
						chat[movecount].flag=0;	
						chat[movecount].dead1=dead1;	
						chat[movecount].dead2=-1;	
					}
					else
					{
						chat[movecount].pos[k]=temp[k];	

					}
					k++;
				}
				movecount++;

			}
		}
		if(flag1==1)
		{
			break;
		}
		i++;
	}
}







