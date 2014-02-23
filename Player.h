//
//  Player.h
//  RDBMS
//
//  Created by Yash Chitneni on 2/17/14.
//  Copyright (c) 2014 yash_chitneni. All rights reserved.
//

#ifndef RDBMS_Player_h
#define RDBMS_Player_h

class Player {
public:
    Player() {
        player_name = "";
        jersey_number = -1;
        team_name = "";
        position = "";
    }
    
    std::string getName() {
        return player_name;
    }
    
    int getJerseyNumber() {
        return jersey_number;
    }
    
    std::string getPosition() {
        return position;
    }
    
private:
    std::string team_name;
    std::string player_name;
    int jersey_number;
    std::string position;
    
};

#endif
