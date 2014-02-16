#include "stdafx.h"
#include "CppUnitTest.h"

#include "Relation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_Database
{
	TEST_CLASS(Test_Database_Operations)
	{
	public:

		TEST_METHOD(Test_Selection)
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

			Team_Project_1_Database::Relation people_sel = *people.selection(conditions);

			Assert::IsTrue(1 == people_sel.get_table().size());
			
			for (auto row : people_sel.get_table()){
				Assert::AreEqual("John", row.second.at(0)->get_value().c_str());
				Assert::AreEqual("22", row.second.at(1)->get_value().c_str());
			}
		}

		TEST_METHOD(Test_Projection)
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

			Team_Project_1_Database::Relation people_proj = *people.projection(proj_constraints);

			int iter = 0;
			for (auto row : people_proj.get_table()){
				Assert::IsTrue(2 > row.second.size());

				if (iter == 0){
					Assert::AreEqual("John", row.second.at(0)->get_value().c_str());
				}
				else{
					Assert::AreEqual("Rachel", row.second.at(0)->get_value().c_str());
				}
				++iter;
			}
		}

		TEST_METHOD(Test_Renaming)
		{
			std::vector<std::string> keys;

			keys.push_back("name");

			std::vector<std::string> header;

			header.push_back("name VARCHAR");
			header.push_back("age INTEGER");

			Team_Project_1_Database::Relation people("people", keys, header);

			std::vector<std::string> new_header;

			new_header.push_back("e_name");
			new_header.push_back("e_age");

			Team_Project_1_Database::Relation r_people = *people.renaming(new_header);

			std::vector<std::string> expected_header;

			expected_header.push_back("%e_name");
			expected_header.push_back("e_age");

			Assert::IsTrue(expected_header == r_people.get_header());
		}

		TEST_METHOD(Test_Union)
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

			Team_Project_1_Database::Relation all_people = *people.set_union(cool_people);

			Assert::IsTrue(3 == all_people.get_table().size());

			int iter = 0;
			for (auto row : all_people.get_table()){
				if (iter == 0){
					Assert::AreEqual("Arnold Schwarzenegger", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("66", row.second.at(1)->get_value().c_str());
				}
				else if (iter == 1){
					Assert::AreEqual("John", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("22", row.second.at(1)->get_value().c_str());
				}
				else{
					Assert::AreEqual("Rachel", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("22", row.second.at(1)->get_value().c_str());
				}
				++iter;
			}
		}

		TEST_METHOD(Test_Difference)
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

			Team_Project_1_Database::Relation only_cool = *cool_people.set_difference(nerdy_people);

			Assert::IsTrue(1 == only_cool.get_table().size());

			for (auto row : only_cool.get_table()){
				Assert::AreEqual("Arnold Schwarzenegger", row.second.at(0)->get_value().c_str());
				Assert::AreEqual("66", row.second.at(1)->get_value().c_str());
			}
		}

		TEST_METHOD(Test_Cross_Product)
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


			Team_Project_1_Database::Relation possible_purchases = *people.cross_product(cars);

			int iter = 0;
			for (auto row : possible_purchases.get_table()){
				switch (iter)
				{
				case 0:
					Assert::AreEqual("John", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("Charger", row.second.at(1)->get_value().c_str());
					break;
				
				case 1:
					Assert::AreEqual("John", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("Model S", row.second.at(1)->get_value().c_str());
					break;
				
				case 2:
					Assert::AreEqual("John", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("Thunderbird", row.second.at(1)->get_value().c_str());
					break;
				
				case 3:
					Assert::AreEqual("Rachel", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("Charger", row.second.at(1)->get_value().c_str());
					break;
				
				case 4:
					Assert::AreEqual("Rachel", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("Model S", row.second.at(1)->get_value().c_str());
					break;
				
				case 5:
					Assert::AreEqual("Rachel", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("Thunderbird", row.second.at(1)->get_value().c_str());
					break;
				}
				++iter;
			}
		}

		TEST_METHOD(Test_Natural_Join)
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

			Team_Project_1_Database::Relation research_directory = *researchers.natural_join(advisors);

			Assert::IsTrue(4 == research_directory.get_table().size());

			int iter = 0;
			for (auto row : research_directory.get_table()){
				switch (iter)
				{
				case 0:
					Assert::AreEqual("Gabe", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("Data Science", row.second.at(1)->get_value().c_str());
					Assert::AreEqual("James Caverlee", row.second.at(2)->get_value().c_str());
					break;

				case 1:
					Assert::AreEqual("John", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("Data Science", row.second.at(1)->get_value().c_str());
					Assert::AreEqual("James Caverlee", row.second.at(2)->get_value().c_str());
					break;

				case 2:
					Assert::AreEqual("Malorie", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("Network Security", row.second.at(1)->get_value().c_str());
					Assert::AreEqual("Goufei Gu", row.second.at(2)->get_value().c_str());
					break;

				case 3:
					Assert::AreEqual("Rachel", row.second.at(0)->get_value().c_str());
					Assert::AreEqual("Network Security", row.second.at(1)->get_value().c_str());
					Assert::AreEqual("Goufei Gu", row.second.at(2)->get_value().c_str());
					break;
				}
				++iter;
			}
		}
	};
}