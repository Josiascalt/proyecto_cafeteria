#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <utility>
#include <deque>
//#include <memory>
//#include <optional>

#include <iostream>

#include "domain.hpp"
#include "file_handler.cpp"

namespace catalogue {
    namespace data_manager {

        using namespace domain::type_naming;

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
            inline UserDataHandler(const UserDataPaths& user_data) 
            : user_queue_(user_data.metadata.queue)
            , names_(user_data.names)
            , identifiers_(user_data.identifiers)
            , genders_(user_data.genders)
            , groups_(user_data.groups)
            {

            }

            template <typename T>
            void Serialize(T* user) {
                if (!user) {
                    throw exceptions::InvalidUserPtr{};
                }
                //metadata
                SerializeMetadata(user);
                //data
                if (auto identifier = dynamic_cast<domain::components::Identifiable*>(user)) {
                    identifiers_.Write(&identifier -> value);
                }
                
                if (auto name = dynamic_cast<domain::components::Nameable*>(user)) {
                    names_.Write(&name -> value);
                }

                if (auto gender = dynamic_cast<domain::components::Genderable*>(user)) {
                    genders_.Write(&gender -> value);
                }

                if (auto group = dynamic_cast<domain::components::Groupable*>(user)) {
                    groups_.Write(&group -> value);
                }
            }
            
            inline std::deque<UserPtr> Deserialize() {
                std::deque<UserPtr> result;
                auto total_users = user_queue_.GetSize();

                for (Size index = 0; index < total_users; index++) {
                    auto user = DeserializeMetadata();
                    if (user) {
                    
                        if (auto identifier = dynamic_cast<domain::components::Identifiable*>(user.get())) {
                            identifiers_.Read(&identifier -> value);
                        }
                        
                        if (auto name = dynamic_cast<domain::components::Nameable*>(user.get())) {
                            names_.Read(&name -> value);
                        }

                        if (auto gender = dynamic_cast<domain::components::Genderable*>(user.get())) {
                            genders_.Read(&gender -> value);
                        }

                        if (auto group = dynamic_cast<domain::components::Groupable*>(user.get())) {
                            groups_.Read(&group -> value);
                        }

                        result.push_back(std::move(user));
                    } else {
                        throw exceptions::InvalidUserPtr{};
                    }
                }
                
                return result;
            }

        private:
            template <typename T>
            inline void SerializeMetadata(T* user) {
                domain::compound_types::UserType user_type = user -> GetUserType();
                user_queue_.Write(&user_type);
            }

            inline UserPtr DeserializeMetadata() {
                domain::compound_types::UserType user_type;

                user_queue_.Read(&user_type);

                return domain::compound_types::MakeUser(user_type);
            }

        private:
            //Metadata
            file_handler::BinaryFile user_queue_;
            //Data
            file_handler::BinaryFile names_;
            file_handler::BinaryFile identifiers_;
            file_handler::BinaryFile genders_;
            file_handler::BinaryFile groups_;
        };

    } //namespace data_manager
} //namespace catalogue