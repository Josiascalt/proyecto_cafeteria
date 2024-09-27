#include "domain.hpp"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <deque>
#include <iostream>

namespace catalogue {
    namespace file_handler {
        
        using namespace domain::type_naming;
        using namespace domain::literals;
        
        //template <typename Type>
        class DatabaseHandler {
        public:
            DatabaseHandler(const std::filesystem::path& path)
            : database_(std::fstream{path, std::ios::out | std::ios::in | std::ios::binary | std::ios::app})
            {
                std::cout << (database_ ? "true" : "false") << '\n';
            }

            //void Read(Type& target);
            //void Write(const Type& );
            

            //~DatabaseHandler();
        private:
            std::fstream database_;
        };

        struct Entry {
            std::string time;
            UserPtr user;
        };

        class RecordHandler {
        public:
            void AddEntry();
        private:
            std::unordered_map<domain::Group, std::deque<const Entry>> records_;
        };
    } //namespace file_handler
} //namespace catalogue