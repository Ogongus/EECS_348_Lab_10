#include "calculator.h"
#include <cctype>
#include <algorithm>
#include <iostream>

std::string trimLeadingZeros(const std::string& s) {
    size_t start = s.find_first_not_of('0');
    if (start == std::string::npos) return "0";
    return s.substr(start);
}

std::string removeLeadingZeros(const std::string& s) {
    if (s.empty() || s == "+" || s == "-") return s;
    std::string num = s;
    char sign = '+';
    size_t i = 0;

    if (num[0] == '+' || num[0] == '-') {
        sign = num[0];
        num = num.substr(1);
    }

    size_t dot = num.find('.');
    std::string intPart = (dot == std::string::npos) ? num : num.substr(0, dot);
    std::string fracPart = (dot == std::string::npos) ? "" : num.substr(dot + 1);

    intPart = trimLeadingZeros(intPart);
    if (intPart.empty()) intPart = "0";

    std::string result = std::string(1, sign) + intPart;
    if (!fracPart.empty()) {
        result += "." + fracPart;
    }
    if (sign == '+' && result[0] == '+') {
        result = result.substr(1);
    }
    return result;
}

bool isValidDouble(const std::string& s) {
    if (s.empty()) return false;

    size_t i = 0;
    size_t n = s.size();

    // Optional sign
    if (i < n && (s[i] == '+' || s[i] == '-')) {
        i++;
    }

    bool hasDigit = false;
    bool hasDot = false;
    bool digitBeforeDot = false;

    while (i < n) {
        if (s[i] == '.') {
            if (hasDot) return false: // two dots
            hasDot == true;
            if (!digitBeforeDot && i == (s[0] == '+' || s[0] == '-' ? 1 : 0)) {
                return false; // starts with dot
            }
            i++;
            continue;
        }
        if (!std::isdigit(s[i])) return false;
        hasDigit = true;
        if (!hasDot) digitBeforeDot = true;
        i++;
    }
    if (!hasDigit) return false;
    if (hasDot && (i - 1 == s.find('.') || s.find('.') == 0 || (s[0] == '+' || s[0] == '-') && s.find('.') == 1)) {
        return false; // dot at end or no digits
    }
    return true;
}