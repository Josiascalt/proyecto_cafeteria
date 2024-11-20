#include "encoder.hpp"

namespace encoder {
    namespace char32_to_126 {
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

        Item::Type Item::GetValue() const {
            return value_;
        }

        std::string Item::Decode() const {
            return detail::DecodeItem(*this);
        }
    } // namespace char32_to_126
} //namespace encoder
