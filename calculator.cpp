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

