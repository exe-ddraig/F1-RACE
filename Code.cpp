#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

char user[50] = {'\0'}, pass[50] = {'\0'}, f_user[50] = {'\0'}, f_pass[50] = {'\0'}, t_user[50] = {'\0'};
int login(), signup();
char c_user[50] = {'\0'};
char y_n;

void g_pass(char *pass) 
{
    int i = 0;
    char ch;

    while (i < 50) 
	{
        ch = getch();

        if (ch == 13)
		{
            pass[i] = '\0';
            printf("\n");
            break;
        }
        else if (ch == 8) 
		{
            if (i > 0) 
			{
                i--;
                printf("\b \b");
            }
        }
        else 
		{
            pass[i++] = ch;
            printf("*");
        }
    }
}

int signup()
{
	FILE *fp = fopen("accounts.txt","a+");

	if(!fp)
	{
		printf("\n\t\t\t\t\t\t\t\t     Unexpected Error! Game Crashed\n");
		exit(0);
	}

	while (1) 
	{
		int taken=0;

		while(1)
		{
			int found = 0;
			fflush(stdin); 

			printf("\n\n\t\t\t\t\t\t\t  Enter the username: ");
			scanf("%49[^\n]", t_user);

			if(t_user[0] == '\0')
			{
				printf("\n\n\t\t\t\t\t\t\t  Please Enter A Name!!\n");
				continue;
			}

			for(int i=0; i<strlen(t_user); i++)
			{
				if(t_user[i] == ',')
				{
					printf("\n\n\t\t\t\t\t\t\t  Please Enter A Valid Name!!\n");
					found = 1;
					break;
				}
			}

			if(!found)
			{
				break;
			}
		}

		rewind(fp);
		while(fscanf(fp,"%[^,],%[^\n] ",f_user, f_pass) != EOF)
		{
			if (strcmp(t_user, f_user) == 0) 
			{
				printf("\n\n\t\t\t\t\t\t\t  Nick Already Taken! Choose Another\n");
				taken=1;
				break;
    		}
		}

		if(!taken)
    	{
			break;
		}

		printf("\n\n\t\t\t\t\t\t\t  Already have an account!? Log in now(Y or N): ");
		y_n = getche();
		fflush(stdin);

		if(y_n=='Y' || y_n=='y')
		{
			fflush(stdin);
			fclose(fp);
			return login();
		}
		else if(y_n=='N' || y_n=='n')
		{
			fflush(stdin);
			continue;
		}
		else
		{
			fflush(stdin);
		}
	}

    strcpy(user,t_user);
    
    while(1)
    {
    	fflush(stdin); 

    	printf("\n\t\t\t\t\t\t\t  Enter new password: ");
	    g_pass(pass);
	  			
		if(pass[0] == '\0')
		{
			printf("\n\n\t\t\t\t\t\t\t  Please Enter A Password!!\n");
			continue;
		}
		break;
	}

	fprintf(fp,"%s,%s\n", user, pass);
    fclose(fp);

    printf("\n\t\t\t\t\t\t\t  Account created successfully!\n\n");
    Sleep(700);
    system("cls");
    return 1;
}

