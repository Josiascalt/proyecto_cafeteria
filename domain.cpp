#include "domain.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <filesystem>

#include <iostream>

namespace catalogue {
    namespace domain {
        namespace literals {
            std::filesystem::path operator""_p(const char* pathname, size_t size) {
                return std::filesystem::path(pathname, pathname + size);
            }
        } //namespace literals

        //class Components member functions definition
        Components& Components::SetHasName (bool value) {
            has_name_ = value;
            return *this;
        }

        Components& Components::SetHasIdentifier (bool value) {
            has_identifier_ = value;
            return *this;
        }

        Components& Components::SetHasGender(bool value) {
            has_gender_ = value;
            return *this;
        }

        Components& Components::SetHasGroup(bool value) {
            has_group_ = value;
            return *this;
        }

        bool Components::HasName() const {
            return has_name_;
        }

        bool Components::HasIdentifier() const {
            return has_identifier_;
        }

        bool Components::HasGender() const {
            return has_gender_;
        }

        bool Components::HasGroup() const {
            return has_group_;
        }

        //class Components::Group member functions definition
        bool Components::Group::IsInitialized() const {
            return !std::holds_alternative<std::monostate>(*this);
        }

        bool Components::Group::IsTAC() const {
            return std::holds_alternative<groups::TAC>(*this);
        }

        bool Components::Group::IsTAIS() const {
            return std::holds_alternative<groups::TAIS>(*this);
        }

        bool Components::Group::IsTAA() const {
            return std::holds_alternative<groups::TAA>(*this);
        }

        groups::TAC Components::Group::GetAsTAC() const {
            return std::get<groups::TAC>(*this);
        }

        groups::TAIS Components::Group::GetAsTAIS() const {
            return std::get<groups::TAIS>(*this);
        }

        groups::TAA Components::Group::GetAsTAA() const {
            return std::get<groups::TAA>(*this);
        }

        //class CompoundTypes member functions definition
        CompoundTypes::CompoundTypes(FinalTypes type) 
        : type_(type) {
            using namespace std::literals;
            switch (type_) {
                case FinalTypes::STUDENT:
                    components_ = Components{}.SetHasName(true)
                                              .SetHasIdentifier(true)
                                              .SetHasGender(true)
                                              .SetHasGroup(true);
                    break;
                default:
                    std::cerr << "UNKNOWN TYPE: ERROR THROWN WHILE CREATING COMPOUND TYPES OBJECT\n"sv;
                    break;
            }
        }

        CompoundTypes::FinalTypes CompoundTypes::GetType() const {
            return type_;
        }

        const Components& CompoundTypes::GetComponents() const {
            return components_;
        }

    } // namespace domain
} // namespace catalogue


