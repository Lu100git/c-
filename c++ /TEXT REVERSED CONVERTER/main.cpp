#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
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

int main()
{
	system("clear");


	bool executing = true;
	while(executing)
	{
		std::string NOMBRE;
		std::string NOMBRE_REVERSA;
		char answer;
		bool valid;


		std::cout << "enter desired name or sentence you wish to reverse" << std::endl;	
		std::cout << std::endl;

		do{
			std::getline(std::cin, NOMBRE);
			valid = true;
/*
			for(std::size_t i{}; i < NOMBRE.length() && valid; i++)
			{
				if(!(std::isalpha(static_cast<unsigned char>(NOMBRE[i])) || std::isspace(static_cast<unsigned char>(NOMBRE[i]))))
				valid = false;
				system("clear");
				std::cout << " use letters only plz, :(" << std::endl;
			}
*/
		}while(!valid);

		system("clear");

		for(int x = NOMBRE.size() -1; x > -1; --x)
		{
			NOMBRE_REVERSA += NOMBRE[x];
		}

		std::cout << "your sentence was : " << NOMBRE << std::endl;
		std::cout << std::endl;
		std::cout << "the reversed sentence is : " << NOMBRE_REVERSA << std::endl;
		std::cout << std::endl;
	
		std::cout << std::endl;
		std::cout << "do you want to convert another one?  y/n " << std::endl;
	
		answer = getch();
		system("clear");
		
		if(answer == 'y' || answer == 'Y')
		{
			NOMBRE.clear();
			NOMBRE_REVERSA.clear();
			executing = false;
			main();

		}
	
		if(answer == 'n' || answer == 'N') 
		{	
			std::cout << "HOPE YOU ENJOYED THIS PROGRAM!!!. CHEERS!, HAVE A GOOD DAY :D" << std::endl;
			break;
		}
	}

	return 0;
}
