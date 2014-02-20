//
//  League.h
//  RDBMS
//
//  Created by Yash Chitneni on 2/17/14.
//  Copyright (c) 2014 yash_chitneni. All rights reserved.
//

#ifndef RDBMS_League_h
#define RDBMS_League_h

#include <iostream>
#include <vector>

/* Guessing I need namespace Database */

class League {
public:
    League() {
        league_name = "";
        country_name = "";
        sponsor_name = "";
        current_champions = "";//
    }
    
    std::string getName() {
        return league_name;
    }
    
    std::string getCountryName() {
        return country_name;
    }
    
    std::string getSponsorName() {
        return sponsor_name;
    }

private:
    std::string league_name;
    std::string country_name;
    std::string sponsor_name;
    static int number_of_teams;
    std::string current_champions;
    
};
#endif
