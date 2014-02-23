//
//  Menu.cpp
//  RDBMS
//
//  Created by Yash Chitneni on 2/22/14.
//  Copyright (c) 2014 yash_chitneni. All rights reserved.
//

#include "Menu.h"
#include "Token_Generator.h"

bool Menu::league_available(std::string league_name){
    
    /* Where/how to check database to see if league_name already exists. */
    
    //PLACE HOLDER FOR RIGHT NOW
    
    if (league_name != league_name) {
        return true;
    }
    return true;
}

bool Menu::team_available(std::string team_name, std::string league_name) {
 
    return true;
}

bool Menu::player_available(std::string player_name, int jersey_number, std::string team_name) {
    
    return true;
}

void Menu::original_menu(){
    
    std::cout << "For the following commands, please type the coinciding number of the command and press enter." << std::endl << std::endl;
    
    std::cout << "1. Create a League" << std::endl;
    std::cout << "2. Create a Team" << std::endl;
    std::cout << "3. Create a Player" << std::endl;
    std::cout << "4. Play Game" << std::endl;
    std::cout << "5. View Player Stats" << std::endl;
    std::cout << "6. View Team Stats" << std::endl;
    std::cout << "7. View League Stats" << std::endl;
    std::cout << "8. Transfer Player" << std::endl;
    std::cout << "9. Exit Program" << std::endl;
}

void Menu::create_league_menu() {
    std::string league_name;
    std::string country_name;
    std::string sponsor_name;
    
    std::cout << "Choose a League name: ";
    std::cin >> league_name;
    
    /* Take care of duplicates */
    
    if (league_available(league_name)) {
        std::cout << "What country is the league located in: ";
        std::cin >> country_name;
        std::cout << "Who are the official sponsors of the league: ";
        std::cin >> sponsor_name;
    }
    else {
        std::cout << "Sorry " << league_name << " already exists. Please choose another team name" << std::endl;
        create_league_menu();
    }
    
    Menu::soccer_DB.execute(Token_Generator::create_league(league_name, country_name, sponsor_name));
    
    /* What do we do about points */
}

void Menu::create_team_menu() {
    std::string team_name;
    std::string league_name;
    std::string city_name;
    std::string sponsor_name;
    int year_founded = 0;
    std::string manager_name;
    std::string kit_color;
    
    std::cout << "Choose a Team name: ";
    std::cin >> team_name;
    std::cout << "What league is the team going to play in: " << std::endl;
    std::cin >> league_name;
    
    /* Take care of duplicates */
    
    if (team_available(team_name, league_name)) {
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
    }
    else {
        std::cout << "Sorry " << team_name << " already exists. Please choose another team name" << std::endl;
        create_league_menu();
    }
    Menu::soccer_DB.execute(Token_Generator::create_team(team_name, league_name, city_name, sponsor_name, year_founded, manager_name, kit_color));
}

void Menu::create_player_menu() {
    
    std::string player_name;
    std::string team_name;
    int jersey_number;
    std::string position;
    
    std::cout << "Choose a Player name: ";
    std::cin >> player_name;
    std::cout << "What is his jersey number: ";
    std::cin >> jersey_number;
    std::cout << "What position does he play: ";
    std::cin >> position;
    std::cout << "What team does he play for: ";
    std::cin >> team_name;
    
    /* Check for Duplicates */
    
    Menu::soccer_DB.execute(Token_Generator::create_player(player_name, jersey_number, team_name, position));
}

void Menu::play_game_menu() {
    std::string league_name;
    
    std::string first_team_name;
    std::string second_team_name;
    
    std::string first_team_goals;
    std::string second_team_goals;
    
    std::string player_name;
    std::cout << "Who scored for " << first_team_name << ": " << std::endl;
    std::cin >> player_name;
    
    std::string first_team_assists;
    std::string second_team_assists;
    
    std::string first_team_cards;
    std::string second_team_cards;
    
    /* Call function that displays players of team if goals scored */
}

void Menu::player_stats_menu() {
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

void Menu::team_stats_menu() {
    std::string team_name;
    std::string league_name;
    
    std::cout << "Name of league in which team is: " << std::endl;
    std::cin >> league_name;
    std::cout << "Name of team: " << std::endl;
    std::cin >> team_name;
}

void Menu::league_stats_menu() {
    std::string league_name;
    
    std::cout << "Name of league to view: " << std::endl;
    std::cin >> league_name;
}

void Menu::transfer_player() {
    
}