int login()
{
	int tries=5;
    FILE *fp = fopen("accounts.txt","r");
    if(!fp)
    {
        printf("\n\t\t\t\t\t\t\t  Unexpected Errror! Game Crashed\n");
        exit(0);
    }

    while(1)
    {
    	t_user[0] = {'\0'};
    	int check;
        fflush(stdin);
        while(1)
		{
			int check = 0;
			fflush(stdin); 

			printf("\n\n\t\t\t\t\t\t\t  Enter the username: ");
			scanf("%49[^\n]", t_user);

			if(t_user[0] == '\0')
			{
				printf("\n\n\t\t\t\t\t\t\t  Please Enter A Name!!\n");
				continue;
			}
			
			for(int i=0; i<strlen(t_user); i++)
			{
				if(t_user[i] == ',')
				{
					printf("\n\n\t\t\t\t\t\t\t  Please Enter A Valid Name!!\n");
					check = 1;
					break;
				}
			}
			
			if(!check)
			{
				break;
			}
		}

        int found = 0;
        rewind(fp);

        while(fscanf(fp,"%[^,],%[^\n] ",f_user,f_pass) != EOF)
        {
            if(strcmp(t_user,f_user) == 0)
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            printf("\n\t\t\t\t\t\t\t  Username Not Found! Want To Create New Account!?\n");
            printf("\n\t\t\t\t\t\t\t  Sign Up Now(Y or N): ");
			y_n = getche();
			printf("\n");
			fflush(stdin);
			
			if(y_n=='Y' || y_n=='y')
			{
				fflush(stdin);
				fclose(fp);
				return signup();
			}
			else if(y_n=='N' || y_n=='n')
			{
				fflush(stdin);
				continue;
			}
			else
			{
				fflush(stdin);
			}
            Sleep(700);
            continue;
        }

        while(1)
        {
            fflush(stdin);
            printf("\n\t\t\t\t\t\t\t  Enter Password: ");
            g_pass(pass);
			
			if(tries<=0)
			{
				printf("\n\n\t\t\t\t\t\t     Too Many Incorrect Tries! Try Signing up again.");
				return signup();
			}
			
            if(strcmp(pass,f_pass) == 0)
            {
                printf("\n\t\t\t\t\t\t\t  Login Successful!\n");
                strcpy(user,t_user);
                Sleep(700);
                system("cls");
                fclose(fp);
                return 1;
            }
            else
            {
            	printf("\n\t\t\t\t\t\t\t  Wrong Password! %d Tries remain.\n", tries);
            	tries--;
			}
        }
    }
}


