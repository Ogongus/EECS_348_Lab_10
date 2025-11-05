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
            if (hasDot) return false; // two dots
            hasDot = true;
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

// Compare two positive decimal strings (returns: -1 if a < b, 0 if a == b, 1 if a > b)
int comparePositive(const std::string& a, const std::string& b) {
    std::string num1 = a, num2 = b;
    
    size_t dot1 = num1.find('.'), dot2 = num2.find('.');
    std::string int1 = (dot1 == std::string::npos) ? num1 : num1.substr(0, dot1);
    std::string frac1 = (dot1 == std::string::npos) ? "" : num1.substr(dot1 + 1);
    std::string int2 = (dot2 == std::string::npos) ? num2 : num2.substr(0, dot2);
    std::string frac2 = (dot2 == std::string::npos) ? "" : num2.substr(dot2 + 1);
    
    int1 = trimLeadingZeros(int1);
    int2 = trimLeadingZeros(int2);
    
    if (int1.size() != int2.size()) {
        return int1.size() > int2.size() ? 1 : -1;
    }
    if (int1 != int2) {
        return int1 > int2 ? 1 : -1;
    }
    
    // Pad fractions
    size_t maxFrac = std::max(frac1.size(), frac2.size());
    while (frac1.size() < maxFrac) frac1 += '0';
    while (frac2.size() < maxFrac) frac2 += '0';
    
    if (frac1 != frac2) {
        return frac1 > frac2 ? 1 : -1;
    }
    return 0;
}

// Subtract two positive decimal strings (assumes a >= b)
std::string subtractPositive(const std::string& a, const std::string& b) {
    std::string num1 = a, num2 = b;
    
    size_t dot1 = num1.find('.'), dot2 = num2.find('.');
    std::string int1 = (dot1 == std::string::npos) ? num1 : num1.substr(0, dot1);
    std::string frac1 = (dot1 == std::string::npos) ? "" : num1.substr(dot1 + 1);
    std::string int2 = (dot2 == std::string::npos) ? num2 : num2.substr(0, dot2);
    std::string frac2 = (dot2 == std::string::npos) ? "" : num2.substr(dot2 + 1);
    
    // Align fractions
    size_t maxFrac = std::max(frac1.size(), frac2.size());
    while (frac1.size() < maxFrac) frac1 += '0';
    while (frac2.size() < maxFrac) frac2 += '0';
    
    // Subtract fractions
    std::string fracDiff;
    int borrow = 0;
    for (int i = maxFrac - 1; i >= 0; --i) {
        int diff = (frac1[i] - '0') - (frac2[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        fracDiff.push_back(diff + '0');
    }
    std::reverse(fracDiff.begin(), fracDiff.end());
    
    // Subtract integers
    std::string intDiff;
    int i = int1.size() - 1, j = int2.size() - 1;
    while (i >= 0 || j >= 0 || borrow) {
        int diff = -borrow;
        if (i >= 0) diff += int1[i--] - '0';
        if (j >= 0) diff -= int2[j--] - '0';
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        intDiff.push_back(diff + '0');
    }
    std::reverse(intDiff.begin(), intDiff.end());
    
    // Remove trailing zeros from fraction
    while (!fracDiff.empty() && fracDiff.back() == '0') {
        fracDiff.pop_back();
    }
    
    // Combine
    std::string result = trimLeadingZeros(intDiff);
    if (result.empty()) result = "0";
    if (!fracDiff.empty()) {
        result += "." + fracDiff;
    }
    
    return result;
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
        int cmp = comparePositive(num1, num2);
        if (cmp == 0) return "0";

        if (cmp > 0) {
            std::string result = subtractPositive(num1, num2);
            return (sign1 == '-' && result != "0") ? "-" + result : result;
        } else {
            std::string result = subtractPositive(num2, num1);
            return (sign2 == '-' && result != "0") ? "-" + result : result;
        }
    }

    // Same sign: add
    size_t dot1 = num1.find('.'), dot2 = num2.find('.');
    std::string int1 = (dot1 == std::string::npos) ? num1 : num1.substr(0, dot1);
    std::string frac1 = (dot1 == std::string::npos) ? "" : num1.substr(dot1 + 1);
    std::string int2 = (dot2 == std::string::npos) ? num2 : num2.substr(0, dot2);
    std::string frac2 = (dot2 == std::string::npos) ? "" : num2.substr(dot2 + 1);

    // Align fractions
    size_t maxFrac = std::max(frac1.size(), frac2.size());
    while (frac1.size() < maxFrac) frac1 += '0';
    while (frac2.size() < maxFrac) frac2 += '0';

    // Add fractions
    std::string fracSum;
    int carry = 0;
    for (int i = maxFrac - 1; i >= 0; --i) {
        int sum = (frac1[i] - '0') + (frac2[i] - '0') + carry;
        fracSum.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    std::reverse(fracSum.begin(), fracSum.end());

    // Add integers
    std::string intSum;
    int i = int1.size() - 1, j = int2.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += int1[i--] - '0';
        if (j >= 0) sum += int2[j--] - '0';
        intSum.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    std::reverse(intSum.begin(), intSum.end());

    while (!fracSum.empty() && fracSum.back() == '0') {
        fracSum.pop_back();
    }

    // Combine
    std::string result = intSum;
    if (!fracSum.empty()) {
    if (!fracSum.empty()) {
        result += "." + fracSum;
    }

    if (sign1 == '-' && result != "0") {
        return "-" + result;
    }
    return result;
}