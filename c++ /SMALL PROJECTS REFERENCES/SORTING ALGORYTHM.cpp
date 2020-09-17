#include <iostream>
#include <vector>
#include <algorithm>

struct ESTRUCTURA
{
bool operator()(int A, int B) const {return B < A;}

}OBJETO;

int main()
{


    std::vector <int> VECTOR(18);

    int ARRAY[] = {10,2,3,99,15,49,1,68,19,45,77,93,45,1089,11,35,61,0};

    VECTOR.insert(VECTOR.begin(), ARRAY, ARRAY + 18);


    std::sort(VECTOR.begin(), VECTOR.begin() + 18);

    for(int i = 0; i < 18; i++) std::cout << VECTOR.at(i) << std::endl;


    std::cout << " fin del loop MENOR A MAYOR " << std::endl;
    std::cout << "############################################" << std::endl;
    std::cout << " iniciando loop de MAYOR A MENOR " << std::endl;


    std::sort(VECTOR.begin(), VECTOR.begin() + 18, OBJETO);

    for(int i = 0; i < 18; i++) std::cout << VECTOR.at(i) << std::endl;


    return 0;
}
