//
//  Application_Interface.cpp
//  RDBMS
//
//  Created by Yash Chitneni on 2/17/14.
//  Copyright (c) 2014 yash_chitneni. All rights reserved.
//

#include "Application_Interface.h"

#include <iostream>
#include <vector>
#include <string>

int main() {
    int input;
    
    std::cout << "For the following commands, please type the coinciding number of the command and press enter";
    
    std::cout << "1. Create a League" << std::endl;
    std::cout << "2. Create a Team" << std::endl;
    std::cout << "3. Create a Player" << std::endl;
    std::cout << "4. Play Game" << std::endl;
    std::cout << "5. View Player Stats" << std::endl;
    std::cout << "6. View Team Stats" << std::endl;
    std::cout << "7. Transfer Player" << std::endl;
    
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
        }
        
        if (input == 2) {
            std::string team_name;
            std::string city_name;
            std::string sponsor_name;
            int year_founded;
            std::string manager_name;
            std::string kit_color;
            
            std::cout << "Choose a Team name: ";
            std::cin >> team_name;
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
            
            std::string first_team_assists;
            std::string second_team_assists;
            
            std::string first_team_cards;
            std::string second_team_cards;

            
            
            /* Call function that displays players of team if goals scored */
            
        }
    }
}
























