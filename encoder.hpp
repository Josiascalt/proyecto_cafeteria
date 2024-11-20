#pragma once

#include <string>
#include <cmath>
#include <cstdint>
#include <vector>
#include <iterator>
#include <utility>
#include <memory>

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


    class Encoder {
    public:
        Encoder() = default;

        Encoder(const std::string& str) 
        : data_(nullptr)
        {   
        }

        template <typename Iter>
        Encoder(Iter beg, Iter end) 
        : data_(nullptr)
        {
        }

        static int CalcDataSizeInItems(int data_size) {
            return std::ceil(data_size / double(Item::CAPACITY));
        }

        template <typename OutIter, typename InputIter>
        static void EncodeData(InputIter beg
                  , InputIter end
                  , OutIter target
                  , int target_capacity) {

            auto iter_begin = beg;
            for (int i = 0; i < target_capacity - 1; i++) {
                auto iter_end = iter_begin + Item::CAPACITY;
                *target++ = std::move(Item{iter_begin, iter_end});
                iter_begin = iter_end;
            }

            *target = std::move(Item{iter_begin, end});
        }

    private:
        std::unique_ptr<Item> data_;
    };
    
    /*inline Encoder EncodeString(const std::string& data) {
        Encoder result;
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
    }*/
} // namespace encoder
