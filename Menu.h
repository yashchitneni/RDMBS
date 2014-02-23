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

/*
I made a couple changes, basically changing the functions to be static functions that take a database as input
Also I don't think that checking if a team/league/player exists already is necessary because the database doesn't allow duplicates in 
	the first place so adding a duplicate will do nothing
Additionally, make sure you do error checking for the inputs from the user (see the revised create_team_menu function), things to watch
	for: cin>> only gets the first word so getline is better, ie: any input that could have multiple words would only get the first word
			 added some error checking for reading integers in from cin
*/


namespace Team_Project_1_Database{
	class Menu {
	public:
<<<<<<< HEAD
        static void original_menu(Database& soccer_DB);
    
        static void create_league_menu(Database& soccer_DB);
        static void create_team_menu(Database& soccer_DB);
        static void create_player_menu(Database& soccer_DB);
        
        static void play_game_menu(Database& soccer_DB);
        
        static void player_stats_menu(Database& soccer_DB);
        static void team_stats_menu(Database& soccer_DB);
        static void league_stats_menu(Database& soccer_DB);
        
        static void transfer_player(Database& soccer_DB);
=======
			Menu();
    
			static void original_menu(Database& soccer_DB);
    
			bool league_available(std::string league_name);
			bool team_available(std::string team_name, std::string league_name);
			bool player_available(std::string player_name, int jersey_number, std::string team_name);
    
			static void create_league_menu(Database& soccer_DB);
			static void create_team_menu(Database& soccer_DB);
			static void create_player_menu(Database& soccer_DB);
			static void play_game_menu(Database& soccer_DB);
			static void player_stats_menu(Database& soccer_DB);
			static void team_stats_menu(Database& soccer_DB);
			static void league_stats_menu(Database& soccer_DB);
			static void transfer_player(Database& soccer_DB);
    
			/* Maybe unnecessary functions */
    
	//    void league_available(bool league_exists());
	//    void team_available(bool team_exists());
	//    void player_available(bool player_exists());
>>>>>>> TIm
	};
}
#endif /* defined(__RDBMS__Menu__) */
