#pragma once

#include "domain.hpp"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <deque>
#include <iostream>

namespace catalogue {
    namespace file_handler {
        
        using namespace domain::components;
        using namespace domain::literals;

        
        
        //template <typename Type>
        class DatabaseHandler {
        public:
            DatabaseHandler(const std::filesystem::path& path);

            bool IsEmpty();

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
            bool is_empty_;
            std::fstream database_;
        };

        struct Entry {
            std::string time;
            domain::User* user;
        };

        /*class RecordHandler {
        public:
            void AddEntry();
        private:
            std::unordered_map<domain::Group, std::deque<const Entry>> records_;
        };*/
    } //namespace file_handler
} //namespace catalogue