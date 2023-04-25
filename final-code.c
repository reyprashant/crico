//Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dos.h>
#include <conio.h>

//Functions included.
//main menu start
void mainMenu();
void history();
//end

//basis match requirement start
void teamDetails();
void convertToOver(int balls1);
void switchb();
//end

//1st inning requirement start
void newScorecard();
void defaultScores();
void scoringProcess();
void extra1st();
void scoreSheet();
//end

//2nd inning requirement start
void Scorecard();
void swapnames();
void scoreSheet2nd();
void default2ndScores();
void scoring2ndProcess();
//end

//Global variables used.
int overs=0,ball=0,wick=0,ballrun=0,bm1=0,bm2=0;//basis variables 
int i=0,j=0;//loop runner variables 
int score=0,bowlid=0,extra=0;//variables used for 1st inning
int score2nd=0,bowl2ndid=0,extra2nd=0;//variables used for 2nd inning
char visit[20],host[20];//visitor and host team names
char bat1st[20],bowl1st[20],bat2nd[20];//bat1st=1st striking team ,bowl1st=1st bowling team and bat2nd=2nd striking team

//Batsmen structure(To store batsman details like name, runs, id etc)
struct batsmen 
{
    int runs;
    char name[20];
    int balls;
    int id;
    bool out;
    bool isBatting;
}bat[11];

//1st inning Bowler structure(To store bowler details like name, wickets taken, id etc)
struct bowlers
{
	int runs;
    int balls;
    char name[20];
    int wickets ;
    int id;
    bool bowling;
    bool out;
    bool isBatting;
}bowl[11];

//Bowler structure(To store bowler details like name, wickets taken, id etc)
struct bowler
{
    int balls;
    char name[20];
    int wickets ;
    int id;
    bool bowling;
}bowl2nd[11];

//Main function
int main()
{
    mainMenu();
    FILE *fp;
	fp = fopen("cric.txt", "a");
	system("cls");	
}

//Main menu(Where you take choice from the user)
void mainMenu()
{
    int ch;
    main:
    system("COLOR 4F");
    printf("\n\n\n\n\n\n\n\t\t\t\t--------------------------");
    printf("\n\t\t\t\t\tCRIC SCORE");
    printf("\n\t\t\t\t--------------------------\n");
    printf("\t\t\t\t1.Create new scoresheet.\n\t\t\t\t2.History\n\t\t\t\t3.Exit.\n");
    printf("\t\t\t\tEnter your choice(1/2/3): ");
    scanf("%d",&ch);
    if(ch==1)
    {
    	system("COLOR F2");
        newScorecard();
        system("COLOR F3");
        ball=0;
        ballrun=0;
        Scorecard();
    }
    else if(ch==2)
    {
    	system("COLOR 9F");
    	history();
    	system("cls");
    	goto main;
	}
    else if(ch==3)
    {
    	system("cls");
    	system("COLOR F4");
    	printf("The application has been exited");
    	exit(0);
	}
    else
    {
    	printf("\t\t\t\tInvalid entry ,please try again.");
    	sleep(1);
    	system("cls");
        mainMenu();
    }
}
//If the choice is 1 then this function is executed.
void newScorecard()
{
    defaultScores();
    teamDetails();
    scoringProcess();

}
//Funtion to get team details(Batting and bowling team)
void teamDetails()
{
	FILE *fp;
	fp = fopen("cric.txt", "a");
	system("cls");	
	int option;
	time_t t;   // not a primitive datatype
    time(&t);
    printf("Match's date: %s\n", ctime(&t));
    fprintf(fp,"\nMatch's date: %s\n",ctime(&t));
	printf("Enter the visitor team name\t");
	getchar();
	gets(visit);
	fprintf(fp,"Visitor team name: %s\n",visit);
	printf("\nEnter the host team name\t");
	gets(host);
	fprintf(fp,"Host team name: %s\n",host);
	printf("Which team chose batting?");
	printf("\n1.%s\n2.%s\n",visit,host);
	scanf("%d",&option);
	if(option==1)
	{
		strcpy(bat1st,visit);
		strcpy(bowl1st,host);
		strcpy(bat2nd,host);
		fprintf(fp,"%s's team batted in 1st inning\n",visit);
		fprintf(fp,"%s's team batted in 2nd inning\n",host);
	}
	else if(option==2)
	{
		strcpy(bat1st,host);
		strcpy(bowl1st,visit);
		strcpy(bat2nd,visit);
		fprintf(fp,"%s's team batted in 1st inning\n",host);
		fprintf(fp,"%s's team batted in 2nd inning\n",visit);
	}
	
    system("cls");
    hehe:
    printf("\n\n\n\n\n\tENTER NUMBER OF OVERS: ");
    scanf("%d",&overs);
    if(overs==0)
    {
    	printf("Invalid entry! Please try again.");
    	sleep(1);
    	system("cls");
    	goto hehe;
	}
    printf("\n\n\tPLAYER DETAILS\n\n");
    printf("\tEnter %s's BATTING team players names(11 players):\n",bat1st);
    int i;
    getchar();
    for(i=1;i<=11;i++)
    {
        printf("\tBatsman %d: ",i);
        bat[i].id=i;
        gets(bat[i].name);
    }
    system("cls");
    printf("\n\n\n\tPLAYER DETAILS\n\n");
    printf("\tEnter %s's BOWLING team players names(11 players):\n",bowl1st);
    int j;
    for(j=1;j<=11;j++)
    {
        printf("\tPlayer %d: ",j);
        bowl[j].id=j;
        gets(bowl[j].name);
    }
    system("cls");
    fprintf(fp,"The number of over played %d\n",overs);
    system("cls");
    system("COLOR 40");
    for(i=3;i>0;i--)
		{
			printf("\n\t\tLoading in.........%d\n",i);
			sleep(1);
			system("cls");
		}
	system("COLOR F2");
}

