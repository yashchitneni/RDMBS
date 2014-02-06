#ifndef _GRAMMAR
#define _GRAMMAR

#include "Relation.h"
#include <regex>

struct Grammar{
	/*
	Main function that takes in the entire input then decides if it is a command or query
	calls either the command or query function
	*/
	static void program(
		std::string input,
		std::vector<Relation>& tables);
private:
	/*
	Command function that takes input and decides which command should be executed
	*/
	static void command(
		std::string input,
		std::vector<Relation>& tables);
	
	static void open_cmd(
		std::string input,
		std::vector<Relation>& tables);
	
	static void close_cmd(
		std::string input,
		std::vector<Relation>& tables);
	
	static void write_cmd(
		std::string input,
		std::vector<Relation>& tables);
	
	static void exit_cmd(
		std::string input,
		std::vector<Relation>& tables);
	
	static void show_cmd(
		std::string input,
		std::vector<Relation>& tables);
	
	static void create_cmd(
		std::string input,
		std::vector<Relation>& tables);
	
	static void update_cmd(
		std::string input,
		std::vector<Relation>& tables);
	
	static void insert_cmd(
		std::string input,
		std::vector<Relation>& tables);
	
	static void delete_cmd(
		std::string input,
		std::vector<Relation>& tables);

	/*
	Query function that takes input and decides what query is wanted
	*/
	static void query(
		std::string input,
		std::vector<Relation>& tables);

	static Relation expr(
		std::string input,
		std::vector<Relation>& tables);
	
	static Relation atomic_expr(
		std::string input,
		std::vector<Relation>& tables);
	
	static Relation find_relation(
		std::string input,
		std::vector<Relation>& tables);
	
	static Relation selection(
		std::string condition,
		Relation table);
	
	static Relation projection(
		std::string attr_list,
		Relation table);
	
	static Relation renaming(
		std::string attr_list,
		Relation table);
	
	static Relation table_union(
		Relation table1,
		Relation table2);
	
	static Relation difference(
		Relation table1,
		Relation table2);
	
	static Relation product(
		Relation table1,
		Relation table2);
	
	static Relation natural_join(
		Relation table1,
		Relation table2);
};

#endif