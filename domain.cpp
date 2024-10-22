#include "domain.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <unordered_map>
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

        namespace detail {
            /*
                The function GetComponents depends completely on the structure of the
                final classes or structures inside Compound Types, so in order to keep the
                program working efficiently, all the final types should be included in the variable
                TYPE_TO_COMPONENTS with its components
                | | | | | | | | | |
                v v v v v v v v v v
            */
            static Components GetComponents(CompoundTypes::FinalTypes type) {
                const std::unordered_map<CompoundTypes::FinalTypes, Components> TYPE_TO_COMPONENTS = 
                {
                    {CompoundTypes::FinalTypes::UNKNOWN, Components{}},
                    {CompoundTypes::FinalTypes::STUDENT, Components{}.SetHasName(true)
                                                    .SetHasIdentifier(true)
                                                    .SetHasGender(true)
                                                    .SetHasGroup(true)
                    }
                };
                
                return TYPE_TO_COMPONENTS.at(type);
            }
        } ////namespace detail

        //class Components member functions definition
        Components CompoundTypes::GetComponents() const {
            return detail::GetComponents(type_);
        }

        CompoundTypes::FinalTypes CompoundTypes::GetType() const {
            return type_;
        }

    } // namespace domain
} // namespace catalogue


