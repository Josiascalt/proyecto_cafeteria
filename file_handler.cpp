#include "file_handler.hpp"

#include "domain.hpp"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <deque>
#include <iostream>

namespace catalogue {
    namespace file_handler {
        
        using namespace domain::type_naming;
        using namespace domain::literals;
        
        
        //class DatabaseHandler member functions definition

            DatabaseHandler::DatabaseHandler(const std::filesystem::path& path)
            : database_(std::fstream{path, std::ios::out | std::ios::in 
                                         | std::ios::binary 
                                         | std::ios::app})
            {
                database_.seekg(0, std::ios::end);
            }

            bool DatabaseHandler::IsEmpty() {
                return database_ ? database_.tellg() == 0 : false;
            }

    } //namespace file_handler
} //namespace catalogue