// fibonacci numbers project

//also bypassing !isdigit from ctype header. COOL uh
#include <iostream>

int main()
{
	int input;
	int A = 0;
	int B = 1;
	int counter = 0;

	std::cout << "how many terms u want foo?" << std::endl;

	while(!(std::cin >> input)){
	std::cin >> input;
	std::cin.clear();
	std::cin.ignore();
	std::cout << "AH... WE GOT A SMART A OVER HERE, numbers only plz" << std::endl;1
}

	if(input <=0){
		std::cout << "plz use positive valuse only (do not break my program!)" << std::endl;
		}

	else if(input == 1){
		std::cout << "sequence up to " << input << ":" <<  std::endl;
		std::cout << A << std::endl;
		//std::cout << " " << std::endl;
	}
	else{
		std::cout << input << "?" << " okay!" << std::endl;
		std::cout << "STARTING FIBONACCI SEQUENCE!...YAS!" << std::endl;

	}

	while(counter < input){

		std::cout << A << std::endl;
		
		int C = A + B;

		A = B;
		B = C;
		counter = counter + 1; 

	} 

	return 0;
}