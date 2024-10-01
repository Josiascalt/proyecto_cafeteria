#include "file_handler.hpp"

#include "domain.hpp"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <deque>
#include <iostream>

namespace catalogue {
    namespace file_handler {
        
        using namespace domain::components;
        using namespace domain::literals;
        
        
        //class DatabaseHandler member functions definition

        DatabaseHandler::DatabaseHandler(const std::filesystem::path& path)
        : database_(std::fstream{path, std::ios::out | std::ios::in 
                                        | std::ios::binary 
                                        | std::ios::app}) {
            if (database_) {
                database_.seekg(0, std::ios::end);
                is_empty_ = database_.tellg() == 0;
                database_.seekg(0, std::ios::beg);
            } else {
                std::cout << "Error while constructing DatabaseHandler";
            }

        }

        bool DatabaseHandler::IsEmpty() {
            return is_empty_;
        }

    } //namespace file_handler
} //namespace catalogue