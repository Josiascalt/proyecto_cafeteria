#pragma once

#include "domain.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <utility>


namespace path_handler {
    using namespace std::literals;
    using namespace catalogue::domain::components;
    using namespace catalogue::domain::literals;

    namespace fs = std::filesystem;

    inline static fs::path ValidateDirectoryPath(fs::path&& p) {
        auto path = std::move(p);

        if (fs::create_directory(path)) {
            std::cout << "A new directory was succesfully created\n"s;
        } else {
            std::cout << "The path: "s << path << " already exists.\n"s;
        }

        return path;
    }

    /*inline static fs::path ValidateFilePath(fs::path&& p) {
        auto path = std::move(p);

        if (!fs::exists(path)) {
            std::cout << "The path: "s << path << " aready exists.\n"s;
        } else {
            std::ofstream new_file(path);
            std::cout << (new_file ? "A new file was successfully created"s : "Error while creating a file"s) << '\n';
        }

        return path;
    }*/
    

    

} //namespace path_handler
