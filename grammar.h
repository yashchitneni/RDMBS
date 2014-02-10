#ifndef _GRAMMAR
#define _GRAMMAR

#include "relation.h"
#include <regex>
#include <fstream>

class grammar{
public:
  /*
  Main function that takes in the entire input then decides if it is a command or query
  calls either the command or query function
  */
  static void program(std::string input, std::vector<relation>& tables);
  static void program(std::vector<relation>& tables);
private:
	friend class relation;
  /*
  Command function that takes input and decides which command should be executed
  */
  static void command(std::string input, std::vector<relation>& tables);
  static void open_cmd(std::string input, std::vector<relation>& tables);
  static void close_cmd(std::string input, std::vector<relation>& tables);
  static void write_cmd(std::string input);
  static void show_cmd(relation& table);
  static void create_cmd(std::string table_name, std::string keys, std::string attrs, std::vector<relation>& tables);
  static void update_cmd(std::string table_name, std::string attrs, std::string conditions, std::vector<relation>& tables);
  static void insert_cmd(relation& table, relation other_table);
  static void insert_cmd(relation& table, std::string literals);
  static  void delete_cmd(relation& table, std::string condition);

  /*
  Query function that takes input and decides what query is wanted
  */
  static void query(std::string input, std::vector<relation>& tables);
  static relation& expr(std::string input, std::vector<relation>& tables);
  static relation& atomic_expr(std::string input, std::vector<relation>& tables);
  static int find_relation(std::string input, std::vector<relation>& tables);
  static relation& selection(std::string condition, relation& table);
  static relation& projection(std::string attr_list, relation& table);
  static relation& renaming(std::string attr_list, relation& table);
  static relation& table_union(relation& table1, relation& table2);
  static  relation& difference(relation& table1, relation& table2);
  static  relation& product(relation& table1, relation& table2);
  static relation& natural_join(relation& table1, relation& table2);

  static std::vector<std::string> split_attr(std::string attrs);
};

#endif