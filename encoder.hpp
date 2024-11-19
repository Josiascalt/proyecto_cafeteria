#pragma once

#include <string>
#include <array>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <utility>

namespace encoder {

    class Product {
    private:
        using Type = u_int64_t;
    public:
        static const int CAPACITY = 18;
        static const int RELATIVE_POSITION = 32;
        static const int ELEM_SIZE = 2;

        Product() = default;

        template <typename Iter>
        static Type EncodeElem(const Iter& elem, int step) {
            return static_cast<Type>(std::pow(10, step * ELEM_SIZE) * (static_cast<int>(*elem) - RELATIVE_POSITION));
        }

        static char DecodeElem(Type value, int step) {
            return static_cast<char>((value % Type(std::pow(10, step * ELEM_SIZE))) + RELATIVE_POSITION);
        }

        template <typename Iter>
        void SetValue(Iter beg, Iter end) {
            int step = 0;
            for (; beg != end; beg++) {
                value_ += EncodeElem(beg, step++);
            }
        }

        Type GetValue() const {
            return value_;
        }
        
        std::string DecodeValue() const {
            
        }

    private:
        Type value_ = 0;
    };
    
    std::ostream& operator<<(std::ostream& out, const Product& item) {
        out << item.GetValue();
        return out;
    }

    
} // namespace encoder
