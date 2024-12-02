#include "src/domain.cpp"
#include "src/data_manager.hpp"
#include "src/utilities/encoder.cpp"
#include <iostream>
#include <string_view>
#include <utility>
//#include <windows.h>

using namespace std::literals;

#define SIZEOF(X) \
        (std::cerr << #X << '\n' << \
        "size = "sv << sizeof(X) << '\t' << \
        "align = "sv << alignof(X) << '\n') 




int main() {
    using namespace catalogue::domain::literals;

    //testing::domain::TestStudentStruct();
    //testing::user_catalogue::TestAddUser();
    //testing::user_catalogue::TestGetUsersByGroup();

    //Root Directory
    const auto ROOT_DIRECTORY = std::filesystem::current_path();
    const auto TEMP_DIRECTORY = file_handler::CreatePathObject("MyOutput", ROOT_DIRECTORY);
    //Subdirectories
    const auto RECORD_DIRECTORY = file_handler::CreatePathObject("Records", TEMP_DIRECTORY);
    const auto DATA_DIRECTORY = file_handler::CreatePathObject("Data", TEMP_DIRECTORY);

    const auto USER_DATA_PATHS = catalogue::data_manager::UserDataPaths{}
                                .SetMetadataPaths(file_handler::CreatePathObject("queue.mdat", DATA_DIRECTORY))
                                .SetIdentifiersPath(file_handler::CreatePathObject("identifiers.dat", DATA_DIRECTORY))
                                .SetNamesPath(file_handler::CreatePathObject("names.dat", DATA_DIRECTORY))
                                .SetGendersPath(file_handler::CreatePathObject("genders.dat", DATA_DIRECTORY))
                                .SetGroupsPath(file_handler::CreatePathObject("groups.dat", DATA_DIRECTORY));

    //catalogue::database::UserCatalogue catalogue;
    //catalogue::catalogue::data_manager::DatabaseHandler database(catalogue, METADATA_PATHS, DATA_PATHS);

    //database.DeserializeUser();
    //auto item = catalogue.GetUserByIdentifier("LAN0109"s);
    //std::cout << (item ? item -> identifier : "none") << '\n';

    /*while (true) {
        std::string input;
        std::getline(std::cin, input);
        if (input == "ADD") {
            database.SerializeUser(catalogue::domain::compound_types::final_types::Student{}.SetName("Josias"s)
                                                                                        .SetGroup(catalogue::domain::components::Group::TAC::BILINGUAL_BUSINESS_DEPARTMENT)
                                                                                        .SetGender(catalogue::domain::components::Gender::MALE)
                                                                                        .SetIdentifier("JCA0109"s));
            database.SerializeUser(catalogue::domain::compound_types::final_types::Student{}.SetName("Liliia"s)
                                                                                        .SetGroup(catalogue::domain::components::Group::TAC::MUSIC_DEPARTMENT)
                                                                                        .SetGender(catalogue::domain::components::Gender::FEMALE)
                                                                                        .SetIdentifier("LIL0109"s));
            database.SerializeUser(catalogue::domain::compound_types::final_types::Student{}.SetName("Lancelot"s)
                                                                                        .SetGroup(catalogue::domain::components::Group::TAIS::NINTH_GRADE)
                                                                                        .SetGender(catalogue::domain::components::Gender::MALE)
                                                                                        .SetIdentifier("LAN0109"s));
            database.SerializeUser(catalogue::domain::compound_types::final_types::Student{}.SetName("Odette"s)
                                                                                        .SetGroup(catalogue::domain::components::Group::TAA::SECOND_GRADE)
                                                                                        .SetGender(catalogue::domain::components::Gender::FEMALE)
                                                                                        .SetIdentifier("ODD0109"s));
        } else if (input.empty() || input == "STOP") {
            std::cout << "Thanks! Bye!\n";
            break;
        } else {
            std::cout << "Student\n";
        }
    }*/

    catalogue::data_manager::UserDataHandler handler(USER_DATA_PATHS);
    //auto student = catalogue::domain::compound_types::Student{}.SetName("Josias Cabrera Altamirano es un compadre bien chindorris."s);
    //handler.SerializeUser(&student);
    //Sleep(10'000);

    auto user = handler.DeserializeUser();
    
    auto student = dynamic_cast<catalogue::domain::compound_types::Student*>(user.get());

    std::cout << student -> GetName() << '\n';

    std::cout << "Success!"sv;
    
    return 0;
}