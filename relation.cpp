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

void relation::set_header(std::vector<std::string> attr_header){
	header = attr_header;
}

std::string relation::get_name() const{
  return table_name;
}

std::vector<std::string> relation::get_header() const{
	return header;
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
		op1 = row.second[pos];
		printf("%d\n", op1->get_class());
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
	delete op1; //these cause my iterator within my update function to break. will we need to delete these values?
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

int relation::find_key(attr* attribute, tuple keys){
	for (int k = 0; k < keys.size(); k++){
		if (*keys[k] == *attribute)
			return k;
	}
	return -1;
}

bool relation::is_key(int pos){
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
		if (is_key(k))
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
				if (is_key(k))
					new_keys.push_back(new_row[k]);
			}
		}
	}
	return true;
}

bool relation::update(std::vector<std::string> attr_list, std::vector<std::string> conjunctions){ //need to implement recursive descent parser for the comparisons....
	std::vector<std::string> comparisons;
	std::regex reg_amp("([\\w_\"\\s*(==|!=|<=|>=|<|>)]+)(?:\\s*)(&&|\|\|)(?:\\s*)([\\w_\"\\s*(==|!=|<=|>=|<|>)]+)*");
	std::smatch amp_match;

	//Split conjunctions into individual comparisons
	for (auto conj_iter = conjunctions.begin(); conj_iter != conjunctions.end(); ++conj_iter){
		if (std::regex_search(*conj_iter, amp_match, reg_amp)) {
			for (auto match_iter = amp_match.begin(); match_iter != amp_match.end(); ++match_iter){
				comparisons.push_back(*match_iter);
			}
		}
		else{
			return false;
		}
	}

	std::vector<std::pair<tuple, tuple>> new_rows;
	//Check which rows satisfy the condition of the comparisons, then modify said rows according to attr_list
	//for (auto row_iter = t.begin(); row_iter != t.end(); ++row_iter){
	auto row_iter = t.begin();
	while (row_iter != t.end()){

		for (auto comp_iter = comparisons.begin(); comp_iter != comparisons.end(); ++comp_iter){

			if (this->meets_condition(*comp_iter, *row_iter)){
				std::vector<std::pair<std::string, attr*>> changes;
				std::regex reg_equal("([\\w_\"]+)(?:\\s*=\\s*)([\\w_\"]+)");
				std::smatch equ_match;

				for (auto attr_iter = attr_list.begin(); attr_iter != attr_list.end(); ++attr_iter){

					if (std::regex_search(*attr_iter, equ_match, reg_equal)){
						printf("265\n");
						std::string attr_name = equ_match[1].str();
						std::string attr_string = equ_match[2].str();
						attr* attribute;

						if (attr_string.size() >= 2 && isalpha(attr_string[1])){
							attribute = new var_char(attr_string.substr(1,attr_string.size()-2));
						}
						else {
							attribute = new integer(atoi(attr_string.c_str()));
						}

						changes.push_back(std::make_pair(std::string(attr_name), attribute));
					}
				}

				tuple new_key;
				tuple new_row = row_iter->second;
				bool key_changed = false;

				for (auto change_iter = changes.begin(); change_iter != changes.end(); ++change_iter){
					std::string& attr_name = change_iter->first;
					if (this->is_key(this->header_pos(attr_name))){
						int key_pos = this->find_key(row_iter->second[this->header_pos(attr_name)], row_iter->first);

						for (int x = 0; x < row_iter->first.size(); ++x){
							if (x != key_pos){
								new_key.push_back(row_iter->first[x]);
							}
						}
						new_row[this->header_pos(attr_name)] = change_iter->second;
						key_changed = true;
					}
				}

				if (key_changed){
					new_rows.push_back(std::make_pair(new_key, new_row));
					t.erase(row_iter++);
				}
				else{
					++row_iter;
				}
			}
		}
	}

	for (auto new_row_it = new_rows.begin(); new_row_it != new_rows.end(); ++new_row_it){
		t[new_row_it->first] = new_row_it->second;
	}
	return true;
}

relation relation::projection(std::vector<std::string> attr_list){
	std::vector<int> attrib_positions;
	std::vector<std::string> projection_header;
	relation projection;

	//Finds column positions (placed into attrib_positions) to access when projecting the relation
	for (auto attr_iter = attr_list.begin(); attr_iter != attr_list.end(); ++attr_iter){
		int position = this->header_pos(*attr_iter);

		if (position != -1) {
			attrib_positions.push_back(position);
			projection_header.push_back(header[position]);
		}
		else {
			std::printf("%s does not match an attribute in %s! Cannot project!", *attr_iter, this->get_name());
			return relation(); //only way I could see to exit gracefully
		}
	}

	projection.set_header(projection_header);

	//For each projected column, push the attribute at that position from original row to the new row, then add the row to the new relation's table
	for (auto table_iter = t.begin(); table_iter != t.end(); ++table_iter){
		relation::tuple projection_row;
		relation::tuple keys;
		
		for (auto attrib_iter = attrib_positions.begin(); attrib_iter != attrib_positions.end(); ++attrib_iter){

			if (this->is_key(*attrib_iter)) {
				keys.push_back(table_iter->second[*attrib_iter]);
			}

			projection_row.push_back(table_iter->second[*attrib_iter]);
		}

		if (keys.size() == 0){
			keys.push_back(projection_row[0]);
		}

		projection.get_table()[keys] = projection_row;
	}
	return projection;
}

relation relation::set_union(relation other_table){
	relation new_relation;

	//Check for union compatibility

	//Compare each row of relation 1 with each row of relation 2, inserting all distinct rows and only 1 of matching rows.

	return relation(); //placeholder
}
relation relation::set_difference(relation other_table){
	relation new_relation;

	//Check for union compatibility

	//Compare each row of relation 1 with each row of relation 2, inserting all distinct rows and only 1 of matching rows.

	return relation(); //placeholder
}

relation relation::natural_join(relation other_table){
	return relation();
}