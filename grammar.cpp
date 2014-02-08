#include "grammar.h"
#include <iostream>
#include <cstdio>

void grammar::program(std::string input, std::vector<relation>& tables){
  std::regex reg_semi_colon(";");
  std::regex reg_cmd("OPEN|CLOSE|WRITE|EXIT|SHOW|(CREATE TABLE)|UPDATE|(INSERT INTO)|(DELETE FROM)");
  std::smatch m;
  if (std::regex_search(input, m, reg_semi_colon)){
	input = m.prefix().str();
  }
  else{
	std::printf("No ending semi-colon\n");
	return;
  }
  if (std::regex_search(input, reg_cmd)){
	command(input, tables);
	return;
  }
  query(input, tables);
  return;
}

void grammar::program( std::vector<relation>& tables){
  std::regex reg_semi_colon(";");
  std::regex reg_exit("^\\s*EXIT\\s*;\\s*$");
  std::regex reg_cmd("OPEN|CLOSE|WRITE|EXIT|SHOW|(CREATE TABLE)|UPDATE|(INSERT INTO)|(DELETE FROM)");
  std::smatch m;
  std::printf("Now running DML interpreter, please enter commands/queries\n");
  std::string input;
  while (getline(std::cin, input)){
	if (std::regex_search(input, reg_exit)) return;
	if (std::regex_search(input, m, reg_semi_colon)){
	  input = m.prefix().str();
	}
	else{
	  std::printf("No ending semi-colon, enter again\n");
	  continue;
	}
	if (std::regex_search(input, reg_cmd)){
	  command(input, tables);
	}
	else{
	  query(input, tables);
	}
  }
  return;
}

