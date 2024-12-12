#pragma once

#include "domain.hpp"
#include "user_catalogue.hpp"
#include "backup_handler.hpp"

namespace catalogue {
    namespace request_handler {
        
        using namespace domain::type_naming;

        class RequestHandler {
        public:
            RequestHandler(const backup::UserDataPaths& paths);
            bool AddUser(UserPtr&& user);
            const UserPtr& GetUserByIdentifier(domain::components::types::Identifier identifier);
            const std::deque<UserPtr>& GetUsers() const;
        private:
            backup::UserDataBackup user_data_;
            database::UserCatalogue catalogue_;
        };
    } //namespace request_handler
} //namespace catalogue