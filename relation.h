#ifndef _RELATION
#define _RELATION

#include "attr.h"
#include <map>
#include <array>
#include <vector>
#include <regex>

class relation{
  typedef std::vector<attr*> tuple;
  typedef std::map<tuple, tuple> table;
  int n_keys;
  int n_attr;
  std::string table_name;
  std::vector<std::string> header;	//keys are represented by adding "%" to the front of the attr title
  table t;
  std::vector<std::string> commands; //might not need
  bool meets_condition(std::string condition, std::pair<tuple, tuple> row);
  int header_pos(std::string name);
	bool is_key(int pos); //is_key seemed more appropriate
	bool key_exists(tuple key);


public:
  relation() : n_keys(0), n_attr(0), table_name(""){}
  /*
	constructor takes in a table name and two vector<strings>
	strings of key_header are of the form "attr_name"
	strings of attr_header are of the form "attr_name TYPE" where TYPE can be INTEGER or VARCHAR(int)
  */
  relation(std::string name, std::vector<std::string> key_header, std::vector<std::string> attr_header);
  //~relation();
  void set_name(std::string name); //sets the name of the table
  void set_header(std::vector<std::string> attr_header);
  std::string get_name() const;	//returns the name of the table
  std::vector<std::string> get_header() const;
  void save(); //checks if there exists a .db file and writes all the commands to ceate the table to the file
  void show(); //prints out the content of the string to std::cout
	table get_table();	//returns a copy of its values

  /*
	Will also need get and set functions to access individual rows
  */
  //create_table(); constructor
  //drop_table(); destructor
  bool insert_into(std::vector<std::string> literals);	//
  bool insert_into(relation other_table);	//OH: does this insert ALL the tuples from other_table into "this" table?
  bool update(std::vector<std::string> attr_list, std::vector<std::string> conjunctions);
  bool delete_from(std::vector<std::string> conjunctions);	//
  relation selection(std::vector<std::string> conjunctions);
  relation projection(std::vector<std::string> attr_list);
  relation renaming(std::vector<std::string> attr_list);
  relation set_union(relation other_table);
  relation set_difference(relation other_table);
  relation cross_product(relation other_table);
  relation natural_join(relation other_table);
};

#endif