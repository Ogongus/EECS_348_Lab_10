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
}