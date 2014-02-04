#ifndef _DATABASE
#define _DATABASE

#include "grammar.h"

class database{
  std::vector<relation> tables;
public:
  database();
  bool command(std::string input);
};

#endif