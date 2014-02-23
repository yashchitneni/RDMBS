//
//  Application_Interface.cpp
//  RDBMS
//
//  Created by Yash Chitneni on 2/17/14.
//  Copyright (c) 2014 yash_chitneni. All rights reserved.
//

#include "Token_Generator.h"
#include "Menu.h"

/*
Some suggestions:
	-instead of having the main do all the work with the main menu, make a main menu method that displays the menu
	-also it might be better to make seperate functions to handle the inputs for each case, ie: a create league 
		function that handles the input/output for creating a league
	-also redisplay the menu after a command has been executed rather than only displaying it at the start of the program
	-might want to move the database declaration inside the main method so its not a global variable
	-I added getting league name for creating a team since it wasn't included
	-We might want to do atexit(close_database) to ensure that database is saved even upon crash or improper exiting (might not work if database is inside main)
	-add a exit option to the menu so that the user is able to exit out of the program
*/

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
			Menu::create_league_menu(soccer_DB);
			break;
		case 2: 
			Menu::create_team_menu(soccer_DB);
			break;
		case 3: 
			Menu::create_player_menu(soccer_DB);
			break;
		case 4: 
			Menu::play_game_menu(soccer_DB);
			break;
		case 5: 
			Menu::player_stats_menu(soccer_DB);
			break;
		case 6: 
			Menu::team_stats_menu(soccer_DB);
			break;
		case 7: 
			Menu::league_stats_menu(soccer_DB);
			break;
		case 8: 
			Menu::transfer_player(soccer_DB);
			break;
		case 9: exit(0);
		}
	}
}

void open_database(){
	soccer_DB.execute("OPEN _LEAGUE;");
	soccer_DB.execute("SHOW _LEAGUE;");
	soccer_DB.execute("OPEN _TEAM;");
	soccer_DB.execute("SHOW _TEAM;");
	soccer_DB.execute("OPEN _PLAYER;");
	soccer_DB.execute("SHOW _PLAYER;");
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




















