#include <iostream>
#include <stdlib.h>
#include <string>
//for reading text files
#include <fstream>
//includes for building getch fucntion
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

//defining  number values as colors
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CIAN 36
#define WHITE 37

void clear(){system("clear");}

//gotoxy build
void gotoxy(int x, int y)
{
	printf("\x1B[%d;%df",y,x);
	fflush(stdout);
}

//background and text color fucntions
void txtcolor(int color) {printf("\x1B[%dm", color);}
void txtbgcolor(int color) {printf("\x1B[%dm", color+ 10);}

//rectangle fucntion, creates a rectangle of strings of desired size
void intRectangle(int top, int left, int width, int height)
{
	for (int i = 0; i <= width; ++i)
		{
			//left edge
			gotoxy(left, top + i);
			printf("%s", "║");
			//right edge
			gotoxy(left + height, top + i);
			printf("%s", "║");
		}

	for (int i = 0; i <= height; ++i)
	{		//top edge
			gotoxy(left + i, top);
			printf("%s", "═");
			//bottom edge
			gotoxy(left + i, top + width);
			printf("%s","═");
	}
	//top left corner
	gotoxy(left, top);
	printf("%s", "╔");
	//bottom left corner
	gotoxy(left,top + width);
	printf("%s", "╚");
	//top right corner
	gotoxy(left + height, top);
	printf("%s", "╗");
	//bottom right corner
	gotoxy(left + height, top + width);
	printf("%s", "╝");
}


//building getch fucntion
char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
 }




//  buillding kbhit   ////////////////////////////////////
void enable_raw_mode()
{
    termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
    tcsetattr(0, TCSANOW, &term);
}
void disable_raw_mode()
{
    termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

bool kbhit()
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}
//  ends building of kbhit fucntionn   //////////////////////



void player(int x, int y)
{

		gotoxy(x+2,y);
		txtbgcolor(MAGENTA);
		printf("%s\n"," ");
		gotoxy(x,y+1);
		printf("%s\n","     ");
}


void bullet(int x, int y)
{
		gotoxy(x,y);
		txtbgcolor(RED);
		printf("%s"," ");
}

void player_bullet(int x, int y)
{
		gotoxy(x,y);
		txtbgcolor(RED);
		printf("%s"," ");
}



void background_color(int color)
{
	gotoxy(80,50);
	txtcolor(GREEN);
	txtbgcolor(color);
	printf("%s\n", "  ");

}


