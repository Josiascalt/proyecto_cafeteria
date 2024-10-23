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

        namespace components {
            //class Group member functions definition
            bool Group::IsTAC() const {
                return std::holds_alternative<TAC>(group_);
            }

            bool Group::IsTAIS() const {
                return std::holds_alternative<TAIS>(group_);
            }

            bool Group::IsTAA() const {
                return std::holds_alternative<TAA>(group_);
            }

            Group::TAC components::Group::GetAsTAC() const {
                return std::get<TAC>(group_);
            }

            Group::TAIS Group::GetAsTAIS() const {
                return std::get<TAIS>(group_);
            }

            Group::TAA Group::GetAsTAA() const {
                return std::get<TAA>(group_);
            }

            bool Group::operator==(const Group& other) const {
                return group_ == other.group_;
            }

            bool Group::operator!=(const Group& other) const {
                return !(*this == other);
            }

            //Class Components member functions definition
            Components& Components::SetHasName (bool value) {
                has_name = value;
                return *this;
            }

            Components& Components::SetHasIdentifier (bool value) {
                has_identifier = value;
                return *this;
            }

            Components& Components::SetHasGender(bool value) {
                has_gender = value;
                return *this;
            }

            Components& Components::SetHasGroup(bool value) {
                has_group = value;
                return *this;
            }
        } //namespace components
        
        namespace compound_types {
            namespace final_types {
                namespace detail {
                    /*
                        The function GetComponents depends completely on the structure of the
                        final classes or structures inside Compound Types, so in order to keep the
                        program working efficiently, all the final types should be included in the variable
                        TYPE_TO_COMPONENTS with its components
                        | | | | | | | | | |
                        v v v v v v v v v v
                    */
                    static components::Components GetComponents(FinalTypes::Types type) {
                        const std::unordered_map<FinalTypes::Types, components::Components> TYPE_TO_COMPONENTS = 
                        {
                            {FinalTypes::Types::STUDENT, components::Components{}.SetHasName(true)
                                                            .SetHasIdentifier(true)
                                                            .SetHasGender(true)
                                                            .SetHasGroup(true)
                            }
                        };
                        
                        return TYPE_TO_COMPONENTS.at(type);
                    }
                } ////namespace detail
                components::Components FinalTypes::GetComponents() const {
                    return detail::GetComponents(type_);
                }

                FinalTypes::Types FinalTypes::GetType() const {
                    return type_;
                }
            } //namespace final_types
        } //namespace compound_types
    } // namespace domain
} // namespace catalogue


