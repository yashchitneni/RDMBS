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
    std::cout << "1. View Leagues" << std::endl;
    std::cout << "2. View Teams" << std::endl;
    std::cout << "3. View Players" << std::endl;
    std::cout << "4. Create a League" << std::endl;
    std::cout << "5. Create a Team" << std::endl;
    std::cout << "6. Create a Player" << std::endl;
    std::cout << "7. Play Game" << std::endl;
    std::cout << "8. View Player Stats" << std::endl;
    std::cout << "9. View Team Stats" << std::endl;
    std::cout << "10. View League Stats" << std::endl;
    std::cout << "11. Transfer Player" << std::endl;
    std::cout << "12. Exit Program" << std::endl;
    std::cout << " -> ";
}

void Menu::create_league_menu(Database& soccer_DB) {
    std::string league_name;
    std::string country_name;
    std::string sponsor_name;
    
    std::cout << "Choose a League name\n -> ";
    std::getline(cin, league_name);
    std::cout << "What country is the league located in\n -> ";
    std::getline(cin, country_name);
    std::cout << "Who are the official sponsors of the league\n -> ";
    std::getline(cin,sponsor_name);
    
    soccer_DB.execute(Token_Generator::create_league(league_name, country_name, sponsor_name));
    
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
    
    soccer_DB.execute(Token_Generator::update_num_teams(league_name, 0));
}

void Menu::create_player_menu(Database& soccer_DB) {
    
    std::string player_name;
    std::string team_name;
    int jersey_number;
    std::string position;
    
    std::cout << "Choose a Player name: ";
    std::getline(cin, player_name);
    do{
        std::cout << "What is his jersey number: ";
        std::string input;
        std::getline(cin, input);
        jersey_number = atoi(input.c_str());
    }while(jersey_number == 0);
    std::cout << "What position does he play: ";
    std::getline(cin, position);
    std::cout << "What team does he play for: ";
    std::getline(cin, team_name);
    
    soccer_DB.execute(Token_Generator::create_player(player_name, jersey_number, team_name, position));
}

void Menu::update_player_goals(Database& soccer_DB, std::string team_name, int goals) {
    if (goals > 0) {
        std::vector<std::string> table_data;
        soccer_DB.execute(Token_Generator::view_team_starting_roster(team_name));
        int assists = 0;
        for (int i = 1; i <= goals; i++) {
            int player_number;
            std::cout << "Enter the number of the player that scored the " << i << " goal\n -> ";
            std::string input;
            std::getline(cin, input);
            player_number = atoi(input.c_str());
            int current_goals = 0;
            soccer_DB.execute(Token_Generator::get_num_goals(team_name, player_number), table_data);
            if(table_data.size())
                current_goals = atoi(table_data[0].c_str()) + 1;
            soccer_DB.execute(Token_Generator::update_goals_player(team_name, player_number, current_goals));
            int assister_number;
            std::cout << "Enter the number of the player that assisted the " << i << " goal (0 for no assist)\n -> ";
            std::getline(cin, input);
            assister_number = atoi(input.c_str());
            if(assister_number){
                int current_assists = 0;
                table_data.clear();
                soccer_DB.execute(Token_Generator::get_num_assists(team_name, player_number), table_data);
                if(table_data.size())
                    current_assists = atoi(table_data[0].c_str()) + 1;
                soccer_DB.execute(Token_Generator::update_assists_player(team_name, assister_number, current_assists));
                assists++;
            }
        }
        int current_team_assists = 0;
        table_data.clear();
        soccer_DB.execute(Token_Generator::get_num_team_assists(team_name), table_data);
        if(table_data.size())
            current_team_assists = atoi(table_data[0].c_str()) + assists;
        soccer_DB.execute(Token_Generator::update_assists_team(team_name, current_team_assists));
    }
}

