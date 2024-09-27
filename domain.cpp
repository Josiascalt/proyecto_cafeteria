#include "domain.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <memory>
#include <variant>
#include <filesystem>

namespace catalogue {
    namespace domain {
        namespace literals {
            std::filesystem::path operator""_p(const char* pathname, size_t size) {
                return std::filesystem::path(pathname, pathname + size);
            }
        } //namespace literals
        
        using namespace type_naming;

        //class Group function member definition
        bool Group::IsInitialized() const {
            return !std::holds_alternative<std::monostate>(*this);
        }

        bool Group::IsTAC() const {
            return std::holds_alternative<grouping::TAC>(*this);
        }

        bool Group::IsTAIS() const {
            return std::holds_alternative<grouping::TAIS>(*this);
        }

        bool Group::IsTAA() const {
            return std::holds_alternative<grouping::TAA>(*this);
        }

        grouping::TAC Group::GetAsTAC() const {
            return std::get<grouping::TAC>(*this);
        }

        grouping::TAIS Group::GetAsTAIS() const {
            return std::get<grouping::TAIS>(*this);
        }

        grouping::TAA Group::GetAsTAA() const {
            return std::get<grouping::TAA>(*this);
        }

        //class Person function member definition
        const Name& Person::GetName() const {
            return name_;
        }
        
        const Gender Person::GetGender() const {
            return gender_;
        }
        
        //class User function member definition
        const Group& User::GetGroup() const {
            return group_;
        }
        
        const Identifier& User::GetIdentifier() const {
            return identifier_;
        }

        
         
    } // namespace domain
} // namespace catalogue


