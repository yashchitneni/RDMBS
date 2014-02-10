#include "grammar.h"
#include "database.h"

int main(){
  std::vector<relation> table;
  grammar::program("OPEN testdata;", table);

	/*
  std::regex reg("([_[:alpha:]])([:alnum:]*).*");
  std::string test("a23jk43 efe / >");
  std::cout<<std::regex_match(test, reg);
  */
	
	std::vector<std::string> keys {"Name"};
  	std::vector<std::string> attrs {"Name VARCHAR","Town VARCHAR","Num_Friends INTEGER"};
  	relation::relation friends("Friends", keys, attrs);
	
	std::vector<std::string> literals {"\"Max\"","\"Anytown\"", "20"};	//so for varchar, need extra quotes
	friends.insert_into(literals);
  	//std::vector<std::string> new_attrs {"Residence","Aquaintances"};
  	//friends.renaming(new_attrs);
	friends.show();
	
	std::vector<std::string> more_keys {"Land"};
	std::vector<std::string> more_attrs {"Land VARCHAR","Town VARCHAR", "Num_Buildings INTEGER"};
	relation::relation neighbors("neighbors", more_keys, more_attrs);
	std::vector<std::string> more_lits {"\"Australia\"", "\"Anytown\"", "30"};
	neighbors.insert_into(more_lits);
	neighbors.show();
	
	friends.natural_join(neighbors);
	
	
  return 0;
}