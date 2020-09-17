#include <iostream>
#include <vector>

int main()
{
    bool ARRAY_BOOLEANS[12];
    std::vector <bool> BOOL_VECTOR(12);

    for(int i = 0; i < 13; i++)
    {
        std::cout << " asignando array " << i << " = falso " <<  std::endl;
        ARRAY_BOOLEANS[i] = false;
    }

    std::cout << std::endl;

    for(int x = 0; x < 13; x++)
    {
        std::cout << " assignando vector " << x << " = falso " << std::endl;
        BOOL_VECTOR.insert(BOOL_VECTOR.begin() + x, ARRAY_BOOLEANS[x]);
    }

    if(!ARRAY_BOOLEANS[12]) ARRAY_BOOLEANS[12] = true;

    if(ARRAY_BOOLEANS[12]) BOOL_VECTOR.at(12) = true;

    std::cout << std::endl;

    for(int z = 0; z < 13; z++)
    {
        std::cout << " el vector "<< z << " es igual a " <<BOOL_VECTOR.at(z) << std::endl;
    }

    std::cout << std::endl;

    if(BOOL_VECTOR.at(12)) std::cout << "EL ARRAY Y EL VECTOR CUMPLIERON SU FUNCION!!" << std::endl;
    std::cout << " el ultimo array y el ultimo vector fueron asignados a true... =  " << BOOL_VECTOR.at(12) << std::endl;

    return 0;
}
