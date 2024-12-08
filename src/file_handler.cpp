#include "file_handler.hpp"

namespace file_handler {
    namespace literals {
        std::filesystem::path operator""_p(const char* pathname, Size size) {
                return std::filesystem::path(pathname, pathname + size);
        }
    } //namespace literals

    //class BinaryFile member functions definition
    BinaryFile::BinaryFile(const fs::path& path) 
    : file_(path, std::ios::out | std::ios::in | std::ios::binary) {
        file_.seekp(0, std::ios::end);
        auto size = file_.tellp();
        size_ = size;
        write_pos_ = size;

        file_.seekg(0, std::ios::beg);
        read_pos_ = file_.tellg();
    }

    Size BinaryFile::GetSize() const {
        return size_;
    }
    
} //namespace file_handler
