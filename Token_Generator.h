/*
 class: Tokenizer
 Acts as direct interface with DBMS by generating tokens in a stringstream and 
    dispensing those tokens to the parser.
 */

/*
 to do:
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


#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Token_Generator {
public:
    //maybe better to make all static, put string stream inside each function, and dispense at end of function
    
    
    //constructors
    Token_Generator();
    
    //option methods
    
    void create_league(string name, string country, string sponsor);    //more data?
        //initialize current_champion to NULL
        //initialize num of teams to 0
    
    void create_team(string name, string city, string sponsor, int year_founded, string manager, string kit);
        //initialize "points" (use point system for wins/losses/ties), goals_scores, assists, and cards to 0 within
    
    void form_roster(string team_name, vector<string> players);
    
    void form_league(string league_name, vector<string> teams);
    
    
    
    void create_player(string name, int number, string position);   //also include "invisible" attributes, like goals and assists
        //goals, assists, cards = 0
        //starting = no
   
    void play_game(/*data, like which teams, etc.*/);   //THESE ARE FINAL STATS, after the game.
    void play_game(string team1, string team2, int num_goals1, int num_goals2, vector<string> goal_scorers1, vector<string> goal_scorers2, int assists1, int assists2, vector<string> assisters1, vector<string> assisters2, int cards1, int cards2, vector<string> foulers1, vector<string> foulers2); //pass array of strings with same size as number of goals
        //look at contents of vector to determine how many for which players
        //decide how vector is structure later
    
    
    void view_player_stats(string player_name, string team_name /* this can change */);
    //not sure exactly what identifying info we need...
    //maybe access the giant Player database and use unique IDs for ALL players? just an idea.
    
    void view_team_stats(string team_name, string league_name /* team key */);
    
    void view_league_stats(string league_name /* league key */);
        //compute current_champion within
    
    void transfer_player(string player_name, string team_from, string team_to /*data, like player to transfer, from/to, etc.*/);
        //CANNOT HAVE CONFLICTING JERSEY NUMBERS so need to give him new one if conflicts.
        //need to update starting roster for each team to maintain at 11
    
    
    /*
     will we have any other user options available?
     */
    
    
    //NEED ERROR HANDLING for teams/players/leagues that don't exist!
    
    
    
    //dispense method, to pour into parser
    std::string dispense();
    
private:
    std::stringstream token_stream;
    
    //sub-methods, to be called by individual options
        //are these necessary?
    
    
    //option play_game
//  void score_goal(/*team, num_goals, player*/);
};