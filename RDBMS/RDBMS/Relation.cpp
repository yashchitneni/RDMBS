#include "Relation.h"

Relation::Relation(std::string name, std::vector<std::string> key_header,	std::vector<std::string> attr_header){
	n_keys = key_header.size();
	n_attr = attr_header.size() - n_keys;
	table_name = name;
}

void Relation::set_name(std::string name){
	table_name = name;
}

std::string Relation::get_name() const{
	return table_name;
}

bool Relation::meets_condition(std::string condition, std::pair<tuple, tuple> row){
	std::regex reg_all("([\\w_\"]+)(?:\\s*)(==|!=|<=|>=|<|>)(?:\\s*)([\\w_\"]+)");
	std::smatch m;
	if (std::regex_search(condition, m, reg_all)){
		Attribute* op1;
		Attribute* op2;
		std::string operation = m[2].str();
		std::string operand1 = m[1].str();
		std::string operand2 = m[3].str();
		std::printf("Operation: %s\nOperand: %s\nOperand: %s\n", operation.c_str(), operand1.c_str(), operand2.c_str());
		std::regex reg_var_char("\\\".*\\\"");
		if (std::regex_search(operand1, m, reg_var_char)){
			std::printf("Operand1 is a var_char\n");
			op1 = new Var_Char(m.str().substr(0, m.str().size() - 2));
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
				op1 = new Integer(atoi(operand1.c_str()));
			}
		}
		if (std::regex_search(operand2, m, reg_var_char)){
			std::printf("Operand2 is a var_char\n");
			op2 = new Var_Char(m.str().substr(0, m.str().size() - 2));
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
				op2 = new Integer(atoi(operand2.c_str()));
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

int Relation::header_pos(std::string name){
	for (int k = 0; k < header.size(); k++){
		if (header[k] == name)
			return k;
	}
	return -1;
}

void Relation::save(){
	//add function to save the table
}

void Relation::show(){
	//add function to show table
}