#ifndef _RELATION
#define _RELATION

#include "Attributes.h"
#include <map>
#include <array>
#include <vector>
#include <regex>
#include <fstream>

namespace Team_Project_1_Database{

	struct less_attr_pt{
		bool operator() (std::vector<Attribute*> lhs, std::vector<Attribute*> rhs) const;
	};

	class Relation{
		typedef std::vector<Attribute*> tuple;
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
		int find_key(Attribute* attribute, tuple keys);

		static std::vector<std::string> split_condition(std::string condition);
		static std::vector<std::string> split_conjunction(std::string conjunction);

		friend class Relation;
		friend class Grammar;

	public:
		Relation() : n_keys(0), n_attr(0), table_name(""){}

		Relation(
			std::string name,
			std::vector<std::string> key_header,
			std::vector<std::string> attr_header);

		Relation(const Relation& other_table);

		~Relation();

		void set_name(std::string name);

		void insert(std::pair<tuple, tuple> row);

		std::vector<std::string> get_header() const;

		table get_table() const;

		void save();
		void show();

		bool operator== (const Relation& rhs) const;
		bool operator!= (const Relation& rhs) const;

		bool insert_into(std::vector<std::string> literals);
		bool insert_into(Relation other_table);

		bool update(
			std::vector<std::string> attr_list,
			std::vector<std::string> conjunctions);

		bool delete_from(std::vector<std::string> conjunctions);

		Relation* selection(std::vector<std::string> conjunctions);

		Relation* projection(std::vector<std::string> attr_list);

		Relation* renaming(std::vector<std::string> attr_list);

		Relation* set_union(Relation& other_table);

		Relation* set_difference(Relation& other_table);

		Relation* cross_product(Relation& other_table);

		Relation* natural_join(Relation& other_table);
	};
}

#endif