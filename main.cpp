#include "database.h"
#include <iostream>
//#include <string>	//OH: included only for test
//#include <vector>	//OH: included only for test

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
	std::vector<std::string> new_attrs {"Residence","Aquaintances"};
	friends.renaming(new_attrs);
	
  return 0;
}