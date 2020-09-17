// the following sudoku puzze solver was taken from a reference from computerphile youtube video 
// where they used python and recursion to solve a sudoku puzzle 
// all i did was just porting the python code shown on the video into c++
// source of the vide:  https://www.youtube.com/watch?v=G_UYXzGuqvM&t=322s
#include <fstream>
#include <stdio.h>
#include <iostream>
//includes for building getch fucntion
#include <unistd.h>
#include <termios.h>


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




bool POSSIBLE(int y_pos,  int x_pos,  int number, int grid[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		if (grid[y_pos][i] == number) return false;
	}

	for (int i = 0; i < 9; i++)
	{
		if (grid[i][x_pos] == number) return false;
	}

	//checking 3x3 grid
	int x0 = (x_pos/3)*3;
	int y0 = (y_pos/3)*3;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			if(grid[y0 + i][x0 + j] == number) return false;
		}
		
	return true;	
}

void solve(int grid[9][9])
{
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if(grid[y][x] == 0)
			{
				for (int n = 1; n < 10; n++)
				{

					if(POSSIBLE(y,x,n,grid))
					{
						grid[y][x] = n;
						solve(grid);
						grid[y][x] = 0;
					}			
				}
				//if dead end for solutions, return
				return;
			}
		}
	}	
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j) std::cout << grid[i][j];
		
		std::cout << std::endl;
	}

}

int main()
{

	char key;

	//clears screen
	system("clear");
	//title
	std::fstream file("title.txt");
	if(file.is_open()) std::cout << file.rdbuf();

	printf("%s\n", " press any key to continue... " );
	printf("%s\n"," or " );
	printf("%s\n", " PRESS ESC TO EXIT ");
	
	key = getch();

	if(key == 0x1B) return 0;

	if(key != 0x1B)
	{
	printf("%s\n", " INSTRUCIONS " );
	std::cout << "enter 1 number then press enter, from left to right, top row first, as shown on sudoku the sudoku puzzle" <<std::endl; 
	std::cout << "enter a 0 for each blank space, " << std::endl;
	}
	int array[9][9];	
	char proceed;


	for (int i = 0; i < 9; ++i)
		{	
			for (int j = 0; j < 9; ++j) 
			{
				std::cin >> array[i][j];

			}
			
			std::cout << " is ROW "<< i + 1 << " correct?" << std::endl;
			
			for (int x = 0; x < 9; x++)
			{
				std::cout << array[i][x];
			}
			
			std::cout << std::endl;
			std::cout << "y/n" << std::endl;
			printf("%s\n", "or press esc to quit" );
			proceed = getch();
			
			if(proceed == 'n' || proceed == 'N')
			{
				system("clear");
				main();
			}

			else if(proceed == 'y' || proceed == 'Y')
			{
				std::cout << " type in next row " << std::endl;

			}
					
			if (proceed == 0x1B) return 0;
		}

	system("clear");
	printf("%s\n", "the sudoku problem provided is : ");
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j) std::cout << array[i][j];
		
		std::cout << std::endl;
	}

	printf("\n");
	printf("%s\n", "THE ANSWER OF THE SUDOKU PUZZLE IS...");
	printf("\n");
	solve(array);
	

	return 0;


}



