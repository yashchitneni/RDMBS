#include "stdafx.h"
#include "CppUnitTest.h"

#include "Grammar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_Database
{
    TEST_CLASS(Test_Parser)
    {
    public:

        TEST_METHOD(Test_Creation)
        {
            //Test table creation
            std::vector<std::string> keys;

            keys.push_back("name");

            std::vector<std::string> header;

            header.push_back("name VARCHAR");
            header.push_back("age INTEGER");

            Team_Project_1_Database::Relation people_wanted("people", keys, header);

            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";

            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(people_wanted == tables[0]);
        }

        TEST_METHOD(Test_Value_Insertion)
        {
            std::vector<std::string> keys;

            keys.push_back("name");

            std::vector<std::string> header;

            header.push_back("name VARCHAR");
            header.push_back("age INTEGER");

            Team_Project_1_Database::Relation people_wanted("people", keys, header);

            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";

            Team_Project_1_Database::Grammar::program(command, tables);

            //Test insertion into relation thru values
            std::vector<std::string> insertion1;
            std::vector<std::string> insertion2;

            insertion1.push_back("\"John\"");
            insertion1.push_back("22");

            insertion2.push_back("\"Rachel\"");
            insertion2.push_back("22");

            people_wanted.insert_into(insertion1);
            people_wanted.insert_into(insertion2);

            command = "INSERT INTO people VALUES FROM (\"John\", 22);";

            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"Rachel\", 22);";

            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(people_wanted == tables[0]);
        }

        TEST_METHOD(Test_Update)
        {
            std::vector<std::string> keys;

            keys.push_back("name");

            std::vector<std::string> header;

            header.push_back("name VARCHAR");
            header.push_back("age INTEGER");

            Team_Project_1_Database::Relation people_wanted("people", keys, header);

            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";

            Team_Project_1_Database::Grammar::program(command, tables);

            std::vector<std::string> insertion1;
            std::vector<std::string> insertion2;

            insertion1.push_back("\"John\"");
            insertion1.push_back("22");

            insertion2.push_back("\"Rachel\"");
            insertion2.push_back("22");

            people_wanted.insert_into(insertion1);
            people_wanted.insert_into(insertion2);

            command = "INSERT INTO people VALUES FROM (\"John\", 22);";

            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"Rachel\", 22);";

            Team_Project_1_Database::Grammar::program(command, tables);

            //Test relation update
            std::vector<std::string> changes;
            changes.push_back("age = 23");

            std::vector<std::string> conditions;
            conditions.push_back("name == \"John\"");

            people_wanted.update(changes, conditions);

            command = "UPDATE people SET age = 23 WHERE name == \"John\";";

            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(people_wanted == tables[0]);
        }

        TEST_METHOD(Test_Deletion)
        {
            std::vector<std::string> keys;

            keys.push_back("name");

            std::vector<std::string> header;

            header.push_back("name VARCHAR");
            header.push_back("age INTEGER");

            Team_Project_1_Database::Relation people_wanted("people", keys, header);

            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";

            Team_Project_1_Database::Grammar::program(command, tables);

            std::vector<std::string> insertion1;
            std::vector<std::string> insertion2;

            insertion1.push_back("\"John\"");
            insertion1.push_back("22");

            insertion2.push_back("\"Rachel\"");
            insertion2.push_back("22");

            people_wanted.insert_into(insertion1);
            people_wanted.insert_into(insertion2);

            command = "INSERT INTO people VALUES FROM (\"John\", 22);";

            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"Rachel\", 22);";

            Team_Project_1_Database::Grammar::program(command, tables);

            //Test deletion from a relation
            std::vector<std::string> conditions;
            conditions.push_back("name == \"Rachel\"");

            people_wanted.delete_from(conditions);

            command = "DELETE FROM people WHERE name == \"Rachel\";";

            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(people_wanted == tables[0]);
        }

        TEST_METHOD(Test_Relation_Insertion)
        {
            //Test insertion from another relation
            std::vector<std::string> keys;

            keys.push_back("name");

            std::vector<std::string> header;

            header.push_back("name VARCHAR");
            header.push_back("age INTEGER");

            Team_Project_1_Database::Relation people_r1("people", keys, header);

            Team_Project_1_Database::Relation people_r2("people", keys, header);

            std::vector<std::string> insertion1;
            std::vector<std::string> insertion2;
            std::vector<std::string> insertion3;
            std::vector<std::string> insertion4;

            insertion1.push_back("\"John\"");
            insertion1.push_back("22");

            insertion2.push_back("\"Rachel\"");
            insertion2.push_back("22");

            insertion3.push_back("\"Jack\"");
            insertion3.push_back("16");

            insertion4.push_back("\"Diane\"");
            insertion4.push_back("15");

            people_r1.insert_into(insertion1);
            people_r1.insert_into(insertion2);

            people_r2.insert_into(insertion3);
            people_r2.insert_into(insertion4);

            people_r1.insert_into(people_r2);


            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE people1 (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "CREATE TABLE people2 (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people1 VALUES FROM (\"John\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people1 VALUES FROM (\"Rachel\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);


            command = "INSERT INTO people2 VALUES FROM (\"Jack\", 16);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people2 VALUES FROM (\"Diane\", 15);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people1 VALUES FROM RELATION people2;";
            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(people_r1 == tables[0]);
        }

        TEST_METHOD(Test_Selection_Query)
        {
            std::vector<std::string> keys;

            keys.push_back("name");

            std::vector<std::string> header;

            header.push_back("name VARCHAR");
            header.push_back("age INTEGER");

            Team_Project_1_Database::Relation people("people", keys, header);

            std::vector<std::string> insertion1;
            std::vector<std::string> insertion2;

            insertion1.push_back("\"John\"");
            insertion1.push_back("22");

            insertion2.push_back("\"Rachel\"");
            insertion2.push_back("22");

            people.insert_into(insertion1);
            people.insert_into(insertion2);

            std::vector<std::string> conditions;

            conditions.push_back("name == \"John\"");

            Team_Project_1_Database::Relation people_wanted = *people.selection(conditions);


            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"John\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"Rachel\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "people_sel <- select (name == \"John\") people;";
            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(people_wanted == tables[1]);
        }

        TEST_METHOD(Test_Projection_Query)
        {
            std::vector<std::string> keys;

            keys.push_back("name");

            std::vector<std::string> header;

            header.push_back("name VARCHAR");
            header.push_back("age INTEGER");

            Team_Project_1_Database::Relation people("people", keys, header);

            std::vector<std::string> insertion1;
            std::vector<std::string> insertion2;

            insertion1.push_back("\"John\"");
            insertion1.push_back("22");

            insertion2.push_back("\"Rachel\"");
            insertion2.push_back("22");

            people.insert_into(insertion1);
            people.insert_into(insertion2);

            std::vector<std::string> proj_constraints;

            proj_constraints.push_back("name");

            Team_Project_1_Database::Relation people_wanted = *people.projection(proj_constraints);

            
            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"John\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"Rachel\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "people_proj <- project (name) people;";
            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(people_wanted == tables[1]);
        }
        
        TEST_METHOD(Test_Renaming_Query)
        {
            std::vector<std::string> expected_header;

            expected_header.push_back("%e_name");
            expected_header.push_back("e_age");

            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "e_people <- rename (e_name, e_age) people;";
            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(expected_header == tables[1].get_header());
        }

        TEST_METHOD(Test_Union_Query)
        {
            std::vector<std::string> keys;

            keys.push_back("name");

            std::vector<std::string> header;

            header.push_back("name VARCHAR");
            header.push_back("age INTEGER");

            Team_Project_1_Database::Relation people("people", keys, header);

            std::vector<std::string> insertion1;
            std::vector<std::string> insertion2;

            insertion1.push_back("\"John\"");
            insertion1.push_back("22");

            insertion2.push_back("\"Rachel\"");
            insertion2.push_back("22");

            people.insert_into(insertion1);
            people.insert_into(insertion2);

            Team_Project_1_Database::Relation cool_people("cool", keys, header);

            cool_people.insert_into(insertion2);

            std::vector<std::string> insertion3;

            insertion3.push_back("\"Arnold Schwarzenegger\"");
            insertion3.push_back("66");

            cool_people.insert_into(insertion3);

            Team_Project_1_Database::Relation people_wanted = *people.set_union(cool_people);

            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"John\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"Rachel\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "CREATE TABLE cool_people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO cool_people VALUES FROM (\"Rachel\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO cool_people VALUES FROM (\"Arnold Schwarzenegger\", 66);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "all_people <- people + cool_people;";
            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(people_wanted == tables[2]);
        }

        TEST_METHOD(Test_Difference_Query)
        {
            std::vector<std::string> keys;

            keys.push_back("name");

            std::vector<std::string> header;

            header.push_back("name VARCHAR");
            header.push_back("age INTEGER");

            Team_Project_1_Database::Relation nerdy_people("nerds", keys, header);

            std::vector<std::string> insertion1;
            std::vector<std::string> insertion2;

            insertion1.push_back("\"John\"");
            insertion1.push_back("22");

            insertion2.push_back("\"Rachel\"");
            insertion2.push_back("22");

            nerdy_people.insert_into(insertion1);
            nerdy_people.insert_into(insertion2);

            Team_Project_1_Database::Relation cool_people("cool", keys, header);

            cool_people.insert_into(insertion2);

            std::vector<std::string> insertion3;

            insertion3.push_back("\"Arnold Schwarzenegger\"");
            insertion3.push_back("66");

            cool_people.insert_into(insertion3);

            Team_Project_1_Database::Relation people_wanted = *cool_people.set_difference(nerdy_people);


            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE nerdy_people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO nerdy_people VALUES FROM (\"John\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO nerdy_people VALUES FROM (\"Rachel\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "CREATE TABLE cool_people (name VARCHAR(20), age INTEGER) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO cool_people VALUES FROM (\"Rachel\", 22);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO cool_people VALUES FROM (\"Arnold Schwarzenegger\", 66);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "only_cool <- cool_people - nerdy_people;";
            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(people_wanted == tables[2]);
        }

        TEST_METHOD(Test_Cross_Product_Query)
        {
            std::vector<std::string> people_keys;

            people_keys.push_back("name");

            std::vector<std::string> people_header;

            people_header.push_back("name VARCHAR");

            Team_Project_1_Database::Relation people("people", people_keys, people_header);

            std::vector<std::string> insertion1;
            std::vector<std::string> insertion2;

            insertion1.push_back("\"John\"");

            insertion2.push_back("\"Rachel\"");

            people.insert_into(insertion1);
            people.insert_into(insertion2);


            std::vector<std::string> car_keys;

            car_keys.push_back("model");

            std::vector<std::string> car_header;

            car_header.push_back("model VARCHAR");

            Team_Project_1_Database::Relation cars("cars", car_keys, car_header);

            std::vector<std::string> insertion3;
            std::vector<std::string> insertion4;
            std::vector<std::string> insertion5;

            insertion3.push_back("\"Thunderbird\"");

            insertion4.push_back("\"Model S\"");

            insertion5.push_back("\"Charger\"");

            cars.insert_into(insertion3);
            cars.insert_into(insertion4);
            cars.insert_into(insertion5);

            Team_Project_1_Database::Relation relation_wanted = *people.cross_product(cars);


            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE people (name VARCHAR(10)) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"John\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO people VALUES FROM (\"Rachel\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "CREATE TABLE cars (model VARCHAR(15)) PRIMARY KEY(model);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO cars VALUES FROM (\"Thunderbird\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO cars VALUES FROM (\"Model S\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO cars VALUES FROM (\"Charger\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "possible_purchases <- people * cars;";
            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(relation_wanted == tables[2]);
        }

        TEST_METHOD(Test_Natural_Join_Query)
        {
            std::vector<std::string> researcher_keys;

            researcher_keys.push_back("name");

            std::vector<std::string> researcher_header;

            researcher_header.push_back("name VARCHAR");
            researcher_header.push_back("department VARCHAR");

            Team_Project_1_Database::Relation researchers("slaves", researcher_keys, researcher_header);

            std::vector<std::string> insertion1;
            std::vector<std::string> insertion2;
            std::vector<std::string> insertion3;
            std::vector<std::string> insertion4;

            insertion1.push_back("\"John\"");
            insertion1.push_back("\"Data Science\"");

            insertion2.push_back("\"Rachel\"");
            insertion2.push_back("\"Network Security\"");

            insertion3.push_back("\"Gabe\"");
            insertion3.push_back("\"Data Science\"");

            insertion4.push_back("\"Malorie\"");
            insertion4.push_back("\"Network Security\"");

            researchers.insert_into(insertion1);
            researchers.insert_into(insertion2);
            researchers.insert_into(insertion3);
            researchers.insert_into(insertion4);


            std::vector<std::string> advisor_keys;

            advisor_keys.push_back("department");

            std::vector<std::string> advisor_header;

            advisor_header.push_back("department VARCHAR");
            advisor_header.push_back("advisor VARCHAR");

            Team_Project_1_Database::Relation advisors("overlords", advisor_keys, advisor_header);

            std::vector<std::string> insertion5;
            std::vector<std::string> insertion6;
            std::vector<std::string> insertion7;

            insertion5.push_back("\"Data Science\"");
            insertion5.push_back("\"James Caverlee\"");

            insertion6.push_back("\"Network Security\"");
            insertion6.push_back("\"Goufei Gu\"");

            insertion7.push_back("\"Rescue Robotics\"");
            insertion7.push_back("\"Robin Murphy\"");

            advisors.insert_into(insertion5);
            advisors.insert_into(insertion6);
            advisors.insert_into(insertion7);

            Team_Project_1_Database::Relation relation_wanted = *researchers.natural_join(advisors);


            std::vector<Team_Project_1_Database::Relation> tables;

            std::string command = "CREATE TABLE researchers (name VARCHAR(10), department VARCHAR(14)) PRIMARY KEY(name);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO researchers VALUES FROM (\"John\", \"Data Science\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO researchers VALUES FROM (\"Rachel\", \"Network Security\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO researchers VALUES FROM (\"Gabe\", \"Data Science\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO researchers VALUES FROM (\"Malorie\", \"Network Security\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "CREATE TABLE advisors (department VARCHAR(14), advisor VARCHAR(15)) PRIMARY KEY(department);";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO advisors VALUES FROM (\"Data Science\", \"James Caverlee\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO advisors VALUES FROM (\"Network Security\", \"Goufei Gu\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "INSERT INTO advisors VALUES FROM (\"Rescue Robotics\", \"Robin Murphy\");";
            Team_Project_1_Database::Grammar::program(command, tables);

            command = "research_directory <- researchers JOIN advisors;";
            Team_Project_1_Database::Grammar::program(command, tables);

            Assert::IsTrue(relation_wanted == tables[2]);
        }
    };
}