#pragma once

#include "domain.hpp"
#include "users_catalogue.hpp"

#include <cassert>
#include <string>

namespace testing {
    using namespace std::literals;
    using namespace catalogue::domain;

    namespace domain {
        void TestStudentStruct() {
            auto s1 = Student{}
                    .SetGender(Gender::MALE)
                    .SetName("AAA"s)
                    .SetIdentifier("111")
                    .SetGroup(grouping::TAIS::SEVENTH_GRADE);
            
            auto s2 = Student{}
                    .SetGender(Gender::FEMALE)
                    .SetName("BBB"s)
                    .SetGroup(grouping::TAA::FIRST_GRADE)
                    .SetIdentifier("222"s);

            auto s3 = Student{};

            auto s4 = Student{}
                    .SetGender(Gender::MALE)
                    .SetGroup(grouping::TAA::FIRST_GRADE);

            assert(s1.GetGender() == Gender::MALE &&
                s1.GetIdentifier() == "111"s && 
                s1.GetGroup().IsTAIS() &&
                s1.GetName() == "AAA"s &&
                s1.GetIdentifier() != ""s &&
                s1.GetName() != "BBB"s &&
                !s1.GetGroup().IsTAC());

            assert(s2.GetGender() == Gender::FEMALE &&
                s2.GetGender() != s1.GetGender() &&
                s2.GetIdentifier() == "222"s && 
                s2.GetIdentifier() != s1.GetIdentifier() &&
                s2.GetName() == "BBB"s &&
                s2.GetName() != "AAA"s &&
                s2.GetName() != s1.GetName() &&
                !s2.GetGroup().IsTAC() &&
                !s2.GetGroup().IsTAIS() &&
                s2.GetGroup() != s1.GetGroup() &&
                s2.GetGroup().IsTAA());

            assert(s3.GetGender() != Gender::FEMALE &&
                s3.GetGender() == s1.GetGender() &&
                s3.GetIdentifier().empty() && 
                !(!s3.GetIdentifier().empty()) &&
                s3.GetName() != "BBB"s &&
                s3.GetName() != s1.GetName() &&
                s3.GetName() == ""s &&
                !s3.GetGroup().IsInitialized() &&
                !s3.GetGroup().IsTAC() &&
                !s3.GetGroup().IsTAIS() &&
                s3.GetGroup() != s1.GetGroup() &&
                s3.GetGroup() != s2.GetGroup());

            assert(s4.GetGender() == Gender::MALE &&
                s4.GetGroup().IsTAA() &&
                s4.GetGroup() == s2.GetGroup() &&
                s4.GetName() == s3.GetName() &&
                s4.GetIdentifier() == s3.GetIdentifier());
        }
    } //namespace domain

    namespace user_catalogue {
        using namespace catalogue::database;

