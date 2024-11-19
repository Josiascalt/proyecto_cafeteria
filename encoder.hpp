#pragma once

#include <string>
#include <array>
#include <cmath>
#include <cstdint>


namespace encoder {
    class Item {
    public:
        using Type = uint64_t;

        static const int CAPACITY = 9;
        static const int RELATIVE_POSITION = 31;

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
        std::string Decode() const;
    private:
        Type value_ = 0;
    };
    
} // namespace encoder
