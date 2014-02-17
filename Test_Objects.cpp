#include "stdafx.h"
#include "CppUnitTest.h"

#include "Relation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_Database
{
    TEST_CLASS(Test_Objects)
    {
    public:

        TEST_METHOD(Test_Attributes)
        {
            Team_Project_1_Database::Var_Char name = "John";

            Assert::AreEqual("John", name.get_value().c_str());

            Team_Project_1_Database::Integer age = 22;

            Assert::IsTrue(22 == atoi(age.get_value().c_str()));
        }

        TEST_METHOD(Test_Relations)
        {
            std::vector<std::string> keys;

            keys.push_back("attr1");

            std::vector<std::string> header;

            header.push_back("attr1 VARCHAR");
            header.push_back("attr2 INTEGER");
            
            Team_Project_1_Database::Relation relation1("rel1", keys, header);

            std::vector<std::string> header_wanted;

            header_wanted.push_back("%attr1");
            header_wanted.push_back("attr2");

            Assert::IsTrue(header_wanted == relation1.get_header());

            Team_Project_1_Database::Relation relation1copy = relation1;

            Assert::IsTrue(relation1 == relation1copy);
        }
    };
}