//This function handles the scoring process.(very important and very difficult to understand)
void scoringProcess()
{
    int b1,b2,nb,bo;
    char brun='1';
    while(ball<=overs*6)
    {
        if(ball==overs*6)
        {
            system("cls");
            system("COLOR 40");
            for(i=3;i>0;i--)
			{
			printf("\n\t\t\t\t1st inning ended\n\t\t\t%s's scoresheet Loading in.........%d\n",bat1st,i);
			sleep(1);
			system("cls");
			}
			system("COLOR F2");
            scoresheet();
			break;  
        }
        if(ball==0)
        {
            system("cls");
            printf("\n\n\n\t\t SELECT %s's BATSMAN\n\n",bat1st);
            printf("\tID  Name        Runs      Balls\n");
            int i;
            for( i = 1; i<=11;i++)
            {
                printf("\t%-3d %-10s: %-3dRuns  %-3dBalls\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
            }
            top:
            printf("NOTE: Enter the valid ID number only from 1 to 11");
            printf("\n\tEnter FIRST Batsman ID (1-11): ");
            scanf("%d",&b1);
            if(b1<1 || b1>11)
            {
                printf("\n\tError:Invalid choice.");
                goto top;
            }else 
            {
                bm1=b1;
                bat[b1].isBatting=true;
            }
            top1:
            printf("\tEnter SECOND Batsman ID (1-11): ");
            scanf("%d",&b2);
            if(bat[b2].isBatting)
                {
                    printf("\tBatsman %d:%s is already batting.\n\tENTER AGAIN\n",bat[b2].id,bat[b2].name);
                    goto top1;
                }
            if(b2<1 || b2>11)
            { 
                printf("\n\tError:Invalid choice.");
                goto top1;
            }else 
            {
                bm2=b2;
                bat[b2].isBatting=true;
            }
        }
        if(ball%6==0 && ball<overs*6)
        {
            system("cls");
            printf("\n\n\n\t\t%s's SELECT BOWLER\n\n",bowl1st);
            printf("\tID  Name        Balls      Wickets\n");
            int j;
            for( j=1;j<=11;j++)
            {
                printf("\t%-3d %-10s: %-3dBalls  %-3dWickets\n",bowl[j].id,bowl[j].name,bowl[j].balls,bowl[j].wickets);
            }
            printf("\n\n\tEnter BOWLER ID (1-11): ");
            scanf("%d",&bo);
            bowlid=bo;
            if(ball>5)
            switchb();
            bowl[bo].bowling=true;
        }
        int no_of_out=0;
        label:
        if(ball<overs*6)
        {
        	widee:
            system("cls");
            scoresheet();
			printf("\n\n\tEnter Ball(1-6 runs, 'o' for out, 'w' for wide): ");
            scanf("%c",&brun);
            if(brun=='0')
            {
                ballrun=0;
                bat[bm1].runs+=0;
                bat[bm1].balls++;
                bowl[bowlid].balls++;
            } else if(brun=='1')
            {
                ballrun=1;
                bat[bm1].runs+=1;
                bat[bm1].balls++;
                bowl[bowlid].balls++;
                switchb();
            } else if(brun=='2')
            {
                ballrun=2;
                bat[bm1].runs+=2;
                bat[bm1].balls++;
                bowl[bowlid].balls++;
            } else if(brun=='3')
            {
                ballrun=3;
                bat[bm1].runs+=3;
                bat[bm1].balls++;
                bowl[bowlid].balls++;
                switchb();
            } else if(brun=='4')
            {
                ballrun=4;
                bat[bm1].runs+=4;
                bat[bm1].balls++;
                bowl[bowlid].balls++;
            } else if(brun=='6')
            {
                ballrun=6;
                bat[bm1].runs+=6;
                bat[bm1].balls++;
                bowl[bowlid].balls++;
            } 
            else if(brun=='w'||brun=='W')
            {
            	extra++;
            	ballrun=1;
            	if(ball==0)
            	{
            		ball=0;
            		score++;
            		goto widee;
				}
				else
				{
					ball=ball-1;
				}
			}
			else if(brun=='o'||brun=='O')
            {
            	ballrun=0;
                bat[bm1].out=true;
                bowl[bowlid].wickets++;
                bowl[bowlid].balls++;
                int a;
                for( a=1;a<=11;a++)
                {
                    if(bat[a].out==true)
                    no_of_out++;
                }
                if(no_of_out==10)
                {
                    ball++;
                    system("cls");
                    printf("\n\n\tFINAL scoresheet");
                    scoresheet();
                    break;
                }
                bat[bm1].isBatting=false;
                printf("\tBatsman %d: %s is out.",bat[bm1].id,bat[bm1].name);
                first:
                printf("\n\tEnter new batsman(1-11): ");
                scanf("%d",&nb);
                if(bat[nb].isBatting)
                {
                    printf("\tBatsman %d:%s is already batting.\n\tENTER AGAIN",bat[nb].id,bat[nb].name);
                    goto first;
                }
                if(bat[nb].out)
                {
                    printf("\tBatsman %d:%s is already out.\n\tENTER AGAIN",bat[nb].id,bat[nb].name);
                    goto first;            
                }
                bat[bm1].balls++;
                bat[nb].isBatting=true;
                bm1=nb;
            }
            else
            {
                printf("\n\tInvalid possibility.Enter again.");
                goto label;
            }
        ball++;
        score=score+ballrun;
		}}
}
//Function to set for 1st inning default values
void defaultScores()
{
    int i;
	for( i =1;i<=11;i++)
    {
        bat[i].balls=0;
        bat[i].runs=0;
        bat[i].out=false;
        bat[i].isBatting=false;
        bowl[i].balls=0;
        bowl[i].wickets=0;
        bowl[i].bowling = false;
    }
}
//Function to display the inning scoresheet.
void scoresheet()
{
	if(ball==overs*6)
    {
    system("cls");
	printf("\n\n\t%s's Final BATTING TEAM STATS:\n\n",bat1st);
	FILE *fp;
	fp = fopen("cric.txt", "a");
    fprintf(fp,"\n\t\t%s's SCORE: %d\tExtra: %d\n",bat1st,score,extra);   
    int i;
	fp = fopen("cric.txt", "a");
    for( i = 1; i<=11;i++)
    {
        if(bat[i].out)
		{
        	printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  OUT\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
        	fprintf(fp,"\t%-3d%-10s: %-3dRuns  %-3dBalls  OUT\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
    	}
        	else 
        {
            if(i==bm1)
            {
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Strike\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
            fprintf(fp,"\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Strike\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
        }
            else if(i==bm2)
            {
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Non Strike\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
            fprintf(fp,"\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Non Strike\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
        }
            else
			{
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
            fprintf(fp,"\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
        }
        }
    }	
	system("pause"); 
	system("cls");
	  system("COLOR 40");
        for(i=3;i>0;i--)
		{
			printf("\n\t\t\t2nd inning starting.........%d\n",i);
			sleep(1);
			system("cls");
		}
		system("COLOR F3");
	}
	else	
	{
	system("cls");
	printf("\n\n\t%s's BATTING TEAM STATS:\n\n",bat1st);
    int i;
    for( i = 1; i<=11;i++)
    {
        if(bat[i].out)
        printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  OUT\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
        else 
        {
            if(i==bm1)
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Strike\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
            else if(i==bm2)
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Non Strike\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
            else
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT\n",bat[i].id,bat[i].name,bat[i].runs,bat[i].balls);
            
        }
    }
	}
    printf("\n\tBOWLING TEAM STATS:\n\n");
    int j;
    for( j =1;j<=11;j++)
    {
        if(bowl[j].bowling)
            printf("\t%-3d%-10s: %-3dBalls  %-3dWickets\n",bowl[j].id,bowl[j].name,bowl[j].balls,bowl[j].wickets);
    }
    printf("\n\tOVERS: ");convertToOver(ball);
    printf("\tSCORE: %d",score);
    printf("\t%dvs%d",score,score2nd);
    printf("\textra: %d",extra);
}
/////////////////////////////////////////////////////////2nd innnig start////////////////////////////////////////////////////////////////////////
//function for 2nd inning
void Scorecard()
{
	swapnames();
    default2ndScores();
    scoring2ndProcess();

}//function for copying 1st inning batsmen as bowler
void swapnames()
{
	int i;
	for (i = 1; i<=11;i++)
	{
		bowl2nd[i].id=bat[i].id;
		strcpy(bowl2nd[i].name,bat[i].name);
	}
}
//Function for 2nd inning calculating score
void scoring2ndProcess()
{
	
    int b1,b2,nb,bo;
    char brun='1';
    while(ball<=overs*6)
    {
        if(ball==overs*6||score2nd>score)
        {
            system("cls");
            system("COLOR 40");
            for(i=3;i>0;i--)
		{
			printf("\n\t\t\t\t2nd inning ended\n\t\t\t%s's scoresheet Loading in.........%d\n",bat2nd,i);
			sleep(1);
			system("cls");
		}
		system("COLOR F3");
            scoreSheet2nd();
            break;
        }
        if(ball==0)
        {
            system("cls");
            printf("\n\n\n\t\t SELECT %s's BATSMAN\n\n",bat2nd);
            printf("\tID  Name        Runs      Balls\n");
            int i;
            for( i = 1; i<=11;i++)
            {
                printf("\t%-3d %-10s: %-3dRuns  %-3dBalls\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
            }
            top:
            printf("NOTE: Enter the valid ID number only from 1 to 11");
            printf("\n\tEnter FIRST Batsman ID (1-11): ");
            
            scanf("%d",&b1);
            if(b1<1 || b1>11)
            {
                printf("\n\tError:Invalid choice.");
                goto top;
            }else 
            {
                bm1=b1;
                bowl[b1].isBatting=true;
            }
            top1:
            printf("\tEnter SECOND Batsman ID (1-11): ");
            scanf("%d",&b2);
            if(bowl[b2].isBatting)
                {
                    printf("\tBatsman %d:%s is already batting.\n\tENTER AGAIN\n",bat[b2].id,bat[b2].name);
                    goto top1;
                }
            if(b2<1 || b2>11)
            { 
                printf("\n\tError:Invalid choice.");
                goto top1;
            }else 
            {
                bm2=b2;
                bowl[b2].isBatting=true;
            }
        }
        if(ball%6==0 && ball<overs*6)
        {
            system("cls");
            printf("\n\n\n\t\t SELECT %s's BOWLER\n\n",bat1st);
            printf("\tID  Name        Balls      Wickets\n");
            int j;
            for( j=1;j<=11;j++)
            {
                printf("\t%-3d %-10s: %-3dBalls  %-3dWickets\n",bowl2nd[j].id,bowl2nd[j].name,bowl2nd[j].balls,bowl2nd[j].wickets);
            }
            printf("\n\n\tEnter BOWLER ID (1-11): ");
            scanf("%d",&bo);
            bowl2ndid=bo;
            if(ball>5)
                switchb();
            bowl2nd[bo].bowling=true;
        }
	  int no_of_out=0;
	  label:
        if(ball<overs*6)
        {
        	wide2nd:
            system("cls");
            scoreSheet2nd();
            printf("\n\n\tEnter Ball(1-6 runs, 'o' for out,'w' for wide): ");
            scanf(" %c",&brun);
            if(brun=='0')
            {
                ballrun='0';
                bowl[bm1].runs+=0;
                bowl[bm1].balls++;
                bowl2nd[bowlid].balls++;
            } 
			else if(brun=='1')
            {
                ballrun=1;
                bowl[bm1].runs+=1;
                bowl[bm1].balls++;
                bowl2nd[bowlid].balls++;
                switchb();
            } 
			else if(brun=='2')
            {
                ballrun=2;
                bowl[bm1].runs+=2;
                bowl[bm1].balls++;
                bowl2nd[bowlid].balls++;
            } 
			else if(brun=='3')
            {
                ballrun=3;
                bowl[bm1].runs+=3;
                bowl[bm1].balls++;
                bowl2nd[bowlid].balls++;
                switchb();
            } 
			else if(brun=='4')
            {
                ballrun=4;
                bowl[bm1].runs+=4;
                bowl[bm1].balls++;
                bowl2nd[bowlid].balls++;
            } 
			else if(brun=='6')
            {
                ballrun=6;
                bowl[bm1].runs+=6;
                bowl[bm1].balls++;
                bowl2nd[bowlid].balls++;
            } 
            else if(brun=='w'||brun=='W')
            {
            	extra2nd++;
            	ballrun=1;
            	if(ball==0)
            	{
            		ball=0;
            		score2nd++;
            		goto wide2nd;
				}
				else
				{
					ball=ball-1;
				}
			}
			else if(brun=='o'||brun=='O')
            {
            	ballrun=0;
                bowl[bm1].out=true;
                bowl2nd[bowlid].wickets++;
                bowl2nd[bowlid].balls++;
                wick++;
                int a;
                for( a=1;a<=11;a++)
                {
                    if(bowl[a].out==true)
					{
                    	no_of_out++;
					}
                }
                if(no_of_out==10)//as there are only 11 player
                {
                    ball++;
                    system("cls");
                    printf("\n\n\t%s's FINAL scoresheet\n",bat2nd);
                    break;
                }
                bowl[bm1].isBatting=false;
                printf("\tBatsman %d: %s is out.",bat[bm1].id,bowl[bm1].name);
                first:
                printf("\n\tEnter new batsman(1-11): ");
                scanf("%d",&nb);
                if(bowl[nb].isBatting)
                {
                    printf("\tBatsman %d:%s is already batting.\n\tENTER AGAIN",bowl[nb].id,bowl[nb].name);
                    goto first;
                }
                if(bowl[nb].out)
                {
                    printf("\tBatsman %d:%s is already out.\n\tENTER AGAIN",bowl[nb].id,bowl[nb].name);
                    goto first;            
                }
                bowl[bm1].balls++;
                bowl[nb].isBatting=true;
                bm1=nb;
            }
			else
            {
                printf("\n\tInvalid possibility.Enter again.");
                goto label;
            }
        }
        ball++;
        score2nd=score2nd+ballrun;
   }	
}
//Function to set for 2nd inning default values
void default2ndScores()
{
    int i;
	for( i =0;i<11;i++)
    {
        bowl[i].balls=0;
        bowl[i].runs=0;
        bowl[i].out=false;
        bowl[i].isBatting=false;
        bowl2nd[i].balls=0;
        bowl2nd[i].wickets=0;
        bowl2nd[i].bowling = false;
    }
}
//Function to display the 2nd innning scoresheet.
void scoreSheet2nd()
{
	 if(ball==overs*6||score2nd>score)
    //system("cls");
    {
    	int gap=0;
    	//gap is the difference of score
    	FILE *fp;
		fp = fopen("cric.txt", "a");
		printf("\n\n\t%s's Final BATTING TEAM STATS:\n\n",bat2nd);
	    fprintf(fp,"\n\t\t%s's SCORE: %d\tExtra: %d\n",bat2nd,score2nd,extra2nd);   
	    int i;
		fp = fopen("cric.txt", "a");
    	for( i = 1; i<=11;i++)
    	{
        	if(bowl[i].out)
		{
        	printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  OUT\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
        	fprintf(fp,"\t%-3d%-10s: %-3dRuns  %-3dBalls  OUT\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
    	}
        else 
        {
            if(i==bm1)
            {
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Strike\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
            fprintf(fp,"\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Strike\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
        }
            else if(i==bm2)
            {
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Non Strike\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
            fprintf(fp,"\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Non Strike\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
        }
            else
			{
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
            fprintf(fp,"\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
        }
        }
	}
	system("cls");
	system("COLOR 4f");
	if(score>score2nd)
		{
			gap=score-score2nd;
			printf("\n\n\n\t\t\t\t%s won the match by %d runs",bat1st,gap);
			getch();
			fprintf(fp,"\n %s won the match by %d runs\n",bat1st,gap);
			}
	else if(score2nd>score)
		{
			gap=10-wick;
			printf("\n\n\n\t\t\t\t%s won the match by %d wickets",bat2nd,gap);
			fprintf(fp,"\n %s won the match by %d wickets\n",bat2nd,gap);
		}
	else if(score==score2nd)
		{
			printf("\n\n\n\t\t\t\tthe match tied");	
			fprintf(fp,"\n The match tied\n");	
		}
	printf("\n\t\t\t-----------------------------------------------\n");
	sleep(1);  
	printf(" \n\t\t\t\t\tDeveloped By :\n");
	printf(" \t\t\t\t\t1. Megha Gurung \n");
	printf(" \t\t\t\t\t2. Mausam Pariyar \n");
	printf(" \t\t\t\t\t3. Prashant Adhikari \n");
	printf("\n\t\t\t\t *** \\>  HAVE A GREAT TIME, SIR </ ***\n");
	system("pause");
	}
	else	
	{
	system("cls");
	printf("\n\n\t%s'sBATTING TEAM STATS:\n\n",bat2nd);
    for( i = 1; i<=11;i++)
    {
        if(bowl[i].out)
        printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  OUT\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
        else 
        {
            if(i==bm1)
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Strike\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
            else if(i==bm2)
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT  *Non Strike\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
            else
            printf("\t%-3d%-10s: %-3dRuns  %-3dBalls  NOT-OUT\n",bowl[i].id,bowl[i].name,bowl[i].runs,bowl[i].balls);
        }
    }
    printf("\n\t%s's BOWLING TEAM STATS:\n\n",bat1st);
    int j;
    for( j =1;j<=11;j++)
    {
        if(bowl2nd[j].bowling)
        printf("\t%-3d%-10s: %-3dBalls  %-3dWickets\n",bowl2nd[j].id,bowl2nd[j].name,bowl2nd[j].balls,bowl2nd[j].wickets);
    }
    printf("\n\tOVERS: ");convertToOver(ball);
    printf("\tSCORE: %d",score2nd);
    printf("\tEXTRA: %d",extra2nd);
    printf("\t%d vs %d",score2nd,score);
}}
//default over count and swapper for bothing inning
//Function to convert balls to overs.(ex: 7 balls to 1.1 overs)
void convertToOver(int balls1)
{
    int o=0,b=0;
    o=balls1/6;
    b=balls1%6;
    printf("%d.%d",o,b);
}

//Function to swtich batsman position(from strike to no strike)
void switchb()
{
    int temp=0;
    temp=bm1;
    bm1=bm2;
    bm2=temp;
}
void history()
{
	FILE* ptr;
    char ch,choice;
	system("cls");
	ptr = fopen("cric.txt", "r");
	//history part start
    if (ptr == NULL) 
	{
        printf("no such file.");
    }
    printf("Match history\n");
    do 
	{
        ch = fgetc(ptr);
        printf("%c", ch);
        // Checking if character is not EOF.
        // If it is EOF stop eading.
    } while (ch != EOF);
    printf("\n");
    system("pause");
    fclose(ptr);
    //history part end
    //delete(whole content)start
    system("cls");
    getchar();
    printf("Do you want to delete the file(y/n)?");
    scanf("%c",&choice);
    if(choice=='y'||choice=='Y')
    {
    	FILE* ptr = fopen("cric.txt", "w");
    	fclose(ptr);
	} 
	
}
//delete end
// Closing the file

    
