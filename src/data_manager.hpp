#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <utility>
#include <deque>
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
            using UserPtr = std::unique_ptr<domain::compound_types::User>;
        public:
            inline UserDataHandler(const UserDataPaths& user_data) 
            : queue_(user_data.metadata.queue, std::ios::in | std::ios::out | std::ios::binary | std::ios::app)
            , names_(user_data.names, std::ios::in | std::ios::out | std::ios::binary | std::ios::app)
            , identifiers_(user_data.identifiers, std::ios::in | std::ios::out | std::ios::binary | std::ios::app)
            , genders_(user_data.genders, std::ios::in | std::ios::out | std::ios::binary | std::ios::app)
            , groups_(user_data.groups, std::ios::in | std::ios::out | std::ios::binary | std::ios::app)
            {

            }

            template <typename T>
            void Serialize(T* user) {
                //metadata
                SerializeMetadata(user);
                //data
                if (auto identifier = dynamic_cast<domain::components::Identifiable*>(user)) {
                    file_handler::WriteInBinary(identifiers_, &identifier -> value);
                }
                
                if (auto name = dynamic_cast<domain::components::Nameable*>(user)) {
                    file_handler::WriteInBinary(names_, &name -> value);
                }

                if (auto gender = dynamic_cast<domain::components::Genderable*>(user)) {
                    file_handler::WriteInBinary(genders_, &gender -> value);
                }

                if (auto group = dynamic_cast<domain::components::Groupable*>(user)) {
                    file_handler::WriteInBinary(groups_, &group -> value);
                }
            }
            
            inline std::deque<UserPtr> Deserialize() {
                std::deque<UserPtr> result;
                for (size_t index = 0; index < file_handler::CalcFileSize(queue_); index++) {
                    if (auto user = DeserializeMetadata()) {
                    
                        if (auto identifier = dynamic_cast<domain::components::Identifiable*>(user.get())) {
                            file_handler::ReadInBinary(identifiers_, &identifier -> value);
                        }
                        
                        if (auto name = dynamic_cast<domain::components::Nameable*>(user.get())) {
                            file_handler::ReadInBinary(names_, &name -> value);
                        }

                        if (auto gender = dynamic_cast<domain::components::Genderable*>(user.get())) {
                            file_handler::ReadInBinary(genders_, &gender -> value);
                        }

                        if (auto group = dynamic_cast<domain::components::Groupable*>(user.get())) {
                            file_handler::ReadInBinary(groups_, &group -> value);
                        }

                        result.push_back(std::move(user));
                        continue;
                    }
                    break;
                }
                
                return result;
            }

        private:
            template <typename T>
            inline void SerializeMetadata(T* user) {
                domain::compound_types::UserType user_type = user -> GetUserType();
                file_handler::WriteInBinary(queue_, &user_type);
            }

            inline UserPtr DeserializeMetadata() {
                domain::compound_types::UserType user_type;
                file_handler::ReadInBinary(queue_, &user_type);

                return domain::compound_types::CreateUser(user_type);
            }

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