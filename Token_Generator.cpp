/*
 class: Tokenizer
 Acts as direct interface with DBMS by generating tokens in a stringstream and
 dispensing those tokens to the parser.
 */

//STANDARDIZED table header titles
//_LEAGUE -> league_name, country, sponsor, current_champ, num_teams
//_TEAM -> team_name, league, city, sponsor, year_founded, manager, kit, points, goals, assists, cards
//_PLAYER -> player_name, jersey_num, team, position, goals, assists, cards, starter


#include "Token_Generator.h"

std::string Token_Generator::create_league(string name, string country, string sponsor) {
    std::stringstream token_stream;
    
    //creating table implementation
    /*
    token_stream << "CREATE TABLE ";
    token_stream << name;
    token_stream << " (name VARCHAR(20), country VARCHAR(10), sponsor VARCHAR(10), ";
    */
    
    
    //league -> NAME, country, sponsor, current_champ, num_teams
    //caps are primary keys
    
    
    token_stream << "INSERT INTO _LEAGUE VALUES FROM (\"" << name;
    token_stream << "\", \"" << country << "\", \"" << sponsor << "\", \"";
    token_stream << " " << "\", 0);";   /* current champ to null -> " " */
    
    return token_stream.str();
}

std::string Token_Generator::create_team(string name, string league, string city, string sponsor, int year_founded, string manager, string kit) {
    std::stringstream token_stream;
    
    //team -> NAME, city, sponsor, year_founded, MANAGER, kit, points, goals, assists, cards
    
    token_stream << "INSERT INTO _TEAM VALUES FROM (\"" << name;
    token_stream << "\", \"" << city << "\", \"" << sponsor << "\", ";
    token_stream << year_founded << ", \"" << manager << "\", \"" << kit << "\"";
    token_stream << " 0, 0, 0, 0);";
    
    return token_stream.str();
}

std::string Token_Generator::create_player(string name, int jersey_num, string team, string position) {
    //player -> name, JERSEY_NUM, TEAM, position, goals, assists, cards, starter
    
    std::stringstream token_stream;
    
    token_stream << "INSERT INTO _PLAYER VALUES FROM (\"" << name;
    token_stream << "\", " << jersey_num << ", \"" << team << "\", \"";
    token_stream << position << "\", 0, 0, 0, \"no\");";    //HOW FORMAT STARTERS??
                                                                    //"no" and "yes"
    return token_stream.str();
}

std::string Token_Generator::form_roster(string team_name) {
    std::stringstream token_stream;
    
    token_stream << team_name << " <- select (team == \"" << team_name;
    token_stream << "\") _PLAYER;";
    
    return token_stream.str();
}

std::string Token_Generator::form_league(string league_name) {
    std::stringstream token_stream;
    
    token_stream << league_name << " <- select (league == \"" << league_name;
    token_stream << "\") _TEAM;";
    
    return token_stream.str();
}

/*
 
 
 play_game methods go here
 
 
 */





std::string Token_Generator::view_player_stats(string player_name, int jersey_num, string team_name) {
    std::stringstream token_stream;
    
    token_stream << player_name << " <- select (jersey_num == " << jersey_num;
    token_stream << " && team == " << team_name << ") _PLAYER;";
    
    return token_stream.str();
}

std::string Token_Generator::view_team_stats(string team_name, string manager) {
    
    std::stringstream token_stream;
    
    token_stream << team_name << " <- select (team_name == \"" << team_name;
    token_stream << "\" && manager == \"" << manager << "\") _TEAM;";
    
    return token_stream.str();
}

std::string Token_Generator::view_league_stats(string league_name) {
    
    std::stringstream token_stream;
    
    token_stream << league_name << " <- select (league_name == \"" << league_name;
    token_stream << "\") _LEAGUE;";
    
    return token_stream.str();
}

std::string Token_Generator::view_team_roster(string team_name) {
    
    std::stringstream token_stream;
    
    token_stream << "SHOW " << team_name << ";";
    
    return token_stream.str();
}

std::string Token_Generator::view_league_teams(string league_name) {
    
    std::stringstream token_stream;
    
    token_stream << "SHOW " << league_name << ";";
    
    return token_stream.str();
}

std::string transfer_player(string player_name, string team_from, string team_to /*data, like player to transfer, from/to, etc.*/) {
    
    //will have to update team AND jersey num...
    
    return "";
}











