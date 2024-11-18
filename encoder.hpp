#pragma once

#include <string>
#include <array>
#include <algorithm>
#include <cmath>
#include <cstdint>

namespace encoder {
    static const int RELATIVE_POSITION = 32;

    static const int UINT64_CAPACITY = 9;
    static const int UINT64_IN_TYPE128 = 2;
    using Type128 = std::array<uint64_t, UINT64_IN_TYPE128>;

    //String encoder in 16 bytes - any char from 32 - 126
    Type128 Encode128(const std::string& str) {
        Type128 result({0,0});
        auto result_index = 0;
        const int size = str.size();
        const int digit_position_step = 2;

        int digit_position = 0;
        for (int i = 0; i < size;) {
            auto step = std::min(UINT64_CAPACITY, size - i);

            if (step == UINT64_CAPACITY) {
                result[result_index] += static_cast<uint64_t>(std::pow(10, digit_position) * (static_cast<int>(str[i++]) - RELATIVE_POSITION));
                digit_position += digit_position_step;

                result[result_index] += static_cast<uint64_t>(std::pow(10, digit_position) * (static_cast<int>(str[i++]) - RELATIVE_POSITION));
                digit_position += digit_position_step;

                result[result_index] += static_cast<uint64_t>(std::pow(10, digit_position) * (static_cast<int>(str[i++]) - RELATIVE_POSITION));
                digit_position += digit_position_step;

                result[result_index] += static_cast<uint64_t>(std::pow(10, digit_position) * (static_cast<int>(str[i++]) - RELATIVE_POSITION));
                digit_position += digit_position_step;

                result[result_index] += static_cast<uint64_t>(std::pow(10, digit_position) * (static_cast<int>(str[i++]) - RELATIVE_POSITION));
                digit_position += digit_position_step;

                result[result_index] += static_cast<uint64_t>(std::pow(10, digit_position) * (static_cast<int>(str[i++]) - RELATIVE_POSITION));
                digit_position += digit_position_step;

                result[result_index] += static_cast<uint64_t>(std::pow(10, digit_position) * (static_cast<int>(str[i++]) - RELATIVE_POSITION));
                digit_position += digit_position_step;

                result[result_index] += static_cast<uint64_t>(std::pow(10, digit_position) * (static_cast<int>(str[i++]) - RELATIVE_POSITION));
                digit_position += digit_position_step;

                result[result_index] += static_cast<uint64_t>(std::pow(10, digit_position) * (static_cast<int>(str[i++]) - RELATIVE_POSITION));
                digit_position += digit_position_step;

                digit_position = 0;
                result_index++;
                continue; 
            }

            result[result_index] += static_cast<uint64_t>(std::pow(10, digit_position) * (static_cast<int>(str[i++]) - RELATIVE_POSITION));
            digit_position += digit_position_step;
        }

        return result;
    }
} // namespace encoder
