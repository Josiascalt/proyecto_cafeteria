#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <utility>
//#include <memory>
//#include <optional>

#include "domain.hpp"
#include "file_handler.hpp"

namespace catalogue {
    namespace data_manager {
        struct UserDataPaths {
            struct Metadata {
                fs::path queue;
            };

            Metadata metadata;
            fs::path names;
            fs::path identifiers;
            fs::path genders;
            fs::path groups;

            UserDataPaths& SetMetadataPaths(fs::path queue_path) {
                metadata.queue = std::move(queue_path);
                return *this;
            }

            UserDataPaths& SetNamesPath(fs::path names_path) {
                names = std::move(names_path);
                return *this;
            }

            UserDataPaths& SetIdentifiersPath(fs::path identifiers_path) {
                identifiers = std::move(identifiers_path);
                return *this;
            }

            UserDataPaths& SetGendersPath(fs::path genders_path) {
                genders = std::move(genders_path);
                return *this;
            }

            UserDataPaths& SetGroupsPath(fs::path groups_path) {
                groups = std::move(groups_path);
                return *this;
            }
        };

        class DataManager {
        public:
            void BackupData();
            void RecoverData();
        private:
            
            
        };

        class UserDataHandler {
        public:
            inline UserDataHandler(const UserDataPaths& user_data) 
            : queue_(user_data.metadata.queue, std::ios::in | std::ios::out | std::ios::binary | std::ios::app)
            , names_(user_data.names, std::ios::in | std::ios::out | std::ios::binary | std::ios::app)
            , identifiers_(user_data.identifiers, std::ios::in | std::ios::out | std::ios::binary | std::ios::app)
            , genders_(user_data.genders, std::ios::in | std::ios::out | std::ios::binary | std::ios::app)
            , groups_(user_data.groups, std::ios::in | std::ios::out | std::ios::binary | std::ios::app)
            {

            }

            /*template <typename T>
            bool Serialize(T obj) {

                SerializeMetadata(&obj);
                
                if (auto name = dynamic_cast<domain::components::Nameable*>(&obj)) {
                    WriteInBinary(data_.name_data.data, obj.name.data());
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
            }*/

        private:
            //Metadata
            std::fstream queue_;
            //Data
            std::fstream names_;
            std::fstream identifiers_;
            std::fstream genders_;
            std::fstream groups_;
        };

    } //namespace data_manager
} //namespace catalogue