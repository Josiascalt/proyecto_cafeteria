#include "encoder.hpp"

namespace encoder {
    namespace detail {
        static std::string DecodeItem(const Item& item) {
            std::string result;

            auto encoded_value = item.GetValue();
            for (int step = 0; step < Item::CAPACITY; step++) {
                Item::Type econded_char = (encoded_value % Item::Type((std::pow(100, step + 1))));
                result += static_cast<char>((econded_char / std::pow(100, step)) + Item::RELATIVE_POSITION);
                encoded_value -= econded_char;
            }

            return result;
        }
    } //namespace detail

    Item::Type Item::GetValue() const {
        return value_;
    }

    std::string Item::DecodeValue() const {
        return detail::DecodeItem(*this);
    }
} //namespace encoder
