#include <utility>

#include "data_manager.hpp"

namespace catalogue {
    namespace data_manager {

        using namespace domain::type_naming;

        //struct UserDataPaths member functions definition
        UserDataPaths& UserDataPaths::SetMetadataPaths(fs::path queue_path) {
            metadata.queue = std::move(queue_path);
            return *this;
        }

        UserDataPaths& UserDataPaths::SetNamesPath(fs::path names_path) {
            names = std::move(names_path);
            return *this;
        }

        UserDataPaths& UserDataPaths::SetIdentifiersPath(fs::path identifiers_path) {
            identifiers = std::move(identifiers_path);
            return *this;
        }

        UserDataPaths& UserDataPaths::SetGendersPath(fs::path genders_path) {
            genders = std::move(genders_path);
            return *this;
        }

        UserDataPaths& UserDataPaths::SetGroupsPath(fs::path groups_path) {
            groups = std::move(groups_path);
            return *this;
        }

        //struct UserDataPaths member functions definition
        UserDataHandler::UserDataHandler(const UserDataPaths& user_data) 
        : user_queue_(user_data.metadata.queue)
        , names_(user_data.names)
        , identifiers_(user_data.identifiers)
        , genders_(user_data.genders)
        , groups_(user_data.groups) 
        {

        }
        
        std::deque<UserPtr> UserDataHandler::Deserialize() {
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

        UserPtr UserDataHandler::DeserializeMetadata() {
            domain::compound_types::UserType user_type;
            
            user_queue_.Read(&user_type);

            return domain::compound_types::MakeUser(user_type);
        }


    } //namespace data_manager
} //namespace catalogue