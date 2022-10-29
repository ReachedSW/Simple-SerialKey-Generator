#include "include/SerialKey.h"

/*
https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
(https://stackoverflow.com/users/23501/ates-goral)
*/
auto SerialKeyGen::get_random_string(size_t length)->std::string
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

    for (int i = 0; i < length; ++i)
    {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}



auto SerialKeyGen::GenerateKey() -> std::string 
{
    // first of all we need to find a key to hash, but it must be unique
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<ld> dist(1.0, 10000000000.0);

    ld nKey = dist(mt);
#ifdef _DBG_
    std::cout << "Debug ( nKey ) : " << nKey << std::endl;
#endif
   
    // now we need to hash the key
    std::string sKey = std::to_string(nKey);
#ifdef _DBG_
    std::cout << "Debug ( sKey ) : " << sKey << std::endl;
#endif

    std::string sHashedKey = get_random_string(sKey.length());
#ifdef _DBG_
    std::cout << "Debug ( sHashedKey ) : " << sHashedKey << std::endl;
#endif

    std::transform(sHashedKey.begin(), sHashedKey.end(), sHashedKey.begin(), ::toupper);

    std::string sHashed = "";

    BYTE bCounter = 0, bLineController = 0;
    for (BYTE i = 0; i < sHashedKey.length()+1; ++i)
    {
        if (bCounter < 4)
        {
            sHashed += sHashedKey[i];
            bCounter++;
        }
        else
        {
            if (bLineController < 3)
            {
                sHashed += "-";
                bCounter = 0;
                i--;
                bLineController++;
            }
        }
    }

#ifdef _DBG_
    std::cout << "Debug ( sHashed ) : " << sHashed << std::endl;
#endif

    m_map_Keys.emplace(this, nKey);

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
