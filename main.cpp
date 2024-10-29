#include "domain.hpp"
#include "domain.cpp"
#include "users_catalogue.hpp"
#include "users_catalogue.cpp"
#include "file_handler.hpp"
#include "file_handler.cpp"
#include "testing.hpp"

#include <iostream>
#include <string_view>
#include <utility>

using namespace std::literals;

#define SIZEOF(X) \
        (std::cerr << #X << '\n' << \
        "size = "sv << sizeof(X) << '\t' << \
        "align = "sv << alignof(X) << '\n') 


int main() {
    using namespace catalogue::domain::literals;

    testing::domain::TestStudentStruct();
    testing::user_catalogue::TestAddUser();
    //testing::user_catalogue::TestGetUsersByGroup();

    //Root Directory
    const auto ROOT_PATH = std::filesystem::current_path();
    const auto TEMP_DIRECTORY = catalogue::file_handler::ValidatePath(ROOT_PATH / "MyOutput"_p);
    //Subdirectories
    const auto RECORD_DIRECTORY = catalogue::file_handler::ValidatePath(TEMP_DIRECTORY / "Records"_p);
    const auto DATA_DIRECTORY = catalogue::file_handler::ValidatePath(TEMP_DIRECTORY / "Data"_p);
    
    const auto METADATA_PATHS = catalogue::file_handler::MetadataPaths{}.SetQueue(DATA_DIRECTORY / "queue.mdat"_p);

    const auto DATA_PATHS = catalogue::file_handler::DataPaths{}.SetNameData(DATA_DIRECTORY / "names.dat"_p)
                                                                .SetIdentifierData(DATA_DIRECTORY / "identifiers.dat"_p)
                                                                .SetGenderData(DATA_DIRECTORY / "genders.dat"_p)
                                                                .SetGroupData(DATA_DIRECTORY / "groups.dat"_p);

    catalogue::file_handler::DatabaseHandler database(METADATA_PATHS, DATA_PATHS);

    while (true) {
        std::string input;
        std::getline(std::cin, input);
        if (input == "ADD") {
            database.Serialize(catalogue::domain::compound_types::final_types::Student{}.SetName("Josias"s));
        } else if (input.empty() || input == "STOP") {
            std::cout << "Thanks! Bye!\n";
            break;
        } else {
            std::cout << "Student\n";
        }
    }

    std::cout << "Success!"sv;
    
    return 0;
}