int main()
{

	bool OVER = false;
	bool SHOOTING = false;
	bool SHOOTING2 = false;
	bool SHOOTING3 = false;
	bool PLAYER_SHOOTING = false;
	bool ALLOW_SHOOT_2 = false;
	bool ALLOW_SHOOT_3 = false;

	int X_POS = 40;
	int Y_POS = 47;
	int key;
	int PLAYER_BULLET_X;
	int PLAYER_BULLET_Y = 47;
	int PLAYER_BULLET_SPEED = 4;

	int ENEMY_X_POS = 3;
	int ENEMY_Y_POS = 2;
	int speed =1;

	//bullet starts at 8, then it follows enemy y pos
	int bullet_speed = 2;
	int BULLET_X = rand()%76;
	int BULLET_Y = 8;

	int BULLET_X_2 = rand()%76;
	int BULLET_Y_2 = 8;

	int BULLET_X_3 = rand()%76;
	int BULLET_Y_3 = 8;

	int LIVES = 3;


	char ENEMIES[25] = {'X',' ','X',' ','X',' ','X',' ','X',' ','X',' ','X',' ','X',' ','X',' ','X',' ','X',' ','X',' '};
	char ENEMIES2[25] = {'W',' ','W',' ','W',' ','W',' ','W',' ','W',' ','W',' ','W',' ','W',' ','W',' ','W',' ','W',' '};	
	char ENEMIES3[25] = {'0',' ','0',' ','0',' ','0',' ','0',' ','0',' ','0',' ','0',' ','0',' ','0',' ','0',' ','0',' '};	


	while(!OVER)
	{
		//FRAME RECTAGLE SHAPE FUCNTION
		intRectangle(0,0,49,79);

		
		//DATA AND INFO ON THE RIGHT CORNER USING GOTOXY
		gotoxy(80,0);
		printf("%s%d\n", " x position = ", X_POS);
		gotoxy(80, 2);
		printf("%s%d\n", " y position = ", Y_POS);
		gotoxy(80,4);
		printf("%s%d\n", " ENEMY X_POS = ", ENEMY_X_POS);
		gotoxy(80,5);
		printf("%s%d\n", " ENEMY Y_POS = ", ENEMY_Y_POS);
		gotoxy(80,6);
		printf("%s%d\n", " LIVES : ", LIVES);

		//ENEMY BULLETS  VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
		//shooting conditions placed after the gotoxys,
		//prevents color glitches
		if(ENEMY_X_POS == BULLET_X)SHOOTING = true;
		else if(BULLET_X > 55 && ENEMY_X_POS == 55) SHOOTING = true;
		else if(BULLET_X < 5 && ENEMY_X_POS == 5) SHOOTING = true;
		if(SHOOTING)
		{
			bullet(BULLET_X, BULLET_Y);
			BULLET_Y += bullet_speed;

			if(BULLET_Y > Y_POS + 2)
			{
				SHOOTING = false;
				BULLET_Y = ENEMY_Y_POS;
				//resets the x position of the bullet to a random place
				BULLET_X = rand() %76;
			}
		}

		if(ENEMY_X_POS == BULLET_X_2)SHOOTING2 = true;
		else if(BULLET_X_2 > 55 && ENEMY_X_POS == 55) SHOOTING2 = true;
		else if(BULLET_X_2 < 5 && ENEMY_X_POS == 5) SHOOTING2 = true;
		if(SHOOTING2)
		{
			bullet(BULLET_X_2, BULLET_Y_2);
			BULLET_Y_2 += bullet_speed;

			if(BULLET_Y_2 > Y_POS + 2)
			{
				SHOOTING2 = false;
				BULLET_Y_2 = ENEMY_Y_POS;
				//resets the x position of the bullet to a random place
				BULLET_X_2 = rand() %76;
			}
		}

		if(ENEMY_X_POS == BULLET_X_3)SHOOTING3 = true;
		else if(BULLET_X_3 > 55 && ENEMY_X_POS == 55) SHOOTING3 = true;
		else if(BULLET_X_3 < 5 && ENEMY_X_POS == 5) SHOOTING3 = true;
		if(SHOOTING3)
		{
			bullet(BULLET_X_3, BULLET_Y_3);
			BULLET_Y_3 += bullet_speed;

			if(BULLET_Y_3 > Y_POS + 2)
			{
				SHOOTING3 = false;
				BULLET_Y_3 = ENEMY_Y_POS;
				//resets the x position of the bullet to a random place
				BULLET_X_3 = rand() %76;
			}
		}
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV

			//player bullets
			if(PLAYER_SHOOTING)
			{
				player_bullet(PLAYER_BULLET_X, PLAYER_BULLET_Y);

				PLAYER_BULLET_Y -= PLAYER_BULLET_SPEED;

				if(PLAYER_BULLET_Y <= 2)
				{
					PLAYER_SHOOTING = false;
					PLAYER_BULLET_Y = 47;
				}


			}
			//this makes the bullet follow the player before shooting
			if(!PLAYER_SHOOTING) PLAYER_BULLET_X = X_POS + 2;



		//ENEMYES 
		gotoxy(ENEMY_X_POS,ENEMY_Y_POS);
		txtbgcolor(BLACK);
		printf("%s\n",ENEMIES);
	
		gotoxy(ENEMY_X_POS,ENEMY_Y_POS + 1);
		txtbgcolor(BLACK);
		printf("%s\n",ENEMIES2);		
		
		gotoxy(ENEMY_X_POS,ENEMY_Y_POS + 2);
		txtbgcolor(BLACK);
		printf("%s\n",ENEMIES3);	

		//PLAYER ENTITY
		player(X_POS, Y_POS);

		//prevents game from glitching colors
		background_color(BLACK);




		//CONTROLS
		enable_raw_mode();
		while(kbhit())
		{
			key = getch();

			//PRESSING Q TO EXIT
			if(key == 113 || key == 81)
			{
				background_color(BLACK);
				clear();
				//opening text file
				std::fstream file("thanks.txt");
				if(file.is_open()) std::cout << file.rdbuf();
				return 0;
			}

			else if(key == 66) Y_POS+= 4;
			else if(key == 65) Y_POS-= 4;
			else if(key == 67) X_POS += 4;
			else if(key == 68) X_POS -= 4;

			else if(key == 112 || key == 80)
			{
				std::cout << " PAUSE PRESS ENTER TO CONTINIUE" << std::endl;
				fflush(stdin);
				std::cin.get();
			}


			//shooting key
			else if(key ==32){
				PLAYER_SHOOTING = true;
			}



		}
		disable_raw_mode();
		tcflush(0, TCIFLUSH);




		// OUT OF BOUNDS PLAYER PREVENTION CONDITIONS
		if(Y_POS >= 47) Y_POS = 47;
		if(X_POS >= 74) X_POS = 74;
		if(Y_POS <= 2) Y_POS = 2;
		if(X_POS <= 2) X_POS = 2;

		
		//ENEMY MOVEMENT
		if(ENEMY_X_POS >= 55)
		{
			speed = -std::abs(speed);
			ENEMY_Y_POS +=1;
		}
		if(ENEMY_X_POS <= 4) 
		{
			speed = std::abs(speed);
			ENEMY_Y_POS +=1;
		}
		ENEMY_X_POS += speed;


		//IF YOU GET SHOT YOU LOOSE LIVES
		for (int i = 0; i < 5; ++i)
		{
		
			if( (BULLET_Y >= Y_POS ) & (BULLET_X == X_POS + i) ){
				LIVES--;
			}
		
			else if( (BULLET_Y_2 >= Y_POS ) & (BULLET_X_2 == X_POS + i) ){
				LIVES--;
			}
			
			else if( (BULLET_Y_3 >= Y_POS ) & (BULLET_X_3 == X_POS + i) ){
				LIVES--;
			}

		}


		//ALLOWING TO SHOT ENEMIES, PER ROW, we begin with a not true statement, because of lazyness
		if(!ALLOW_SHOOT_2)
		{
		
			for (int i = 0; i < 24; ++i)
			{
			
				if( (PLAYER_BULLET_Y <= ENEMY_Y_POS + 3) & (PLAYER_BULLET_X == ENEMY_X_POS + i) )
				{
					if(ENEMIES3[i] == '0')
					{
						ENEMIES3[i] = ' ';
						PLAYER_SHOOTING = false;
						PLAYER_BULLET_Y = 47;
					}
				}
			}
		}


		if(ALLOW_SHOOT_2)
		{
			for (int i = 0; i < 24; ++i)
			{
			
				if( (PLAYER_BULLET_Y <= ENEMY_Y_POS + 2) & (PLAYER_BULLET_X == ENEMY_X_POS + i) )
				{
					if(ENEMIES2[i] == 'W')
					{
						ENEMIES2[i] = ' ';
						PLAYER_SHOOTING = false;
						PLAYER_BULLET_Y = 47;
					}
				}
			}
		}

		if(ALLOW_SHOOT_3)
		{
			for (int i = 0; i < 24; ++i)
			{
			
				if( (PLAYER_BULLET_Y <= ENEMY_Y_POS ) & (PLAYER_BULLET_X == ENEMY_X_POS + i) )
				{
					if(ENEMIES[i] == 'X')
					{
						ENEMIES[i] = ' ';
						PLAYER_SHOOTING = false;
						PLAYER_BULLET_Y = 47;
					}
				}
			}
		}


		//IF THE ENEMY GOES OUT OF BOUNDS GAME OVER
		if(ENEMY_Y_POS > 48)
		{
			clear();
			return 0;
		}

		//all enemies on  array 3 defeated
		std::string DATA3 = ENEMIES3;
		std::string DATA2 = ENEMIES2;
		std::string FINAL_DATA = ENEMIES;

		if(DATA3 == "                        "){
			ALLOW_SHOOT_2 = true;

		}
		if(DATA2 == "                        "){
			ALLOW_SHOOT_3  = true;
		}

		//beating all enemies game over
		if(FINAL_DATA == "                        "){
			clear();
			std::fstream file("thanks.txt");
			if(file.is_open()) std::cout << file.rdbuf();
			return 0;	
		}

		//zero lives game over
		if (LIVES == 0)
		{
			clear();
			std::fstream file("thanks.txt");
			if(file.is_open()) std::cout << file.rdbuf();
			return 0;	
		}

		//RENDER AND CLEARING FRAMES

		//620  and 596 best performance
		system("sleep 0.0596s");
		clear();



	}
	//resets the terminal bacground to original colors
	background_color(BLACK);
	clear();
	return 0;
}
