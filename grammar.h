#ifndef _GRAMMAR
#define _GRAMMAR

#include "relation.h"
#include <regex>

struct grammar{
  /*
  Main function that takes in the entire input then decides if it is a command or query
  calls either the command or query function
  */
  static void program(std::string input, std::vector<relation>& tables);
private:
  /*
  Command function that takes input and decides which command should be executed
  */
  static void command(std::string input, std::vector<relation>& tables);
  static void open_cmd(std::string input, std::vector<relation>& tables);
  static void close_cmd(std::string input, std::vector<relation>& tables);
  static void write_cmd(std::string input, std::vector<relation>& tables);
  static void exit_cmd(std::string input, std::vector<relation>& tables);
  static void show_cmd(std::string input, std::vector<relation>& tables);
  static void create_cmd(std::string input, std::vector<relation>& tables);
  static void update_cmd(std::string input, std::vector<relation>& tables);
  static void insert_cmd(std::string input, std::vector<relation>& tables);
  static  void delete_cmd(std::string input, std::vector<relation>& tables);

  /*
  Query function that takes input and decides what query is wanted
  */
  static void query(std::string input, std::vector<relation>& tables);
  static relation expr(std::string input, std::vector<relation>& tables);
  static relation atomic_expr(std::string input, std::vector<relation>& tables);
  static relation find_relation(std::string input, std::vector<relation>& tables);
  static relation selection(std::string condition, relation table);
  static relation projection(std::string attr_list, relation table);
  static relation renaming(std::string attr_list, relation table);
  static relation table_union(relation table1, relation table2);
  static  relation difference(relation table1, relation table2);
  static  relation product(relation table1, relation table2);
  static relation natural_join(relation table1, relation table2);
};

#endif