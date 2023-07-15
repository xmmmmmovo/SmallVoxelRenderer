//
// Created by xmmmmmovo on 2023/7/5.
//

#ifndef VOXEL_RENDERER_UTIL_STRING_UTIL_HPP
#define VOXEL_RENDERER_UTIL_STRING_UTIL_HPP

#include <codecvt>
#include <locale>
#include <string>

namespace voxel {

std::wstring u8StrToWStr(const std::string &str) noexcept {
    wchar_t      wc;
    std::wstring result;
    int          tail = 0;
    for (auto c : str) {
        if (c & 0b10000000) {
            int     prefix_length = 1;
            uint8_t test_bit      = 0b01000000;
            while (static_cast<uint8_t>(c) & test_bit) {
                prefix_length++;
                test_bit >>= 1;
            }
            int const     valid_bit   = 7 - prefix_length;
            wchar_t const valid_value = c & ((1 << valid_bit) - 1);
            if (prefix_length == 1) {
                tail--;
                wc <<= valid_bit;
                wc |= valid_value;
                if (!tail) { result += wc; }
            } else {
                tail = prefix_length - 1;
                wc   = valid_value;
            }
        } else {
            result += static_cast<wchar_t>(c);
        }
    }
    return result;
}

std::string wStrToU8Str(const std::wstring &wide_str) noexcept {
    std::string str;
    for (auto wc : wide_str) {
        if ((wc & 0b1111111) == wc) {
            str += static_cast<char>(wc);
        } else if ((wc & 0b11111111111) == wc) {
            str += static_cast<char>(0b11000000 | ((wc >> 6) & 0b00011111));
            str += static_cast<char>(0b10000000 | (wc & 0b00111111));
        } else {
            str += static_cast<char>(0b11100000 | ((wc >> 12) & 0b00001111));
            str += static_cast<char>(0b10000000 | ((wc >> 6) & 0b00111111));
            str += static_cast<char>(0b10000000 | (wc & 0b00111111));
        }
    }
    return str;
}

}// namespace voxel

#endif//VOXEL_RENDERER_UTIL_STRING_UTIL_HPP
