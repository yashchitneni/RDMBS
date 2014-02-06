#ifndef _RELATION
#define _RELATION

#include "Attribute.h"
#include <map>
#include <array>
#include <vector>
#include <regex>

class Relation{
	typedef std::vector<Attribute*> tuple;
	typedef std::map<tuple, tuple> table;
	int n_keys;
	int n_attr;
	std::string table_name;
	std::vector<std::string> header;
	table t;
	std::vector<std::string> commands; //might not need
	
	int header_pos(std::string name);


public:
	bool meets_condition(std::string condition, std::pair<tuple, tuple> row);
	Relation() : n_keys(0), n_attr(0), table_name(""){}
	/*
	constructor takes in a table name and two vector<strings>
	strings of key_header are of the form "attr_name"
	strings of attr_header are of the form "attr_name TYPE" where TYPE can be INTEGER or VARCHAR(int)
	*/
	Relation(std::string name, std::vector<std::string> key_header, std::vector<std::string> attr_header);
	//~Relation();
	void set_name(std::string name); //sets the name of the table
	std::string get_name() const;	//returns the name of the table
	void save(); //checks if there exists a .db file and writes all the commands to ceate the table to the file
	void show(); //prints out the content of the string to std::cout
	/*
	Will also need get and set functions to access individual rows
	*/
	//create_table(); constructor
	//drop_table(); destructor
	bool insert_into(std::vector<std::string> literals);
	bool insert_into(Relation other_table);
	bool update(std::vector<std::string> attr_list, std::vector<std::string> conjunctions);
	bool delete_from(std::vector<std::string> conjunctions);
	Relation selection(std::vector<std::string> conjunctions);
	Relation projection(std::vector<std::string> attr_list);
	Relation renaming(std::vector<std::string> attr_list);
	Relation set_union(Relation other_table);
	Relation set_difference(Relation other_table);
	Relation cross_product(Relation other_table);
	Relation natural_join(Relation other_table);
};

#endif