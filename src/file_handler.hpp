#pragma once

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace file_handler {
    using Size = size_t;

    namespace literals {
        std::filesystem::path operator""_p(const char* pathname, Size size);
    } //namespace literals

    namespace exceptions {
        struct ValidationPathError {};
    } //namespace exceptions

    using namespace literals;

    inline static fs::path CreatePathObject(const char* path_to_validate, const fs::path& parent_path = ""_p) {
        fs::path path = parent_path / fs::path(path_to_validate);
        if (!std::filesystem::exists(path)) {
            if (path.has_extension()) {
                static std::ofstream new_file;
                new_file.open(path);
                if (new_file) {
                    new_file.close();
                } else {
                    throw exceptions::ValidationPathError{};
                }

            } else {
                fs::create_directory(path);
            }
        }
        
        return path;
    }

    class BinaryFile {
    public:
        BinaryFile(const fs::path& path);

        template <typename T>
        inline void Write(T* source, Size size = sizeof(T)) {
            file_.seekp(write_pos_);

            if (file_) {
                file_.write(reinterpret_cast<char*>(source), size);
            }

            size_ += size;
            write_pos_ += size;
            
        }

        template <typename T>
        inline void Read(T* target, Size size = sizeof(T)) {
            file_.seekg(read_pos_);

            if (file_) {
                file_.read(reinterpret_cast<char*>(target), size);
            }

            write_pos_ += size;
        } 

        Size GetSize() const;

    private:
        std::fstream file_;

        Size size_;
        Size write_pos_;
        Size read_pos_;
    };
} //namespace file_handler
