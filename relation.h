#ifndef _RELATION
#define _RELATION

#include "attr.h"
#include <map>
#include <array>
#include <vector>
#include <regex>
#include <fstream>


struct less_attr_pt{
	bool operator() (std::vector<attr*> lhs, std::vector<attr*> rhs) const;
};

class relation{
  typedef std::vector<attr*> tuple;
  typedef std::map<tuple, tuple, less_attr_pt> table;

  int n_keys;
  int n_attr;
  std::string table_name;
  std::vector<std::string> header;
  table t;

  bool meets_condition(
	  std::string condition,
	  std::pair<tuple, tuple> row);

  bool meets_conjunction(
	  std::string conjunction,
	  std::pair<tuple, tuple> row);
  
  int header_pos(std::string name);
  bool is_key(int pos);
  int find_key(attr* attribute, tuple keys);
  
  static std::vector<std::string> split_condition(std::string condition);
  static std::vector<std::string> split_conjunction(std::string conjunction);
  
  friend class relation;
  friend class grammar;

public:
  relation() : n_keys(0), n_attr(0), table_name(""){}

  relation(
	  std::string name,
	  std::vector<std::string> key_header,
	  std::vector<std::string> attr_header);

  relation(const relation& other_table);
  
  ~relation();

  void set_name(std::string name);
  
  void insert(std::pair<tuple, tuple> row);
  
  table get_table() const;

  void save();
  void show();

  bool insert_into(std::vector<std::string> literals);
  bool insert_into(relation other_table);

  bool update(
	  std::vector<std::string> attr_list,
	  std::vector<std::string> conjunctions);

  bool delete_from(std::vector<std::string> conjunctions);

  relation* selection(std::vector<std::string> conjunctions);

  relation* projection(std::vector<std::string> attr_list);

  relation* renaming(std::vector<std::string> attr_list);

  relation* set_union(relation& other_table);

  relation* set_difference(relation& other_table);

  relation* cross_product(relation& other_table);

  relation* natural_join(relation& other_table);
};

#endif