void grammar::command(std::string input, std::vector<relation>& tables){
  std::regex reg_open("^\\s*OPEN");
  std::regex reg_close("^\\s*CLOSE");
  std::regex reg_write("^\\s*WRITE");
  std::regex reg_show("^\\s*SHOW");
  std::regex reg_create("^\\s*CREATE TABLE");
  std::regex reg_update("^\\s*UPDATE");
  std::regex reg_insert("^\\s*INSERT INTO");
  std::regex reg_delete("^\\s*DELETE FROM");
  std::smatch m;
  if (std::regex_search(input, m, reg_open)){
	std::printf("Open: %s\n", m.suffix().str().c_str());
	std::string arg = m.suffix().str();
	std::regex reg_rel_name("[_[:alpha:]][_\\w]*");
	if (std::regex_search(arg, m, reg_rel_name)){
	  std::string rel_name = m.str(); 
	  open_cmd(rel_name, tables);
	  return;
	}
	std::printf("Unable to process \"%s\" as the argument for open\n", input.c_str());
	return;
  }
  if (std::regex_search(input, m, reg_close)){
	std::printf("Close: %s\n", m.suffix().str().c_str());
	std::string arg = m.suffix().str();
	std::regex reg_rel_name("[_[:alpha:]][_\\w]*");
	if (std::regex_search(arg, m, reg_rel_name)){
	  std::string rel_name = m.str();
	  close_cmd(rel_name, tables);
	  return;
	}
	std::printf("Unable to process \"%s\" as the argument for close\n", input.c_str());
	return;
  }
  if (std::regex_search(input, m, reg_write)){
	std::printf("Write: %s\n", m.suffix().str().c_str());
	std::string arg = m.suffix().str();
	std::regex reg_rel_name("[_[:alpha:]][_\\w]*");
	if (std::regex_search(arg, m, reg_rel_name)){
	  std::string rel_name = m.str();
	  write_cmd(rel_name);
	  return;
	}
	std::printf("Unable to process \"%s\" as the argument for write\n", input.c_str());
	return;
  }
  if (std::regex_search(input, m, reg_show)){
		std::printf("Show: %s\n", m.suffix().str().c_str());
		std::string arg = m.suffix().str();
		relation atomic = atomic_expr(arg, tables);
		show_cmd(atomic);
	return;
  }
  if (std::regex_search(input, m, reg_create)){
		std::printf("Create: %s\n", m.suffix().str().c_str());
		std::regex reg_rel_name("[_[:alpha:]][_\\w]*");
		std::string arg = m.suffix().str();
		if (std::regex_search(arg, m, reg_rel_name)){
			std::cout << m.str() << std::endl;
			std::string rel_name = m.str();
			arg = m.suffix().str();
			std::printf("Relation name: %s\n", rel_name.c_str());
			std::regex reg_key("(?:\\(\\s*)(.*)(?:\\)\\s*)(?:\\s*PRIMARY KEY\\s*)(?:\\(\\s*)(.*)(?:\\s*\\))");
			if (std::regex_search(arg, m, reg_key)){
				std::string attr_list = m[1].str();
				std::string key_list = m[2].str();
				std::printf("Attribute list: %s\nPrimary key: %s\n", attr_list.c_str(), key_list.c_str());
				create_cmd(rel_name, key_list, attr_list, tables);
				return;
			}
		}
		std::printf("Unable to process \"%s\" as the argument for create\n", input.c_str());
		return;
  }
  if (std::regex_search(input, m, reg_update)){
		std::printf("Update: %s\n", m.suffix().str().c_str());
		std::regex reg_rel_name("[_[:alpha:]][_\\w]*");
		std::string arg = m.suffix().str();
		if (std::regex_search(arg, m, reg_rel_name)){
			std::string rel_name = m.str();
			std::printf("Relation name: %s\n", rel_name.c_str());
			arg = m.suffix().str();
			std::regex reg_set("SET");
			if (std::regex_search(arg, m, reg_set)){
				arg = m.suffix().str();
				std::regex reg_attr("WHERE");
				if (std::regex_search(arg, m, reg_attr)){
					std::string attr_list = m.prefix().str();
					std::string condition = m.suffix().str();
					std::printf("Attr: %s\nCondition: %s\n", attr_list.c_str(), condition.c_str());
					update_cmd(rel_name, attr_list, condition, tables);
					return;
				}
			}
		}
		std::printf("Unable to process \"%s\" as the argument for update\n", input.c_str());
		return;
  }
  if (std::regex_search(input, m, reg_insert)){
		std::printf("Insert: %s\n", m.suffix().str().c_str());
		std::regex reg_rel_name("[_[:alpha:]][_\\w]*");
		std::string arg = m.suffix().str();
		if (std::regex_search(arg, m, reg_rel_name)){
			std::string rel_name = m.str();
			int pos = find_relation(rel_name, tables);
			if (pos == -1) return;
			relation* table = &tables[pos];
			arg = m.suffix().str();
			std::regex reg_expr("VALUES FROM RELATION");
			if (std::regex_search(arg, m, reg_expr)){
				std::string expr_arg = m.suffix().str();
				relation other_table = expr(expr_arg, tables);
				std::printf("Relation name: %s\nExpr: %s\n", rel_name.c_str(), expr_arg.c_str());
				insert_cmd(*table, other_table);
				return;
			}
			reg_expr = std::regex("VALUES FROM\\s*\\(");
			if (std::regex_search(arg, m, reg_expr)){
				arg = m.suffix().str();
				reg_expr = std::regex("\\)");
				std::regex_search(arg, m, reg_expr);
				arg = m.prefix().str();
				insert_cmd(*table, arg);
			return;
	  }
	}
	std::printf("Unable to process \"%s\" as the argument for delete\n", input.c_str());
	return;
  }
  if (std::regex_search(input, m, reg_delete)){
		std::printf("Delete: %s\n", m.suffix().str().c_str());
		std::regex reg_rel_name("[_[:alpha:]][_\\w]*");
		std::string arg = m.suffix().str();
		if (std::regex_search(arg, m, reg_rel_name)){
			std::string rel_name = m.str();
			int pos = find_relation(rel_name, tables);
			if (pos == -1) return;
			relation* table = &tables[pos];
			arg = m.suffix().str();
			std::regex reg_cond("WHERE\\s*");
			if (std::regex_search(arg, m, reg_cond)){
				std::string condition = m.suffix().str();
				std::printf("Relation name: %s\nCondition: %s\n", rel_name.c_str(), condition.c_str());
				delete_cmd(*table, condition);
				return;
			}
		}
		std::printf("Unable to process \"%s\" as the argument for delete\n", input.c_str());
		return;
  }
}

void grammar::open_cmd(std::string input, std::vector<relation>& tables){
  std::string file_name = input + ".db";
  std::ifstream table_file(file_name);
  if (table_file.fail()) std::printf("Failed to open table file: %s\n", file_name.c_str());
  else{
	std::printf("Opened: %s\n", file_name.c_str());
	std::string line;
	while (std::getline(table_file, line)){
	  std::printf("%s\n", line.c_str());
	  program(line, tables);
	}
  }
}

void grammar::close_cmd(std::string input, std::vector<relation>& tables){
  int pos = find_relation(input, tables);
  if (pos != -1){
	relation* table = &tables[pos];
	table->save();
	tables.erase(tables.begin() + pos);
  }
}

void grammar::write_cmd(std::string input){
  std::string file_name = input + ".db";
  std::ofstream table_file(file_name);
}

void grammar::show_cmd(relation& table){
  table.show();
}

