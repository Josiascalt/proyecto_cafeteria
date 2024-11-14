#pragma once

#include <string>
#include <array>
#include <algorithm>
#include <cstdint>

namespace encoder {
    static const int UINT32_IN_TYPE128 = 4;
    using EncodingType128 = std::array<uint32_t, UINT32_IN_TYPE128>;

    //String encoder in 16 bytes - any char from 32 - 126
    //The string size should be 20 or less
    EncodingType128 Encode128(const std::string& str) {
        EncodingType128 result;
        const int size = str.size();
        for (int i = 0; i < size;) {
            auto step = std::min(UINT32_IN_TYPE128, size - i);
            /*some code here*/
            i += step;
        }

        return result;
    }
} // namespace encoder
