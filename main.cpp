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
  return 0;
}