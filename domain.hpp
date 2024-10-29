#pragma once

#include <string>
#include <string_view>
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
            using Name = std::string;

            using Identifier = std::string;

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
            
            /*This struct should contain a has-version of all the datatypes declared above*/
            struct Composition {
                Composition& SetHasName (bool value);
                Composition& SetHasIdentifier (bool value);
                Composition& SetHasGender(bool value);
                Composition& SetHasGroup(bool value);

                bool has_name = false;
                bool has_identifier = false;
                bool has_gender = false;
                bool has_group = false;
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
            //struct-interface
            struct Person {
                components::Name name;
                components::Gender gender;
            protected:
                virtual ~Person() = default;
            };

            //struct Person's helper struct to enable named parameter idiom
            template <typename Owner>
            struct PersonPathProps : Person {
                Owner& SetName(components::Name n) {
                    name = std::move(n);
                    return static_cast<Owner&>(*this);
                }
                
                Owner& SetGender(components::Gender g) {
                    gender = g;
                    return static_cast<Owner&>(*this);
                }

            protected:
                virtual ~PersonPathProps() = default;
            };

            //struct-interface
            struct User {
                components::Identifier identifier;
                components::Group group;
            protected:
                virtual ~User() = default;
            };

            //struct User's helper struct to enable named parameter idiom
            template <typename Owner>
            struct UserPathProps : User {
                Owner& SetIdentifier(components::Identifier i) {
                    identifier = std::move(i);
                    return static_cast<Owner&>(*this);
                }
                
                template <typename GroupType>
                Owner& SetGroup(GroupType g) {
                    group = g;
                    return static_cast<Owner&>(*this);
                }
                
            protected:
                virtual ~UserPathProps() = default;
            };

            /*
                Every single final class/struct should be declared in the namespace final_types.
                All final types should he under the FinalTypes interface.
                Final types are the classes/structs available for the user.
                | | | | | | | | | |
                v v v v v v v v v v
            */

            namespace final_types {
                //class interface
                class FinalTypes {
                public:
                    enum class TypeNames : char;
                    
                    FinalTypes() = default;
                    explicit FinalTypes(TypeNames);

                    TypeNames GetTypeName() const;
                    components::Composition GetComponents() const;
                private:
                    TypeNames typename_;
                };

                //Final class
                class Student final : public FinalTypes, public PersonPathProps<Student>, public UserPathProps<Student>{
                public:
                    Student();
                };

                enum class FinalTypes::TypeNames : char {
                    STUDENT
                };

            } //namespace final_types
        } //namespace compound_types         
    } // namespace domain
} // namespace catalogue


