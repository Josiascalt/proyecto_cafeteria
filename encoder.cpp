#include "encoder.hpp"

namespace encoder {
    namespace ascii {
        namespace detail {
            static std::string DecodeItem(const Item& item) {
                std::string result;
                auto encoded_value = item.GetValue();

                for (int step = 0; step < Item::CAPACITY && encoded_value != 0;) {
                    Item::Type step_coeficient = std::pow(100, ++step);
                    Item::Type stepped_encoded_char = (encoded_value % step_coeficient);

                    result += static_cast<char>(stepped_encoded_char / (step_coeficient / 100) + Item::RELATIVE_POSITION);

                    encoded_value -= stepped_encoded_char;
                }

                return result;
            }
        } //namespace detail

        //class Item member functions definition
        Item::Type Item::GetValue() const {
            return value_;
        }

        std::string Item::Decode() const {
            return detail::DecodeItem(*this);
        }

        //class ItemArray member functions definition
        ItemArray::ItemArray(ItemArray::Data&& data, size_t size) 
        : data_(std::move(data))
        , size_(size) 
        {
        }

        const ItemArray::Data& ItemArray::GetData() const {
            return data_;
        }

        size_t ItemArray::GetSize() const {
            return size_;
        }

        std::string ItemArray::Decode() const {
            std::string result;
            result.reserve(size_ * Item::CAPACITY);

            std::string buffer;
            for (size_t index = 0; index < size_; index++) {
                buffer = data_[index].Decode();
                result += buffer;
            }

            return result;
        }

        // (namespace ascii) functions definition
        
    } // namespace ascii
} //namespace encoder
