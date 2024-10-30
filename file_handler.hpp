#pragma once

#include "domain.hpp"
#include "users_catalogue.hpp"

#include <fstream>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <utility>
#include <optional>
#include <memory>
#include <optional>

namespace catalogue {
    namespace file_handler {
        namespace fs = std::filesystem;
        using namespace domain::literals;
        using namespace domain::components;
        using namespace domain::compound_types::final_types;
        
        namespace exceptions {
            struct ValidationPathError {};
        } //namespace exceptions
        
        /*
            The struct DataPaths depends on the datatypes of the struct Composition 
            in the namespace domain. Every path in the struct DataPaths links to file 
            that storages a datatype from struct Composition.
        */

        struct DataPaths {
            struct SizedData {
                fs::path data;
                fs::path sizes;
            };
            
            SizedData name_data;
            SizedData identifier_data;
            fs::path gender_data;
            fs::path group_data;

            DataPaths& SetNameData(SizedData paths) {
                name_data = std::move(paths);
                return *this;
            }

            DataPaths& SetIdentifierData(SizedData paths) {
                identifier_data = std::move(paths);
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
            fs::path queue;

            MetadataPaths& SetQueue(fs::path path) {
                queue = std::move(path);
                return *this;
            }
        };

        static fs::path ValidatePath(const fs::path&& path_to_validate);

        //template <typename Type>
       class DatabaseHandler {
        public: //Public member functions
            DatabaseHandler(database::UserCatalogue& catalogue, const MetadataPaths& metadata, const DataPaths& data);

            template <typename T>
            bool Serialize(T obj) {
                auto layout = obj.GetComponents();

                SerializeMetadata(&obj);
                
                if (layout.has_name) {
                    Size size = obj.name.size();
                    WriteInBinary(data_.name_data.sizes, &size);
                    WriteInBinary(data_.name_data.data, obj.name.data(), size);
                }
                
                if (layout.has_identifier) {
                    Size size = obj.identifier.size();

                    WriteInBinary(data_.identifier_data.sizes, &size);
                    WriteInBinary(data_.identifier_data.data, obj.identifier.data(), size);
                }

                if (layout.has_group) {
                    WriteInBinary(data_.group_data, &obj.group);
                }

                if (layout.has_gender) {
                    WriteInBinary(data_.gender_data, &obj.gender);
                }

                return false;
            }

            bool Deserialize() {
                using namespace domain::compound_types::final_types;
                using namespace domain::components;

                //Metadata
                auto queue = DeserializeFile<FinalTypes>(metadata_.queue);
                
                //Data
                auto names_sizes = DeserializeFile<Size>(data_.name_data.sizes);
                auto names = DeserializeFile<domain::components::Name>(data_.name_data.data, names_sizes);
                auto identifiers_sizes = DeserializeFile<Size>(data_.identifier_data.sizes);
                auto identifiers = DeserializeFile<domain::components::Identifier>(data_.identifier_data.data, identifiers_sizes);
                //auto groups = DeserializeFile<domain::components::Group>(data_.gender_data);
                auto genders = DeserializeFile<domain::components::Gender>(data_.gender_data);
                
                /*if (elem.GetTypeName() == FinalTypes::TypeNames::STUDENT) {
                    catalogue_.AddUser(CreateObject<Student>());
                }*/ 

                return true;
            }

            //~DatabaseHandler();

        private: //Private member fuctions
            using Size = int;
            
            bool SerializeMetadata(FinalTypes* obj) {
                return WriteInBinary(metadata_.queue, obj);
            }

            template <typename T>
            std::unique_ptr<std::vector<T>> DeserializeFile(fs::path path) {
                handler_.open(path, std::ios::in | std::ios::binary | std::ios::ate);
                if (Size file_size = handler_.tellg(); file_size > 0 && handler_) {
                    handler_.seekg(0);

                    std::vector<T> file_content;
                    file_content.resize(file_size / sizeof(T));

                    handler_.read(reinterpret_cast<char*>(file_content.data()), file_size);

                    handler_.close();

                    return std::make_unique<std::vector<T>>(file_content);
                } 

                return nullptr;  
            }

            template <typename T>
            std::unique_ptr<std::vector<T>> DeserializeFile(fs::path path, const std::unique_ptr<std::vector<Size>>& sizes) {
                handler_.open(path, std::ios::in | std::ios::binary | std::ios::ate);
                if (Size file_size = handler_.tellg(); file_size > 0 && handler_ && sizes) {
                    handler_.seekg(0);

                    std::vector<T> file_content;
                    file_content.reserve(sizes -> size());

                    T elem;
                    for (auto size : *sizes) {
                        elem.resize(size);
                        handler_.read(reinterpret_cast<char*>(elem.data()), size);
                        file_content.push_back(std::move(elem));
                    }

                    handler_.close();

                    return std::make_unique<std::vector<T>>(file_content);;
                }

                return nullptr;
            }

            template <typename T>
            bool WriteInBinary(fs::path path, T* value, Size size = sizeof(T)) {
                handler_.open(path, std::ios::out | std::ios::binary | std::ios::app);

                if (handler_) {
                    handler_.write(reinterpret_cast<char*>(value), size);
                    handler_.close();
                    return handler_ ? true : false;
                }
                
                return false;
            } 

            template <typename T>
            bool ReadInBinary(fs::path path, T* target, Size size = sizeof(T)) {
                handler_.open(path, std::ios::in | std::ios::binary);
                if (handler_) {
                    handler_.read(reinterpret_cast<char*>(target), size);
                    handler_.close();
                    return handler_ ? true : false;
                }
                
                return false;
            }
            
            template <typename T>
            T CreateObject() {
                T obj;

                auto layout = obj.GetComponents();

                if (layout.has_name) {
                    int size = 0;
                    ReadInBinary(data_.name_data.sizes, &size);

                    obj.name.resize(size);
                    ReadInBinary(data_.name_data.data, obj.name.data(), size);
                }
                
                if (layout.has_identifier) {
                    int size;
                    ReadInBinary(data_.identifier_data.sizes, &size);

                    obj.identifier.resize(size);
                    ReadInBinary(data_.identifier_data.data, obj.identifier.data(), size);
                }

                if (layout.has_group) {
                    ReadInBinary(data_.group_data, &obj.group);
                }

                if (layout.has_gender) {
                    ReadInBinary(data_.gender_data, &obj.gender);
                }

                return obj;
            }

        private: //Private data members
            database::UserCatalogue& catalogue_;
            const MetadataPaths& metadata_;
            const DataPaths& data_;

            std::fstream handler_;  
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