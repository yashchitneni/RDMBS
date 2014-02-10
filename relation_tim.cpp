#include "relation_tim.h"

bool less_attr_pt::operator() (std::vector<attr*> lhs, std::vector<attr*> rhs) const {
	for (unsigned int k = 0; k < lhs.size() && k < rhs.size(); k++){
		if (*(lhs[k]) < *(rhs[k]))
			return true;
		if (*(lhs[k]) == *(rhs[k]))
			continue;
		else
			return false;
	}
	return false;
}

/*
	constructor takes in a table name and two vector<strings>
	strings of key_header are of the form "attr_name"
	strings of attr_header are of the form "attr_name TYPE" where TYPE can be INTEGER or VARCHAR(int)
*/
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

/*
	copy constructor
*/
relation::relation(const relation& other_table){
	table other_t = other_table.get_table();
	std::vector<std::string> other_header = other_table.header;
	n_keys = other_table.n_keys;
	n_attr = other_table.n_attr;
	table_name = other_table.table_name;
	for (auto x : other_header){
		header.push_back(x);
	}
	for (auto x: other_t){
		tuple new_row;
		tuple new_keys;
		tuple other_attr = x.second;
		for (unsigned int k = 0; k < other_attr.size(); k++){
			attr* new_attr;
			if (other_attr[k]->get_class() == attr::attr_type::INTEGER){
				integer* temp = dynamic_cast<integer*>(other_attr[k]);
				new_attr = new integer(*temp);
			}
			else{
				var_char* temp = dynamic_cast<var_char*>(other_attr[k]);
				new_attr = new var_char(*temp);
			}
			new_row.push_back(new_attr);
			if (is_key(k)){
				new_keys.push_back(new_attr);
			}
		}
		t.insert(std::pair<tuple, tuple>(new_keys, new_row));
	}
}

/*
	destructor
	*/
relation::~relation(){
	for (auto x : t){
		for (auto a : x.second){
			delete a;
		}
	}
}

