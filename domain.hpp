#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <memory>
#include <variant>
#include <filesystem>




namespace catalogue {
    namespace domain {
        namespace groups {
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
        }//namespace groups
        

        /*
            Every data members of every single class declared within the class "CompoundTypes"
            should be declared in the class "components", in order to keep all the basic types
            in one place. This process makes easier the handling of types for storing them properly.

            | | | | | | | | | |
            v v v v v v v v v v
        */

        class Components final {
        public:
            //class Person data member
            using Name = std::string;
            //class User data member
            using Identifier = std::string;
            //class Person data member
            enum class Gender : bool {
                MALE,
                FEMALE
            };
            //class User data member
            struct Group : std::variant<std::monostate, groups::TAC, groups::TAIS, groups::TAA> {
                using variant::variant;
                
                bool IsInitialized() const;
                bool IsTAC() const;
                bool IsTAIS() const;
                bool IsTAA() const;
                groups::TAC GetAsTAC() const;
                groups::TAIS GetAsTAIS() const;
                groups::TAA GetAsTAA() const;
            };

        public:
            Components& SetHasName (bool value);
            Components& SetHasIdentifier (bool value);
            Components& SetHasGender(bool value);
            Components& SetHasGroup(bool value);
            bool HasName() const;
            bool HasIdentifier() const;
            bool HasGender() const;
            bool HasGroup() const;

        private:
            bool has_name_ = false;
            bool has_identifier_ = false;
            bool has_gender_ = false;
            bool has_group_ = false;
        };

        /*
            Every single class/struct should be declared in the class "CompoundTypes", and every data member
            should be taken from the class "Components". In case that the desired datatype is not part of "Component",
            it must be declared there and then make use of it as a data member in a class/struct in the class "CompoundTypes".

            | | | | | | | | | |
            v v v v v v v v v v
        */

        class CompoundTypes final {
        public:
            /*--------------classes/structs interfaces and helpers--------------*/
            //struct-interface
            struct Person {
                Components::Name name;
                Components::Gender gender;
            protected:
                virtual ~Person() = default;
            };

            //struct Person's helper struct to enable named parameter idiom
            template <typename Owner>
            struct PersonPathProps : Person {
                Owner& SetName(Components::Name n) {
                    name = std::move(n);
                    return static_cast<Owner&>(*this);
                }
                
                Owner& SetGender(Components::Gender g) {
                    gender = g;
                    return static_cast<Owner&>(*this);
                }

            protected:
                virtual ~PersonPathProps() = default;
            };

            //struct-interface
            struct User {
                Components::Identifier identifier;
                Components::Group group;
            protected:
                virtual ~User() = default;
            };

            //struct User's helper struct to enable named parameter idiom
            template <typename Owner>
            struct UserPathProps : User {
                Owner& SetIdentifier(Components::Identifier i) {
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

            /*--------------final classes/structs--------------*/
            class Student final : public PersonPathProps<Student> , public UserPathProps<Student> {};



            /*
                In the enum class FinalTypes must be included all the final struct/clases
                that were declared inside the class CompoundTypes, this is with the aim of
                getting all the final classes/structs in one place.
                | | | | | | | | | |
                v v v v v v v v v v
            */

            enum class FinalTypes : char {
                UNKNOWN,
                STUDENT
            };

        public:
            template <typename T> 
            explicit CompoundTypes(T* type);
            explicit CompoundTypes(FinalTypes);
            FinalTypes GetType() const;
            const Components& GetComponents() const;    

        private:
            FinalTypes type_;
            Components components_;
        };

        namespace literals {
            std::filesystem::path operator""_p(const char* pathname, size_t size);
        } //namespace literals

        
        
        
        
        
        
        
        
        
         
    } // namespace domain
} // namespace catalogue


