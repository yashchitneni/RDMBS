//
//  Application_Interface.cpp
//  RDBMS
//
//  Created by Yash Chitneni on 2/17/14.
//  Copyright (c) 2014 yash_chitneni. All rights reserved.
//

#include "Token_Generator.h"
#include "Database.h"

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

void open_database();
void close_database();

Team_Project_1_Database::Database soccer_DB;

int main() {
	open_database();
	atexit(close_database);
    int input;
    
    std::cout << "For the following commands, please type the coinciding number of the command and press enter." << std::endl;
    std::cout << "1. Create a League" << std::endl;
    std::cout << "2. Create a Team" << std::endl;
    std::cout << "3. Create a Player" << std::endl;
    std::cout << "4. Play Game" << std::endl;
    std::cout << "5. View Player Stats" << std::endl;
    std::cout << "6. View Team Stats" << std::endl;
    std::cout << "7. Transfer Player" << std::endl;
		std::cout << "8. Exit" << std::endl << std::endl;
    std::cout << "-> ";

    while (true) {
        std::cin >> input;
        
        if (input == 1) {
            std::string league_name;
            std::string country_name;
            std::string sponsor_name;
            
            std::cout << "Choose a League name: ";
            std::cin >> league_name;
            std::cout << "What country is the league located in: ";
            std::cin >> country_name;
            std::cout << "Who are the official sponsors of the league: ";
            std::cin >> sponsor_name;
            
            /* TAKE CARE OF CHAMPIONS BASED ON POINTS ? */
        }
        
        if (input == 2) {
            std::string team_name;
						std::string league_name;
            std::string city_name;
            std::string sponsor_name;
            int year_founded;
            std::string manager_name;
            std::string kit_color;
            
            std::cout << "Choose a Team name: ";
            std::cin >> team_name;
						std::cout << "What league do they play in: ";
            std::cin >> league_name;
            std::cout << "What city is the team located in: ";
            std::cin >> city_name;
            std::cout << "Who are the official sponsors of the team: ";
            std::cin >> sponsor_name;
            std::cout << "What year was the team founded: ";
            std::cin >> year_founded;
            std::cout << "What is the name of the coach: ";
            std::cin >> manager_name;
            std::cout << "What is the color of the kit: ";
            std::cin >> kit_color;
            
            soccer_DB.execute(Token_Generator::create_team(team_name, league_name, city_name, sponsor_name, year_founded, manager_name, kit_color));
        }
        
        if (input == 3) {
            
            /* Error check to ensure jersey number is not repeated */
            
            std::string player_name;
            int jersey_number;
            std::string position;
            
            std::cout << "Choose a Player name: ";
            std::cin >> player_name;
            std::cout << "What is his jersey number: ";
            std::cin >> jersey_number;
            std::cout << "What position does he play: ";
            std::cin >> position;
        }
        
        if (input == 4) {
            std::string league_name;
            
            std::string first_team_name;
            std::string second_team_name;
            
            std::string first_team_goals;
            std::string second_team_goals;
            
            bool goalScored(int goals);
            
            
            std::string first_team_assists;
            std::string second_team_assists;
            
            std::string first_team_cards;
            std::string second_team_cards;

            
            
            /* Call function that displays players of team if goals scored */
        }
        
        if (input == 5) {
            std::string player_name;
            std::string jersey_num;
            std::string team_name;
            
            std::cout << "Name of team in which player plays: " << std::endl;
            std::cin >> team_name;
            std::cout << "What is his jersey number: " << std::endl;
            std::cin >> jersey_num;
            std::cout << "What is the player's name: ";
            std::cin >> player_name;
            
        }
        
        if (input == 6) {
            std::string team_name;
            std::string league_name;
            
            std::cout << "Name of league in which team is: " << std::endl;
            std::cin >> league_name;
            std::cout << "Name of team: " << std::endl;
            std::cin >> team_name;
        }
        
        if (input == 7) {
            std::string league_name;
            
            std::cout << "Name of league to view: " << std::endl;
            std::cin >> league_name;
        }
				if (input == 8) {
					exit(0);
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




















