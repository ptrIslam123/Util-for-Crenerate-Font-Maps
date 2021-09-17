#pragma once

#include <string>
#include <fstream>
#include <inttypes.h>
#include <vector>

/**
 * @brief Перечисление содержащее типы ошибок в системе и статус ok
 */
enum Status {
    Status_ok, //!< Статус говорящий о положительном результате
    Status_bad_alloc, //!< Статус ошибки аллокации памяти
    Status_file_not_found, //!< Статус ошибки, что не найден файл
    Status_wrong_arguments_lit, //!< Ошибка в переданных параметрах командной строки
    Status_undefine_flag_app, //!< Ошибка неизвестного флага командной строки
    Status_undefine_exception //!<неизвестная ошибка
};

typedef std::pair<Status, std::string> StatusInfo; //!< Тип статут результата операций

/**
 * @brief Возвращает статус ok, с пустой строкой
 * @return std::pair, содержащий Статус ok и пустую строку
 */
StatusInfo makeStatusOk();

/**
 * @brief Класс для генерации массива, содержащие бинарные данные шрифта
 */
class FontDataArray {
public:
    /**
     * @brief Конструктор инициализирует все внутренние переменные начальными значениями, которые ему передали
     * @param arrayName имя массива, который будет сгенерирован
     */
    FontDataArray(const std::string &arrayName);

    /**
     * @brief Конструктор уничтожает все внутренние ресурсы класса
     */
    ~FontDataArray() = default;

    /**
     * @brief оператор, для чтения байтов из файла шрифта
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
    StatusInfo generateHeaderFile(const std::string &doc, const std::vector<std::string> &includes, std::ofstream &file);

    /**
     * @brief Генерирует cpp файл, содержащий определение массива данных
     * @param file ссылка на экземпляр файлового потока, для записи байт данных в сгенерированный файл
     * @return возвращает true в если чтение успешно, false иначе
     */
    StatusInfo generateSourceFile(std::ofstream &file);

    /**
     * @brief Возвращает размер буфера
     * @return размер буфера
     */
    size_t sizeArray() const;

private:
    typedef uint8_t Byte; //!< объявление типа байт

    /**
     * @brief Считывает в массив байт из указанного файлового потока.
     * @param file ссылка на экземпляр файлового потока, для чтения байт данных из файла шрифта
     * @return
     */
    StatusInfo readBytes(std::ifstream &file);

    /**
     * @brief Записывает в указанный файловый поток, массив байт
     * @param file ссылка на экземпляр файлового потока, для записи байт данных в файл
     */
    void writeBytes(std::ofstream &file);

    /**
     *  @brief Вычисляет и возвращает размер файла
     * @param file ссылка на экземпляр файлового потока, для чтения байт данных из файла шрифта
     * @return размер файла
     */
    size_t getFileSize(std::ifstream &file);

    std::string arrayName_; //!< Названия генерируемого массива
    std::vector<Byte> data_; //!< Буфер данных шрифта
    size_t sizeArray_; //!< размер буфера данных шрифта
};
