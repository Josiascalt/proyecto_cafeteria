#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <memory>
#include <variant>
#include <filesystem>

namespace catalogue {
    namespace domain {
        class User;
        namespace type_naming {
            using Name = std::string;
            using NameLink = std::string_view;
            using Identifier = std::string;
            using IdentifierLink = std::string_view;
            using Index = int;
            using UserPtr = std::shared_ptr<User>;
        } //namespace type_naming

        namespace literals {
            std::filesystem::path operator""_p(const char* pathname, size_t size);
        } //namespace literals
        
        using namespace type_naming;

        enum class Gender : bool {
            MALE,
            FEMALE
        };

        namespace grouping {
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
        };

        class Group : public std::variant<std::monostate, grouping::TAC, grouping::TAIS, grouping::TAA> {
        public:
            using variant::variant;

            bool IsInitialized() const;
            bool IsTAC() const;
            bool IsTAIS() const;
            bool IsTAA() const;

            grouping::TAC GetAsTAC() const;
            grouping::TAIS GetAsTAIS() const;
            grouping::TAA GetAsTAA() const;
        };
        
        class Person {
        public: 
            virtual const Name& GetName() const;
            virtual const Gender GetGender() const;
        protected:
            Name name_;
            Gender gender_;

            virtual ~Person() = default;
        };
        
        
        template <typename Owner>
        class PersonPathProps : public Person {
        public:
            Owner& SetName(Name name) {
                name_ = name;
                return static_cast<Owner&>(*this);
            }
            
            Owner& SetGender(Gender gender) {
                gender_ = gender;
                return static_cast<Owner&>(*this);
            }
        protected:
            virtual ~PersonPathProps() = default;
        };
        
        class User {
        public:
            virtual const Group& GetGroup() const;
            virtual const Identifier& GetIdentifier() const;
        protected:
            Identifier identifier_;
            Group group_;
            
            virtual ~User() = default;
        };
        
        template <typename Owner>
        class UserPathProps : public User {
        public:
            Owner& SetIdentifier(Identifier identifier) {
                identifier_ = std::move(identifier);
                return static_cast<Owner&>(*this);
            }
            
            template <typename GroupType>
            Owner& SetGroup(GroupType g) {
                group_ = g;
                return static_cast<Owner&>(*this);
            }
            
        protected:
            virtual ~UserPathProps() = default;
        };
        
        class Student final : public PersonPathProps<Student> , public UserPathProps<Student> {

        };
        
         
    } // namespace domain
} // namespace catalogue


