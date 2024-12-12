#include <utility>
#include <deque>

#include "user_catalogue.hpp"

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

        bool UserCatalogue::HasUser(const UserPtr& user) const {
            using namespace domain::components;
            if (user) {
                if (auto identifier = dynamic_cast<const Identifiable*>(user.get());
                    identifier && identifier_to_user_.count(identifier -> GetIdentifier())) {
                    return false;
                }

                return true;
            }

            return false;
        }

        void UserCatalogue::AddUser(UserPtr&& user) {
            if (!user) {
                return;
            }

            users_.push_back(std::move(user));
            
            if (auto identifier = dynamic_cast<Identifiable*>(users_.back().get())) {
                identifier_to_user_[identifier -> GetIdentifier()] = users_.size() - 1;
            }
            
        }

        const UserPtr& UserCatalogue::GetUserByIdentifier(types::Identifier identifier) const {
            static const UserPtr dummy_user;
            auto result = identifier_to_user_.find(identifier);
            return result == identifier_to_user_.end() ? dummy_user : users_[result -> second];
        }

        const std::deque<UserPtr>& UserCatalogue::GetUsers() const {
            return users_;
        }

        

    } //namespace database
} //namespace catalogue