#pragma once

#include <random>
#include <string>

namespace utilities {
    using Num = std::uint_fast32_t; 
    using Engine = std::mt19937;

    static std::string GenerateRandomStr(int size) {
        static const int ASCII_CHAR_START = 33;
        static const int ASCII_CHAR_END = 126;

        std::string result;
        result.reserve(size);
        
        static std::random_device os_seed;
        static const Num seed = os_seed();
        
        static Engine generator(seed);
        static std::uniform_int_distribution<Num> distribute(33, 126);
        
        for (int repetition = 0; repetition < size; repetition++) {
            result.push_back(char(distribute(generator)));    
        }
        
        return result;
    }
} //namespace utilities

