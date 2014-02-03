#include "grammar.h"
#include <iostream>
#include <cstdio>

void grammar::program(std::string input, std::vector<relation>& tables){
  std::regex reg_cmd("OPEN|CLOSE|WRITE|EXIT|SHOW|(CREATE TABLE)|UPDATE|(INSERT INTO)|(DELETE FROM)");
  if (std::regex_search(input, reg_cmd)){
	command(input, tables);
	return;
  }
  query(input, tables);
  return;
}

void grammar::command(std::string input, std::vector<relation>& tables){}
void grammar::open_cmd(std::string input, std::vector<relation>& tables){}
void grammar::close_cmd(std::string input, std::vector<relation>& tables){}
void grammar::write_cmd(std::string input, std::vector<relation>& tables){}
void grammar::exit_cmd(std::string input, std::vector<relation>& tables){}
void grammar::show_cmd(std::string input, std::vector<relation>& tables){}
void grammar::create_cmd(std::string input, std::vector<relation>& tables){}
void grammar::update_cmd(std::string input, std::vector<relation>& tables){}
void grammar::insert_cmd(std::string input, std::vector<relation>& tables){}
void grammar::delete_cmd(std::string input, std::vector<relation>& tables){}

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

relation grammar::expr(std::string input, std::vector<relation>& tables){
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
	std::string select_arg = m.suffix().str();
	std::regex reg_cond("\\([\\s\\w&\\|!=<>\"]+\\)");
	if (std::regex_search(select_arg, m, reg_cond)){
	  std::string condition = m.str().substr(1, m.str().size() - 2);
	  std::printf("condition: %s\natomic: %s\n", condition.c_str(), m.suffix().str().c_str());
	  relation atomic = atomic_expr(m.suffix().str(), tables);
	  return selection(condition, atomic);
	}
	std::printf("Unable to discern select arguments\n");
  }
  if (std::regex_search(input, m, reg_projection)){
	std::printf("case: %s\n", "projection");
	std::string select_arg = m.suffix().str();
	std::regex reg_attr("\\(\\s*[_[:alpha:]][_\\w]*\\s*(,\\s*[_[:alpha:]][_\\w]*\\s*)*\\)");
	if (std::regex_search(select_arg, m, reg_attr)){
	  std::string attr_list = m.str().substr(1, m.str().size() - 2);
	  std::printf("condition: %s\natomic: %s\n", attr_list.c_str(), m.suffix().str().c_str());
	  relation atomic = atomic_expr(m.suffix().str(), tables);
	  return relation();
	}
	std::printf("Unable to discern project arguments\n");
  }
  if (std::regex_search(input, m, reg_renaming)){
	std::printf("case: %s\n", "renaming");
	std::string select_arg = m.suffix().str();
	std::regex reg_attr("\\(\\s*[_[:alpha:]][_\\w]*\\s*(,\\s*[_[:alpha:]][_\\w]*\\s*)*\\)");
	if (std::regex_search(select_arg, m, reg_attr)){
	  std::string attr_list = m.str().substr(1, m.str().size() - 2);
	  std::printf("condition: %s\natomic: %s\n", attr_list.c_str(), m.suffix().str().c_str());
	  relation atomic = atomic_expr(m.suffix().str(), tables);
	  return relation();
	  //add rename function call and return
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
	return relation();
	//combine string declaration and relation declaration
	//add union function call and return
  }
  if (std::regex_search(input, m, reg_difference)){
	std::printf("case: %s\n", "difference");
	std::string atomic1_str = m.prefix().str();
	std::string atomic2_str = m.suffix().str();
	std::printf("atomic1: %s\natomic2: %s\n", atomic1_str.c_str(), atomic2_str.c_str());
	relation atomic1 = atomic_expr(atomic1_str, tables);
	relation atomic2 = atomic_expr(atomic2_str, tables);
	return relation();
	//combine string declaration and relation declaration
	//add difference function call and return
  }
  if (std::regex_search(input, m, reg_product)){
	std::printf("case: %s\n", "product");
	std::string atomic1_str = m.prefix().str();
	std::string atomic2_str = m.suffix().str();
	std::printf("atomic1: %s\natomic2: %s\n", atomic1_str.c_str(), atomic2_str.c_str());
	relation atomic1 = atomic_expr(atomic1_str, tables);
	relation atomic2 = atomic_expr(atomic2_str, tables);
	return relation();
	//combine string declaration and relation declaration
	//add product function call and return
  }
  if (std::regex_search(input, m, reg_natural_join)){
	std::printf("case: %s\n", "natural-join");
	std::string atomic1_str = m.prefix().str();
	std::string atomic2_str = m.suffix().str();
	std::printf("atomic1: %s\natomic2: %s\n", atomic1_str.c_str(), atomic2_str.c_str());
	relation atomic1 = atomic_expr(atomic1_str, tables);
	relation atomic2 = atomic_expr(atomic2_str, tables);
	return relation();
	//combine string declaration and relation declaration
	//add natural-join function call and return
  }
  std::printf("atomic-expr: %s\n", input.c_str());
  return atomic_expr(input, tables);
}

