/*Name: Program of a gamble game called Roulette
File Name: Roulette.c
Date: Oct, 2016 - Dec, 2016
Author: Zhenghang Zhong(Klaus)
*/ 
#include<stdio.h>                  /*include information about standard buffered input&output stdio.h*/
#include<stdlib.h>                 /*include function to clear screen(system("cls"), rand(), malloc(), free() stdlib.h*/
#include<math.h>                   /**/
#include<windows.h>                /*include function of Sleep() windows.h*/
#include<time.h>                   /*include function of time() time.h*/
#include<conio.h>                  /*include function getch() conio.h*/

struct entry                       /*declare a struct to store the surname, given_name, password and money of an account*/
{
	char surname[31];
	char given_name[31];
	char password[51];
	long long money;
 };

int _create(char *filename);              /*define a _create function to enable uses to create a new account*/
int logIn(char *filename);                /*define a logIn function to enable users to log in with name and password*/
void _chessboard(void);                   /*define a _chessboard function to draw the whole chessboard */
void _gamble(int, char *filename);         /*define a _gamble function to enable users who has logged in to play the roulette game*/

int main(int argc, char *argv[])              /*define a main function with two variables of type int and char separetly */
{										  /*argc represents the number of files transferred to main(),argv[] represents the name of file*/
	int flag1=0, flag2, option;			  /*variable flag1 controls the while loop and flag2 controls whether users log in successfully*/
	int n;								  /*variable n represents the location of user's information in file*/
    FILE * fptr;                          /*declare a file pionter called fptr*/
	
    char filename[40]="account.dat";      /*name of file*/
    if(argc>1)							  /*Check if an additional argument (filename) has been added to the excution list*/
 	    {
	    strcpy(filename,argv[2]);		  /*If there is a filename copy it to the filename variable contining the default name*/
	    }
	
     fptr = fopen(filename,"ab");		  /*Try to open the file for writing or create the file if it doesn't exist - openmode is binary*/
 
     if(fptr == NULL)				      /*Test the success of fopen - close the program if failed*/
 		    {
	    	printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		    Sleep(2000);
		    exit(0);
		    }
 
    fclose(fptr);						  /*close the file*/
    
     while(flag1==0)				      /*enter a while loop to keep the program running till the user selects option 3*/
 	{
 		flag2=0;
 		Sleep(2000);
	    system("cls");	  
	    printf("choose the mode:\n1.create a new account\n2.log in!\n3.End the program.\n");
	    while(scanf("%d",&option)!=1 && (option<1 || option>3))		/* Display menu and get user entry - check user entry validity*/
 		{
			printf("Invalid entry\n\n");
			Sleep(1000);
			fflush(stdin);
			system("cls");
			printf("choose the mode£»\n1.create a new account\n2.log in!\n3.End the program.\n");
	    }
		switch(option){
			case 1: _create(filename);	    	  /*call function _create*/
					break;
			case 2: n = logIn(filename);          /*call function logIn*/
					if(n==0) break;
					flag2=1;                      /*call function _gamble later*/
					break;
			case 3: flag1=1;			          /*set flag 1 to end the program loop and close the program*/
					break;
			
		}
		if(flag2==1)   							  /*n-1 means the location of user in the file*/
			_gamble(n-1,filename); 
	}
	
	printf("\n\nThank you for playing!");
    Sleep(2000);
    return 0;									  /*return 0 to the system indicating successful program execution and termination*/
}

