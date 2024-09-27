#include "domain.hpp"
#include "users_catalogue.hpp"
#include "domain.cpp"
#include "users_catalogue.cpp"
#include "path_handler.hpp"
#include "file_handler.hpp"
#include "testing.hpp"

#include <iostream>
#include <iomanip>
#include <string_view>

using namespace std::literals;

#define SIZEOF(X) \
        (std::cerr << #X << '\n' << \
        "size = "sv << sizeof(X) << '\t' << \
        "align = "sv << alignof(X) << '\n') 



int main() {
    using namespace catalogue::domain::type_naming;
    using namespace catalogue::domain::literals;

    testing::domain::TestStudentStruct();
    testing::user_catalogue::TestAddUser();
    //testing::user_catalogue::TestGetUsersByGroup();

    const auto ROOT_PATH = std::filesystem::current_path() /  "Documents"_p / "Repositories"_p / "output"_p;
    //Directories
    const auto RECORD_DIRECTORY = path_handler::ValidateDirectoryPath(ROOT_PATH / "Records"_p);
    const auto DATA_DIRECTORY = path_handler::ValidateDirectoryPath(ROOT_PATH / "Data"_p);
    //Files
    const auto SOURCE_FILE = DATA_DIRECTORY / "data.dat"_p;

    catalogue::file_handler::DatabaseHandler database(SOURCE_FILE);
    //std::cout << std::boolalpha << database.IsEmpty() << '\n';
    std::cout << "Success!"sv;
    
    return 0;
}