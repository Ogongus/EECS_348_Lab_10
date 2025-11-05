#include <iostream>
#include <fstream>
#include <sstream>
#include "calculator.h"

int main(int argc, char* argv[]) {
    std::string filename = (argc > 1) ? argc[1] : "input.txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return 1;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        lineNum++;
        std::istringstream iss(line);
        std::string num1, num2;

        if(!(iss >> num1 >> num2)) {
            std::cout << "Line " << lineNum << ": Invalid format" << std::endl;
            continue;
        }

        
    }
}