relation grammar::atomic_expr(std::string input, std::vector<relation>& tables){
  std::regex reg_expr("\\(.*\\)");
  std::smatch m;
  if (std::regex_search(input, m, reg_expr)){
	std::string expr_str = m.str().substr(1, m.str().length() - 2);
	std::printf("expr: %s\n", expr_str.c_str());
	return expr(expr_str, tables);
  }
  return find_relation(input, tables);
}

relation grammar::find_relation(std::string input, std::vector<relation>& tables){
  std::regex name("[:alpha:]\\w*");
  std::smatch m;
  if (std::regex_search(input, m, name)){
	for (auto x : tables){
	  if (x.get_name() == m.str())
		return x;
	}
  }
  std::printf("unable to find %s\n", input.c_str());
  return relation();
}

relation grammar::selection(std::string condition, relation table){
  std::vector<std::string> conjunctions;
  std::regex reg_conj("\\s*\\|\\|\\s*");
  std::smatch m;
  while (std::regex_search(condition, m, reg_conj)){
	std::string conj = m.prefix().str();
	conjunctions.push_back(conj);
	condition = m.suffix().str();
  }
  conjunctions.push_back(condition);
  //add function for a table to remove rows that dont meet a vector of conjuctions
  return relation();
}

relation grammar::projection(std::string attr_list, relation table){
  std::vector<std::string> attr_names;
  std::regex reg_attr_name("\\s*,\\s*");
  std::smatch m;
  while (std::regex_search(attr_list, m, reg_attr_name)){
	std::string attr_name = m.prefix().str();
	attr_names.push_back(attr_name);
	attr_list = m.suffix().str();
  }
  attr_names.push_back(attr_list);
  //add function for a table to remove columns that dont match attr_lists
  return relation();
}

relation grammar::renaming(std::string attr_list, relation table){
  std::vector<std::string> attr_names;
  std::regex reg_attr_name("\\s*,\\s*");
  std::smatch m;
  while (std::regex_search(attr_list, m, reg_attr_name)){
	std::string attr_name = m.prefix().str();
	attr_names.push_back(attr_name);
	attr_list = m.suffix().str();
  }
  attr_names.push_back(attr_list);
  //add function for a table to rename the columns
  return relation();
}

relation grammar::table_union(relation table1, relation table2){
  //add function for a table to do a union
  return relation();
}

relation grammar::difference(relation table1, relation table2){
  //add function for a table to do a difference
  return relation();
}

relation grammar::product(relation table1, relation table2){
  //add function for a table to do a product
  return relation();
}

relation grammar::natural_join(relation table1, relation table2){
  //add function for a table to do a natural_join
  return relation();
}