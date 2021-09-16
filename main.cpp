#include <iostream>
#include "generate_font_data_array.h"

const std::string inFilePath = "/home/islam/CLionProjects/makeBitMaps/resources/defaultFontForFontManager.wfnt";
const std::string outHeaderFilePath = "/home/islam/CLionProjects/makeBitMaps/resources/buffer.h";
const std::string outSourceFilePath = "/home/islam/CLionProjects/makeBitMaps/resources/buffer.cpp";

int main() {

    FontDataArray fontArray("buffer", 128, 128);
    std::ifstream inFile(inFilePath, std::ios::in | std::ios::binary);
    std::ofstream outHeaderFile(outHeaderFilePath, std::ios::out);
    std::ofstream outSourceFile(outSourceFilePath, std::ios::out);

    fontArray << inFile;

    fontArray.generateHeaderFile({
        "#include \"wise_types.h\"",
        "#include \"containers/array.h\""
        }, outHeaderFile);

    fontArray.generateSourceFile(outSourceFile);

    inFile.close();
    outHeaderFile.close();
    outSourceFile.close();

    return 0;
}
