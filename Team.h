//
//  Team.h
//  RDBMS
//
//  Created by Yash Chitneni on 2/17/14.
//  Copyright (c) 2014 yash_chitneni. All rights reserved.
//

#ifndef RDBMS_Team_h
#define RDBMS_Team_h

#include <iostream>
#include <vector>

class Team {
public:
    Team() {
        team_name = "";
        city_name = "";
        sponsor_name = "";
        year_founded = -1;
        manager_name = "";
        kit_color = "";
    }
    
    std::string getName() {
        return team_name;
    }
    
    std::string getCityName() {
        return city_name;
    }
    
    std::string getSponsorName() {
        return sponsor_name;
    }
    
    int getYearFounded() {
        return year_founded;
    }
    
    /* Check to see if there has been a goal scored */
    bool goalScored(int goals);
    
    /* Function to display roster of team if goal scored
     Do I show a vector full of players? What do I return here */
    std::vector<std::Player*> player_names; // PROBABLY NOT

    
private:
    std::string team_name;
    std::string city_name;
    std::string sponsor_name;
    int year_founded;
    std::string manager_name;
    std::string kit_color;
    
};

#endif
