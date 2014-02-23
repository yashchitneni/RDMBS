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
    //maybe better to make all static, put string stream inside each function, and dispense at end of function
    
    
    //constructors
    //Token_Generator();
    
    //option methods
    
    static std::string create_league(string name, string country, string sponsor);    //more data?
        //creates tuple to insert into leagues
        //initialize current_champion to NULL
        //initialize num of teams to 0
    
    static std::string create_team(string name, string league, string city, string sponsor, int year_founded, string manager, string kit);
        //initialize "points" (use point system for wins/losses/ties), goals_scores, assists, and cards to 0 within
    
    static std::string create_player(string name, int jersey_num, string team, string position);   //also include "invisible" attributes, like goals and assists
        //goals, assists, cards = 0
        //starting = no
        //can pass "" for team to make free agent
            //probably not...
    
    static std::string form_roster(string team_name);   //don't need this... ", vector<string> players"
    
    static std::string form_league(string league_name); //don't need this... ", vector<string> teams"
   
    static std::string play_game(/*data, like which teams, etc.*/);   //THESE ARE FINAL STATS, after the game.
    static std::string play_game(string team1, string team2, int num_goals1, int num_goals2, vector<string> goal_scorers1, vector<string> goal_scorers2, int assists1, int assists2, vector<string> assisters1, vector<string> assisters2, int cards1, int cards2, vector<string> foulers1, vector<string> foulers2); //pass array of strings with same size as number of goals
        //look at contents of vector to determine how many for which players
        //decide how vector is structure later\
    
        //SPLIT UP INTO SEVERAL FUNCTIONS, with each update separate
    
    
        //update scores and goals, etc. for ONLY "big three" tables!
        //and REGENERATE roster tables for EVERY show!
    
    static std::string play_game(string team1, string team2);
    //static std::string game_goals_scored();
        //not sure how we're going to do this. can i access within? no..
    
    //may need more info to access (primary keys)
    static std::string update_goals_team(string team_name, int goals);
    static std::string update_goals_player(string team_name, int jersey_num);
    static std::string update_assists_team(string team_name, int assists);
    static std::string update_assists_player(string team_name, int jersey_num);
    static std::string update_cards_team(string team_name, int cards);
    static std::string update_cards_player(string team_name, int jersey_num);
    static std::string update_points_team(std::string team_name, int points);

    static std::string view_player_stats(string player_name, int jersey_num, string team_name /* this can change */);
    //not sure exactly what identifying info we need...
    //maybe access the giant Player database and use unique IDs for ALL players? just an idea.
    
    static std::string view_team_stats(string team_name, string manager);   //do we need league too?
    
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