int _create(char *filename){              						/*create a new account*/
	struct entry account,person;   								/*struct account store information from file, struct person store user' input information*/
	FILE *fptr;
	
	fflush(stdin);	 
 	system("cls"); 
 	
 	printf("Hint£ºNo blank space between characters, the one after blank space will be ignored!!\n\n");
 	printf("Please enter the surname of the person:\n\n\t");								/*Obtain each structure member information checking each for validity*/
 	while(scanf("%s",person.surname)==0 || strlen(person.surname)>30)  						/*The logic expression is evaluated from left to right so the scanf is evaluated first to ensure the string is read*/
 	{																						/*the right hand side checks the value obtained by the scanf to ensure the length of the string is less than maximum length*/
		printf("Please try again and make sure the name has less than 30 characters");
		fflush(stdin);
		Sleep(2000);
		system("cls");
 		printf("Please enter the surname of the person\n\n\t");
	}
	fflush(stdin);		/*Ensure input buffer is empty*/
		
 	printf("Please enter the given name of the person:\n\n\t");
	 while(scanf("%s",person.given_name)==0 || strlen(person.given_name)>30)
 	{
		printf("Please try again and make sure the name has less than 30 characters");
		fflush(stdin);
		Sleep(2000);
		system("cls");
 		printf("Please enter the given name of the person:\n\n\t");
	}
	
	fptr = fopen(filename,"ab+");
	if(fptr == NULL) 		/*Test the success of opening the file*/
 		{
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
		}
		
	while(fread(&account,sizeof(struct entry),1,fptr)==1){
		if(strcmp(account.surname,person.surname)!=0 || strcmp(account.given_name,person.given_name)!=0)
			continue;
		else{ 
			fclose(fptr);
			printf("Sorry, the same account exists!\n");
			return 0;					/*return 0 to indicate the name was found and that the values have been written to the variable in function main*/
		}		
	}
	
	if(feof(fptr)==0){
		fclose(fptr);
		printf("Sorry, read the file error!\n");
		exit(0); 
	}
	
	printf("Please enter the password of your account:\n\n\t");
	 while(scanf("%s",person.password)==0)							
 	{
		printf("Please try again and make sure the number has less than 19 digits");
		fflush(stdin);
		Sleep(2000);
		system("cls");
 		printf("Please enter the password of your account:\n\n\t");
	}
	
	printf("Please credit you account with some money for following game!\n");
	while(scanf("%lli",&person.money)==0||person.money<10){      						/* %lli is the format type for a long long*/
		printf("Please try again and make sure the number are correct");
		fflush(stdin);
		Sleep(2000);
		system("cls");
 		printf("Please credit you account with some money for following game!\n\n\t");
	}
	printf("Success to credit the money, now you have %lli Yuan in total",person.money);
	
	fseek(fptr, 0L, SEEK_END);
	fwrite(&person,sizeof(struct entry),1,fptr);					/*refresh the information*/
 	fclose(fptr); 													/*Close the file*/
	   
}

int logIn(char *filename){
	int flag=0,n=0;
	FILE *fptr;
	long long credit;
	char searchs[31], searchg[31],password[51];	         		 	 /*declare 3 variables to store the information of user temporaryly*/
	struct entry person;    										 /*declare a struct of type entry*/
	
	fflush(stdin);	            									 /*clear the standard input buffer*/
	
 	printf("Please enter the surname:\n");
 	while(scanf("%s",searchs)==0 || strlen(searchs)>30 ) 			 /*Test the entry of the persons name*/
 	{
		printf("Please try again and make sure the name are less than 30 characters long");
		fflush(stdin);
		Sleep(2000);
		system("cls");
 		printf("Please enter the surname of the person");
	}
	fflush(stdin);
	printf("Please enter the given name:\n");
	while(scanf("%s",searchg)==0 || strlen(searchg)>30 ) 			 /*Test the entry of the persons name*/
 	{
		printf("Please try again and make sure the name are less than 30 characters long");
		fflush(stdin);
		Sleep(2000);
		system("cls");
 		printf("Please enter the given_name of the person");
	}
	
	printf("Please enter your password:\n");
	while(scanf("%s",password)==0 || strlen(password)>50) 			/*Test the entry of the persons name*/
 	{
		printf("Please try again and make sure the password are less than 50 characters long");
		fflush(stdin);
		Sleep(2000);
		system("cls");
 		printf("Please enter your password:\n");
	}

  	fflush(stdin);
	
	fptr = fopen(filename,"rb+");       							/*open the file in rb+ mode*/
	if(fptr == NULL) 												/*Test the success of opening the file*/
 		{
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
		}
		
	fseek(fptr,0L,SEEK_SET);										/*set the cursor to the beginning of file*/	
	
	while(fread(&person,sizeof(struct entry),1,fptr)==1){           /*read until find same account or to the end of file*/
		if(strcmp(person.surname,searchs)!=0 || strcmp(person.given_name,searchg)!=0)
		{
			n++;           											/*n represents the location of cursor is in size of n structure entry*/
			continue;	
		}
		else{
			flag=1;                                 				/*No existing accounts*/
			break;
		}
	}
		
		if(flag==1) {
			if(strcmp(person.password,password)==0){                /*judge if password is correct*/
				printf("Log in succesffully!\nYou have\t%lli\tYuan\tLeft.\nWould you like to credit more money, Yes: press 'Y', No: press other buttons!\n",person.money);
				if(getch()=='Y'){									/*credit more money*/
					printf("Please input the money!\n");
					while(scanf("%lli",&credit)!=1||credit<10){  				/*store the money user rechargeg in variable credit*/
						printf("Sorry, please input the number in correct form!\n");
						fflush(stdin);
						printf("Please input the money!\n");
					}
					person.money=(person.money+credit);
					fseek(fptr,0L,SEEK_SET);
					fseek(fptr,sizeof(struct entry)*n,SEEK_CUR);    /*find the location of user's information*/
					fwrite(&person,sizeof(struct entry),1,fptr);	/*refresh the information whole structure*/
					printf("Rechange the money successfully, now you have %lli Yuan in total!!\n",person.money); 
							
					fclose(fptr);
					}	   	    		
				return n+1;
			}
			else{
				printf("Sorry, the password is not correct, please have another try!");
				fclose(fptr);
				return 0;
			}
		}
		else{
			printf("No such account exists, you can register a new account!\n");
			fclose(fptr);
			return 0;
		}
}

