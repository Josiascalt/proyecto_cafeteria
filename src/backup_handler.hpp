#pragma once

#include <deque>
#include <unordered_map>
#include <utility>

#include "domain.hpp"
#include "file_handler.hpp"

namespace catalogue {
    namespace backup {

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

            UserDataPaths& SetMetadataPaths(fs::path queue_path);
            UserDataPaths& SetNamesPath(fs::path names_path);
            UserDataPaths& SetIdentifiersPath(fs::path identifiers_path);
            UserDataPaths& SetGendersPath(fs::path genders_path);
            UserDataPaths& SetGroupsPath(fs::path groups_path);
        };

        class UserDataBackup {
        public:
            UserDataBackup(const UserDataPaths& user_data);

            template <typename T>
            inline void Serialize(T* user) {
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
            
            std::deque<UserPtr> Deserialize();

        private:
            template <typename T>
            inline void SerializeMetadata(T* user) {
                domain::compound_types::UserType user_type = user -> GetUserType();
                user_queue_.Write(&user_type);
            }

            UserPtr DeserializeMetadata();

        private:
            //Metadata
            file_handler::BinaryFile user_queue_;
            //Data
            file_handler::BinaryFile names_;
            file_handler::BinaryFile identifiers_;
            file_handler::BinaryFile genders_;
            file_handler::BinaryFile groups_;
        };

    } //namespace backup
} //namespace catalogue