#include "Database.h"

Database::Database(){

}

bool Database::command(std::string input){
	return true;
}

void Database::create_table(
	std::string table_name,
	std::vector<Attribute*> keys,
	std::vector<std::string> attr_header){

	int num_keys = keys.size();
	int num_attr = attr_header.size();

	tables.push_back(Relation(num_keys, num_attr, table_name, attr_header));
}

void Database::drop_table(std::string table_name){
	for (int table_iter = 0; table_iter < tables.size(); ++table_iter){
		if (table_name == tables[table_iter].get_name()){
			 tables.erase( tables.begin() + table_iter );
		}
	}
}