#include "relation.h"

void relation::set_name(std::string name){
  table_name = name;
}

std::string relation::get_name() const{
  return table_name;
}