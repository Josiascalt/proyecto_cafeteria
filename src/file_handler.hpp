#pragma once

#include <filesystem>
#include <fstream>

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
                static std::ofstream new_file(path);
                if (!new_file) {
                    throw exceptions::ValidationPathError{};
                }
            } else {
                fs::create_directory(path);
            }
        }
        
        return path;
    }

    template <typename T>
    inline static bool WriteInBinary(const fs::path& path, T* source, size_t size = sizeof(T)) {
        //bfout = binary-file-out
        static std::ofstream bfout;
        bfout.open(path, std::ios::out | std::ios::binary | std::ios::app);

        if (bfout) {
            bfout.write(reinterpret_cast<char*>(source), size);
            bfout.close();
        }
        
        return bfout ? true : false;
    } 

    template <typename T>
    inline static bool ReadInBinary(const fs::path& path, T* target, size_t size = sizeof(T)) {
        //bfin = binary-file-in
        static std::ifstream bfin;
        bfin.open(path, std::ios::in | std::ios::binary);
        if (bfin) {
            bfin.read(reinterpret_cast<char*>(target), size);
            bfin.close();
        }
        
        return bfin ? true : false;
    }
    
    
} //namespace file_handler
