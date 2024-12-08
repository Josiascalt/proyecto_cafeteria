#include <utility>
#include <deque>

#include "user_catalogue.hpp"
#include "domain.hpp"

namespace catalogue {
    namespace database {

        using namespace domain::type_naming;
        using namespace domain::components;

        //UserCatalogue class member functions definition
        UserCatalogue::UserCatalogue() = default;
        UserCatalogue::UserCatalogue(std::deque<UserPtr>&& users) 
        {
            for (auto&& user : users) {
                this -> AddUser(std::move(user));
            }
        }

        void UserCatalogue::AddUser(UserPtr&& user) {
            if (!user) {
                return;
            }

            users_.push_back(std::move(user));
            identifier_to_user_[users_.back() -> GetIdentifier()] = users_.size() - 1;
        }

        const UserPtr& UserCatalogue::GetUserByIdentifier(types::Identifier identifier) const {
            static const UserPtr dummy_user;
            auto result = identifier_to_user_.find(identifier);
            return result == identifier_to_user_.end() ? dummy_user : users_[result -> second];
        }

    } //namespace database
} //namespace catalogue