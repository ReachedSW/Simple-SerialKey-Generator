#ifndef SERIALKEY_H
#define SERIALKEY_H
#include <iostream>
#include <map>
#include <random>
#include <string>
#include "typedef.h"
#include <algorithm>



class SerialKeyGen
{
private:
    int m_nKey;
    std::map<SerialKeyGen*, int> m_map_Keys;
    int m_iRule;

public:
// inline
    SerialKeyGen(int nKey = 0) : m_nKey(nKey) {}
    inline auto     GetKey() const -> int { return m_nKey; }
    inline auto     SetKey(int nKey) -> void { m_nKey = nKey; }



    auto            GenerateKey() -> std::string;
    auto            get_random_string(size_t length) -> std::string;
    auto            GetHashedKeys() -> void;
};









#endif // SERIALKEY_H