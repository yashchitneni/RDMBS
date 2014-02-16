#include "Attributes.h"

using namespace Team_Project_1_Database;

Integer::Integer(const Integer& other){
	value = atoi(other.get_value().c_str());
}

void Integer::set_value(std::string v){
	value = atoi(v.c_str());
}

std::string Integer::get_value() const {
	return std::to_string(value); 
}
int Integer::get_class() const {
	return INTEGER;
}

bool Integer::operator<(const Attribute& rhs) const {
	const Integer* other = static_cast<const Integer*>(&rhs);
	if (other == NULL) return false;
	return value < atoi(other->get_value().c_str());
 }
  
bool Integer::operator==(const Attribute& rhs) const{
	const Integer* other = static_cast<const Integer*>(&rhs);
	if (other == NULL) return false;
	return value == atoi(other->get_value().c_str());
 }
	
bool Integer::operator!=(const Attribute& rhs) const {
		return !(*this == rhs);
}

Var_Char::Var_Char(const Var_Char& other){
		value = other.get_value();
}

void Var_Char::set_value(std::string v){
	value = v;
}
  
std::string Var_Char::get_value() const {
	return value;
}
  
int Var_Char::get_class() const {
	return VAR_CHAR;
}
  
bool Var_Char::operator<(const Attribute& rhs) const {
	const Var_Char* other = static_cast<const Var_Char*>(&rhs);
	if (other == NULL) return false;
	return value < other->get_value();
 }
  
bool Var_Char::operator==(const Attribute& rhs) const {
	const Var_Char* other = static_cast<const Var_Char*>(&rhs);
	if (other == NULL) return false;
	return value == other->get_value();
 }
	
bool Var_Char::operator!=(const Attribute& rhs) const {
	return !(*this == rhs);
}