void grammar::create_cmd(std::string table_name, std::string keys, std::string attrs, std::vector<relation>& tables){
  std::vector<std::string> key_list = split_attr(keys);
  std::vector<std::string> attr_list = split_attr(attrs);
  relation new_relation(table_name, key_list, attr_list);
  tables.push_back(new_relation);
}

void grammar::update_cmd(std::string table_name, std::string attrs, std::string conditions, std::vector<relation>& tables){
  int pos = find_relation(table_name, tables);
  if (pos == -1) return;
  relation* table = &tables[pos];
  std::vector<std::string> attr_list = split_attr(attrs);
  std::vector<std::string> conjunctions = split_condition(conditions);
  //table->update(attr_list, conjunctions);
}

void grammar::insert_cmd(relation& table, relation other_table){
  //table.insert_into(other_table);
}

void grammar::insert_cmd(relation& table, std::string literals){
  std::vector<std::string> literal_list = split_attr(literals);
  table.insert_into(literal_list);
}

void grammar::delete_cmd(relation& table, std::string condition){
  std::vector<std::string> conjunctions = split_condition(condition);
  //table.delete_from(conjunctions);
}

void grammar::query(std::string input, std::vector<relation>& tables){
  std::regex reg_rel_name("\\s*<-\\s*");
  std::smatch m;
  std::regex_search(input, m, reg_rel_name);
  std::string relation_name = m.prefix().str();
  std::string expr_arg = m.suffix().str();
  std::printf("relation-name: %s\nquery: %s\n", relation_name.c_str(), expr_arg.c_str());
  relation new_relation = expr(m.suffix().str(), tables);
  new_relation.set_name(relation_name);
  tables.push_back(new_relation);
}

relation& grammar::expr(std::string input, std::vector<relation>& tables){
  std::printf("\n\nInput: %s\n", input.c_str());
  std::regex reg_select("^\\s*select\\s*");
  std::regex reg_projection("^\\s*project\\s*");
  std::regex reg_renaming("^\\s*rename\\s*");
  std::regex reg_union("\\+\\s*");
  std::regex reg_difference("\\-\\s*");
  std::regex reg_product("\\*\\s*");
  std::regex reg_natural_join("JOIN\\s*");
  std::smatch m;
  if (std::regex_search(input, m, reg_select)){
	std::printf("case: %s\n", "selection");
	std::string arg = m.suffix().str();
	std::regex reg_cond("(?:\\(\\s*)([\\s\\w&\\|!=<>\"]+)(?:\\s*\\))");
	if (std::regex_search(arg, m, reg_cond)){
	  std::string condition = m[1].str();
	  std::printf("condition: %s\natomic: %s\n", condition.c_str(), m.suffix().str().c_str());
	  relation atomic = atomic_expr(m.suffix().str(), tables);
	  return selection(condition, atomic);
	}
	std::printf("Unable to discern select arguments\n");
  }
  if (std::regex_search(input, m, reg_projection)){
	std::printf("case: %s\n", "projection");
	std::string arg = m.suffix().str();
	std::regex reg_attr("\\(\\s*[_[:alpha:]][_\\w]*\\s*(,\\s*[_[:alpha:]][_\\w]*\\s*)*\\)");
	if (std::regex_search(arg, m, reg_attr)){
	  std::string attr_list = m.str().substr(1, m.str().size() - 2);
	  std::printf("attribute list: %s\natomic: %s\n", attr_list.c_str(), m.suffix().str().c_str());
	  relation atomic = atomic_expr(m.suffix().str(), tables);
		return projection(attr_list, atomic);
	}
	std::printf("Unable to discern project arguments\n");
  }
  if (std::regex_search(input, m, reg_renaming)){
	std::printf("case: %s\n", "renaming");
	std::string arg = m.suffix().str();
	std::regex reg_attr("\\(\\s*[_[:alpha:]][_\\w]*\\s*(,\\s*[_[:alpha:]][_\\w]*\\s*)*\\)");
	if (std::regex_search(arg, m, reg_attr)){
	  std::string attr_list = m.str().substr(1, m.str().size() - 2);
	  std::printf("attribute list: %s\natomic: %s\n", attr_list.c_str(), m.suffix().str().c_str());
	  relation atomic = atomic_expr(m.suffix().str(), tables);
		return renaming(attr_list, atomic);
	}
	std::printf("Unable to discern rename arguments\n");
  }
  if (std::regex_search(input, m, reg_union)){
	std::printf("case: %s\n", "union");
	std::string atomic1_str = m.prefix().str();
	std::string atomic2_str = m.suffix().str();
	std::printf("atomic1: %s\natomic2: %s\n", atomic1_str.c_str(), atomic2_str.c_str());
	relation atomic1 = atomic_expr(atomic1_str, tables);
	relation atomic2 = atomic_expr(atomic2_str, tables);
	return table_union(atomic1, atomic2);
	//combine string declaration and relation declaration
  }
  if (std::regex_search(input, m, reg_difference)){
	std::printf("case: %s\n", "difference");
	std::string atomic1_str = m.prefix().str();
	std::string atomic2_str = m.suffix().str();
	std::printf("atomic1: %s\natomic2: %s\n", atomic1_str.c_str(), atomic2_str.c_str());
	relation atomic1 = atomic_expr(atomic1_str, tables);
	relation atomic2 = atomic_expr(atomic2_str, tables);
	return difference(atomic1, atomic2);
	//combine string declaration and relation declaration
  }
  if (std::regex_search(input, m, reg_product)){
	std::printf("case: %s\n", "product");
	std::string atomic1_str = m.prefix().str();
	std::string atomic2_str = m.suffix().str();
	std::printf("atomic1: %s\natomic2: %s\n", atomic1_str.c_str(), atomic2_str.c_str());
	relation atomic1 = atomic_expr(atomic1_str, tables);
	relation atomic2 = atomic_expr(atomic2_str, tables);
	return product(atomic1, atomic2);
	//combine string declaration and relation declaration
  }
  if (std::regex_search(input, m, reg_natural_join)){
	std::printf("case: %s\n", "natural-join");
	std::string atomic1_str = m.prefix().str();
	std::string atomic2_str = m.suffix().str();
	std::printf("atomic1: %s\natomic2: %s\n", atomic1_str.c_str(), atomic2_str.c_str());
	relation atomic1 = atomic_expr(atomic1_str, tables);
	relation atomic2 = atomic_expr(atomic2_str, tables);
	return natural_join(atomic1, atomic2);
	//combine string declaration and relation declaration
  }
  std::printf("atomic-expr: %s\n", input.c_str());
  return atomic_expr(input, tables);
}

