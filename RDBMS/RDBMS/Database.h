#ifndef _DATABASE
#define _DATABASE

#include "Grammar.h"

class Database{
	std::vector<Relation> tables;
public:
	Database();
	bool command(std::string input);

	void create_table(
		std::string table_name,
		std::vector<std::string> key_header,
		std::vector<std::string> attr_header);

	void drop_table(std::string table_name);
};

#endif