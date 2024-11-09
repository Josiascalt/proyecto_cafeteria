#pragma once

#include <string>
#include <string_view>
#include <list>
#include <unordered_map>
#include <utility>
#include <optional>

namespace log {
    namespace exceptions {
        struct AppendingLoginError {};
    } // namespace exceptions

    struct Login {
        std::string identifier;
        std::string password;


        Login& SetIdentifier(std::string value) {
            identifier = std::move(value);
            return *this;
        }

        Login& SetPassword(std::string value) {
            password = std::move(value);
            return *this;
        }

        bool operator==(const Login& other) const {
            this -> identifier == other.identifier;
            this -> password == other.password;
        }
    };

    static inline bool operator!=(const Login& lhs, const Login& rhs) {
        return !(lhs == rhs);
    }

    class Log {
    public:
        enum class Privileges : char {
            FULL_READ_AND_WRITE_ACCESS,
            FULL_READ_ACCESS,
            PARTIAL_READ_AND_WRITE_ACCESS,
            PARTIAL_READ_ACCESS,
            NO_ACCESS
        };

        struct LoginData {
            Login* login;
            Privileges privileges;
        };

    public:
        Log() = default;

        void AddLogin(Login login, Privileges privileges = Privileges::NO_ACCESS) {
            logins_.push_back(std::move(login)); 
            auto& last_added_elem = logins_.back();
            identifier_to_logindata_[last_added_elem.identifier] = {&last_added_elem, privileges};
        }

        bool MatchLogin();

    private:
        std::list<Login> logins_;
        std::unordered_map<std::string_view, LoginData> identifier_to_logindata_;
    };

} //namespace log