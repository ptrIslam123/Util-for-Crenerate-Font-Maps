#include <iostream>
#include "generate_font_data_array.h"

/**
 * @brief Генерирует h и cpp файлы содержащие массив данных шрифта
 * @param arrayName Название генерируемого буфера
 * @param wfntFilePath Путь до файла со шрифтом
 * @return 0, если успешно, -1 иначе
 */
StatusInfo GenerateFontDataArray(const std::string &arrayName, const std::string &wfntFilePath) {
    const std::string headerFile(arrayName + ".h");
    const std::string cppFile(arrayName + ".cpp");
    std::ifstream wfntFile(wfntFilePath, std::ios::in | std::ios::binary);

    if (!wfntFile.is_open()) {
        return std::make_pair(Status_file_not_found, wfntFilePath);
    }

    std::ofstream outHeaderFile(headerFile);
    std::ofstream outSourceFile(cppFile);
    FontDataArray fontDataArray(arrayName);
    fontDataArray << wfntFile;

    auto result = fontDataArray.generateHeaderFile(
        "Сгенерированные данные шрифта",
        {
        "#include \"wise_types.h\"",
        "#include \"containers/array.h\""
        }, outHeaderFile);
    if (result.first != Status_ok) {
        return result;
    }

    result = fontDataArray.generateSourceFile(outSourceFile);
    if (result.first != Status_ok) {
        return result;
    }
    wfntFile.close();
    outHeaderFile.close();
    outSourceFile.close();
    return std::make_pair(Status_ok, headerFile + " and " + cppFile);
}

/**
 * @brief Выводит список флагом и параметров программы
 * @return 0, если успешно, -1 иначе
 */
int PrintHelpInfo() {
    std::cout << "Преобразует массив данных из файла шрифта, в .h и .cpp файлы, содержащие бинарные данные"
            << std::endl;
    std::cout << "-g [arrayName] [fileName.wfnt]    генерирует данные шрифта" << std::endl;
    std::cout << "-h                                вывод справочной информации" << std::endl;
    return EXIT_SUCCESS;
}

/**
 * @brief Обработчик ошибок
 * @param status Статус результата
 * @param description детализированное описание результат
 * @return 0, в случае успеха, код шибки иначе
 */
int ErrorHandler(const Status &status, const std::string &description=std::string()) {
    switch (status) {
        case Status_ok:
            std::cout << "[OK] Successfully generate files: [" << description << "]" << std::endl;
            return EXIT_SUCCESS;
        case Status_bad_alloc:
            std::cout << "Bad_alloc: [" << description << "]" << std::endl;
            return -1;
        case Status_file_not_found:
            std::cout << "File: [" << description << "] not found" << std::endl;
            return -2;
        case Status_wrong_arguments_lit:
            std::cout << "Wrong arguments list" << std::endl;
            return -3;
        case Status_undefine_flag_app:
            std::cout << "Undefine flag or argument command line => [" << description << "]" << std::endl;
            return -4;
        case Status_undefine_exception:
            std::cout << "Undefine exception: [" << description << "]" << std::endl;
            return -5;
        default:
            return EXIT_SUCCESS;
    }
}

/**
 * @brief Проверка количества переданных аргументов на корректность
 * @param argc Количество переданных аргументов командной строки
 * @return true в случае корректности, false в ином случае
 */
bool CheckArgc(int argc) {
    if (argc == 2) {
        return true;
    } else if (argc == 4) {
        return true;
    }
    return false;
}

/**
 * @brief Генерирует h и cpp файлы содержащие массив с данными шрифта
 *
 * @details Для генерации файлов необходимо указать -g [имя массива с данными шрифта] [путь до файла со шрифтом]
 * @param argc Количество переданных аргументов
 * @param argv Указатель на массив указатель на строки со значениями переданных аргументов
 * @return 0, если успешно, код ошибки иначе
 */
int main(int argc, char **argv) {
    std::pair<Status, std::string> result;

    if (!CheckArgc(argc)) {
        return ErrorHandler(Status_wrong_arguments_lit);
    }

    const std::string flag = argv[1];
    if (flag == "-g") {
        result = GenerateFontDataArray(argv[2], argv[3]);
    } else if ((flag == "-h") || (flag == "--help")) {
       return PrintHelpInfo();
    } else {
        result = std::make_pair(Status_undefine_flag_app, flag);
    }
    return ErrorHandler(result.first, result.second);
}
