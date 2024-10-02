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
                    .SetGender(Components::Gender::MALE)
                    .SetName("AAA"s)
                    .SetIdentifier("111")
                    .SetGroup(groups::TAIS::SEVENTH_GRADE);
            
            auto s2 = Student{}
                    .SetGender(Components::Gender::FEMALE)
                    .SetName("BBB"s)
                    .SetGroup(groups::TAA::FIRST_GRADE)
                    .SetIdentifier("222"s);

            auto s3 = Student{};

            auto s4 = Student{}
                    .SetGender(Components::Gender::MALE)
                    .SetGroup(groups::TAA::FIRST_GRADE);

            assert(s1.gender == Components::Gender::MALE &&
                s1.identifier == "111"s && 
                s1.group.IsTAIS() &&
                s1.name == "AAA"s &&
                s1.identifier != ""s &&
                s1.name != "BBB"s &&
                !s1.group.IsTAC());

            assert(s2.gender == Components::Gender::FEMALE &&
                s2.gender != s1.gender &&
                s2.identifier == "222"s && 
                s2.identifier != s1.identifier &&
                s2.name == "BBB"s &&
                s2.name != "AAA"s &&
                s2.name != s1.name &&
                !s2.group.IsTAC() &&
                !s2.group.IsTAIS() &&
                s2.group != s1.group &&
                s2.group.IsTAA());

            assert(s3.gender != Components::Gender::FEMALE &&
                s3.gender == s1.gender &&
                s3.identifier.empty() && 
                !(!s3.identifier.empty()) &&
                s3.name != "BBB"s &&
                s3.name != s1.name &&
                s3.name == ""s &&
                !s3.group.IsInitialized() &&
                !s3.group.IsTAC() &&
                !s3.group.IsTAIS() &&
                s3.group != s1.group &&
                s3.group != s2.group);

            assert(s4.gender == Components::Gender::MALE &&
                s4.group.IsTAA() &&
                s4.group == s2.group &&
                s4.name == s3.name &&
                s4.identifier == s3.identifier);
        }
    } //namespace domain

    namespace user_catalogue {
        using namespace catalogue::database;

        void TestAddUser() {
            UserCatalogue catalogue;
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAA::FIRST_GRADE).SetIdentifier("1111"s).SetName("Liliana"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::MALE).SetGroup(groups::TAIS::NINTH_GRADE).SetIdentifier("2222"s).SetName("Victor"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAC::THEOLOGY_DEPARTMENT).SetIdentifier("3333"s).SetName("Juan"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAA::SECOND_GRADE).SetIdentifier("4444"s).SetName("Franco"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::MALE).SetGroup(groups::TAIS::ELEVENTH_GRADE).SetIdentifier("5555"s).SetName("Mateo"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAC::BILINGUAL_BUSINESS_DEPARTMENT).SetIdentifier("6666"s).SetName("Lucas"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAA::SECOND_GRADE).SetIdentifier("7777"s).SetName("Joaz"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::MALE).SetGroup(groups::TAIS::TENTH_GRADE).SetIdentifier("8888"s).SetName("Felipe"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAC::MUSIC_DEPARTMENT).SetIdentifier("9999"s).SetName("Pedro"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::MALE).SetGroup(groups::TAIS::SEVENTH_GRADE).SetIdentifier("1000"s).SetName("Tere"s));
            
            auto t1 = catalogue.GetUserByIdentifier("7777"s);
            auto t2 = catalogue.GetUserByIdentifier("1000"s);
            auto t3 = catalogue.GetUserByIdentifier("3333"s);
            auto t4 = catalogue.GetUserByIdentifier("4444"s);
            auto t5 = catalogue.GetUserByIdentifier("9999"s);

            auto t1_casted = dynamic_cast<const Student*>(t1.get());
            assert(t1_casted &&
                   t1_casted -> gender == Components::Gender::FEMALE && 
                   t1_casted -> gender != Components::Gender::MALE && 
                   t1_casted -> identifier == "7777"s && 
                   t1_casted -> identifier != "1000"s &&
                   t1_casted -> group.IsTAA() &&
                   !t1_casted -> group.IsTAC() &&
                   !t1_casted -> group.IsTAIS() &&
                   t1_casted -> group.GetAsTAA() == groups::TAA::SECOND_GRADE &&
                   t1_casted -> group.GetAsTAA() != groups::TAA::FIRST_GRADE &&
                   t1_casted -> name == "Joaz"s &&
                   t1_casted -> name != "Jooaz"s);
            assert(dynamic_cast<const Student*>(t2.get()));
            assert(dynamic_cast<const Student*>(t3.get()));
            assert(dynamic_cast<const Student*>(t4.get()));
            assert(dynamic_cast<const Student*>(t5.get()));


            assert(t1 -> group.IsTAA());
            assert(t2 -> group.IsTAIS());
            assert(t3 -> group.IsTAC());
            assert(t4 -> group.IsTAA());
            assert(t5 -> group.IsTAC());
        }

        /*void TestGetUsersByGroup() {
            UserCatalogue catalogue;
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAA::FIRST_GRADE).SetIdentifier(1111).SetName("Liliana"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::MALE).SetGroup(groups::TAIS::NINTH_GRADE).SetIdentifier(2222).SetName("Victor"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAC::THEOLOGY_DEPARTMENT).SetIdentifier(3333).SetName("Juan"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAA::SECOND_GRADE).SetIdentifier(4444).SetName("Franco"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::MALE).SetGroup(groups::TAIS::ELEVENTH_GRADE).SetIdentifier(5555).SetName("Mateo"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAC::BILINGUAL_BUSINESS_DEPARTMENT).SetIdentifier(6666).SetName("Lucas"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAA::SECOND_GRADE).SetIdentifier(7777).SetName("Joaz"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::MALE).SetGroup(groups::TAIS::TENTH_GRADE).SetIdentifier(8888).SetName("Felipe"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::FEMALE).SetGroup(groups::TAC::MUSIC_DEPARTMENT).SetIdentifier(9999).SetName("Pedro"s));
            catalogue.AddUser(Student{}.SetGender(Components::Gender::MALE).SetGroup(groups::TAIS::SEVENTH_GRADE).SetIdentifier(1000).SetName("Tere"s));

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