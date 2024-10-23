#pragma once

#include "domain.hpp"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <utility>
#include <optional>

namespace catalogue {
    namespace file_handler {
        namespace fs = std::filesystem;
        using namespace domain::literals;

        namespace exceptions {
            struct ValidationPathError {};
        } //namespace exceptions
        
        static fs::path ValidatePath(const fs::path&& path_to_validate);

        class PathBase {
        public:
            PathBase(const fs::path& path) 
            : parent_path_(path) 
            {
            }

        protected:
            fs::path parent_path_;
            virtual ~PathBase() = default;
        };

        struct MetadataPaths : PathBase {
            fs::path layout;
            fs::path queue;

            MetadataPaths& SetLayout(fs::path path) {
                layout = std::move(path);
                return *this;
            }
            
            MetadataPaths& SetQueue(fs::path path) {
                queue = std::move(path);
                return *this;
            }
        };

        /*
            The struct DataPaths depends on the datatypes of the struct Components 
            in the namespace domain. Every path in the struct DataPaths links to file 
            that storages a datatype from struct Components.
        */

        struct DataPaths : PathBase {
            fs::path name_data;
            fs::path identificator_data;
            fs::path gender_data;
            fs::path group_data;

            DataPaths& SetNameData(fs::path path) {
                name_data = std::move(path);
                return *this;
            }

            DataPaths& SetIdentificatorData(fs::path path) {
                identificator_data = std::move(path);
                return *this;
            }

            DataPaths& SetGenderData(fs::path path) {
                gender_data = std::move(path);
                return *this;
            }

            DataPaths& SetGroupData(fs::path path) {
                group_data = std::move(path);
                return *this;
            }
        };
        
        //template <typename Type>
        class DatabaseHandler {
        public:
            DatabaseHandler(const MetadataPaths& metadata, const DataPaths& data);

            
            

            //~DatabaseHandler();
        private:
            std::fstream data_stream_;
            const MetadataPaths& metadata_;
            const DataPaths& data_;
            
        };

        struct Entry {
            std::string time;
            domain::compound_types::User* user;
        };

        /*class RecordHandler {
        public:
            void AddEntry();
        private:
            std::unordered_map<domain::Group, std::deque<const Entry>> records_;
        };*/
    } //namespace file_handler
}//namespace catalogue