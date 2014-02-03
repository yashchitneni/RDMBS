#ifndef _RELATION
#define _RELATION

#include "attr.h"
#include <map>
#include <array>
#include <vector>

/*
array<attr, num_keys> k
array<attr, num_attr> a
map<k, t> t
*/
class relation{
  const int n_keys;
  const int n_attr;
  std::string table_name;
  void* table;
  std::vector<std::string> commands;

public:
  relation() : n_keys(0), n_attr(0), table_name(""){}
  relation(int num_keys, int num_attr, std::string name);
  void set_name(std::string name);
  std::string get_name() const;
};

#endif