#include "database.h"

database::database(){

}

void database::execute(std::string input){
	grammar::program(input, tables);
}