#include "generate_font_data_array.h"

#include <iostream>

inline
StatusInfo makeStatusOk() {
    return std::make_pair(Status_ok, std::string());
}

FontDataArray::FontDataArray(const std::string &arrayName):
arrayName_(arrayName),
data_(),
sizeArray_(0) {
}

bool FontDataArray::operator<< (std::ifstream &file) {
    sizeArray_ = getFileSize(file);
    readBytes(file);
    return true;
}

StatusInfo FontDataArray::generateHeaderFile(
        const std::string &doc, const std::vector<std::string> &includes, std::ofstream &file) {
    for (auto &include : includes) {
        file << include;
        file << "\n";
    }

    file << "\nnamespace wise {\n\n";

        file << "/**\n";
        file << " * @brief " << doc << "\n";
        file << " */\n";
        file << "extern Array<Byte, " << sizeArray_ << "> " << arrayName_ << ";";

    file << "\n\n} //namespace wise\n";
    return makeStatusOk();
}

StatusInfo FontDataArray::generateSourceFile(std::ofstream &file) {
    file << "#include \"" << arrayName_ << ".h\"\n";
    file << "\nnamespace wise {\n\n";

        file << "const Array<Byte, " << sizeArray_ << "> " << arrayName_ << " = {";
        writeBytes(file);
        file << "\n};";

    file << "\n\n} //namespace wise\n";
    return makeStatusOk();
}

StatusInfo FontDataArray::readBytes(std::ifstream &file) {
    try {
        data_.resize(sizeArray_);
    } catch (std::bad_alloc &e) {
        return std::make_pair(Status_bad_alloc, "the file size  is too large");
    } catch (const std::exception &e) {
        return std::make_pair(Status_undefine_exception, e.what());
    }

    while (!file.eof()) {
        data_.push_back(file.get());
    }
    return makeStatusOk();
}

void FontDataArray::writeBytes(std::ofstream &file) {
    for (size_t i = 0; i <sizeArray_; ++i) {
        if ((i % 20) == 0) {
            file << '\n';
            file << "    ";
        }

        file << static_cast<uint16_t>(data_[i]) << "U";
        if (i < sizeArray_ - 1) {
            file << ", ";
        }
    }
}

size_t FontDataArray::getFileSize(std::ifstream &file) {
    file.seekg(0, std::ios::end);
    const size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    return size;
}

size_t FontDataArray::sizeArray() const {
    return sizeArray_;
}