void Menu::update_player_cards(Database& soccer_DB, std::string team_name, int cards) {
    if (cards > 0) {
        std::vector<std::string> table_data;
        soccer_DB.execute(Token_Generator::view_team_starting_roster(team_name));
        for (int i = 1; i <= cards; i++) {
            int player_number;
            std::cout << "Enter the number of the player that received the " << i << " card\n -> ";
            std::string input;
            std::getline(cin, input);
            player_number = atoi(input.c_str());
            int current_cards = 0;
            soccer_DB.execute(Token_Generator::get_num_cards(team_name, player_number), table_data);
            if(table_data.size())
                current_cards = atoi(table_data[0].c_str()) + 1;
            soccer_DB.execute(Token_Generator::update_cards_player(team_name, player_number, current_cards));
        }
    }
}

void Menu::play_game_menu(Database& soccer_DB) {
    std::string league_name = "";
    
    std::string first_team_name = "";
    std::string second_team_name = "";
    
    std::string int_input;
    int first_team_goals = 0;
    int second_team_goals = 0;
    
    int first_team_cards = 0;
    int second_team_cards = 0;
    std::vector<std::string> table_data;
    
    soccer_DB.execute("SHOW _LEAGUE;");
    std::cout << "What league do the teams play in?\n -> ";
    std::getline(cin, league_name);
    soccer_DB.execute(Token_Generator::view_league_teams(league_name));
    std::cout << "What is the name of the first team?\n -> ";
    std::getline(cin, first_team_name);
    do{
        std::cout << "What is the name of the second team?\n -> ";
        std::getline(cin, second_team_name);
    }while(first_team_name == second_team_name);
    std::cout << "MATCH LINEUP\n";
    soccer_DB.execute(Token_Generator::view_match_lineup(first_team_name, second_team_name));
    std::cout << "How many goals did " << first_team_name << " score\n -> ";
    std::getline(cin, int_input);
    first_team_goals = atoi(int_input.c_str());
    soccer_DB.execute(Token_Generator::get_num_team_goals(first_team_name), table_data);
    int first_team_current_goals = 0;
    if(table_data.size())
        first_team_current_goals = first_team_goals + atoi(table_data[0].c_str());
    soccer_DB.execute(Token_Generator::update_goals_team(first_team_name, first_team_current_goals));
    
    std::cout << "How many goals did " << second_team_name << " score\n -> ";
    std::getline(cin, int_input);
    second_team_goals = atoi(int_input.c_str());
    table_data.clear();
    soccer_DB.execute(Token_Generator::get_num_team_goals(second_team_name), table_data);
    int second_team_current_goals = 0;
    if(table_data.size())
        second_team_current_goals = second_team_goals + atoi(table_data[0].c_str());
    soccer_DB.execute(Token_Generator::update_goals_team(second_team_name, second_team_current_goals));
    
    match_points(soccer_DB, first_team_name, second_team_name, first_team_goals, second_team_goals);
    
    update_player_goals(soccer_DB, first_team_name, first_team_goals);
    update_player_goals(soccer_DB, second_team_name, second_team_goals);
    
    std::cout << "How many cards did " << first_team_name << " receive: " << std::endl;
    std::getline(cin, int_input);
    first_team_cards = atoi(int_input.c_str());
    table_data.clear();
    soccer_DB.execute(Token_Generator::get_num_team_cards(first_team_name), table_data);
    int first_team_current_cards = 0;
    if(table_data.size())
        first_team_current_cards = first_team_cards + atoi(table_data[0].c_str());
    soccer_DB.execute(Token_Generator::update_cards_team(first_team_name, first_team_current_cards));
    std::cout << "How many cards did " << second_team_name << " receive: " << std::endl;
    std::getline(cin, int_input);
    second_team_cards = atoi(int_input.c_str());
    table_data.clear();
    soccer_DB.execute(Token_Generator::get_num_team_cards(second_team_name), table_data);
    int second_team_current_cards = 0;
    if(table_data.size())
        second_team_current_cards = second_team_cards + atoi(table_data[0].c_str());
    soccer_DB.execute(Token_Generator::update_cards_team(second_team_name, second_team_current_cards));
    
    update_player_cards(soccer_DB, first_team_name, first_team_cards);
    update_player_cards(soccer_DB, second_team_name, second_team_cards);
}

