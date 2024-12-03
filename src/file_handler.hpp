#pragma once

#include <fstream>
#include <filesystem>
#include "domain.hpp"

namespace fs = std::filesystem;

namespace file_handler {
    namespace exceptions {
        struct ValidationPathError {};
    } //namespace exceptions

    using namespace catalogue::domain::literals;

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

    inline static std::fstream CreateBinaryFstream(const fs::path& path) {
        return std::fstream{path, std::ios::in | std::ios::out | std::ios::binary | std::ios::app};
    }

    inline static size_t CalcFileSize(std::fstream& file) {
        auto initial_pos = file.tellg();
        file.seekg(0, std::ios::end);
        auto file_size = file.tellg();
        file.seekg(initial_pos);
        
        return file_size;
    }

    template <typename T>
    inline static bool WriteInBinary(std::fstream& bfout /*binary-file-out*/, T* source, size_t size = sizeof(T)) {
        if (bfout) {
            bfout.write(reinterpret_cast<char*>(source), size);
        }
        
        return bfout ? true : false;
    } 

    template <typename T>
    inline static bool ReadInBinary(std::fstream& bfin /*binary-file-in*/, T* target, size_t size = sizeof(T)) {
        if (bfin) {
            bfin.read(reinterpret_cast<char*>(target), size);
        }
        
        return bfin ? true : false;
    }

    
    
    
} //namespace file_handler
