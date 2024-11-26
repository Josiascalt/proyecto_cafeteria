#pragma once

#include "utilities/encoder.hpp"

#include <string>
#include <string_view>
#include <array>
#include <utility>
#include <memory>
#include <variant>
#include <filesystem>

#include <type_traits>

namespace catalogue {
    namespace domain {
        namespace literals {
            std::filesystem::path operator""_p(const char* pathname, size_t size);
        } //namespace literals

        /*
            Every data members of every single struct/class declared within the namespace compound_types
            should be declared in the namespace "components", in order to keep all the basic types
            in one place. This process makes easier the handling of types for storing them properly.

            | | | | | | | | | |
            v v v v v v v v v v
        */

        namespace components {
            namespace types {
                using Name = std::array<encoder::ascii::Item, 10>;

                using Identifier = std::array<encoder::ascii::Item, 6>;

                enum class Gender : bool {
                    MALE,
                    FEMALE
                };
                
                class Group {
                public:  
                    enum class TAA : char {
                        MONOSTATE,
                        FIRST_GRADE,
                        SECOND_GRADE,
                        THIRD_GRADE
                    };

                    enum class TAC : char {
                        MONOSTATE,
                        BILINGUAL_BUSINESS_DEPARTMENT,
                        HEALTH_EDUCATION_DEPARTMENT,
                        MUSIC_DEPARTMENT,
                        THEOLOGY_DEPARTMENT
                    };

                    enum class TAIS : char {
                        MONOSTATE,
                        SEVENTH_GRADE,
                        EIGHTH_GRADE,
                        NINTH_GRADE,
                        TENTH_GRADE,
                        ELEVENTH_GRADE,
                        TWELFTH_GRADE
                    };
                    
                    Group() = default;

                    template <class GroupName>
                    Group(GroupName group) 
                    : group_(group) 
                    {
                    }

                    template <class GroupName>
                    Group& operator=(GroupName group) {
                        group_ = group;
                        return *this;
                    }

                    bool IsTAC() const;
                    bool IsTAIS() const;
                    bool IsTAA() const;
                    TAC GetAsTAC() const;
                    TAIS GetAsTAIS() const;
                    TAA GetAsTAA() const;

                    bool operator==(const Group& other) const;
                    bool operator!=(const Group& other) const;

                private:
                    std::variant<TAC, TAIS, TAA> group_;
                };
            
            } //namespace types

            struct Nameable {
                types::Name value;
            protected:
                virtual ~Nameable() = default;
            };

            //struct Person's helper struct to enable named parameter idiom
            template <typename Owner>
            struct NameablePathProps : Nameable {
                Owner& SetName(types::Name name) {
                    this -> value = std::move(name);
                    return static_cast<Owner&>(*this);
                }
            protected:
                virtual ~NameablePathProps() = default;
            };

            struct Identifiable {
                types::Identifier value;
            protected:
                virtual ~Identifiable() = default;
            };

            //struct Person's helper struct to enable named parameter idiom
            template <typename Owner>
            struct IdentifiablePathProps : Identifiable {
                Owner& SetIdentifier(types::Identifier identifier) {
                    this -> value = std::move(identifier);
                    return static_cast<Owner&>(*this);
                }
            protected:
                virtual ~IdentifiablePathProps() = default;
            };

            struct Genderable {
                types::Gender value;
            protected:
                virtual ~Genderable() = default;
            };

            //struct Person's helper struct to enable named parameter idiom
            template <typename Owner>
            struct GenderablePathProps : Genderable {
                Owner& SetGender(types::Gender gender) {
                    this -> value = gender;
                    return static_cast<Owner&>(*this);
                }
            protected:
                virtual ~GenderablePathProps() = default;
            };
            
            struct Groupable {
                types::Group value;
            protected:
                virtual ~Groupable() = default;
            };

            //struct Person's helper struct to enable named parameter idiom
            template <typename Owner>
            struct GroupablePathProps : Groupable {
                Owner& SetGroup(types::Group group) {
                    this -> value = group;
                    return static_cast<Owner&>(*this);
                }
            protected:
                virtual ~GroupablePathProps() = default;
            };
            
        } //namespace components 

        /*
            Every single class/struct should be declared in the namespace compound_types, 
            and every data member type should be taken from the namespace components. 
            In case that the desired datatype is not declared in the namespace component,
            it must be declared there and then make use of it as a data member type 
            in a class/struct in the namespace compound_types.
            | | | | | | | | | |
            v v v v v v v v v v
        */

        namespace compound_types {
            /*
                Every single final class/struct should be declared in the namespace final_types.
                All final types should he under the FinalTypes interface.
                Final types are the classes/structs available for the user.
                | | | | | | | | | |
                v v v v v v v v v v
            */

            using namespace components;

            enum class FinalTypes : char {
                STUDENT
            };
                
            class Student final : public NameablePathProps<Student>
                                , public GenderablePathProps<Student> 
                                , public IdentifiablePathProps<Student>
                                , public GroupablePathProps<Student> {
            public:
                Student() = default;
            };

        } //namespace compound_types         
    } // namespace domain
} // namespace catalogue

