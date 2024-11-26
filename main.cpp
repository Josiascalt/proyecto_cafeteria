#include "domain.hpp"
#include "domain.cpp"
#include "encoder.hpp"
#include "encoder.cpp"
//#include "users_catalogue.hpp"
//#include "users_catalogue.cpp"
//#include "file_handler.hpp"
//#include "file_handler.cpp"
//#include "testing.hpp"

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

    //testing::domain::TestStudentStruct();
    //testing::user_catalogue::TestAddUser();
    //testing::user_catalogue::TestGetUsersByGroup();

    /*//Root Directory
    const auto ROOT_PATH = std::filesystem::current_path();
    const auto TEMP_DIRECTORY = catalogue::file_handler::CreatePathObject("MyOutput", ROOT_PATH);
    //Subdirectories
    const auto RECORD_DIRECTORY = catalogue::file_handler::CreatePathObject("Records", TEMP_DIRECTORY);
    const auto DATA_DIRECTORY = catalogue::file_handler::CreatePathObject("Data", TEMP_DIRECTORY);
    
    const auto METADATA_PATHS = catalogue::file_handler::MetadataPaths{}.SetQueue(DATA_DIRECTORY / "queue.mdat"_p);

    const auto DATA_PATHS = catalogue::file_handler::DataPaths{}.SetNameData({DATA_DIRECTORY / "names.dat"_p, DATA_DIRECTORY / "namessz.dat"_p})
                                                                .SetIdentifierData({DATA_DIRECTORY / "identifiers.dat"_p, DATA_DIRECTORY / "identifierssz.dat"_p})
                                                                .SetGenderData(DATA_DIRECTORY / "genders.dat"_p)
                                                                .SetGroupData(DATA_DIRECTORY / "groups.dat"_p);*/

    //catalogue::database::UserCatalogue catalogue;
    //catalogue::file_handler::DatabaseHandler database(catalogue, METADATA_PATHS, DATA_PATHS);

    //database.Deserialize();
    //auto item = catalogue.GetUserByIdentifier("LAN0109"s);
    //std::cout << (item ? item -> identifier : "none") << '\n';

    /*while (true) {
        std::string input;
        std::getline(std::cin, input);
        if (input == "ADD") {
            database.Serialize(catalogue::domain::compound_types::final_types::Student{}.SetName("Josias"s)
                                                                                        .SetGroup(catalogue::domain::components::Group::TAC::BILINGUAL_BUSINESS_DEPARTMENT)
                                                                                        .SetGender(catalogue::domain::components::Gender::MALE)
                                                                                        .SetIdentifier("JCA0109"s));
            database.Serialize(catalogue::domain::compound_types::final_types::Student{}.SetName("Liliia"s)
                                                                                        .SetGroup(catalogue::domain::components::Group::TAC::MUSIC_DEPARTMENT)
                                                                                        .SetGender(catalogue::domain::components::Gender::FEMALE)
                                                                                        .SetIdentifier("LIL0109"s));
            database.Serialize(catalogue::domain::compound_types::final_types::Student{}.SetName("Lancelot"s)
                                                                                        .SetGroup(catalogue::domain::components::Group::TAIS::NINTH_GRADE)
                                                                                        .SetGender(catalogue::domain::components::Gender::MALE)
                                                                                        .SetIdentifier("LAN0109"s));
            database.Serialize(catalogue::domain::compound_types::final_types::Student{}.SetName("Odette"s)
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

    auto str = "efeefe sqdqdVWF WGFDBTSG R GTGw3335"s;
    auto item = encoder::ascii::EncodeData(str.begin(), str.end());
    std::cout << item.Decode() << '\n';
    std::cout << "Success!"sv;
    
    return 0;
}