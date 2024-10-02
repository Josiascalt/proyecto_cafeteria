#include "file_handler.hpp"

#include "domain.hpp"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <deque>
#include <iostream>

namespace catalogue {
    namespace file_handler {

        using namespace domain::literals;
        
        
        //class DatabaseHandler member functions definition

        DatabaseHandler::DatabaseHandler(const std::filesystem::path& parent_directory)
        : data_stream_(std::fstream{parent_directory, std::ios::out | std::ios::in 
                                        | std::ios::binary 
                                        | std::ios::app}) {


        }
    } //namespace file_handler
} //namespace catalogue