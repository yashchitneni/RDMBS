#ifndef _RELATION
#define _RELATION

#include "attr.h"
#include <map>
#include <array>
#include <vector>

class relation{
  typedef std::vector<attr*> key;
  typedef std::vector<attr*> tuple;
  typedef std::map<key, tuple> table;
  const int n_keys;
  const int n_attr;
  std::string table_name;
  std::vector<std::string> header;
  table t;
  std::vector<std::string> commands; //might not need

public:
  relation() : n_keys(0), n_attr(0), table_name(""){}
  relation(int num_keys, int num_attr, std::string name);
  void set_name(std::string name);
  std::string get_name() const;
};

#endif