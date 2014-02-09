#include "database.h"
#include <iostream>

int main(){
  std::vector<relation> table;
  grammar::program("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);", table);

  grammar::program("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);", table);
  grammar::program("INSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);", table);
  grammar::program("INSERT INTO animals VALUES FROM (\"Snoopy\", \"dog\", 3);", table);
  grammar::program("INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1);", table);
  grammar::program("INSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);", table);

  grammar::program("SHOW animals;", table);

  grammar::program("UPDATE animals SET kind = \"bat\" WHERE years <= 5;", table);

  //::program("SHOW animals;", table);

  //grammar::program("CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);", table);

  //grammar::program("INSERT INTO species VALUES FROM RELATION project (kind) animals;", table);

  while (true);
  /*
  std::regex reg("([_[:alpha:]])([:alnum:]*).*");
  std::string test("a23jk43 efe / >");
  std::cout<<std::regex_match(test, reg);
  */
  return 0;
}