void _gamble(int number, char *filename){                            /*begin the game*/
	int i,k,Bets,delay,flag3=1;										/*Bets stands the number of bets user would place*/
	char key,*Num;
	long long bMoney,cMoney;										/*bMoney stores the money user want to bet every time,cMoney stores the money user want recharge*/
	struct entry person;
	FILE *fptr;
	
	system("cls");
	fptr = fopen(filename,"rb+");
	if(fptr == NULL) 												/*Test the success of opening the file*/
 		{
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
		}
	fseek(fptr,sizeof(struct entry)*number,SEEK_SET);
	fread(&person,sizeof(struct entry),1,fptr);
	fclose(fptr);
	
	while(flag3==1){
	fflush(stdin);
	system("cls");
	_chessboard();
	printf("\tWelcome to Roulette Royale!!!\t\tYou have %lli Yuan left!!\n\n1.Press 'B' to start the game!!!\n",person.money);        /*show the money user has*/
	printf("2.Press 'Y' to rechange more money!\n3.Press 'R' to log out and return to beginning interface.\nHint: The numbers in bracket are where you could place your bets\n\n");
	
	fflush(stdin);
	while(scanf("%c",&key)!=1){
		printf("Error!!please enter an character as asked!\n");
		fflush(stdin);
	} 
	
	if(person.money>=10&&key=='B'){         		/*start the game*/
		system("cls");
		_chessboard();                  			/*draw the chessboard*/
		printf("\nEnter the bets you want to place!!\tYou have %lli Yuan left!!\n\nHint: The bets you place could only be 10, 100, 1000, 10000 !!!\n",person.money);
		while(scanf("%lli",&bMoney)!=1||(bMoney!=10&&bMoney!=100&&bMoney!=1000&&bMoney!=10000)){        /*The bets could only be 10, 100, 1000 and 10000 every time*/
			printf("Sorry, but error happend. Check if the bets you place is not as asked!!!\n");
			fflush(stdin);
			printf("\nEnter the bets you want to place!!\tYou have %lli Yuan left!!\n\nHint: The bets you place could only be 10, 100, 1000, 10000 !!!\n",person.money);
		} 
		
		printf("Enter how many bets you want place!!!(an integer according your money)\n"); 
		while(scanf("%d",&Bets)!=1||bMoney*Bets>person.money){                            			/*when user's money is not enough*/
			printf("Error!! Check if the number entered is not allowed or your money is not enough!!\n");
			fflush(stdin);
			printf("Please input the number of bets you want \n");
		}
		person.money=person.money-bMoney*Bets;											/*minus the money used to bet*/
		
		Num = (char *)malloc(Bets * sizeof(char *));      								/*creates a block of memory space with a size of Bets * the byte size of a char variable*/
	
		printf("Please start your bets! Seperate numbers with blank space!!\n");
		for(i = 0;i<Bets;i++){
			while(scanf("%d",&Num[i])!=1||Num[i]>43||Num[i]<0){         				/*the number users bet could only between 0 and 42 and 37 to 42 represents an area of numbers rather than a number*/
				printf("Error!!Check if the number entered is not allowed or it's not in [0,42] !!\n");
				fflush(stdin);
				printf("Please start your bets! Seperate numbers with blank space!!\n");
			}
		} 
		printf("You have %lli Yuan left!!\n\n",person.money);
		Sleep(1000);
		printf("Begin!!!\n\n");
		
		srand(time(0));         				/*create a srand according to time function*/
		delay=60;
		for(i = 0;i<15;i++){
			k= rand()%37;		   				/*k is in the interval [1,COLS]*/  
			printf("XXX\t%02d\tXXX",k);         /*to simulate the process of turning the turntable*/
			printf("\r"); 						/*only refresh the current row */
			Sleep(delay);
			delay=delay+i*i;					/*to make the change speed of numbers slower and slower, as a simulation*/
		}
		printf("\n\nThe final number is %d",k);
		
		for(i = 0;i<Bets;i++){         			/*judge if user wins and obtain money*/
			if(Num[i]==k) person.money=person.money+37*bMoney;
			
			if((Num[i]==37&&k>=1&&k<=12) || (Num[i]==38&&k>=13&&k<=24) || (Num[i]==39&&k>=25&&k<=36)) person.money=person.money+3*bMoney;
			
			if((Num[i]==40&&k>=1&&k<=18)||(Num[i]==41&&k>=19&&k<=36)) person.money=person.money+2*bMoney;

			if(Num[i]==42&&k%2==0&&k!=0) person.money=person.money+2*bMoney;
			
			if(Num[i]==43&&k%2==1)       person.money=person.money+2*bMoney;
		}
		free(Num);
	}
		
	else if(key=='Y'){
		printf("Please enter the money you want to recharge! More than 10 Yuan!\n");
		while(scanf("%lli",&cMoney)!=1||cMoney<10){
		 	printf("Error!! please have another try! More than 10 Yuan are accepted!\n");
		 	fflush(stdin);
		 	printf("Please enter the money yoy want to recharge! More than 10 Yuan!");
		}
		person.money=person.money+cMoney;
	}
	else if(key=='R') flag3=0;       /*exit and return to stating interface*/
	else{
		printf("Check if your money is less than 10 or gave a wrong instruction!!\n");
		fflush(stdin);
	}
	
	fptr = fopen(filename,"rb+");
	if(fptr == NULL) 												/*Test the success of opening the file*/
 		{
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
		}
	fseek(fptr,sizeof(struct entry)*number,SEEK_SET);
	fwrite(&person,sizeof(struct entry),1,fptr);
	fclose(fptr);
	
	printf("\nYou have %lli Yuan left!!\nPress any button to continue!\n",person.money);
	getch();	
}
}

