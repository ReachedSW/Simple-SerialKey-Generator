#include <iostream>

#include "include/SerialKey.h"


int main()
{
    SerialKeyGen key;
    bool bStop = true;

    while (bStop)
    {
        int iChoose = 0;
        std::cout << "1- Generate Number" << std::endl;
        std::cout << "2- See Generated Numbers" << std::endl;
        std::cout << ": ";
        std::cin >> iChoose;

        std::cout << std::endl;


        switch (iChoose)
        {
            case 1:
            {
                key.GenerateKey();
            }
            break;

            case 2:
            {
                key.GetHashedKeys();
            }
            break;
        
            default:
                std::cout << " ?? " << std::endl;
                bStop = false;
                break;
        }

        std::cout << std::endl;
    }


    std::cin.get();
    

    return 0;
}