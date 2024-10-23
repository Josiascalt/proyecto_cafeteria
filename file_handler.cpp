#include "file_handler.hpp"
#include "domain.hpp"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <deque>
#include <exception>

namespace catalogue {
    namespace file_handler {
        using namespace std::literals;
        using namespace domain::literals;
        
        

        fs::path ValidatePath(const fs::path&& path_to_validate) {
            auto path = std::move(path_to_validate);
            if (!std::filesystem::exists(path)) {
                if (path.has_extension()) {
                    std::ofstream new_file(path);
                    if (!new_file) {
                        throw exceptions::ValidationPathError{};
                    }
                } else {
                    fs::create_directory(path);
                }
            }
            
            return path;
        }
        
        //class DatabaseHandler member functions definition
        DatabaseHandler::DatabaseHandler(const MetadataPaths& metadata, const DataPaths& data) 
        : data_stream_()
        , metadata_(metadata)
        , data_(data)
        {

        }
        
    } //namespace file_handler
} //namespace catalogue