void Menu::match_points(Database& soccer_DB, std::string first_team_name, std::string second_team_name, int first_team_goals, int second_team_goals) {
    int first_team_match_points = 0;
    int second_team_match_points = 0;
    std::vector<std::string> table_data;
    if (first_team_goals > second_team_goals) {
        first_team_match_points = 3;
        second_team_match_points = 0;
    }
    else if (first_team_goals == second_team_goals) {
        first_team_match_points = 1;
        second_team_match_points = 1;
    }
    else if (first_team_goals < second_team_goals) {
        first_team_match_points = 0;
        second_team_match_points = 3;
    }
    soccer_DB.execute(Token_Generator::get_num_points(first_team_name), table_data);
    if(table_data.size())
        first_team_match_points += atoi(table_data[0].c_str());
    soccer_DB.execute(Token_Generator::update_points_team(first_team_name, first_team_match_points));
    table_data.clear();
    soccer_DB.execute(Token_Generator::get_num_points(second_team_name), table_data);
    if(table_data.size())
        second_team_match_points += atoi(table_data[0].c_str());
    soccer_DB.execute(Token_Generator::update_points_team(second_team_name, second_team_match_points));
}

void Menu::player_stats_menu(Database& soccer_DB) {
    int jersey_num;
    std::string team_name;
    
    std::cout << "Name of team in which player plays: " << std::endl;
    std::getline(cin, team_name);
    soccer_DB.execute(Token_Generator::view_team_roster(team_name));
    std::cout << "What is his jersey number: " << std::endl;
    std::cin >> jersey_num;
    
    soccer_DB.execute(Token_Generator::view_player_stats(jersey_num, team_name));
}

void Menu::team_stats_menu(Database& soccer_DB) {
    std::string team_name;
    std::string league_name;
    
    std::cout << "Name of league in which team is: " << std::endl;
    std::getline(cin, league_name);
    soccer_DB.execute(Token_Generator::view_league_teams(league_name));
    std::cout << "Name of team: " << std::endl;
    std::getline(cin, team_name);
    
    soccer_DB.execute(Token_Generator::view_team_stats(team_name));
}

void Menu::league_stats_menu(Database& soccer_DB) {
    std::string league_name;
    
    std::cout << "Name of league to view: " << std::endl;
    std::cin >> league_name;
    
    soccer_DB.execute(Token_Generator::view_league_stats(league_name));
}

void Menu::transfer_player(Database& soccer_DB) {
    std::string team_name;
    int player_number;
    std::string new_team_name;
    int new_player_number;
    
    std::cout << "What team does the player you're looking to transfer play for: " << std::endl;
    std::getline(cin, team_name);
    soccer_DB.execute(Token_Generator::view_team_roster(team_name));
    std::cout << "What is the number of the player you want to transfer: " << std::endl;
    std::cin >> player_number;
    std::cout << "What team do you want to transfer player to: " << std::endl;
    std::getline(cin, new_team_name);
    
    soccer_DB.execute(Token_Generator::view_team_roster(new_team_name));
    
    std::cout << "Please choose a number to assign to the player that does not exist: " << std::endl;
    std::cin >> new_player_number;
    
    if (player_exists(soccer_DB, new_team_name, player_number)) {
        std::cout << "Please choose a number to assign to the player that does not exist: " << std::endl;
        std::cin >> new_player_number;
    }
    
    soccer_DB.execute(Token_Generator::transfer_player(player_number, new_player_number, team_name, new_team_name));
}

void Menu::view_league(Database& soccer_DB){
	soccer_DB.execute("SHOW _LEAGUE;");
}

void Menu::view_team(Database& soccer_DB){
	soccer_DB.execute("SHOW _TEAM;");
}

void Menu::view_player(Database& soccer_DB){
	soccer_DB.execute("SHOW _PLAYER;");
}