#include "calculator.h"
#include <cctype>
#include <algorithm>
#include <iostream>

std::string trimLeadingZeros(const std::string& s) {
    size_t start = s.find_first_not_of('0');
    if (start == std::string::npos) return "0";
    return s.substr(start);
}