void _chessboard(void){            /*draw the chessboard*/
	int i,j,k;
	int Nums = 37;
	char *chessboard;
	chessboard = (char *)malloc(Nums * sizeof(char *));                                                      /*creates a block of memory space with a size of ROWS * the byte size of a pointer to a char pointer*/
	
	for(i = 0;i<Nums;i++) *(chessboard+i) = i;
	printf("\t\t\t\tRoulette Royale\n\n\t");
	for(j=3;j<=36;j=j+3) printf("%d    ",*(chessboard+j));
	printf("\n\n   %d\t",*chessboard);
	for(j=2;j<=35;j=j+3) printf("%d    ",*(chessboard+j));
	printf("\n\n\t");
	for(j=1;j<=34;j=j+3) printf("%d    ",*(chessboard+j));
	printf("\n\n\t------------------------------------------------------------------\n");
	printf("\t|     1st (37)     |       2nd (38)       |       3rd (39)       |\n");          /*37 declares numbers from 1 to 12, 38 declares numbers from 13 to 24, 39 declares numbers from 25 to 36*/
	printf("\t------------------------------------------------------------------\n");
	printf("\t|   1-18 (40)   |    EVEN (42)   |    ODD(43)   |    19-36 (41)  |\n");          /*42 declares even numbers, 43 declares odd numbers*/
	printf("\t------------------------------------------------------------------\n");
	
	free(chessboard);     			/*free the block of memory space created before*/
}




