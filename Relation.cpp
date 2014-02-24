/*
Core implementation of Relation Tables in the Database.
*/

#include "Relation.h"

using namespace Team_Project_1_Database;

bool less_attr_pt::operator() (std::vector<Attribute*> lhs, std::vector<Attribute*> rhs) const {
    for (unsigned int k = 0; k < lhs.size() && k < rhs.size(); k++){

        if (*(lhs[k]) < *(rhs[k])){
            return true;
        }

        if (*(lhs[k]) == *(rhs[k])){
            continue;
        }
        else{
            return false;
        }
    }
    return false;
}

/*
constructor takes in a table name and two vector<strings>
strings of key_header are of the form "attr_name"
strings of attr_header are of the form "attr_name TYPE" where TYPE can be INTEGER or VARCHAR(int)
*/
Relation::Relation(
    std::string name,
    std::vector<std::string> key_header,
    std::vector<std::string> attr_header){

    n_keys = key_header.size();
    n_attr = attr_header.size();
    table_name = name;
    std::regex reg_header("([_[:alpha:]][_\\w]*)(?:\\s*(INTEGER|VARCHAR(.*)))");
		std::regex reg_key("[_[:alpha:]][_\\w]*");
    std::smatch m;

    for (auto x : attr_header){
        if (std::regex_search(x, m, reg_header)){
            std::string header_name = m[1].str();
            header.push_back(header_name);
        }
    }
    for (auto x : key_header){
			if(std::regex_search(x, m, reg_key)){
        int pos = header_pos(m.str());
        if (pos != -1){
            header[pos] = "%" + header[pos];
        }
			}
    }
}

