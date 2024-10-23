#include "domain.hpp"
#include "domain.cpp"
#include "users_catalogue.hpp"
#include "users_catalogue.cpp"
#include "file_handler.hpp"
#include "file_handler.cpp"
#include "testing.hpp"

#include <iostream>
#include <iomanip>
#include <string_view>
#include <utility>
#include <optional>

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
    
    const auto METADATA_PATHS = catalogue::file_handler::MetadataPaths{}.SetLayout("layout.mdat")
                                                                        .SetQueue("queue.mdat");

    const auto DATA_PATHS = catalogue::file_handler::DataPaths{}.SetNameData("names.dat"_p)
                                                                .SetIdentificatorData("identificators.dat"_p)
                                                                .SetGenderData("genders.dat"_p)
                                                                .SetGroupData("groups"_p);

    catalogue::file_handler::DatabaseHandler database(METADATA_PATHS, DATA_PATHS);
    
    std::cout << "Success!"sv;
    
    return 0;
}