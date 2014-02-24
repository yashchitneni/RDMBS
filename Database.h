/*
 class: Database
 Main container for database that holds relations and accepts input from user.
 */

#ifndef _DATABASE
#define _DATABASE

#include "Relation.h"
#include "Grammar.h"

namespace Team_Project_1_Database{
    class Database{
        std::vector<Relation> tables;
    public:
        Database();
        
        void execute(std::string input);
        void execute(std::string input, std::vector<std::string>& result);
    };
}

#endif