/*
copy constructor
*/
Relation::Relation(const Relation& other_table){
    table other_t = other_table.get_table();
    std::vector<std::string> other_header = other_table.header;
    n_keys = other_table.n_keys;
    n_attr = other_table.n_attr;
    table_name = other_table.table_name;

    for (auto x : other_header){
        header.push_back(x);
    }

    for (auto x : other_t){
        tuple new_row;
        tuple new_keys;
        tuple other_attr = x.second;

        for (unsigned int k = 0; k < other_attr.size(); k++){
            Attribute* new_attr;
            if (other_attr[k]->get_class() == Attribute::attr_type::INTEGER){
                Integer* temp = dynamic_cast<Integer*>(other_attr[k]);
                new_attr = new Integer(*temp);
            }
            else{
                Var_Char* temp = dynamic_cast<Var_Char*>(other_attr[k]);
                new_attr = new Var_Char(*temp);
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
assignment operator
*/
Relation& Relation::operator=(const Relation& rhs){
	if(*this == rhs)
		return *this;
	header.clear();
	t.clear();
	header = rhs.header;
  n_keys = rhs.n_keys;
  n_attr = rhs.n_attr;
  table_name = rhs.table_name;
  insert_into(rhs);
	return *this;
}

/*
destructor
*/
Relation::~Relation(){
	header.clear();
  for (auto row_iter : t){
    for (auto attr_iter : row_iter.second){
        delete attr_iter;
    }
  }
}

bool Relation::meets_condition(
    std::string condition,
    std::pair<tuple, tuple> row){

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
        Attribute* op1;
        Attribute* op2;
        std::string operation = m[2].str();
        std::string operand1 = m[1].str();
        std::string operand2 = m[3].str();
        std::regex reg_var_char("(?:\\\")(.*)(?:\\\")");

        if (std::regex_search(operand1, m, reg_var_char)){
            op1 = new Var_Char(m[1].str());
        }
        else{
            int pos = header_pos(operand1);

            if (pos != -1){

                if (row.second[pos]->get_class() == Attribute::attr_type::INTEGER){
                    op1 = new Integer(*dynamic_cast<Integer*>(row.second[pos]));
                }
                else{
                    op1 = new Var_Char(*dynamic_cast<Var_Char*>(row.second[pos]));
                }
            }
            else{
                op1 = new Integer(atoi(operand1.c_str()));

                if (op1->get_value() != operand1.c_str()){
                    return false;
                }
            }
        }

        if (std::regex_search(operand2, m, reg_var_char)){
            op2 = new Var_Char(m[1].str());
        }
        else{
            int pos = header_pos(operand2);

            if (pos != -1){

                if (row.second[pos]->get_class() == Attribute::attr_type::INTEGER){
                    op2 = new Integer(*dynamic_cast<Integer*>(row.second[pos]));
                }
                else{
                    op2 = new Var_Char(*dynamic_cast<Var_Char*>(row.second[pos]));
                }
            }
            else{
                op2 = new Integer(atoi(operand2.c_str()));

                if (op2->get_value() != operand2.c_str()){
                    return false;
                }
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
        bool out = false;

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

bool Relation::meets_conjunction(
    std::string conjunction,
    std::pair<tuple, tuple> row){

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

int Relation::header_pos(std::string name){
	std::regex reg_attr("[\\w_]+");
	std::smatch m;
	if(std::regex_search(name, m, reg_attr))
		name = m.str();
    for (unsigned int k = 0; k < header.size(); k++){
        if (header[k] == name || (header[k] == "%" + name)){
            return k;
        }
    }
    return -1;
}

bool Relation::is_key(int pos){
    if (header[pos][0] == '%'){
        return true;
    }
    return false;
}

std::vector<std::string> Relation::split_condition(std::string condition){
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

std::vector<std::string> Relation::split_conjunction(std::string conjunction){
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

void Relation::set_name(std::string name){
    table_name = name;
}

void Relation::insert(std::pair<tuple, tuple> row){
    t.insert(row);
}

std::vector<std::string> Relation::get_header() const{
    return header;
}

Attribute* Relation::get_attribute(std::string conjunction, std::string column){
	int pos = header_pos(column);

	if( pos != -1 ){

		for( auto row : t ){

			if(meets_conjunction(conjunction, row))
				return row.second[pos];
		}

	}

	return new Integer();
}


Relation::table Relation::get_table() const{
    return t;
}

int Relation::get_size() const{
	return t.size();
}

void Relation::save(){
    std::string file_name = table_name + ".db";
    std::ifstream file_exists(file_name);

    if (file_exists.fail()){
        std::printf("Failed to open table file: %s\n", file_name.c_str());
				file_exists.close();
        return;
    }
		file_exists.close();

    std::ofstream table_file(file_name, std::ios_base::trunc | std::ios_base::out);
    std::string c_table = "CREATE TABLE " + table_name + " (";
    std::string c_header = "";
    std::string c_key = " ) PRIMARY KEY (";

    for (int k = 0; k < header.size(); k++){

        if (is_key(k)){
					c_header += " " + header[k].substr(1, header[k].size() - 1) + " INTEGER,";
          c_key += " " + header[k].substr(1, header[k].size() - 1) + " ,";
        }
        else{
          c_header += " " + header[k] + " INTEGER,";
        }
    }

    c_header.pop_back();
    c_key.pop_back();
    c_table += c_header + c_key + ");";
    table_file << c_table;
    for (auto row : t){
        std::string c_row = "\nINSERT INTO " + table_name + " VALUES FROM (";
				
        for (auto attr : row.second){
          if (attr->get_class() == Attribute::attr_type::VAR_CHAR){
              c_row += " \"" + attr->get_value() + "\" ,";
          }
          else{
              c_row += " " + attr->get_value() + " ,";
          }
        }

        c_row.pop_back();
        c_row += ");";
        table_file << c_row;
    }
		
		table_file.close();
}

void Relation::show() const{
    std::printf("TABLE NAME: %s\n", table_name.c_str());
		std::vector<int> length;
		int pos = 0;
		for( auto x : header){
			length.push_back(x.size());
		}

		for(auto row : t){
			pos = 0;

			for(auto attr : row.second){
				length[pos] = std::max(length[pos], (int)attr->get_value().length());
				pos++;
			}

		}

		pos = 0;
    for (auto x : header){

      if (x[0] == '%'){
          std::printf("%-*s", length[pos]+ 3, x.substr(1, x.size() - 1).c_str());
      }
      else{
          std::printf("%-*s", length[pos]+ 3, x.c_str());
      }
			pos++;
    }

    std::printf("\n");
		
    for (auto row : t){
			pos = 0;
      for (auto attr : row.second){
          std::printf(" %-*s", length[pos]+ 2, attr->get_value().c_str());
					pos++;
      }

      std::printf("\n");
    }

    std::printf("\n");
}


bool Relation::operator== (const Relation& rhs) const{
    if (this->get_header() != rhs.get_header()){
        return false;
    }
    else{
        int lhs_index = 0;
        for (auto lhs_row : this->get_table()){
            
            int rhs_index = 0;
            for (auto rhs_row : rhs.get_table()){
                
                if (lhs_index == rhs_index){
                    
                    for (int attr_index = 0; attr_index < lhs_row.second.size(); ++attr_index){
                        
                        if (lhs_row.second.at(attr_index)->get_value() != rhs_row.second.at(attr_index)->get_value()){
                            return false;
                        }
                    }
                }
                ++rhs_index;
            }
            ++lhs_index;
        }
    }
    return true;
}

bool Relation::operator!= (const Relation& rhs) const{
    return !(*this == rhs);
}

bool Relation::insert_into(std::vector<std::string> literals){
    std::regex reg_var("(?:\")([\\w\\s+=-_]+)(?:\")");
    std::smatch m;
    tuple keys;
    tuple attrs;

    for (auto x : literals){
        Attribute* new_attr;

        if (std::regex_search(x, m, reg_var)){
          new_attr = new Var_Char(m[1].str());
        }
        else{
          new_attr = new Integer(atoi(x.c_str()));
        }

        attrs.push_back(new_attr);
    }

    for (unsigned int k = 0; k < header.size(); k++){
        if (is_key(k))
            keys.push_back(attrs[k]);
    }

    t.insert(std::pair<std::vector<Attribute*>, std::vector<Attribute*>>(keys, attrs));
    return true;
}

bool Relation::insert_into(Relation other_table){
    for (auto row : other_table.t){
        tuple new_row;
        tuple new_keys;
        for (auto attrs : row.second){
            Attribute* new_attr;

            if (attrs->get_class() == Attribute::attr_type::INTEGER){
                Integer* temp = dynamic_cast<Integer*>(attrs);
                new_attr = new Integer(*temp);
            }
            else{
                Var_Char* temp = dynamic_cast<Var_Char*>(attrs);
                new_attr = new Var_Char(*temp);
            }

            new_row.push_back(new_attr);
        }

        for (unsigned int k = 0; k < new_row.size(); k++){

            if (is_key(k)){
                new_keys.push_back(new_row[k]);
            }
        }

        t.insert(std::pair<std::vector<Attribute*>, std::vector<Attribute*>>(new_keys, new_row));
    }
    return true;
}

int Relation::find_key(Attribute* attribute, tuple keys){
    for (int k = 0; k < keys.size(); k++){

        if (*keys[k] == *attribute){
            return k;
        }
    }
    return -1;
}

bool Relation::update(std::vector<std::string> attr_list, std::vector<std::string> conjunctions){
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

bool Relation::delete_from(std::vector<std::string> conjunctions){
    std::vector<tuple> remove;
    for (auto conj : conjunctions){

        for (auto row : t){

            if (meets_conjunction(conj, row)){
                tuple key_to_remove;
              for(auto attribute : row.first){
								key_to_remove.push_back(attribute);
							}
							remove.push_back(key_to_remove);
            }
        }
    }

    for (auto r : remove) {
        t.erase(r);
    }
    return true;
}

Relation* Relation::selection(std::vector<std::string> conjunctions){
    std::vector<std::string>::iterator it1 = header.begin();
    std::vector<std::string> new_key_header;
    std::vector<std::string> new_attr_header;
    
    // Take care of header for new table being created
    
    while (it1 != header.end()) {
        std::string temp1 = *it1;
        bool is_key = false;
        
        //keys have been assigned % sign and hence making the check to ensure finding the right keys
        if (temp1.substr(0, 1) == "%") {
            temp1 = temp1.substr(1, temp1.length() - 1);
            is_key = true;
        }

        new_attr_header.push_back(temp1 + " INTEGER");

        if (is_key){
            new_key_header.push_back(temp1);
        }
        ++it1;
    }

    Relation* new_relation = new Relation("", new_key_header, new_attr_header);

    for (auto conj : conjunctions){

        for (auto row : t){
            tuple new_row;
            tuple new_keys;

            if (meets_conjunction(conj, row)){

                for (auto attrs : row.second){
                    Attribute* new_attr;

                    if (attrs->get_class() == Attribute::attr_type::INTEGER){
                        Integer* temp = dynamic_cast<Integer*>(attrs);
                        new_attr = new Integer(*temp);
                    }
                    else{
                        Var_Char* temp = dynamic_cast<Var_Char*>(attrs);
                        new_attr = new Var_Char(*temp);
                    }

                    new_row.push_back(new_attr);
                }

                for (unsigned int k = 0; k < new_row.size(); k++){

                    if (is_key(k)){
                        new_keys.push_back(new_row[k]);
                    }
                }
                new_relation->insert(std::pair<std::vector<Attribute*>, std::vector<Attribute*>>(new_keys, new_row));
            }
        }
    }
    return new_relation;
}

Relation* Relation::projection(std::vector<std::string> attr_list){
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
            std::printf("%s does not match!\n", (*attr_iter).c_str());
        }
    }

    Relation* new_relation = new Relation("", projection_key, projection_header);

    //For each projected column, push the attribute at that position from original row to the new row, then add the row to the new relation's table
    for (auto table_iter = t.begin(); table_iter != t.end(); ++table_iter){
        tuple projection_row;
        tuple keys;
        tuple old_row = table_iter->second;

        for (auto pos : attrib_positions){
            Attribute* new_a;

            if (old_row[pos]->get_class() == Attribute::attr_type::INTEGER){
                new_a = new Integer(*dynamic_cast<Integer*>(old_row[pos]));
            }
            else{
                new_a = new Var_Char(*dynamic_cast<Var_Char*>(old_row[pos]));
            }

            projection_row.push_back(new_a);

            if (is_key(pos)){
                keys.push_back(new_a);
            }
        }

        new_relation->insert(std::pair<tuple, tuple>(keys, projection_row));
    }
    return new_relation;
}

Relation* Relation::renaming(std::vector<std::string> attr_list){
    Relation* new_relation;
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

    new_relation = new Relation("", new_key_header, new_attr_header);
    new_relation->insert_into(*this);
    return new_relation;
}

Relation* Relation::set_union(Relation& other_table){
    if (header.size() != other_table.header.size()) {
        return new Relation();
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
            temp1 = temp1.substr(1, temp1.length() - 1);
            is_k = true;
        }
        if (temp2.substr(0, 1) == "%") {
            temp2 = temp2.substr(1, temp2.length() - 1);
            is_k = true;
        }
        if (temp1 != temp2) {
            return new Relation();
        }
        new_attr_header.push_back(temp1 + " INTEGER");
        if (is_k){
            new_key_header.push_back(temp1);
        }
        ++it1;
        ++it2;
    }

    Relation* new_relation = new Relation("", new_key_header, new_attr_header);

    new_relation->insert_into(*this);
    new_relation->insert_into(other_table);
    return new_relation;
}

Relation* Relation::set_difference(Relation& other_table){
    if (header.size() != other_table.header.size()) {
        return new Relation();
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
            temp1 = temp1.substr(1, temp1.length() - 1);
            is_key = true;
        }
        if (temp2.substr(0, 1) == "%") {
            temp2 = temp2.substr(1, temp2.length() - 1);
            is_key = true;
        }
        if (temp1 != temp2) {
            return new Relation();
        }

        new_attr_header.push_back(temp1 + " INTEGER");

        if (is_key){
            new_key_header.push_back(temp1);
        }
        ++it1;
        ++it2;
    }

    Relation* new_relation = new Relation("", new_key_header, new_attr_header);

    for (auto row : t) {
        tuple new_row;
        tuple new_keys;
        bool match_rows = false;

        for (auto row_other : other_table.t) {

            for (int i = 0; i < row.second.size(); i++) {

                if (*(row.second[i]) == *(row_other.second[i])) {

                    if (i == row.second.size() - 1){
                        match_rows = true;
                    }
                    continue;
                }
                break;
            }
            if (match_rows){
                break;
            }
        }

        if (!match_rows) {

            for (int k = 0; k < row.second.size(); k++) {
                Attribute* new_attr;

                if (row.second[k]->get_class() == Attribute::attr_type::INTEGER) {
                    Integer* temp = dynamic_cast<Integer*>(row.second[k]);
                    new_attr = new Integer(*temp);
                }

                else {
                    Var_Char* temp = dynamic_cast<Var_Char*>(row.second[k]);
                    new_attr = new Var_Char(*temp);
                }

                new_row.push_back(new_attr);

                if (is_key(k)){
                    new_keys.push_back(new_row[k]);
                }
            }

            new_relation->insert(std::pair<tuple, tuple>(new_keys, new_row));
        }
    }
    return new_relation;
}

Relation* Relation::cross_product(Relation& other_table) {
    std::vector<std::string> new_key_header;
    std::vector<std::string> new_attr_header;
    std::vector<std::string> other_header = other_table.header;

    //compiles together header titles into one
    for (std::vector<std::string>::iterator it1 = header.begin(); it1 != header.end(); ++it1) {    //uses iterators for quick traversal of vector

        if ((*it1)[0] == '%'){
            std::string temp = it1->substr(1, it1->size() - 1);
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

    Relation* new_relation = new Relation("", new_key_header, new_attr_header);

    //creates new tuples by pairing each tuple in this relation with all other tuples in other_table
    for (auto row1 : t){
        tuple attr1 = row1.second;

        for (auto row2 : other_table.t){
            tuple new_key;
            tuple new_attr;
            tuple attr2 = row2.second;

            for (unsigned int k = 0; k < attr1.size(); k++){
                Attribute* new_a;
                if (attr1[k]->get_class() == Attribute::attr_type::INTEGER){
                    new_a = new Integer(*dynamic_cast<Integer*>(attr1[k]));
                }
                else{
                    new_a = new Var_Char(*dynamic_cast<Var_Char*>(attr1[k]));
                }

                new_attr.push_back(new_a);
                if (is_key(k)){
                    new_key.push_back(new_a);
                }
            }

            for (unsigned int k = 0; k < attr2.size(); k++){
                Attribute* new_a;
                if (attr2[k]->get_class() == Attribute::attr_type::INTEGER){
                    new_a = new Integer(*dynamic_cast<Integer*>(attr2[k]));
                }

                else{
                    new_a = new Var_Char(*dynamic_cast<Var_Char*>(attr2[k]));
                }

                new_attr.push_back(new_a);
                if (other_table.is_key(k)){
                    new_key.push_back(new_a);
                }
            }
            new_relation->insert(std::pair<tuple, tuple>(new_key, new_attr));
        }
    }
    return new_relation;
}

Relation* Relation::natural_join(Relation& other_table){
    std::map<int, int> header_matches;
    int pos1 = 0;
    int pos2 = 0;

    for (std::vector<std::string>::iterator header_check1 = header.begin(); header_check1 != header.end(); header_check1++) {
        std::string temp1 = "";

        if ((*header_check1).substr(0, 1) == "%") {
            temp1 = (*header_check1).substr(1, (*header_check1).length());
        }
        else {
            temp1 = *header_check1;
        }

        for (std::vector<std::string>::iterator header_check2 = other_table.header.begin(); header_check2 != other_table.header.end(); header_check2++) {
            std::string temp2 = "";

            if ((*header_check2).substr(0, 1) == "%") {
                temp2 = (*header_check2).substr(1, (*header_check2).length());
            }
            else {
                temp2 = *header_check2;
            }

            if (temp1 == temp2) {
                header_matches.insert(std::pair<int, int>(pos1, pos2));
                break;
            }
            pos2++;
        }
        pos2 = 0;
        pos1++;
    }

    if (header_matches.size() <= 0) {
        return cross_product(other_table);
    }

    std::vector<std::string> new_header;
    std::vector<std::string> new_keys;
    pos1 = 0;

    for (std::vector<std::string>::iterator header_check1 = header.begin(); header_check1 != header.end(); header_check1++) {

        if (header_matches.find(pos1) == header_matches.end()) {

            if ((*header_check1).substr(0, 1) == "%") {
                std::string temp1 = (*header_check1).substr(1, (*header_check1).length());
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

    for (std::vector<std::string>::iterator header_check2 = other_table.header.begin(); header_check2 != other_table.header.end(); header_check2++) {

        if (other_table.is_key(pos2)) {
            std::string temp = (*header_check2).substr(1, (*header_check2).length());
            new_keys.push_back(temp);
            new_header.push_back(temp + " INTEGER");
        }
        else {
            new_header.push_back(*header_check2 + " INTEGER");
        }
        pos2++;
    }

    Relation* new_relation = new Relation("", new_keys, new_header);

    for (auto first_t : t){

        for (auto second_t : other_table.t){
            bool matches = true;
            tuple first_row = first_t.second;
            tuple second_row = second_t.second;

            for (auto match : header_matches){
                Attribute* a1 = first_row[match.first];
                Attribute* a2 = second_row[match.second];
                if (*a1 == *a2){
                    continue;
                }

                matches = false;
                break;
            }

            if (matches){
                tuple new_key;
                tuple new_header;
                Attribute* new_a;

                for (int k = 0; k < first_row.size(); k++){

                    if (header_matches.find(k) == header_matches.end()){

                        if (first_row[k]->get_class() == Attribute::attr_type::INTEGER){
                            new_a = new Integer(*dynamic_cast<Integer*>(first_row[k]));
                        }
                        else{
                            new_a = new Var_Char(*dynamic_cast<Var_Char*>(first_row[k]));
                        }

                        new_header.push_back(new_a);

                        if (is_key(k)){
                            new_key.push_back(new_a);
                        }
                    }
                }

                for (int k = 0; k < second_row.size(); k++){
                    if (second_row[k]->get_class() == Attribute::attr_type::INTEGER){
                        new_a = new Integer(*dynamic_cast<Integer*>(second_row[k]));
                    }
                    else{
                        new_a = new Var_Char(*dynamic_cast<Var_Char*>(second_row[k]));
                    }

                    new_header.push_back(new_a);

                    if (other_table.is_key(k)){
                        new_key.push_back(new_a);
                    }
                }

                new_relation->insert(std::pair<tuple, tuple>(new_key, new_header));
            }
        }
    }
    return new_relation;
}