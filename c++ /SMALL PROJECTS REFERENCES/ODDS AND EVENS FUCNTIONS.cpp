// PRINTING ODDS AND EVEN NUMBERS

#include <iostream>


int ODDSUM(int NUM){
	int A = 0;
	int B = 1;
	int result;

	for(int x = 0; x <= NUM; x++){
		result = A + B; 
		A++;
		B++;
		std::cout << result << std::endl;

	}

}

int EVENSUM(int NUM){
	int A = 0;
	int B = 2;
	int result;

	for(int x = 0; x <= NUM; x++){
		result = A + B; 
		A++;
		B++;
		std::cout << result << std::endl;
	}
}

int main()
{
	ODDSUM(100);
	EVENSUM(100);


	return 0;
}