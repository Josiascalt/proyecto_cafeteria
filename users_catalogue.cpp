#include "users_catalogue.hpp"

namespace catalogue {
    namespace database {

        const domain::User* UserCatalogue::GetUserByIdentifier(Identifier identifier) const noexcept {
            auto iter = identifier_to_user_.find(identifier);
            return iter == identifier_to_user_.end() ? DUMMY : users_[iter -> second];
        }

    } //namespace database
} //namespace catalogue