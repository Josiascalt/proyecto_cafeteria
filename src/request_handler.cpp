#include <utility>

#include "request_handler.hpp"

namespace catalogue {
    namespace request_handler {
        //struct RequestHandler member functions definition
        RequestHandler::RequestHandler(const backup::UserDataPaths& paths) 
        : user_data_(paths)
        , catalogue_(user_data_.Deserialize())
        {

        }

        bool RequestHandler::AddUser(UserPtr&& user) {
            if (catalogue_.HasUser(user)) {
                user_data_.Serialize(user.get());
                catalogue_.AddUser(std::move(user));
                return true;
            } 
            
            return false;
        }

        const UserPtr& RequestHandler::GetUserByIdentifier(domain::components::types::Identifier identifier) {
            return catalogue_.GetUserByIdentifier(identifier);
        }

        const std::deque<UserPtr>& RequestHandler::GetUsers() const {
            return catalogue_.GetUsers();
        }

    } //namespace request_handler
} //namespace catalogue