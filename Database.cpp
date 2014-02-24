#include "Database.h"

using namespace Team_Project_1_Database;

Database::Database(){

}

void Database::execute(std::string input){
    Grammar::program(input, tables);
}

void Database::execute(std::string input, std::vector<std::string>& result){
    Grammar::program(input, tables, result);
}