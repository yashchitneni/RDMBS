//
//  Application_Interface.cpp
//  RDBMS
//
//  Created by Yash Chitneni on 2/17/14.
//  Copyright (c) 2014 yash_chitneni. All rights reserved.
//

#include "Token_Generator.h"
#include "Menu.h"

#include <iostream>
#include <vector>
#include <string>

using namespace Team_Project_1_Database;

void open_database();
void close_database();

Database soccer_DB;

int main() {
	open_database();
	atexit(close_database);
	while(true){
		std::string input;
		int choice;
		Menu::original_menu(soccer_DB);
		std::getline(cin, input);
		choice = atoi(input.c_str());
		switch(choice){
            case 0:
                std::cout << "Error reading input, try again" << std::endl;
                break;
            case 1:
                Menu::view_league(soccer_DB);
                break;
            case 2:
                Menu::view_team(soccer_DB);
                break;
            case 3:
                Menu::view_player(soccer_DB);
                break;
            case 4:
                Menu::create_league_menu(soccer_DB);
                break;
            case 5:
                Menu::create_team_menu(soccer_DB);
                break;
            case 6:
                Menu::create_player_menu(soccer_DB);
                break;
            case 7:
                Menu::play_game_menu(soccer_DB);
                break;
            case 8:
                Menu::player_stats_menu(soccer_DB);
                break;
            case 9:
                Menu::team_stats_menu(soccer_DB);
                break;
            case 10:
                Menu::league_stats_menu(soccer_DB);
                break;
            case 11:
                Menu::transfer_player(soccer_DB);
                break;
            case 12: exit(0);
		}
	}
}

void open_database(){
	soccer_DB.execute("OPEN _LEAGUE;");
	soccer_DB.execute("OPEN _TEAM;");
	soccer_DB.execute("OPEN _PLAYER;");
	std::cout << "Players, Teams, and Leagues have been loaded.\n";
	return;
}

void close_database(){
	soccer_DB.execute("CLOSE _LEAGUE;");
	soccer_DB.execute("CLOSE _TEAM;");
	soccer_DB.execute("CLOSE _PLAYER;");
	std::cout << "Players, Teams, and Leagues have been saved.\n";
	return;
}