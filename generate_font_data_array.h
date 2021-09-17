#pragma once

#include <string>
#include <fstream>
#include <inttypes.h>
#include <vector>

/**
 * @brief Класс для генерации массива, содержащие бинарные данные шрифта
 */
class FontDataArray {
public:
    typedef uint8_t Byte; //!< объявление типа байт

    /**
     * @brief Конструктор инициализирует все внутренние переменные начальными значениями, которые ему передали
     * @param arrayName имя массива, который будет сгенерирован
     * @param height размер высоты данных шрифта в байтах
     * @param width размер ширины данных шрифта в байтах
     */
    FontDataArray(const std::string &arrayName, size_t height, size_t width);

    /**
     * @brief Конструктор уничтожает все внутренние ресурсы класса
     */
    ~FontDataArray();

    /**
     * @brief оператор, для цтения юайтов из файла шрифта
     * @param file ссылка на экземпляр файлового потока, для чтения байт данных из файла шрифта
     * @return возвращает true в если чтение успешно, false иначе
     */
    bool operator<< (std::ifstream &file);

    /**
     * @brief Генерирует хедер файл, содержащий объявление массива данных
     * @param doc Документация к массиву
     * @param includes Список всех подключаемых файлов внутри генерируемого хедера
     * @param file ссылка на экземпляр файлового потока, для записи байт данных в сгенерированный файл
     * @return возвращает true в если чтение успешно, false иначе
     */
    bool generateHeaderFile(const std::string &doc, const std::vector<std::string> &includes, std::ofstream &file);

    /**
     * @brief Генерирует cpp файл, содержащий определение массива данных
     * @param file ссылка на экземпляр файлового потока, для записи байт данных в сгенерированный файл
     * @return возвращает true в если чтение успешно, false иначе
     */
    bool generateSourceFile(std::ofstream &file);

private:
    /**
     * @brief Считывает в массив байт из указанного файлового потока.
     * @param file ссылка на экземпляр файлового потока, для чтения байт данных из файла шрифта
     * @return
     */
    Byte *readBytes(std::ifstream &file);

    /**
     * @brief Записывает в указанный файловый поток, массив байт
     * @param file ссылка на экземпляр файлового потока, для записи байт данных в файл
     */
    void writeBytes(std::ofstream &file);

    std::string arrayName_; //!< Названия генерируемого массива
    Byte *data_; //!< Указатель на буфер данных шрифта
    size_t sizeArray_; //!< размер буфера данных шрифта
};
