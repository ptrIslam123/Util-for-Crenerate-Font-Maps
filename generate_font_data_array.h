#pragma once

#include <string>
#include <fstream>
#include <inttypes.h>
#include <vector>

class FontDataArray {
public:
    typedef uint8_t Byte;

    FontDataArray(const std::string &arrayName, size_t height, size_t width);
    ~FontDataArray();

    bool operator<< (std::ifstream &file);

    bool generateHeaderFile(const std::vector<std::string> &includes, std::ofstream &file);
    bool generateSourceFile(std::ofstream &file);

private:
    Byte *readBytes(std::ifstream &file);
    void writeBytes(std::ofstream &file);

    std::string arrayName_;
    Byte *data_;
    size_t sizeArray_;
};
