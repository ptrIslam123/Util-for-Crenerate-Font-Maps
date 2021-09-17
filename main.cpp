#include <iostream>
#include <cstring>
#include "generate_font_data_array.h"


/**
 * @brief Генериурет h и cpp файлы содержащие массив данных шрифта
 * @param arrayName Название генерируемого буфера
 * @param wfntFilePath Путь до файла со шрифтом
 * @param height Высота текстуры со шрифтом
 * @param width Ширина текстуры со шрифтом
 * @return 0 если успешно, -1 иначе
 */
int GenerateFontDataArray(const std::string &arrayName, const std::string &wfntFilePath, size_t height, size_t width) {
    FontDataArray fontDataArray(arrayName, height, width);
    std::ifstream wfntFile(wfntFilePath, std::ios::in | std::ios::binary);
    std::ofstream outHeaderFile(arrayName + ".h");
    std::ofstream outSourceFile(arrayName + ".cpp");

    if (!wfntFile.is_open()) {
        std::cout << "File: " << wfntFilePath << "not found" << std::endl;
        return -1;
    }

    fontDataArray << wfntFile;

    fontDataArray.generateHeaderFile(
        "Сгенерированные данные шрифта",
        {
        "#include \"wise_types.h\"",
        "#include \"containers/array.h\""
        }, outHeaderFile);

    fontDataArray.generateSourceFile(outSourceFile);

    wfntFile.close();
    outHeaderFile.close();
    outSourceFile.close();
    return 0;
}

/**
 * @brief Выводит список флагом и параметров программы
 * @return 0 если успешно, -1 иначе
 */
int PrintHelpInfo() {
    std::cout << "Преобразует в массив данных из файла шрифта в header и cpp файлы содержащие бинарные данные"
            << std::endl;
    std::cout << "-g [arrayName] [fileName.wfnt] [height] [width]   генерирует данные шрифта" << std::endl;
    std::cout << "-h                                                выводит справочник команд и флагов" << std::endl;
    return 0;
}

int main(int argc, char **argv) {
    int result = 0;

    if (argc < 2 || argc > 6) {
        std::cout << "Wrong arguments list" << std::endl;
        result = -1;
    }

    const std::string flag = argv[1];
    if (flag == "-g") {
        result = GenerateFontDataArray(
                argv[2], argv[3], atoi(argv[4]), atoi(argv[5]));
    } else if (flag == "-h") {
        result = PrintHelpInfo();
    } else {
        std::cout << "Wrong arguments list" << std::endl;
        result = -1;
    }
    return result;
}
