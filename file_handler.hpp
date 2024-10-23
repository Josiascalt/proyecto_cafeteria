#pragma once

#include "domain.hpp"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <utility>
#include <optional>
#include <cstdint>

namespace catalogue {
    namespace file_handler {
        namespace fs = std::filesystem;
        using namespace domain::literals;

        namespace exceptions {
            struct ValidationPathError {};
        } //namespace exceptions
        
        static fs::path ValidatePath(const fs::path&& path_to_validate);
        /*
            The struct DataPaths depends on the datatypes of the struct Components 
            in the namespace domain. Every path in the struct DataPaths links to file 
            that storages a datatype from struct Components.
        */

        struct DataPaths {
            fs::path name_data;
            fs::path identifier_data;
            fs::path gender_data;
            fs::path group_data;

            DataPaths& SetNameData(fs::path path) {
                name_data = std::move(path);
                return *this;
            }

            DataPaths& SetIdentifierData(fs::path path) {
                identifier_data = std::move(path);
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
        
        struct MetadataPaths {
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

        //template <typename Type>
        class DatabaseHandler {
        public: //Public member functions
            DatabaseHandler(const MetadataPaths& metadata, const DataPaths& data);

            template <typename T>
            bool Serialize(T obj) {
                using namespace domain::compound_types::final_types;
                FinalTypes elem = obj;
                auto elem_layout = elem.GetComponents();
                
                WriteInBinary(metadata_.queue, &elem);
                WriteInBinary(metadata_.layout, &elem_layout);
                
                if (elem_layout.has_name) {
                    int8_t size = obj.name.size();
                    WriteInBinary(data_.name_data, &size);
                    WriteInBinary(data_.name_data, obj.name.data(), size);
                }
                
                if (elem_layout.has_identifier) {
                    int8_t size = obj.identifier.size();
                    WriteInBinary(data_.identifier_data, &size);
                    WriteInBinary(data_.name_data, obj.name.data(), size);
                }

                /*if (elem_layout.has_group) {
                    WriteInBinary(data_.group_data, obj.group);
                }

                if (elem_layout.has_gender) {
                    WriteInBinary(data_.gender_data, obj.gender);
                }*/

                return false;
            }

            /*bool Deserialize() {
                fstream file_handler;
                
                catalogue::domain::CompoundTypes queue_elem;
                catalogue::domain::Components layout;
                
                ReadInBinary(file_handler, metadata.queue, &queue_elem);
                ReadInBinary(file_handler, metadata.layout, &layout);
                
                if (layout.HasName()) {
                    
                }
                return true;
            }*/

            //~DatabaseHandler();
        private: //Private member fuctions
            template <typename T>
            bool WriteInBinary(fs::path path, T* value, uint8_t size = sizeof(T)) {
                handler_.open(path, std::ios::out | std::ios::binary | std::ios::app);

                if (handler_) {
                    handler_.write(reinterpret_cast<char*>(value), size);
                    handler_.close();
                    return handler_ ? true : false;
                }
                
                return false;
            } 

            template <typename T>
            bool ReadInBinary(fs::path path, T* target, uint8_t size = sizeof(T)) {
                handler_.open(path, std::ios::in | std::ios::binary);
                if (handler_) {
                    handler_.read(reinterpret_cast<char*>(target), size);
                    handler_.close();
                    return handler_ ? true : false;
                }
                
                return false;
            }

        private: //Private data members
            std::fstream handler_;
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