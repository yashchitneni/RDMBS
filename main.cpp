#include "database.h"
#include <iostream>

int main(){
  std::vector<relation> table;
  grammar::program("INSERT INTO animals VALUES FROM (\"Joe\", 4, 5); ", table);
  /*
  std::regex reg("([_[:alpha:]])([:alnum:]*).*");
  std::string test("a23jk43 efe / >");
  std::cout<<std::regex_match(test, reg);
  */
	
	//renaming test by OH
	std::vector<std::string> keys {"%Name"};
	std::vector<std::string> attrs {"Town","Num_Friends"};
	relation::relation friends("Friends", keys, attrs);
	//grammar::program("INSERT INTO Friends VALUES FROM (\"Max\", \"Anytown\", 5); ", table);
	std::vector<std::string> literals {"Max","Anytomn","20"};
	friends.insert_into(literals);
	std::vector<std::string> new_attrs {"Residence","Aquaintances"};
	friends.renaming(new_attrs);
	friends.show();
	
  return 0;
}