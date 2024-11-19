#pragma once

#include <string>
#include <cmath>
#include <cstdint>
#include <vector>
#include <iterator>

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

    using EncodedData = std::vector<Item>;
    
    inline EncodedData EncodeData(const std::string& data) {
        EncodedData result;
        int size_in_items = std::ceil(data.size() / double(Item::CAPACITY));
        result.reserve(size_in_items);

        auto begin = data.begin();
        for (int i = 0; i < size_in_items - 1; i++) {
            auto end = begin + Item::CAPACITY;
            result.emplace_back(begin, end);
            begin = end;
        }
        
        result.emplace_back(begin, data.end());

        return result;
    }
} // namespace encoder
