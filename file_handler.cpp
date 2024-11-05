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
        
        

        fs::path CreatePathObject(const char* path_to_validate, const fs::path parent_path = ""_p) {
            fs::path path = parent_path / fs::path(path_to_validate);
            if (!std::filesystem::exists(path)) {
                if (path.has_extension()) {
                    std::ofstream new_file(path);
                    if (!new_file) {
                        throw exceptions::paths::ValidationPathError{};
                    }
                } else {
                    fs::create_directory(path);
                }
            }
            
            return path;
        }
        
        //class DatabaseHandler member functions definition
        DatabaseHandler::DatabaseHandler(database::UserCatalogue& catalogue, const MetadataPaths& metadata, const DataPaths& data) 
        : catalogue_(catalogue)
        , metadata_(metadata)
        , data_(data)
        , handler_()
        {

        }
        
    } //namespace file_handler
} //namespace catalogue