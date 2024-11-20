#pragma once

#include <string>
#include <cmath>
#include <cstdint>
#include <iterator>
#include <utility>
#include <memory>

namespace encoder {
    namespace char32_to_126 {
        class Item {
        public:
            using Type = uint64_t;

            static const int CAPACITY = 9;
            static const int RELATIVE_POSITION = 31;

            Item() = default;

            template <typename InputIter>
            Item(InputIter beg, InputIter end) {
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

            std::string Decode() const {
                std::string result;
                result.reserve(size_ * Item::CAPACITY);

                std::string buffer;
                for (size_t index = 0; index < size_; index++) {
                    buffer = data_[index].Decode();
                    result += buffer;
                }

                return result;
            }


        private:
            Data data_ = nullptr;
            size_t size_ = 0;
        };

        static size_t CalcDataSizeInItems(size_t data_size) {
            return std::ceil(data_size / double(Item::CAPACITY));
        }

        template <typename InputIter>
        static ItemArray EncodeData(InputIter data_beg
                    , InputIter data_end
                    , const size_t items_count) {
            
            if (items_count <= 0) {
                return ItemArray{};
            }

            ItemArray::Data data(new Item[items_count]);

            auto beg = data_beg;
            for (int i = 0; i < items_count - 1; i++) {
                auto end = beg + Item::CAPACITY;
                data[i] = Item{beg, end};
                beg = end;
            }

            data[items_count - 1] = Item{beg, data_end};

            return ItemArray{std::move(data), items_count};
        }

        template <typename InputIter, typename OutputIter>
        static void EncodeDataInIterable(InputIter data_beg
                            , InputIter data_end
                            , OutputIter target
                            , const size_t target_size) {
            if (target_size > 0) {
                auto beg = data_beg;
                for (int i = 0; i < target_size - 1; i++) {
                    auto end = beg + Item::CAPACITY;
                    *target++ = Item{beg, end};
                    beg = end;
                }

                *target = Item{beg, data_end};
            }
        }

        template <typename InputIter>
        static std::string DecodeDataFromIterable(InputIter beg, InputIter end, size_t items_count) {
            std::string result;
            result.reserve(items_count * Item::CAPACITY);

            std::string buffer;
            for (; beg != end; beg++) {
                buffer = beg -> Decode();
                result += buffer;
            }

            return result;
        }
    } // namespace char32_to_126
    
} // namespace encoder
