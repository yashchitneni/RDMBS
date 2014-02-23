/*
 class: Tokenizer
 Acts as direct interface with DBMS by generating tokens in a stringstream and 
    dispensing those tokens to the parser.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Token_Generator {
public:
    
    static std::string create_league(string name, string country, string sponsor);
    
    static std::string create_team(string name, string league, string city, string sponsor, int year_founded, string manager, string kit);
    
    static std::string create_player(string name, int jersey_num, string team, string position);
    
    static std::string update_goals_team(string team_name, int goals);
    static std::string update_goals_player(string team_name, int jersey_num);
    static std::string update_assists_team(string team_name, int assists);
    static std::string update_assists_player(string team_name, int jersey_num);
    static std::string update_cards_team(string team_name, int cards);
    static std::string update_cards_player(string team_name, int jersey_num);
    static std::string update_points_team(std::string team_name, int points);

    static std::string view_player_stats(string player_name, int jersey_num, string team_name /* this can change */);
    
    static std::string view_team_stats(string team_name, string manager);
    
    static std::string view_league_stats(string league_name /* league key */);
        //compute current_champion within
    
    static std::string view_team_roster(string team_name);
        //for displaying roster
        //NEED TO BE SURE THAT THE RELATION HAS BEEN MADE FIRST
            //I have no error checking in here, b/c i don't know. either in DBMS or in the calling function.
    
    static std::string view_league_teams(string league_name);
        //for displaying list of teams in league
    
    static std::string transfer_player(string player_name, string team_from, string team_to /*data, like player to transfer, from/to, etc.*/);
        //CANNOT HAVE CONFLICTING JERSEY NUMBERS so need to give him new one if conflicts.
        //need to update starting roster for each team to maintain at 11
    
    
    /*
     will we have any other user options available?
     */
    
    
    //NEED ERROR HANDLING for teams/players/leagues that don't exist!
    
    
    
    //dispense method, to pour into parser
    //std::string dispense();
    
private:
    //std::stringstream token_stream;
    
    //sub-methods, to be called by individual options
        //are these necessary?
    
    
    //option play_game
//  void score_goal(/*team, num_goals, player*/);
};