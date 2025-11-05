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

std::string addStrings(const std::string & a, const std::string & b) {
    std::string num1 = a, num2 = b;
    char sign1 = '+', sign2 = '+';
    if (!num1.empty() && (num1[0] == '+' || num1[0] == '-')) {
        sign1 = num1[0];
        num1 = num1.substr(1);
    }
    if (!num2.empty() && (num2[0] == '+' || num2[0] == '-')) {
        sign2 = num2[0];
        num2 = num2.substr(1);
    }

    if (sign1 != sign2) {
        // Different signs: subtract
        if (sign1 == '-') {
            return addStrings("-" + num1, num2) == "0" ? "0" : "-" + addStrings(num2, "-" + num1);
        } else {
            return addStrings(num1, "-" + num2);
        }
    }

    // Same sign: add
    size_t dot1 = num1.find('.'), dot2 = num2.find('.');
    std::string int1 = (dot1 == std::string::npos) ? num1 : num1.substr(0, dot1);
    std::string frac1 = (dot1 == std::string::npos) ? "" : num1.substr(dot1 + 1);
    std::string int2 = (dot2 == std::string::npos) ? num2 : num2.substr(0, dot2);
    std::string frac2 = (dot2 == std::string::npos) ? "" : num2.substr(dot2 + 1);
}