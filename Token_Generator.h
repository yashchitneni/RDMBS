/*
 class: Tokenizer
 Acts as direct interface with DBMS by generating tokens in a stringstream and 
    dispensing those tokens to the parser.
 */

/*
 to do:
    initialize leagues, teams, players tables at beginning
 
    nail down menu options
        get specifics of internals of menu options
    implement menu option functions
    implement token generator function
    connect menu option functions to token generator
    display menu
        parsing user input
        displaying team roster when picking goal scorers
    pretty-ify the show functions
    work with Tim on proper grammar wording
    make sure no conflicts with header files
    create demo .db files to load at program start, to make initializing easier
 
    REPORT
        framework
    KEEP DEV LOG up to date
 */

//ordering of tuples
//league -> NAME, country, sponsor, current_champ, num_teams
//team -> NAME, league, city, sponsor, year_founded, MANAGER, kit, points, goals, assists, cards
//player -> name, JERSEY_NUM, TEAM, position, goals, assists, cards, starter
    //right now, uppercase attrs are primary keys
    //use update to change team(key)

//STANDARDIZED table header titles
//_LEAGUE -> league_name, country, sponsor, current_champ, num_teams
//_TEAM -> team_name, league, city, sponsor, year_founded, manager, kit, points, goals, assists, cards
//_PLAYER -> player_name, team, jersey_num, position, goals, assists, cards, starter


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
    
    static std::string transfer_player(string player_name, string team_from, string team_to /*data, like player to transfer, from/to, etc.*/);
        //CANNOT HAVE CONFLICTING JERSEY NUMBERS so need to give him new one if conflicts.
        //need to update starting roster for each team to maintain at 11
};