int main()
{
	HANDLE Console=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorpos={0,0};
	CONSOLE_CURSOR_INFO cursorinfo;
	GetConsoleCursorInfo(Console,&cursorinfo);
	cursorinfo.bVisible=FALSE;
	SetConsoleCursorInfo(Console,&cursorinfo);
	SetConsoleTitle("F1 RACE");

	int road_l=10, road_w[5]={60, 66, 72, 78, 84}, c_lane=2, fuel=100, speed=80;
	int obs=4, obs_r[obs], obs_l[obs], p_obs, w_obs;
	int pwr_r=-1, pwr_l=0, t_pwr=0;
	int s_pwr_r=-1, s_pwr_l=0, s_t_pwr=0;
	int menu, mode, s_flag=0, m_flag=0, pits=3, rl_keyd, spawn_t, score=0, crash, end;
	int i_laps, i_load, i_exit, i_space1, i_space2, i_frame=0, i_beep, i_obs;

	srand((unsigned)time(NULL));

	int choice, logged_in=0;

    while (1) 
	{		
		while(!logged_in)
		{
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t=============== LOGIN  MENU ===============\n"
				   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t     1. Sign Up\t\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t     2. Log  In\t\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t     3. Exit\t\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
				   "\t\t\t\t\t\t\t===========================================\n\n");
	        printf("\t\t\t\t\t\t\t\t     Enter choice: ");
	        scanf("%d", &choice);
	
	        if (choice == 1)
	        {
	        	logged_in = signup();
	        	break;
			}
	        else if (choice == 2)
	        {
	        	logged_in = login();
	        	break;
			} 
			else if( choice == 3)
			{
				printf("\n\t\t\t\t\t\t\t\t     Exiting Game");
				Beep(1000, 200);
				for(int i=0; i<3; i++)
				{
					printf(".");
					Sleep( 700 );	
				}
				exit( 0 );
			}
	        else
	        {
	        	printf("\n\t\t\t\t\t\t\t\t     Invalid option!\n");
	        	fflush(stdin);
	            Sleep(1200);
	            system( "cls" );
			}
		}
        
		while(1)
		{
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t================ GAME  MENU ===============\n"
				   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t     1. Start\t\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t     2. Pit Stop\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t     3. View Stats\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t     4. High Scores\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t     5. Game History\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t     6. Log Out\t\t\t ||\n"
				   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
				   "\t\t\t\t\t\t\t===========================================\n\n");
			printf("\t\t\t\t\t\t\t\t     Enter choice: ");
			scanf( " %d", &menu );
			
			switch (menu)
			{
				case 1:
				{
					fflush(stdin);
					
					s_flag = 1;	spawn_t = 0;	w_obs = 0;	pwr_r = -1;	pwr_l = 0;	t_pwr = 0;	s_pwr_r = -1;	s_pwr_l =0;	s_t_pwr=0;
					
					for( i_obs = 0; i_obs < obs; i_obs++ )
					{
						obs_r[i_obs] = -2;
					}
					
					if(m_flag==0)
					{
						while(1)
						{
							system( "cls" );
							fflush( stdin );
							
							printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t============ SELECT DIFFICULTY ============\n"
									   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
									   "\t\t\t\t\t\t\t||\t 1. Easy  \t\t\t ||\n"
									   "\t\t\t\t\t\t\t||\t 2. Medium\t\t\t ||\n"
									   "\t\t\t\t\t\t\t||\t 3. Insane\t\t\t ||\n"
									   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
									   "\t\t\t\t\t\t\t===========================================\n\n");
							printf("\t\t\t\t\t\t\t\tEnter Difficulty Mode: ");
							scanf( " %d", &mode );
							
							switch( mode )
							{
								case 1:
								{
									speed=80;
									break;
								}
								case 2:
								{
									speed=40;
									break;
								}
								case 3:
								{
									speed=1;
									break;
								}
								default:
								{
									fflush(stdin);
									printf("\n\t\t\t\t\t\t\t\t     Invalid Input.");
									Sleep(1200);
									break;
								}
							}
							if( mode >= 1 && mode <= 3 )
							{
								break;
							}
						}
						m_flag=1;
					}
					
					printf("\n\t\t\t\t\t\t\t      Loading Engine...[");
					for(i_load=0; i_load<10; i_load++, Sleep(100))
					{
						printf("#");
					}
					printf("]\n\t\t\t\t\t\t\t      Race Started!! Zoom Zoom\n\n");
					Beep(800,400);
					Sleep(1200);
					system("cls");
					
					while(1)
					{
						cursorpos.X=0;
						cursorpos.Y=15;
						SetConsoleCursorPosition(Console,cursorpos);
						
						printf("\t\t\t\t\t\t\t     Score:%3d   Fuel:", score);
						if(fuel > 60) 
						{
				            SetConsoleTextAttribute(Console, 10);
				        } 
						else if(fuel > 30) 
						{
				            SetConsoleTextAttribute(Console, 6);
				        } 
						else 
						{
				            SetConsoleTextAttribute(Console, 4);
				        }
						printf("%3d  ", fuel );
						SetConsoleTextAttribute(Console, 7);
						printf("Pits:%d\n", pits);
						printf("\t\t\t\t\t\t\t    -------------------------------\n");
						
						if(w_obs==0)
						{
							spawn_t++;
							if(spawn_t>=12)
							{
								w_obs=4;
								spawn_t=0;
							}
						}
						
						else
						{
							for(i_obs=0; i_obs<obs; i_obs++)
							{
								if(obs_r[i_obs]==-2)
								{
									obs_l[i_obs]=rand()%5;
									obs_r[i_obs]=-1;
									w_obs--;
									break;
								}	
							}
						}
						
						for(i_obs=0; i_obs<obs; i_obs++)
						{
							if(obs_r[i_obs]!=-2)
							{
								obs_r[i_obs]++;
								if(obs_r[i_obs]>=road_l)
								{
									obs_r[i_obs]=-2;
								}
							}
						}
						
						t_pwr++;
						if(pwr_r == -1 && t_pwr >= 30)
						{
							pwr_l = rand() % 5;
							pwr_r = 0;
							t_pwr=0;
						}
						else if(pwr_r != -1)
						{
							pwr_r++;
							if(pwr_r >= road_l)
							{
								pwr_r = -1;
							}
						}
						
						s_t_pwr++;
						if(s_pwr_r == -1 && s_t_pwr >= 1000)
						{
							s_pwr_l = rand() % 5;
							s_pwr_r = 0;
							s_t_pwr=0;
						}
						else if(s_pwr_r != -1)
						{
							s_pwr_r++;
							if(s_pwr_r >= road_l)
							{
								s_pwr_r = -1;
							}
						}
						
						for(i_space1=0; i_space1<road_l; i_space1++) 
						{  
							if (i_space1 < (road_l-1)) 
							{
								for (i_space2=0; i_space2<=90; i_space2++) 
								{
	        						p_obs=0;
									for (i_obs=0; i_obs<obs; i_obs++) 
									{
										if (obs_r[i_obs]==i_space1 && i_space2==road_w[obs_l[i_obs]]+2 && (i_space2>=60)) 
										{
											SetConsoleTextAttribute(Console, 4 );
											printf("XXX");
											SetConsoleTextAttribute(Console, 7 );
	                						i_space2+=2;
	                						p_obs=1;
	            						}
	        						}
	
	        						if (p_obs)
	        						{
	        							continue;
									}
									
									if (pwr_r == i_space1 && i_space2 == road_w[pwr_l]+2 && (i_space2>=60)) 
									{
										SetConsoleTextAttribute(Console, 10 );
										printf("+++");
										SetConsoleTextAttribute(Console, 7 );
							            i_space2 += 2;
							            continue;
							        }
							        
							        if (s_pwr_r == i_space1 && i_space2 == road_w[s_pwr_l]+2 && (i_space2>=60)) 
									{
										SetConsoleTextAttribute(Console, 3 );
										printf("+++");
										SetConsoleTextAttribute(Console, 7 );
							            i_space2 += 2;
							            continue;
							        }
	
	        						if (((i_space1+i_frame)%2==1) && (i_space2%6==0) && (i_space2>=60)) 
									{
	            						printf("|");
							        } 
									else 
									{
	        						    printf(" ");
	        						}
	    						}
							}
							else if(i_space1==(road_l-1))
							{
								for(i_space2=0; i_space2<=90; i_space2++)
								{
									if(i_space2==road_w[c_lane]+1)
									{
										SetConsoleTextAttribute(Console, 6 );
										printf("|/^\\|");
										SetConsoleTextAttribute(Console, 7 );
										i_space2+=4;
										continue;
									}
									p_obs = 0;
	        						for (i_obs=0; i_obs<obs; i_obs++) 
									{
	            						if (obs_r[i_obs]==i_space1 && i_space2==road_w[obs_l[i_obs]]+2 && (i_space2>=60)) 
										{
											SetConsoleTextAttribute(Console, 4 );
	                						printf("XXX");
	                						SetConsoleTextAttribute(Console, 7 );
	    						            i_space2 += 2;
	            						    p_obs = 1;
	            						    continue;
	            						}
	        						}
	        						
	        						if (p_obs)
	        						{
	        							continue;
									}
									
									if (pwr_r == i_space1 && i_space2 == road_w[pwr_l]+2 && (i_space2>=60)) 
									{
										SetConsoleTextAttribute(Console, 10 );
										printf("+++");
										SetConsoleTextAttribute(Console, 7 );
							            i_space2 += 2;
							            continue;
							        }
									
									if (s_pwr_r == i_space1 && i_space2 == road_w[s_pwr_l]+2 && (i_space2>=60)) 
									{
										SetConsoleTextAttribute(Console, 3 );
										printf("+++");
										SetConsoleTextAttribute(Console, 7 );
							            i_space2 += 2;
							            continue;
							        }
							        
									
	        						if (((i_space1 + i_frame)%2==1) && i_space2%6==0 && (i_space2>=60)) 
									{
	            						printf("|");
	        						}
									else 
									{
	            						printf(" ");
	        						}
	    						}
							}
							printf("\n");
						}
					
						Sleep(speed);
						i_frame++;
						
						printf("\t\t\t\t\t\t\t    -------------------------------\n");
						
						crash=0;
						
						for (i_obs=0; i_obs<obs; i_obs++) 
						{
	    					if (obs_r[i_obs]==road_l-1 && obs_l[i_obs]==c_lane)
							{
	        					crash=1;
								break;
	    					}
						}
						
						if(crash)
						{
							Beep(1200,100); Beep(300,100);
	        				printf("\t\t\t\t\t\t\t    Crashed! Game Over\n");
	        				Sleep(1200);
	        				printf("\t\t\t\t\t\t\t    Your Score: %d\n", score);
	        				Sleep(1200);
	        				
	        				FILE *log = fopen("games_log.txt","a");
							fprintf(log,"%s,%d\n", user, score); 
							fclose(log);
	       				
	    					score = 0; speed = 80;	pits = 3;	fuel = 100;	s_flag=0;	m_flag=0;
	    					
							break;	
						}
						
						if (pwr_r == road_l - 1 && pwr_l == c_lane) 
						{	
							fuel+=4;
							Beep(500,50);
						    pwr_r = -1;
						}
						
						if (s_pwr_r == road_l - 1 && s_pwr_l == c_lane) 
						{	
							pits++;
							Beep(500,50);
						    s_pwr_r = -1;
						}
						
						score++;
						
						if(kbhit())
						{
							rl_keyd=getch();
							if(rl_keyd==97 && c_lane>0)
							{
								c_lane--;
								fuel--;
							}
							else if((rl_keyd==97 && c_lane<=0) || (rl_keyd==100 && c_lane>=4))
							{
								Beep(1000,50);
								fflush(stdin);
							}
							else if(rl_keyd==100 && c_lane<4)
							{
								c_lane++;
								fuel--;
							}
							else if(rl_keyd==224)
							{
								rl_keyd=getch();
								{
									if(rl_keyd==75 && c_lane>0)
									{
										c_lane--;
										fuel--;
									}
									else if((rl_keyd==75 && c_lane<=0) || (rl_keyd==77 && c_lane>=4))
									{
										Beep(1000,50);
										fflush(stdin);
									}
									else if(rl_keyd==77 && c_lane<4)
									{
										c_lane++;
										fuel--;
									}
								}
							}
							else if(rl_keyd==27)
							{
								break;
							}
						}
						
						if(fuel<=0)
						{	
							for (i_beep = 200; i_beep <= 1000; i_beep += 100) 
							{
							    Beep(i_beep, 50);
							}
							printf("\n\n\t\t\t\t\t\t\t    Fuel ran out!!");
							break;
						}
						
						if(i_frame%10==0)
						{
							fuel--;
						}
						
						if(i_frame%30==0 && speed>1)
						{
							speed--;							
						}
					}
					
					printf("\n\n\t\t\t\t\t\t\t    Returning To Main Menu...[");
					for(i_load=0;i_load<10;i_load++)
					{
						printf("#");
						Sleep(100);
					}
					printf("]");
					Beep(1000,100);
					Sleep(700);
					while (kbhit()) 
					{
						
						getch();
					}
					break;
				}
				case 2:
				{
					fflush(stdin);
					system("cls");
					if(s_flag==0)
					{
						printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t===========================================\n"
							   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
							   "\t\t\t\t\t\t\t||\tYou Must Start the Race First\t ||\n"
							   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
							   "\t\t\t\t\t\t\t===========================================\n\n");
						Sleep(1200);
						break;
					}
					if(pits>0)
					{
						for (i_beep = 200; i_beep <= 1000; i_beep += 100) 
						{
						    Beep(i_beep, 100);
						}
						printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t===========================================\n"
							   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
							   "\t\t\t\t\t\t\t||\t  Car Stopped for Refueling  \t ||\n"
							   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
							   "\t\t\t\t\t\t\t===========================================\n\n");
							   
						Sleep(800);
						pits--;	
						fuel=100;
						speed=100;
					}
					else
					{
						printf("No Pit Stops Left!\n");
						pits--;
					}
					Sleep(100);
					system("cls");
					break;
				}
				case 3:
				{
					fflush(stdin);
					system("cls");
					
					if(s_flag==0)
					{
						printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t===========================================\n"
							   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
							   "\t\t\t\t\t\t\t||\tYou Must Start the Race First\t ||\n"
							   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
							   "\t\t\t\t\t\t\t===========================================\n\n");
							   
						Sleep(1200);
					
						break;
					}
					else
					{
						printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t================== STATS ==================\n"
							   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
							   "\t\t\t\t\t\t\t||\t\tFuel: %d \t\t ||\n"
							   "\t\t\t\t\t\t\t||\t\tScore: %d\t\t ||\n"
							   "\t\t\t\t\t\t\t||\t    Pit Stops Left: %d    \t ||\n"
							   "\t\t\t\t\t\t\t||\t\t\t\t\t ||\n"
							   "\t\t\t\t\t\t\t===========================================\n\n",fuel, score, pits);
					}				
					printf("\t\t\t\t\t\t\t  Press ESC To Go Back To Main Menu...");
					do
					{
						end = getch();
					}while(end != 27);
					break;
					
				}
				
				case 4:
				{
					fflush(stdin);
					system("cls");
					
					char players[100][50], t_p_name[50];
					int t_p_score, p_score[100];
					int n_turn, f_flag, index, t_players=0;
					int temp_s;	char temp_n[50];
					
					for( int i = 0; i < 100; i++ )
					{
						players[i][0] = '\0' ;
						p_score[i] = 0;
					}
					
					FILE *hs = fopen("games_log.txt", "r");
	
					printf( "\n\n" );
					while( fscanf( hs,"%[^,],%d ", t_p_name, &t_p_score ) == 2 )
					{
						f_flag=0;
						for(int i = 0; i < t_players; i++)
						{
							if( strcmp( players[i], t_p_name ) == 0 )
							{
								f_flag=1;
								index=i;
								break;
							}
						}
						if( f_flag )
						{
							if( t_p_score > p_score[index] )
							{
								p_score[index] = t_p_score;
							}
						}
						else
						{
							strcpy( players[t_players], t_p_name );
							p_score[t_players] = t_p_score;
							t_players++;
						}
					}
	
					fclose(hs);
					
					for( int i=0; i<t_players-1; i++ )
					{
						for( int j=i+1; j<t_players; j++ )
						{
							if( p_score[j] > p_score[i] )
							{
								temp_s = p_score[i];
								p_score[i] = p_score[j];
								p_score[j] = temp_s;
	
								strcpy( temp_n, players[i] );
								strcpy( players[i], players[j] );
								strcpy( players[j], temp_n );
							}
						}
					}
	
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t  =========================== TOP  PLAYERS ===========================\n"
						   "\t\t\t\t\t\t\t\t\t\t\t\t\t  \n");
					for( int i = 0; i < 3; i++ )
					{
						printf("\t\t\t\t\t    %d => Name: %s\tScore: %d \n", i + 1, strupr(players[i]), p_score[i] );
					}
					printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\n"
						   "\t\t\t\t\t  =====================================================================\n\n");
					
					printf("\t\t\t\t\t\t\t  Press ESC To Go Back To Main Menu...");
					do
					{
						end = getch();
					}while( end != 27 );
					break;
				}
				
				case 5:
				{
					fflush( stdin );
					system( "cls" );
					
					char t_name[50];
					int t_score;
	
					FILE *sh = fopen( "games_log.txt", "r" );
					
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  =================== YOUR GAME HISTORY ==================\n");
					
					while( fscanf( sh,"%[^,],%d ", t_name, &t_score ) == 2 )
					{
						if(( strcmp( user, t_name ) == 0 ))
						{
							printf("\n\t\t\t\t\t\t\t  Score: %d\n", t_score);
						}
					}
					
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  ========================================================\n");
	
					fclose( sh );
					
					printf("\t\t\t\t\t\t\t  Press ESC To Go Back To Main Menu...");
					
					do
					{
						end = getch();
					}while( end != 27 );
					
					break;
				}
				case 6:
				{
					fflush(stdin);
					
					Beep( 1000, 500 );
					
					printf("\n\t\t\t\t\t\t\t\t     Loging Out");
					for(i_exit=0;i_exit<3;i_exit++,Sleep(200))
					{
						printf(".");
					}
					
					logged_in = 0;
					
					system( "cls" );
					break;
				}
				default:
				{
					fflush( stdin );
					menu=-1;
					break;
				}
			}
			if( fuel <= 0 && pits <= 0 )
			{
				printf("\n\n\t\t\t\t\t\t\t    Only If You Had More Fuel! Exiting Now...[");
				for( i_load=0; i_load<10; i_load++ )
				{
					printf("#");
					Sleep(50);
				}
				printf("]");
				
				FILE *log = fopen( "games_log.txt", "a" );
				
				fprintf(log,"%s,%d\n", user, score); 
				
				fclose(log);
				
				Beep( 1000, 100 );
				Sleep( 800 );
				
				break;
			}
			
			if(menu==6)
			{
				menu=-1;
				break;
			}
			
			if(menu==-1)
			{
				Beep( 1000, 500 );
				printf("\n\t\t\t\t\t\t\t\t     Invalid Input.");
				fflush(stdin);
				Sleep( 800 );
				break;
			}
		}
	}
	return 0;
}