#ifndef _DATABASE
#define _DATABASE

#include "relation.h"
#include "grammar.h"

class database{
  std::vector<relation> tables;
public:
  database();
	void execute(std::string input);
};

#endif