//
//  Menu.h
//  RDBMS
//
//  Created by Yash Chitneni on 2/22/14.
//  Copyright (c) 2014 yash_chitneni. All rights reserved.
//

#ifndef __RDBMS__Menu__
#define __RDBMS__Menu__

#include <iostream>
#include "Database.h"

#endif /* defined(__RDBMS__Menu__) */

class Menu {
public:
    Menu();
    
    void original_menu();
    
    bool league_available(std::string league_name);
    bool team_available(std::string team_name, std::string league_name);
    bool player_available(std::string player_name, int jersey_number, std::string team_name);
    
    void create_league_menu();
    void create_team_menu();
    void create_player_menu();
    void play_game_menu();
    void player_stats_menu();
    void team_stats_menu();
    void league_stats_menu();
    void transfer_player();
    
    /* Maybe unnecessary functions */
    
//    void league_available(bool league_exists());
//    void team_available(bool team_exists());
//    void player_available(bool player_exists());
    
private:
    Team_Project_1_Database::Database soccer_DB;
};