#pragma once

#include "domain.hpp"

#include <deque>
#include <unordered_map>
#include <memory>

namespace catalogue {
    namespace database {

        using namespace domain::type_naming;
        using namespace domain::components;

        class UserCatalogue {
        private:
            using Index = size_t;
        public:
            UserCatalogue();
            UserCatalogue(std::deque<UserPtr>&& users);
            
            bool HasUser(const UserPtr& user) const;
            void AddUser(UserPtr&& user);
            const UserPtr& GetUserByIdentifier(types::Identifier identifier) const;
            const std::deque<UserPtr>& GetUsers() const;
            
        private:
            std::deque<UserPtr> users_;
            std::unordered_map<types::Identifier, Index> identifier_to_user_;
        };
    } //namespace database
} //namespace catalogue