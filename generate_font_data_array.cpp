#include "generate_font_data_array.h"

#include <iostream>



FontDataArray::FontDataArray(const std::string &arrayName, const size_t height, const size_t width):
arrayName_(arrayName),
data_(nullptr),
sizeArray_(height * width) {
}

FontDataArray::~FontDataArray() {
    delete data_;
}

bool FontDataArray::operator<< (std::ifstream &file) {
    if (readBytes(file) == nullptr) {
        /* */
        throw std::bad_alloc{};
    }
    return true;
}

bool FontDataArray::generateHeaderFile(const std::vector<std::string> &includes, std::ofstream &file) {
    for (auto &include : includes) {
        file << include;
        file << "\n";
    }

    file << "\nnamespace wise {\n\n";
        file << "extern Array<Byte, " << sizeArray_ << "> " << arrayName_ << ";";
    file << "\n\n} //namespace wise\n";
    return true;
}

bool FontDataArray::generateSourceFile(std::ofstream &file) {
    file << "#include \"" << arrayName_ << ".h\"\n";
    file << "\nnamespace wise {\n\n";

        file << "const Array<Byte, " << sizeArray_ << "> " << arrayName_ << " = {";
        writeBytes(file);
        file << "\n};";

    file << "\n\n} //namespace wise\n";
    return true;
}

FontDataArray::Byte *FontDataArray::readBytes(std::ifstream &file) {
    data_ = new Byte [sizeArray_];

    if (data_ == nullptr) {
        return nullptr;
    }
    file.read((char*)data_, sizeArray_);
    return data_;
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