        void TestAddUser() {
            UserCatalogue catalogue;
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAA::FIRST_GRADE).SetIdentifier("1111"s).SetName("Liliana"s));
            catalogue.AddUser(Student{}.SetGender(Gender::MALE).SetGroup(grouping::TAIS::NINTH_GRADE).SetIdentifier("2222"s).SetName("Victor"s));
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAC::THEOLOGY_DEPARTMENT).SetIdentifier("3333"s).SetName("Juan"s));
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAA::SECOND_GRADE).SetIdentifier("4444"s).SetName("Franco"s));
            catalogue.AddUser(Student{}.SetGender(Gender::MALE).SetGroup(grouping::TAIS::ELEVENTH_GRADE).SetIdentifier("5555"s).SetName("Mateo"s));
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAC::BILINGUAL_BUSINESS_DEPARTMENT).SetIdentifier("6666"s).SetName("Lucas"s));
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAA::SECOND_GRADE).SetIdentifier("7777"s).SetName("Joaz"s));
            catalogue.AddUser(Student{}.SetGender(Gender::MALE).SetGroup(grouping::TAIS::TENTH_GRADE).SetIdentifier("8888"s).SetName("Felipe"s));
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAC::MUSIC_DEPARTMENT).SetIdentifier("9999"s).SetName("Pedro"s));
            catalogue.AddUser(Student{}.SetGender(Gender::MALE).SetGroup(grouping::TAIS::SEVENTH_GRADE).SetIdentifier("1000"s).SetName("Tere"s));
            
            auto t1 = catalogue.GetUserByIdentifier("7777"s);
            auto t2 = catalogue.GetUserByIdentifier("1000"s);
            auto t3 = catalogue.GetUserByIdentifier("3333"s);
            auto t4 = catalogue.GetUserByIdentifier("4444"s);
            auto t5 = catalogue.GetUserByIdentifier("9999"s);

            auto t1_casted = dynamic_cast<Student*>(t1.get());
            assert(t1_casted &&
                   t1_casted -> GetGender() == Gender::FEMALE && 
                   t1_casted -> GetGender() != Gender::MALE && 
                   t1_casted -> GetIdentifier() == "7777"s && 
                   t1_casted -> GetIdentifier() != "1000"s &&
                   t1_casted -> GetGroup().IsTAA() &&
                   !t1_casted -> GetGroup().IsTAC() &&
                   !t1_casted -> GetGroup().IsTAIS() &&
                   t1_casted -> GetGroup().GetAsTAA() == grouping::TAA::SECOND_GRADE &&
                   t1_casted -> GetGroup().GetAsTAA() != grouping::TAA::FIRST_GRADE &&
                   t1_casted -> GetName() == "Joaz"s &&
                   t1_casted -> GetName() != "Jooaz"s);
            assert(dynamic_cast<Student*>(t2.get()));
            assert(dynamic_cast<Student*>(t3.get()));
            assert(dynamic_cast<Student*>(t4.get()));
            assert(dynamic_cast<Student*>(t5.get()));


            assert(t1 -> GetGroup().IsTAA());
            assert(t2 -> GetGroup().IsTAIS());
            assert(t3 -> GetGroup().IsTAC());
            assert(t4 -> GetGroup().IsTAA());
            assert(t5 -> GetGroup().IsTAC());
        }

        /*void TestGetUsersByGroup() {
            UserCatalogue catalogue;
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAA::FIRST_GRADE).SetIdentifier(1111).SetName("Liliana"s));
            catalogue.AddUser(Student{}.SetGender(Gender::MALE).SetGroup(grouping::TAIS::NINTH_GRADE).SetIdentifier(2222).SetName("Victor"s));
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAC::THEOLOGY_DEPARTMENT).SetIdentifier(3333).SetName("Juan"s));
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAA::SECOND_GRADE).SetIdentifier(4444).SetName("Franco"s));
            catalogue.AddUser(Student{}.SetGender(Gender::MALE).SetGroup(grouping::TAIS::ELEVENTH_GRADE).SetIdentifier(5555).SetName("Mateo"s));
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAC::BILINGUAL_BUSINESS_DEPARTMENT).SetIdentifier(6666).SetName("Lucas"s));
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAA::SECOND_GRADE).SetIdentifier(7777).SetName("Joaz"s));
            catalogue.AddUser(Student{}.SetGender(Gender::MALE).SetGroup(grouping::TAIS::TENTH_GRADE).SetIdentifier(8888).SetName("Felipe"s));
            catalogue.AddUser(Student{}.SetGender(Gender::FEMALE).SetGroup(grouping::TAC::MUSIC_DEPARTMENT).SetIdentifier(9999).SetName("Pedro"s));
            catalogue.AddUser(Student{}.SetGender(Gender::MALE).SetGroup(grouping::TAIS::SEVENTH_GRADE).SetIdentifier(1000).SetName("Tere"s));

            auto t1 = catalogue.GetUserIdsByGroup(Group::TAA);
            auto t2 = catalogue.GetUserIdsByGroup(Group::TAIS);
            auto t3 = catalogue.GetUserIdsByGroup(Group::TAC);

            assert(t1.size() == 3);
            assert(t1[0] == 1111 && t1[1] == 4444 && t1[2] == 7777);
            assert(t2.size() == 4 && t2.size() != t1.size());
            assert(t2[0] == 2222 && t2[1] == 5555 && t2[2] == 8888 && t2[3] == 1000);
            assert(t3.size() == 3 && t3.size() == t1.size() && t3.size() != t2.size());
            assert(t3[0] == 3333 && t3[1] == 6666 && t3[2] == 9999);
        }*/
    } //user_catalogue
} //testing