#include "relation.h"

relation::relation(std::string name, std::vector<std::string> key_header, std::vector<std::string> attr_header){
  n_keys = key_header.size();
  n_attr = attr_header.size();
  table_name = name;
	std::regex reg_header("([_[:alpha:]][_\\w]*)(?:\\s*(INTEGER|VARCHAR))");
	std::smatch m;
	for (auto x : attr_header){
		if (std::regex_search(x, m, reg_header)){
			std::string header_name = m[1].str();
			header.push_back(header_name);
		}
	}
	for (auto x : key_header){
		int pos = header_pos(x);
		if (pos != -1){
			header[pos] = "%" + header[pos];
		}
	}
}

void relation::set_name(std::string name){
  table_name = name;
}

std::string relation::get_name() const{
  return table_name;
}

relation::table relation::get_table(){
	return t;
}

bool relation::meets_condition(std::string condition, std::pair<tuple, tuple> row){
	std::regex reg_all("([\\w_\"]+)(?:\\s*)(==|!=|<=|>=|<|>)(?:\\s*)([\\w_\"]+)");
  std::smatch m;
  if (std::regex_search(condition, m, reg_all)){
	attr* op1;
	attr* op2;
	std::string operation = m[2].str();
	std::string operand1 = m[1].str();
	std::string operand2 = m[3].str();
	std::printf("Operand: %s\nOperand: %s\n", operand1.c_str(), operand2.c_str());
	std::regex reg_var_char("\\\".*\\\"");
	if (std::regex_search(operand1, m, reg_var_char)){
	  std::printf("Operand1 is a var_char\n");
	  op1 = new var_char(m.str().substr(0, m.str().size() - 2));
	}
	else{
	  int pos = header_pos(operand1);
	  if (pos != -1){
		std::printf("Operand1 is a attr header\n");
		if (pos < n_keys) op1 = row.first[pos];
		else op1 = row.second[pos - n_keys];
	  }
	  else{
		std::printf("Operand1 is an int\n");
		op1 = new integer(atoi(operand1.c_str()));
	  }
	}
	if (std::regex_search(operand2, m, reg_var_char)){
	  std::printf("Operand2 is a var_char\n");
	  op2 = new var_char(m.str().substr(0, m.str().size() - 2));
	}
	else{
	  int pos = header_pos(operand2);
	  if (pos != -1){
		std::printf("Operand2 is a attr header\n");
		if (pos < n_keys) op2 = row.first[pos];
		else op2 = row.second[pos - n_keys];
	  }
	  else{
		std::printf("Operand2 is an int\n");
		op2 = new integer(atoi(operand2.c_str()));
	  }
	}
	if (op1->get_class() != op2->get_class()){
	  std::printf("Cant compare: objects are not the same type\n");
	  return false;
	}
	std::regex reg_equal("\\s*==\\s*");
	std::regex reg_not_equal("\\s*!=\\s*");
	std::regex reg_less("\\s*<\\s*");
	std::regex reg_greater("\\s*>\\s*");
	std::regex reg_less_equal("\\s*<=\\s*");
	std::regex reg_greater_equal("\\s*>=\\s*");
	bool out;
	if (std::regex_search(condition, m, reg_equal)){
	  std::printf("Operation: Equal\n");
	  out = (*op1 == *op2);
	}
	else if (std::regex_search(condition, m, reg_not_equal)){
	  std::printf("Operation: Not Equal\n");
	  out = !(*op1 == *op2);
	}
	else if (std::regex_search(condition, m, reg_less_equal)){
	  std::printf("Operation: Less Than\n");
	  out = !(*op2 < *op1);
	}
	else if (std::regex_search(condition, m, reg_greater_equal)){
	  std::printf("Operation: Greater Than\n");
	  out = !(*op1 < *op2);
	}
	else if (std::regex_search(condition, m, reg_less)){
	  std::printf("Operation: Less Than Equal\n");
	  out = (*op1 < *op2);
	}
	else if (std::regex_search(condition, m, reg_greater)){
	  std::printf("Operation: Greater Than Equal\n");
	  out = (*op2 < *op1);
	}
	std::printf("\n\n");
	delete op1;
	delete op2;
	return out;
  }
  return false;
}

int relation::header_pos(std::string name){
  for (int k = 0; k < header.size(); k++){
		if (header[k] == name || (header[k] == "%" + name))
	  return k;
  }
  return -1;
}

bool relation::is_header(int pos){
	if (header[pos][0] == '%'){
		return true;
	}
	return false;
}

bool relation::key_exists(tuple key){
	for (auto x : t){
		for (int k = 0; k < key.size(); k++){
			if (*(x.first[k]) != *(key[k]))
				break;
			if (k == key.size() - 1)
				return true;
		}
	}
	return false;
}

void relation::save(){
  //add function to save the table
}

void relation::show(){
	std::printf("TABLE NAME: %s\n", table_name.c_str());
	for (auto x : header){
		/*
		if (x[0] == '%')
			std::printf("%15s", x.substr(1, x.size()-1).c_str());
		else
		*/
			std::printf("%15s", x.c_str());
	}
	std::printf("\n");
	for (auto row : t){
		for (auto a : row.second){
			std::printf("%15s", a->get_value().c_str());
		}
		std::printf("\n");
	}
	std::printf("\n");
}

bool relation::insert_into(std::vector<std::string> literals){
	std::regex reg_var("(?:\")([\\w\\s]+)(?:\")");
	std::smatch m;
	tuple keys;
	tuple attrs;
	for (auto x : literals){
		attr* new_attr;
		if (std::regex_search(x, m, reg_var)){
			new_attr = new var_char(m[1].str());
		}
		else{
			new_attr = new integer(atoi(x.c_str()));
		}
		attrs.push_back(new_attr);
	}
	for (int k = 0; k < header.size(); k++){
		if (is_header(k))
			keys.push_back(attrs[k]);
	}
	if (!key_exists(keys)){
		t[keys] = attrs;
		return true;
	}
	return false;
}

bool relation::insert_into(relation other_table){
	table other_t = other_table.get_table();
	tuple new_row;
	tuple new_keys;
	for (auto x : other_t){
		if (t.find(x.first) != t.end()){
			for (auto attrs : x.second){
				attr* new_attr;
				if (attrs->get_class() == attr::attr_type::INTEGER){
					integer* temp = dynamic_cast<integer*>(attrs);
					new_attr = new integer(*temp);
				}
				else{
					var_char* temp = dynamic_cast<var_char*>(attrs);
					new_attr = new var_char(*temp);
				}
				new_row.push_back(new_attr);
			}
			for (int k = 0; k < new_row.size(); k++){
				if (is_header(k))
					new_keys.push_back(new_row[k]);
			}
		}
	}
	return true;
}