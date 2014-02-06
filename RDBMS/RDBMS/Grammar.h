#ifndef _GRAMMAR
#define _GRAMMAR

#include "Relation.h"
#include <regex>
#include <fstream>

class Grammar{
public:
	/*
	Main function that takes in the entire input then decides if it is a command or query
	calls either the command or query function
	*/
	static void program(std::string input, std::vector<Relation>& tables);
	static void program(std::vector<Relation>& tables);
private:
	/*
	Command function that takes input and decides which command should be executed
	*/
	static void command(std::string input, std::vector<Relation>& tables);
	static void open_cmd(std::string input, std::vector<Relation>& tables);
	static void close_cmd(std::string input, std::vector<Relation>& tables);
	static void write_cmd(std::string input);
	static void show_cmd(Relation table);
	static void create_cmd(std::string table_name, std::string keys, std::string attrs, std::vector<Relation>& tables);
	static void update_cmd(std::string table_name, std::string attrs, std::string conditions, std::vector<Relation>& tables);
	static void insert_cmd(Relation table, Relation other_table);
	static void insert_cmd(Relation table, std::string literals);
	static void delete_cmd(Relation table, std::string condition);

	/*
	Query function that takes input and decides what query is wanted
	*/
	static void query(std::string input, std::vector<Relation>& tables);
	static Relation expr(std::string input, std::vector<Relation>& tables);
	static Relation atomic_expr(std::string input, std::vector<Relation>& tables);
	static int find_relation(std::string input, std::vector<Relation>& tables);
	static Relation selection(std::string condition, Relation table);
	static Relation projection(std::string attr_list, Relation table);
	static Relation renaming(std::string attr_list, Relation table);
	static Relation table_union(Relation table1, Relation table2);
	static Relation difference(Relation table1, Relation table2);
	static Relation product(Relation table1, Relation table2);
	static Relation natural_join(Relation table1, Relation table2);

	static std::vector<std::string> split_attr(std::string attrs);
	static std::vector<std::string> split_condition(std::string condition);
};

#endif