bool relation::meets_condition(std::string condition, std::pair<tuple, tuple> row){
	std::regex reg_cond("^(?:\\()(.*)(?:\\))$");
	std::regex reg_all("([\\w_]+|\\\".*\\\")(?:\\s*)(==|!=|<=|>=|<|>)(?:\\s*)([\\w_]+|\\\".*\\\")");
	std::smatch m;
	if (std::regex_search(condition, m, reg_cond)){
		std::vector<std::string> conjunctions = split_condition(m[1].str());
		for (auto conj : conjunctions){
			if (meets_conjunction(conj, row))
				continue;
			return false;
		}
		return true;
	}
	else if (std::regex_search(condition, m, reg_all)){
		attr* op1;
		attr* op2;
		std::string operation = m[2].str();
		std::string operand1 = m[1].str();
		std::string operand2 = m[3].str();
		std::regex reg_var_char("(?:\\\")(.*)(?:\\\")");

		if (std::regex_search(operand1, m, reg_var_char)){
			op1 = new var_char(m[1].str());
		}
		else{
			int pos = header_pos(operand1);
			if (pos != -1){
				if (row.second[pos]->get_class() == attr::attr_type::INTEGER)
					op1 = new integer(*dynamic_cast<integer*>(row.second[pos]));
				else
					op1 = new var_char(*dynamic_cast<var_char*>(row.second[pos]));
			}
			else{
				op1 = new integer(atoi(operand1.c_str()));
				if (op1->get_value() != operand1.c_str())
					return false;
			}
		}

		if (std::regex_search(operand2, m, reg_var_char)){
			op2 = new var_char(m[1].str());
		}
		else{
			int pos = header_pos(operand2);
			if (pos != -1){
				if (row.second[pos]->get_class() == attr::attr_type::INTEGER)
					op2 = new integer(*dynamic_cast<integer*>(row.second[pos]));
				else
					op2 = new var_char(*dynamic_cast<var_char*>(row.second[pos]));
			}
			else{
				op2 = new integer(atoi(operand2.c_str()));
				if (op2->get_value() != operand2.c_str())
					return false;
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
			out = (*op1 == *op2);
		}
		else if (std::regex_search(condition, m, reg_not_equal)){
			out = !(*op1 == *op2);
		}
		else if (std::regex_search(condition, m, reg_less_equal)){
			out = !(*op2 < *op1);
		}
		else if (std::regex_search(condition, m, reg_greater_equal)){
			out = !(*op1 < *op2);
		}
		else if (std::regex_search(condition, m, reg_less)){
			out = (*op1 < *op2);
		}
		else if (std::regex_search(condition, m, reg_greater)){
			out = (*op2 < *op1);
		}
		delete op1;
		delete op2;
		return out;
	}
	return false;
}

bool relation::meets_conjunction(std::string conjunction, std::pair<tuple, tuple> row){
	std::vector<std::string> compares = split_conjunction(conjunction);
	for (unsigned int j = 0; j < compares.size(); j++){
		if (meets_condition(compares[j], row)){
			if (j == compares.size() - 1){
				return true;
			}
			continue;
		}
		break;
	}
	return false;
}

int relation::header_pos(std::string name){
	for (unsigned int k = 0; k < header.size(); k++){
		if (header[k] == name || (header[k] == "%" + name))
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

std::vector<std::string> relation::split_condition(std::string condition){
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

std::vector<std::string> relation::split_conjunction(std::string conjunction){
	std::regex reg_compare("\\s*&&\\s*");
	std::smatch m;
	std::vector<std::string> compares;
	while (std::regex_search(conjunction, m, reg_compare)){
		compares.push_back(m.prefix().str());
		conjunction = m.suffix().str();
	}
	compares.push_back(conjunction);
	return compares;
}

void relation::set_name(std::string name){
  table_name = name;
}

void relation::insert(std::pair<std::vector<attr*>, std::vector<attr*>> row){
	t.insert(row);
}

relation::table relation::get_table() const{
	return t;
}

void relation::save(){
  //add function to save the table
}

void relation::show(){
	std::printf("TABLE NAME: %s\n", table_name.c_str());
	for (auto x : header){
		if (x[0] == '%')
			std::printf("%15s", x.substr(1, x.size()-1).c_str());
		else
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
	for (unsigned int k = 0; k < header.size(); k++){
		if (is_key(k))
			keys.push_back(attrs[k]);
	}
	t.insert(std::pair<std::vector<attr*>, std::vector<attr*>>(keys, attrs));
	return true;
}

bool relation::insert_into(relation other_table){
	for (auto x : other_table.t){
		tuple new_row;
		tuple new_keys;
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
		for (unsigned int k = 0; k < new_row.size(); k++){
			if (is_key(k)){
				new_keys.push_back(new_row[k]);
			}
		}
		t.insert(std::pair<std::vector<attr*>, std::vector<attr*>>(new_keys, new_row));
	}
	return true;
}

bool relation::update(std::vector<std::string> attr_list, std::vector<std::string> conjunctions){
	std::regex reg_amp("\\s*&&\\s*");
	std::regex reg_equal("([_[:alpha:]][_\\w*]+)(?:\\s*=\\s*)(?:\"?)(\\w*)(?:\"?)");
	std::smatch m;
	std::vector<std::pair<int, std::string>> changes;
	for (auto attr_iter = attr_list.begin(); attr_iter != attr_list.end(); ++attr_iter){
		if (std::regex_search(*attr_iter, m, reg_equal)){
			std::string attr_name = m[1].str();
			std::string attr_string = m[2].str();
			int pos_header = header_pos(attr_name);
			if (pos_header != -1)
				changes.push_back(std::pair<int, std::string>(pos_header, attr_string));
		}
	}
	for (auto conj : conjunctions){
		std::vector<std::string> compares;
		while (std::regex_search(conj, m, reg_amp)){
			compares.push_back(m.prefix().str());
			conj = m.suffix().str();
		}
		compares.push_back(conj);
		for (auto row_iter = t.begin(); row_iter != t.end(); ++row_iter){
			bool update_row = true;
			for (auto comp_iter = compares.begin(); comp_iter != compares.end() && update_row; ++comp_iter){
				if (!meets_condition(*comp_iter, *row_iter)){
					update_row = false;
				}
			}
			if (update_row){
				for (auto update_attr : changes){
					int pos_header = update_attr.first;
					std::string new_value = update_attr.second;
					row_iter->second[pos_header]->set_value(new_value);
					if (row_iter->second[pos_header]->get_value() != new_value)
						std::printf("Error updating value\n");
				}
			}
		}
	}
	return true;
}

bool relation::delete_from(std::vector<std::string> conjunctions){
	for (auto conj : conjunctions){
		for (auto row: t){
			if (meets_conjunction(conj, row)){
				t.erase(t.find(row.first));
			}
		}
	}
	return true;
}

relation* relation::selection(std::vector<std::string> conjunctions){
    
	std::vector<std::string>::iterator it1 = header.begin();
	std::vector<std::string> new_key_header;
	std::vector<std::string> new_attr_header;
    
	while (it1 != header.end()) {
		std::string temp1 = *it1;
		bool is_key = false;
		if (temp1.substr(0, 1) == "%") {
			temp1 = temp1.substr(1, temp1.length() - 1);
			is_key = true;
		}
		new_attr_header.push_back(temp1 + " INTEGER");
		if (is_key)
			new_key_header.push_back(temp1);
		++it1;
	}
    
	relation* new_relation = new relation("", new_key_header, new_attr_header);
    
	for (auto conj : conjunctions){
		for (auto row : t){
			tuple new_row;
			tuple new_keys;
            
			if (meets_conjunction(conj, row)){
				for (auto attrs : row.second){
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
				for (unsigned int k = 0; k < new_row.size(); k++){
					if (is_key(k)){
						new_keys.push_back(new_row[k]);
					}
				}
				new_relation->insert(std::pair<std::vector<attr*>, std::vector<attr*>>(new_keys, new_row));
			}
		}
	}
	return new_relation;
    
}

relation* relation::projection(std::vector<std::string> attr_list){
	std::vector<int> attrib_positions;
	std::vector<std::string> projection_header;
	std::vector<std::string> projection_key;
	//Finds column positions (placed into attrib_positions) to access when projecting the relation
	for (auto attr_iter = attr_list.begin(); attr_iter != attr_list.end(); ++attr_iter){
		int position = header_pos(*attr_iter);
		if (position != -1) {
			attrib_positions.push_back(position);
			projection_header.push_back(*attr_iter + "INTEGER");
			if (is_key(position)){
				projection_key.push_back(*attr_iter);
			}
		}
		else{
			std::printf("%s does not match!", (*attr_iter).c_str());
			//FIXME fail gracefully somehow
			//dont worry if the column doesnt exist, just dont copy it into the new table
		}
	}
	relation* new_relation = new relation("test", projection_key, projection_header);
	//For each projected column, push the attribute at that position from original row to the new row, then add the row to the new relation's table
	for (auto table_iter = t.begin(); table_iter != t.end(); ++table_iter){
		tuple projection_row;
		tuple keys;
		tuple old_row = table_iter->second;
		for (auto pos : attrib_positions){
			attr* new_a;
			if (old_row[pos]->get_class() == attr::attr_type::INTEGER)
				new_a = new integer(*dynamic_cast<integer*>(old_row[pos]));
			else
				new_a = new var_char(*dynamic_cast<var_char*>(old_row[pos]));
			projection_row.push_back(new_a);
			if (is_key(pos))
				keys.push_back(new_a);
		}
		new_relation->insert(std::pair<tuple, tuple>(keys, projection_row));
	}
	return new_relation;
}

relation* relation::renaming(std::vector<std::string> attr_list){
	relation* new_relation;
	std::vector<std::string> new_key_header;
	std::vector<std::string> new_attr_header;
	for (int k = 0; k < attr_list.size() && k < header.size(); k++){
		if (is_key(k)){
			new_key_header.push_back(attr_list[k]);
			new_attr_header.push_back(attr_list[k] + " INTEGER");
		}
		else
			new_attr_header.push_back(attr_list[k] + " INTEGER");
	}
	new_relation = new relation("", new_key_header, new_attr_header);
	new_relation->insert_into(*this);
	return new_relation;
}

relation* relation::set_union(relation& other_table){
	if (header.size() != other_table.header.size()) {
		return new relation();
	}
	std::vector<std::string>::iterator it1 = header.begin();
	std::vector<std::string>::iterator it2 = other_table.header.begin();
	std::vector <std::string> new_key_header;
	std::vector<std::string> new_attr_header;
	while (it1 != header.end()) {
		std::string temp1 = *it1;
		std::string temp2 = *it2;
		bool is_k = false;
		if (temp1.substr(0, 1) == "%") {
			temp1 = temp1.substr(1, temp1.length()-1);
			is_k = true;
		}
		if (temp2.substr(0, 1) == "%") {
			temp2 = temp2.substr(1, temp2.length()-1);
			is_k = true;
		}
		if (temp1 != temp2) {
			return new relation();
		}
		new_attr_header.push_back(temp1 + " INTEGER");
		if (is_k)
			new_key_header.push_back(temp1);
		++it1;
		++it2;
	}
	relation* new_relation = new relation("", new_key_header, new_attr_header);
	new_relation->insert_into(*this);
	new_relation->insert_into(other_table);
	return new_relation;
}

relation* relation::set_difference(relation& other_table){
	if (header.size() != other_table.header.size()) {
        return new relation();
    }
    
    std::vector<std::string>::iterator it1 = header.begin();
    std::vector<std::string>::iterator it2 = other_table.header.begin();
    std::vector<std::string> new_key_header;
    std::vector<std::string> new_attr_header;
    
    while (it1 != header.end()) {
        std::string temp1 = *it1;
        std::string temp2 = *it2;
        bool is_key = false;
        if (temp1.substr(0, 1) == "%") {
            temp1 = temp1.substr(1, temp1.length()-1);
            is_key = true;
        }
        if (temp2.substr(0, 1) == "%") {
            temp2 = temp2.substr(1, temp2.length()-1);
            is_key = true;
        }
        if (temp1 != temp2) {
            return new relation();
        }
        new_attr_header.push_back(temp1 + " INTEGER");
        if (is_key)
            new_key_header.push_back(temp1);
        ++it1;
        ++it2;
    }
    relation* new_relation = new relation("", new_key_header, new_attr_header);
    // REMOVE THE ONES THAT TABLE 1 HAS BUT TABLE 2 DOES NOT
    
    return new_relation;
}

relation* relation::cross_product(relation& other_table) {
	std::vector<std::string> new_key_header;
	std::vector<std::string> new_attr_header;
	std::vector<std::string> other_header = other_table.header;

	for (std::vector<std::string>::iterator it1 = header.begin(); it1 != header.end(); ++it1) {
		if ((*it1)[0] == '%'){
			std::string temp = it1->substr(1, it1->size() -1);
			new_attr_header.push_back(temp + "INTEGER");
			new_key_header.push_back(temp);
		}
		else{
			std::string temp = *it1;
			new_attr_header.push_back(temp + "INTEGER");
		}
	}
	for (std::vector<std::string>::iterator it2 = other_header.begin(); it2 != other_header.end(); ++it2) {
		if ((*it2)[0] == '%'){
			std::string temp = it2->substr(1, it2->size() - 1);
			new_attr_header.push_back(temp + "INTEGER");
			new_key_header.push_back(temp);
		}
		else{
			std::string temp = *it2;
			new_attr_header.push_back(temp + "INTEGER");
		}
	}

	relation* new_relation = new relation("", new_key_header, new_attr_header);

	for (auto row1 : t){
		tuple attr1 = row1.second;
		for (auto row2 : other_table.t){
			tuple new_key;
			tuple new_attr;
			tuple attr2 = row2.second;
			for (unsigned int k = 0; k < attr1.size(); k++){
				attr* new_a;
				if (attr1[k]->get_class() == attr::attr_type::INTEGER)
					new_a = new integer(*dynamic_cast<integer*>(attr1[k]));
				else
					new_a = new var_char(*dynamic_cast<var_char*>(attr1[k]));
				new_attr.push_back(new_a);
				if (is_key(k))
					new_key.push_back(new_a);
			}
			for (unsigned int k = 0; k < attr2.size(); k++){
				attr* new_a;
				if (attr2[k]->get_class() == attr::attr_type::INTEGER)
					new_a = new integer(*dynamic_cast<integer*>(attr2[k]));
				else
					new_a = new var_char(*dynamic_cast<var_char*>(attr2[k]));
				new_attr.push_back(new_a);
				if (other_table.is_key(k))
					new_key.push_back(new_a);
			}
			new_relation->insert(std::pair<tuple, tuple>(new_key, new_attr));
		}
	}
	return new_relation;
}

relation* relation::natural_join(relation& other_table){
	
	/*
	 compare NOT ONLY headers BUT ALSO attr!
	 */
	
	std::map<int, int> header_matches;	//<position in this, position in other>
	
	
	int pos1 = 0;
	int pos2 = 0;
	
	//checking to see if any headers match, and storing the matches in header_matches
	for(std::vector<std::string>::iterator header_check1 = header.begin(); header_check1 != header.end(); header_check1++) {
		
		std::string temp1 = "";
		
		if((*header_check1).substr(0,1) == "%") {
			temp1 =(*header_check1).substr(1,(*header_check1).length());
		}
		else {
			temp1 = *header_check1;
		}
		
		for(std::vector<std::string>::iterator header_check2 = other_table.header.begin(); header_check2 != other_table.header.end(); header_check2++) {
			std::string temp2 = "";
			
			if((*header_check2).substr(0,1) == "%") {
				temp2 =(*header_check2).substr(1,(*header_check2).length());
			}
			else {
				temp2 = *header_check2;
			}
			
			if(temp1 == temp2) {
				header_matches.insert(std::pair<int,int>(pos1, pos2));
				break;
			}
			pos2++;
		}
		pos2 = 0;
		pos1++;
	}
	
	if(header_matches.size() <= 0) {
		return cross_product(other_table);
	}
	
	std::vector<std::string> new_header;
	std::vector<std::string> new_keys;

/*
	for(auto x : header_matches) {
		std::cout << "Header firsts: " << x.first << " and " << x.second << std::endl;
	}
*/
	
	pos1 = 0;
	//iterate through, checking each header title for both headers
	for(std::vector<std::string>::iterator header_check1 = header.begin(); header_check1 != header.end(); header_check1++) {
		
//		std::cout << "Header check: " << *header_check1 << std::endl;
		if(header_matches.find(pos1) == header_matches.end()) {
			
			
			if((*header_check1).substr(0,1) == "%") {
				std::string temp1 =(*header_check1).substr(1,(*header_check1).length());
				new_keys.push_back(temp1);
				new_header.push_back(temp1 + " INTEGER");
			}
			else {
				new_header.push_back(*header_check1 + " INTEGER");
			}
		}
	
		pos1++;
	}
	
	pos2 = 0;
	for(std::vector<std::string>::iterator header_check2 = other_table.header.begin(); header_check2 != other_table.header.end(); header_check2++) {
		
		if(other_table.is_key(pos2)) {
			std::string temp =(*header_check2).substr(1,(*header_check2).length());
			new_keys.push_back(temp);
			new_header.push_back(temp + " INTEGER");
		}
		else {
			new_header.push_back(*header_check2 + " INTEGER");
		}
		
		pos2++;
	}
	
	relation* new_relation = new relation("", new_keys, new_header);
/*
	new_relation->show();
	for(auto x : new_keys) {
		std::cout << x << std::endl;
	}
	std::cout << std::endl;
	for(auto x : new_header) {
		std::cout << x << std::endl;
	}
*/
	
	
	
	return new relation();
}