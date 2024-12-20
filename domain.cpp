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

            Group::TAC Group::GetAsTAC() const {
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

            //Class Composition member functions definition
            Composition& Composition::SetHasName (bool value) {
                has_name = value;
                return *this;
            }

            Composition& Composition::SetHasIdentifier (bool value) {
                has_identifier = value;
                return *this;
            }

            Composition& Composition::SetHasGender(bool value) {
                has_gender = value;
                return *this;
            }

            Composition& Composition::SetHasGroup(bool value) {
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
                    static components::Composition GetComponents(FinalTypes::TypeNames type) {
                        const std::unordered_map<FinalTypes::TypeNames, components::Composition> TYPE_TO_COMPONENTS = 
                        {
                            {FinalTypes::TypeNames::STUDENT, components::Composition{}.SetHasName(true)
                                                            .SetHasIdentifier(true)
                                                            .SetHasGender(true)
                                                            .SetHasGroup(true)
                            }
                        };
                        
                        return TYPE_TO_COMPONENTS.at(type);
                    }
                } ////namespace detail
                //Class FinalTypes member functions definition
                FinalTypes::FinalTypes(TypeNames name)
                : typename_(name) {
                    
                }

                FinalTypes::TypeNames FinalTypes::GetTypeName() const {
                    return typename_;
                }

                components::Composition FinalTypes::GetComponents() const {
                    return detail::GetComponents(typename_);
                }

                //Class Student member functions definition
                Student::Student() 
                : FinalTypes(TypeNames::STUDENT)
                , PersonPathProps<Student>()
                , UserPathProps<Student>()
                {

                }

            } //namespace final_types
        } //namespace compound_types
    } // namespace domain
} // namespace catalogue


