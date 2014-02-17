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
    };
}

#endif