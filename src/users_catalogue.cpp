/*#include "users_catalogue.hpp"

namespace catalogue {
    namespace database {

        const UserCatalogue::UserPtr& UserCatalogue::GetUserByIdentifier(domain::components::Identifier identifier) const noexcept {
            static const UserPtr DUMMY = nullptr;
            
            auto iter = identifier_to_user_.find(identifier);
            return iter == identifier_to_user_.end() ? DUMMY : users_[iter -> second];
        }

    } //namespace database
} //namespace catalogue*/