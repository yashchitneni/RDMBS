#include "database.h"
#include <iostream>

int main(){
  std::vector<relation> table;
  grammar::program("INSERT INTO animals VALUES FROM (\"Joe\", 4, 5) ", table);
  /*
  std::regex reg("([_[:alpha:]])([:alnum:]*).*");
  std::string test("a23jk43 efe / >");
  std::cout<<std::regex_match(test, reg);
  */
  return 0;
}