relation& grammar::atomic_expr(std::string input, std::vector<relation>& tables){
  std::regex reg_expr("\\(.*\\)");
  std::smatch m;
  if (std::regex_search(input, m, reg_expr)){
		std::string expr_str = m.str().substr(1, m.str().length() - 2);
		std::printf("expr: %s\n", expr_str.c_str());
		return expr(expr_str, tables);
  }
  int pos = find_relation(input, tables);
  if (pos != -1)
		return tables[pos];
  return *(new relation());
}

int grammar::find_relation(std::string input, std::vector<relation>& tables){
  std::regex name("[_[:alpha:]][_\\w]*");
  std::smatch m;
  if (std::regex_search(input, m, name)){
	for (int k = 0; k < tables.size(); k++){
	  if (tables[k].get_name() == m.str())
			return k;
	}
  }
  std::printf("unable to find %s\n", input.c_str());
  return -1;
}

relation& grammar::selection(std::string condition, relation& table){
  std::vector<std::string> conjunctions = split_condition(condition);
	//add function for a table to remove rows that dont meet a vector of conjuctions
	return *(new relation());
}

relation& grammar::projection(std::string attr_list, relation& table){
  std::vector<std::string> attr_names = split_attr(attr_list);
  //add function for a table to remove columns that dont match attr_lists
	return *(new relation());
}

relation& grammar::renaming(std::string attr_list, relation& table){
  std::vector<std::string> attr_names = split_attr(attr_list);
  //add function for a table to rename the columns
  return relation();
}

relation& grammar::table_union(relation& table1, relation& table2){
  //add function for a table to do a union
  return relation();
}

relation& grammar::difference(relation& table1, relation& table2){
  //add function for a table to do a difference
  return relation();
}

relation& grammar::product(relation& table1, relation& table2){
  //add function for a table to do a product
  return relation();
}

relation& grammar::natural_join(relation& table1, relation& table2){
  //add function for a table to do a natural_join
  return relation();
}

std::vector<std::string> grammar::split_attr(std::string attr_list){
  std::vector<std::string> attr_names;
  std::regex reg_attr_name("\\s*,\\s*");
  std::smatch m;
  while (std::regex_search(attr_list, m, reg_attr_name)){
	std::string attr_name = m.prefix().str();
	attr_names.push_back(attr_name);
	attr_list = m.suffix().str();
  }
  attr_names.push_back(attr_list);
  return attr_names;
}

std::vector<std::string> grammar::split_condition(std::string condition){
  std::vector<std::string> conjunctions;
  std::regex reg_conj("\\s*\\|\\|\\s*");
  std::smatch m;
  while (std::regex_search(condition, m, reg_conj)){
	std::string conj = m.prefix().str();
	conjunctions.push_back(conj);
	condition = m.suffix().str();
  }
  conjunctions.push_back(condition);
  return conjunctions;
}