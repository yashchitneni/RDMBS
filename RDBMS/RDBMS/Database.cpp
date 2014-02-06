#include "Database.h"

Database::Database(){

}

bool Database::command(std::string input){
	return true;
}

void Database::create_table(
	std::string table_name,
	std::vector<std::string> key_header,
	std::vector<std::string> attr_header){

	int num_keys = key_header.size();
	int num_attr = attr_header.size();

	tables.push_back(Relation(table_name, key_header, attr_header));
}

void Database::drop_table(std::string table_name){
	for (int table_iter = 0; table_iter < tables.size(); ++table_iter){
		if (table_name == tables[table_iter].get_name()){
			 tables.erase( tables.begin() + table_iter );
		}
	}
}