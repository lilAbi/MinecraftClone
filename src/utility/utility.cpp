
#include "utility.h"

std::string util::ReadFromFile(std::string_view filePath) {
    std::string data;

    std::fstream inputFile(filePath, std::ios::in);

    if(inputFile) {
        inputFile.seekg(0, std::ios::end);
        data.resize(inputFile.tellg());
        inputFile.seekg(0, std::ios::beg);
        inputFile.read(&data[0], (long) data.size());
    }
    inputFile.close();

    return data;
}