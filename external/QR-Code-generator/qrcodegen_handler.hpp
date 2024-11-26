#pragma once

#include <string>

#include "src/qrcodegen.hpp"

using qrcodegen::QrCode;

namespace utilities {
    static std::string GenerateSvgQrCode(const std::string& value, QrCode::Ecc errCorLvl);
} //namespace utilities

