#pragma once

#include "domain.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <utility>

namespace catalogue {
    namespace file_handler {
        using namespace domain::literals;

        namespace fs = std::filesystem;

        static fs::path ValidateDirectoryPath(fs::path&& p);

        /*
            The struct DataPaths depends on the datatypes of the struct Components 
            in the namespace domain. Every path in the struct DataPaths links to file 
            that storages a datatype from struct Components.
        */

        struct DataPaths {
            fs::path name_data;
            fs::path identificator_data;
            fs::path gender_data;
            fs::path group_data;

            DataPaths& SetNameData(fs::path data) {
                name_data = std::move(data);
                return *this;
            }

            DataPaths& SetIdentificatorData(fs::path data) {
                identificator_data = std::move(data);
                return *this;
            }

            DataPaths& SetGenderData(fs::path data) {
                gender_data = std::move(data);
                return *this;
            }

            DataPaths& SetGroupData(fs::path data) {
                group_data = std::move(data);
                return *this;
            }
        };
        
        //template <typename Type>
        class DatabaseHandler {
        public:
            DatabaseHandler(const DataPaths& paths);

            /*template <typename Type>
            void Read(Type& target) {
                if (!this -> IsEmpty()) {
                    
                }
            }*/

            /*template <typename Type>
            void Write(Type* ) {
                if constexpr (Type == domain::Person)
            }*/
            

            //~DatabaseHandler();
        private:
            std::fstream data_stream_;
            DataPaths databases_;
            
        };

        struct Entry {
            std::string time;
            domain::compound_types::User* user;
        };

        /*class RecordHandler {
        public:
            void AddEntry();
        private:
            std::unordered_map<domain::Group, std::deque<const Entry>> records_;
        };*/
    } //namespace file_handler
}//namespace catalogue