#pragma once

#include "domain.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <utility>


namespace path_handler {
    using namespace std::literals;
    using namespace catalogue::domain::type_naming;
    using namespace catalogue::domain::literals;

    namespace fs = std::filesystem;

    inline static fs::path ValidateDirectoryPath(const fs::path p) {
        auto path = std::move(p);

        if (fs::create_directory(path)) {
            std::cout << "A new directory was succesfully created\n"s;
        } else {
            std::cout << "The path: " << path << " already exists.\n"s;
        }

        return path;
    }
    

    

} //namespace path_handler
