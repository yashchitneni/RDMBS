#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Token_Generator {
public:
    static std::string create_league(string name, string country, string sponsor);
    
    static std::string create_team(string name, string league, string city, string sponsor, int year_founded, string manager, string kit);
    static std::string delete_
    
    static std::string create_player(string name, int jersey_num, string team, string position);
    static std::string delete_player(int jersey_num, string team_name);
    
    static std::string update_goals_team(string team_name, int goals);
    static std::string update_goals_player(string team_name, int jersey_num, int goals);
    static std::string update_assists_team(string team_name, int assists);
    static std::string update_assists_player(string team_name, int jersey_num, int assists);
    static std::string update_cards_team(string team_name, int cards);
    static std::string update_cards_player(string team_name, int jersey_num, int assists);
    static std::string update_points_team(std::string team_name, int points);
    static std::string update_num_teams(std::string league_name, int num_teams);
    
    static std::string get_num_goals(string team_name, int jersey_num);
    static std::string get_num_assists(string team_name, int jersey_num);
    static std::string get_num_cards(string team_name, int jersey_num);
    static std::string get_num_points(string team_name);
    
    static std::string get_num_team_goals(string team_name);
    static std::string get_num_team_assists(string team_name);
    static std::string get_num_team_cards(string team_name);
    
    static std::string view_player_stats(int jersey_num, string team_name);
    
    static std::string view_team_stats(string team_name);
    
    static std::string view_league_stats(string league_name);
    
    static std::string view_team_roster(string team_name);
    static std::string view_team_starting_roster(string team_name);
    static std::string view_match_lineup(std::string team_name1, std::string team_name2);
    
    static std::string view_league_teams(string league_name);
    
    static std::string transfer_player(int player_number, int new_player_number, string team_from, string team_to);
};