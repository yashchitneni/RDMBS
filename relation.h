#ifndef _RELATION
#define _RELATION

#include "attr.h"
#include <map>
#include <array>
#include <vector>

class relation{
  typedef std::vector<attr*> tuple;
  typedef std::map<tuple, tuple> table;
  int n_keys;
  int n_attr;
  std::string table_name;
  std::vector<std::string> header;
  table t;
  std::vector<std::string> commands; //might not need
  static bool meets_condition(std::string condition, std::pair<tuple, tuple> row);


public:
  relation() : n_keys(0), n_attr(0), table_name(""){}
  relation(int num_keys, int num_attr, std::string name);
  ~relation();
  void set_name(std::string name);
  std::string get_name() const;
  //create_table(); constructor
  //drop_table(); destructor
  bool insert_into(std::vector<std::string> literals);
  bool insert_into(relation table);
  bool update(std::vector<std::string> attr_list, std::vector<std::string> conjunctions);
  bool delete_from(std::vector<std::string> conjunctions);
  relation selection(std::vector<std::string> conjunctions);
  relation projection(std::vector<std::string> attr_list);
  relation renaming(std::vector<std::string> attr_list);
  relation set_union(relation table);
  relation set_difference(relation table);
  relation cross_product(relation table);
  relation natural_join(relation table);
};

#endif