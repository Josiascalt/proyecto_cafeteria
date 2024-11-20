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

    class ItemArray {
    public:
        using Data = std::unique_ptr<Item[]>;

        ItemArray() = default;

        ItemArray(Data&& data, size_t size) 
        : data_(std::move(data))
        , size_(size) 
        {
        }

        const Data& GetData() const {
            return data_;
        }

        size_t GetSize() const {
            return size_;
        }


    private:
        Data data_ = nullptr;
        size_t size_ = 0;
    };

    static size_t CalcDataSizeInItems(size_t data_size) {
        return std::ceil(data_size / double(Item::CAPACITY));
    }

    template <typename InputIter>
    static ItemArray EncodeData(InputIter beg
                , InputIter end
                , const size_t size_in_items) {
        
        if (size_in_items <= 0) {
            return ItemArray{};
        }

        ItemArray::Data data(new Item[size_in_items]);

        auto iter_begin = beg;
        for (int i = 0; i < size_in_items - 1; i++) {
            auto iter_end = iter_begin + Item::CAPACITY;
            data[i] = Item{iter_begin, iter_end};
            iter_begin = iter_end;
        }

        data[size_in_items - 1] = Item{iter_begin, end};
        return ItemArray{std::move(data), size_in_items};
    }

    template <typename InputIter, typename OutputIter>
    static void EncodeDataInTarget(InputIter data_beg
                         , InputIter data_end
                         , OutputIter target
                         , const size_t target_size) {

        /*some code here*/
    }
    
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
