#pragma once

#include <string>
#include <array>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <utility>

namespace encoder {

    class Item {
    public:
        using Type = uint64_t;

        static const int CAPACITY = 9;
        static const int RELATIVE_POSITION = 32;

        Item() = default;

        template <typename Iter>
        Item(Iter beg, Iter end) {
            int step = 0;
            for (; beg != end; beg++) {
                value_ += static_cast<Type>(std::pow(100, step++) * (static_cast<int>(*beg) - RELATIVE_POSITION));
            }
        }

        Item(Item&& other) = default;
        Item(const Item& other) = delete;
        Item& operator=(Item&& other) = default; 
        Item& operator=(const Item& other) = delete; 

        Type GetValue() const;
        std::string DecodeValue() const;
    private:
        Type value_ = 0;
    };
    
    std::ostream& operator<<(std::ostream& out, const Item& item) {
        out << item.GetValue();
        return out;
    }

    
} // namespace encoder
