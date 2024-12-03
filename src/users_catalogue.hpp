#pragma once

#include "domain.hpp"

#include <string>
#include <string_view>
#include <deque>
#include <unordered_map>
#include <memory>
#include <utility>

namespace catalogue {
    namespace database {
        class UserCatalogue {
        public:
            template<typename UserInterface>
            void AddUser(UserInterface user) {
                users_.push_back(std::make_shared<UserInterface>(std::move(user)));

                Index new_user_index = users_.size() - 1;

                identifier_to_user_[users_[new_user_index] -> identifier] = new_user_index;
            }
            
            const UserPtr& GetUserByIdentifier(domain::components::Identifier identifier) const noexcept;

        private:
            Users users_;
            std::unordered_map<std::string_view, Index> identifier_to_user_;
        };
    } //namespace database
} //namespace catalogue