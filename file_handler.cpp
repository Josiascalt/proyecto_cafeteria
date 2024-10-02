#include "file_handler.hpp"

#include "domain.hpp"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <deque>
#include <iostream>

namespace catalogue {
    namespace file_handler {
        using namespace std::literals;
        using namespace domain::literals;
        
        fs::path ValidateDirectoryPath(fs::path&& p) {
            auto path = std::move(p);

            if (fs::create_directory(path)) {
                std::cout << "A new directory was succesfully created\n"s;
            } else {
                std::cout << "The path: "s << path << " already exists.\n"s;
            }

            return path;
        }
        
        //class DatabaseHandler member functions definition

        DatabaseHandler::DatabaseHandler(const DataPaths& paths) {
        }
    } //namespace file_handler
} //namespace catalogue