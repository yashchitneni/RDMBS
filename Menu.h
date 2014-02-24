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



namespace Team_Project_1_Database{
    class Menu {
    public:
        static void original_menu(Database& soccer_DB);
        
        static void create_league_menu(Database& soccer_DB);
        static void create_team_menu(Database& soccer_DB);
        static void create_player_menu(Database& soccer_DB);
        
        static void play_game_menu(Database& soccer_DB);
        
        static bool goals_scored(std::string team_name, int goals);
        static bool assists_given(std::string team_name, int assists);
        static bool cards_received(std::string team_name, int cards);
        
        static void update_player_goals(Database& soccer_DB, std::string team_name, int goals);
        static void update_player_assists(Database& soccer_DB, std::string team_name, int assists);
        static void update_player_cards(Database& soccer_DB, std::string team_name, int cards);
        
        static void player_stats_menu(Database& soccer_DB);
        static void team_stats_menu(Database& soccer_DB);
        static void league_stats_menu(Database& soccer_DB);

				static void match_points(Database& soccer_DB, std::string first_team_name, std::string second_team_name, int first_team_goals, int second_team_goals);
        
        static void transfer_player(Database& soccer_DB);

				static void view_league(Database& soccer_DB);
				static void view_team(Database& soccer_DB);
				static void view_player(Database& soccer_DB);
    };
}
#endif /* defined(__RDBMS__Menu__) */