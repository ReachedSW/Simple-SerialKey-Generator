#include "include/SerialKey.h"

/*
https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
(https://stackoverflow.com/users/23501/ates-goral)
*/
auto SerialKeyGen::get_random_string(size_t length) -> std::string
{
    // dynamically create a string of random characters
    static constexpr char alphanum[] = 
    {
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
    };
    
    // create a random number generator
    std::string tmp_s;

    // create a distribution that maps to the random characters
    tmp_s.reserve(length);

    // Special thanks for : https://github.com/aeTunga
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, std::ssize(alphanum)-1);

    char test;
    for (int i = 0; i < length; ++i)
    {
        test = alphanum[dist(mt)];
#ifdef _DBG_
        std::cout << "Debug ( test ): " << test << std::endl;
#endif
        tmp_s += test;
    }

    return tmp_s;
}



auto SerialKeyGen::GenerateKey() -> std::string 
{
    // first of all we need to find a key to hash, but it must be unique


    // This is for unique sized keys

   /* std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, 16);

    int nKey = dist(mt);*/


    // Special thanks for : https://github.com/aeTunga


    // This is for static sized keys 
    int iKey = 16;

#ifdef _DBG_
    std::cout << "Debug ( nKey ) : " << iKey << std::endl;
#endif
   
    // now we need to hash the key
    std::string sHashedKey = get_random_string(iKey);
#ifdef _DBG_
    std::cout << "Debug ( sHashedKey ) : " << sHashedKey << std::endl;
#endif


    //std::transform(sHashedKey.begin(), sHashedKey.end(), sHashedKey.begin(), ::toupper); // Written for make variables between upper and lower cases.


  
    std::string sHashed = "";

    BYTE bCounter = 0;
    for (BYTE i = 0; i < sHashedKey.length()+1; ++i)
    {
        if (bCounter < 4)
        {
            sHashed += sHashedKey[i];
            bCounter++;
        }
        else
        {
            if (i == sHashedKey.length())
            {
                sHashed += "-";
                bCounter = 0;
                i--;
            }
        }
    }

#ifdef _DBG_
    std::cout << "Debug ( sHashed ) : " << sHashed << std::endl;
#endif

    m_map_Keys.emplace(this, iKey);

    // now we need to return the key
    return sHashed;
}

auto SerialKeyGen::GetHashedKeys() -> void
{
    auto it = m_map_Keys.begin();

    while (it != m_map_Keys.end())
    {
        std::cout << it->first << " " << it->second << std::endl;
        it++;
    }

    std::cout << std::endl;

}
