#include <iostream>
#include <string_view>
#include <utility>

#include "src/domain.cpp"
#include "src/data_manager.cpp"
#include "src/utilities/encoder.cpp"
#include "src/user_catalogue.cpp"
//#include <windows.h>

using namespace std::literals;

#define SIZEOF(X) \
        (std::cerr << #X << '\n' << \
        "size = "sv << sizeof(X) << '\t' << \
        "align = "sv << alignof(X) << '\n') 




int main() {

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

    
    catalogue::data_manager::UserDataHandler handler(USER_DATA_PATHS);
    catalogue::domain::compound_types::Student student;
    student.SetName("Josias Cabrera"s);
    student.SetGroup(catalogue::domain::components::types::Group::TAC::BILINGUAL_BUSINESS_DEPARTMENT);
    student.SetGender(catalogue::domain::components::types::Gender::MALE);
    student.SetIdentifier("JCA0109"s);
    handler.Serialize(&student);
    //Sleep(10'000);

    auto users = handler.Deserialize();
    for (const auto& user : users) {
        if (auto s = dynamic_cast<catalogue::domain::compound_types::Student*>(user.get()))
        std::cout << s -> GetIdentifier() << '\n';
    }
    catalogue::database::UserCatalogue catalogue(std::move(users));
    std::hash<std::string> hasher;

    std::string input;
    while (input != "exit"s) {
        std::getline(std::cin, input);
        
        const auto& result = catalogue.GetUserByIdentifier(hasher(input));
        std::cout << (result ? "Please enter!" : "Get out!") << '\n';
    }
    

    
    std::cout << "Success!"sv;
    
    return 0;
}