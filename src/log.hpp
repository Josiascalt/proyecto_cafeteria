#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <utility>

namespace log {

    struct LoginData {
        std::string identifier;
        std::string password;


        LoginData& SetIdentifier(std::string value) {
            identifier = std::move(value);
            return *this;
        }

        LoginData& SetPassword(std::string value) {
            password = std::move(value);
            return *this;
        }
    };


    class Log {
    public:
        enum class Privileges : char {
            FULL_READ_AND_WRITE_ACCESS,
            FULL_READ_ACCESS,
            PARTIAL_READ_AND_WRITE_ACCESS,
            PARTIAL_READ_ACCESS,
            NO_ACCESS
        };

        Log();


    private:
        std::vector<LoginData> logins_;
        std::unordered_map<std::string_view, LoginData*> identifier_to_logindata_;
        std::unordered_map<std::string_view, Privileges> identifier_to_privileges_;
    };

} //namespace log