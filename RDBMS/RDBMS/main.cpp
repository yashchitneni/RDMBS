#include "Database.h"
#include <iostream>

int main(){
  std::vector<Relation> table;
	Relation r;
  //Grammar::program("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);", table);
	std::pair<std::vector<Attribute*>, std::vector<Attribute*>> row;
	r.meets_condition("  age== \"5\"", row);
  
  std::string test;
  getline(std::cin, test);
  return 0;
}