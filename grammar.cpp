#include "grammar.h"

void program(std::string input, std::vector<relation>& tables, std::vector<relation>& views){
  std::regex reg_cmd("");
}

void command(std::string input, std::vector<relation>& tables);
void open_cmd(std::string input, std::vector<relation>& tables);
void close_cmd(std::string input, std::vector<relation>& tables);
void write_cmd(std::string input, std::vector<relation>& tables);
void exit_cmd(std::string input, std::vector<relation>& tables);
void show_cmd(std::string input, std::vector<relation>& tables);
void create_cmd(std::string input, std::vector<relation>& tables);
void update_cmd(std::string input, std::vector<relation>& tables);
void insert_cmd(std::string input, std::vector<relation>& tables);
void delete_cmd(std::string input, std::vector<relation>& tables);
void query(std::string input, std::vector<relation>& tables);
relation expr(std::string input, std::vector<relation>& tables);
relation atomic(std::string input, std::vector<relation>& tables);
relation selection(std::string input, std::vector<relation>& tables);
relation projection(std::string input, std::vector<relation>& tables);
relation renaming(std::string input, std::vector<relation>& tables);
relation table_union(std::string input, std::vector<relation>& tables);
relation difference(std::string input, std::vector<relation>& tables);
relation product(std::string input, std::vector<relation>& tables);
relation natural_join(std::string input, std::vector<relation>& tables);
