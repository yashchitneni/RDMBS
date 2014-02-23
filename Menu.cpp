//
//  Menu.cpp
//  RDBMS
//
//  Created by Yash Chitneni on 2/22/14.
//  Copyright (c) 2014 yash_chitneni. All rights reserved.
//

#include "Menu.h"
#include "Token_Generator.h"

using namespace Team_Project_1_Database;

void Menu::original_menu(Database& soccer_DB){
    
    std::cout << "\nFor the following commands, please type the coinciding number of the command and press enter." << std::endl;
    std::cout << "1. Create a League" << std::endl;
    std::cout << "2. Create a Team" << std::endl;
    std::cout << "3. Create a Player" << std::endl;
    std::cout << "4. Play Game" << std::endl;
    std::cout << "5. View Player Stats" << std::endl;
    std::cout << "6. View Team Stats" << std::endl;
    std::cout << "7. View League Stats" << std::endl;
    std::cout << "8. Transfer Player" << std::endl;
    std::cout << "9. Exit Program" << std::endl;
    std::cout << " -> ";
}

void Menu::create_league_menu(Database& soccer_DB) {
    std::string league_name;
    std::string country_name;
    std::string sponsor_name;
    
    std::cout << "Choose a League name: ";
    std::cin >> league_name;
    std::cout << "What country is the league located in: ";
    std::cin >> country_name;
    std::cout << "Who are the official sponsors of the league: ";
    std::cin >> sponsor_name;
    
    soccer_DB.execute(Token_Generator::create_league(league_name, country_name, sponsor_name));
    
    /* What do we do about points */
}

void Menu::create_team_menu(Database& soccer_DB) {
    std::string team_name;
    std::string league_name;
    std::string city_name;
    std::string sponsor_name;
    int year_founded = 0;
    std::string manager_name;
    std::string kit_color;
    
    std::cout <<"\nEnter the following information about the team:" << std::endl;
    std::cout << "Choose a Team name: ";
    std::getline(cin, team_name);
    std::cout << "What league is the team going to play in: ";
    std::getline(cin, league_name);
    std::cout << "What city is the team located in: ";
    std::getline(cin, city_name);
    std::cout << "Who are the official sponsors of the team: ";
    std::getline(cin, sponsor_name);
    do{
        std::cout << "What year was the team founded: ";
        std::string input;
        std::getline(cin, input);
        year_founded = atoi(input.c_str());
    }while(!year_founded);
    std::cout << "What is the name of the coach: ";
    std::getline(cin, manager_name);
    std::cout << "What is the color of the kit: ";
    std::getline(cin, kit_color);
    soccer_DB.execute(Token_Generator::create_team(team_name, league_name, city_name, sponsor_name, year_founded, manager_name, kit_color));
}

void Menu::create_player_menu(Database& soccer_DB) {
    
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
    
    soccer_DB.execute(Token_Generator::create_player(player_name, jersey_number, team_name, position));
}

void Menu::update_player_goals(Database& soccer_DB, std::string team_name, int goals) {
    if (goals > 0) {
        soccer_DB.execute(Token_Generator::view_team_roster(team_name));
        int assists = 0;
        for (int i = 0; i <= goals; i++) {
            int player_number;
            std::cout << "Who scored the " << i << " goal: " << std::endl;
            std::cin >> player_number;
            soccer_DB.execute(Token_Generator::update_goals_player(team_name, player_number));
            int assister_number;
            std::cout << "Who assisted the " << i << " goal: " << std::endl;
            std::cin >> assister_number;
            soccer_DB.execute(Token_Generator::update_assists_player(team_name, assister_number));
            assists++;
        }
        soccer_DB.execute(Token_Generator::update_assists_team(team_name, assists));
    }
}

void Menu::update_player_cards(Database& soccer_DB, std::string team_name, int cards) {
    if (cards > 0) {
        soccer_DB.execute(Token_Generator::view_team_roster(team_name));
        for (int i = 0; i <= cards; i++) {
            int player_number;
            std::cout << "Who received the " << i << " card: " << std::endl;
            std::cin >> player_number;
            soccer_DB.execute(Token_Generator::update_cards_player(team_name, player_number));
        }
    }
}

void Menu::play_game_menu(Database& soccer_DB) {
    std::string league_name;
    
    std::string first_team_name;
    std::string second_team_name;
    
    int first_team_goals;
    int second_team_goals;
    
    int first_team_cards;
    int second_team_cards;
    
    std::cout << "How many goals did " << first_team_name << " score: " << std::endl;
    std::cin >> first_team_goals;
    soccer_DB.execute(Token_Generator::update_goals_team(first_team_name, first_team_goals));
    
    std::cout << "How many goals did " << second_team_name << " score: " << std::endl;
    std::cin >> second_team_goals;
    soccer_DB.execute(Token_Generator::update_goals_team(second_team_name, second_team_goals));
    
    update_player_goals(soccer_DB, first_team_name, first_team_goals);
    update_player_goals(soccer_DB, second_team_name, second_team_goals);
    
    std::cout << "How many cards did " << first_team_name << " receive: " << std::endl;
    std::cin >> first_team_cards;
    std::cout << "How many cards did " << second_team_name << " receive: " << std::endl;
    std::cin >> second_team_cards;
    
    update_player_cards(soccer_DB, first_team_name, first_team_cards);
    update_player_cards(soccer_DB, second_team_name, second_team_cards);
}

void Menu::player_stats_menu(Database& soccer_DB) {
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

void Menu::team_stats_menu(Database& soccer_DB) {
    std::string team_name;
    std::string league_name;
    
    std::cout << "Name of league in which team is: " << std::endl;
    std::cin >> league_name;
    std::cout << "Name of team: " << std::endl;
    std::cin >> team_name;
}

void Menu::league_stats_menu(Database& soccer_DB) {
    std::string league_name;
    
    std::cout << "Name of league to view: " << std::endl;
    std::cin >> league_name;
}

void Menu::transfer_player(Database& soccer_DB) {
    
}