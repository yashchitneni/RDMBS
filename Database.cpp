#include "Database.h"

using namespace Team_Project_1_Database;

Database::Database(){

}

void Database::execute(std::string input){
    Grammar::program(input, tables);
}