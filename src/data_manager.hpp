#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <utility>
#include <vector>
//#include <memory>
//#include <optional>

#include "domain.hpp"
#include "file_handler.hpp"

namespace catalogue {
    namespace data_manager {
        namespace exceptions {
            struct InvalidUserPtr {};
        }

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

        class UserDataHandler {
        public:
            using UserPtr = std::unique_ptr<domain::compound_types::User>;
        public:
            inline UserDataHandler(const UserDataPaths& user_data) 
            : user_queue_(file_handler::CreateBinaryFstream(user_data.metadata.queue))
            , names_(file_handler::CreateBinaryFstream(user_data.names))
            , identifiers_(file_handler::CreateBinaryFstream(user_data.identifiers))
            , genders_(file_handler::CreateBinaryFstream(user_data.genders))
            , groups_(file_handler::CreateBinaryFstream(user_data.groups))
            {

            }

            template <typename T>
            void Serialize(T* user) {
                if (!user) {
                    throw InvalidUserPtr{};
                }
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
            
            inline std::vector<UserPtr> Deserialize() {
                std::vector<UserPtr> result;
                auto total_users = file_handler::CalcFileSize(user_queue_);
                result.reserve(total_users);

                for (size_t index = 0; index < total_users; index++) {
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

                    throw exceptions::InvalidUserPtr{};
                }
                
                return result;
            }

        private:
            template <typename T>
            inline void SerializeMetadata(T* user) {
                domain::compound_types::UserType user_type = user -> GetUserType();
                file_handler::WriteInBinary(user_queue_, &user_type);
            }

            inline UserPtr DeserializeMetadata() {
                domain::compound_types::UserType user_type;
                file_handler::ReadInBinary(user_queue_, &user_type);

                return domain::compound_types::MakeUser(user_type);
            }

        private:
            //Metadata
            std::fstream user_queue_;
            //Data
            std::fstream names_;
            std::fstream identifiers_;
            std::fstream genders_;
            std::fstream groups_;
        };

    } //namespace data_manager
} //namespace catalogue