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
            Every data members of every single class declared within the namespace "domain"
            should be declared in the namespace "components", in order to keep all the basic types
            in one place. This process makes easier the handling of types for storing them properly.
        */
        namespace components {
            using Name = std::string;
            using Identifier = std::string;
            using Index = int;

            enum class Gender : bool {
                MALE,
                FEMALE
            };

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
        } //namespace components

        namespace literals {
            std::filesystem::path operator""_p(const char* pathname, size_t size);
        } //namespace literals
        

        using namespace components;

        struct Person {
            Name name;
            Gender gender;
        protected:
            virtual ~Person() = default;
        };
        
        
        template <typename Owner>
        struct PersonPathProps : Person {
            Owner& SetName(Name n) {
                name = std::move(n);
                return static_cast<Owner&>(*this);
            }
            
            Owner& SetGender(Gender g) {
                gender = g;
                return static_cast<Owner&>(*this);
            }

        protected:
            virtual ~PersonPathProps() = default;
        };
        
        struct User {
            Identifier identifier;
            Group group;
        protected:
            virtual ~User() = default;
        };
        
        template <typename Owner>
        struct UserPathProps : User {
            Owner& SetIdentifier(Identifier i) {
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
        
        class Student final : public PersonPathProps<Student> , public UserPathProps<Student> {

        };
         
    } // namespace domain
} // namespace catalogue


