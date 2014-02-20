/*
 class: Tokenizer
 Acts as direct interface with DBMS by generating tokens in a stringstream and
 dispensing those tokens to the parser.
 */

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
    
    
    token_stream << "INSERT INTO " << /* leagues table name << */ " VALUES FROM (\"" << name;
    token_stream << "\", \"" << country << "\", \"" << sponsor << "\", \"";
    token_stream << /* current champ to null */ " " << "\", 0);";
    
    return token_stream.str();
}

std::string create_team(string name, string league, string city, string sponsor, int year_founded, string manager, string kit) {
    std::stringstream token_stream;
    
    //team -> NAME, city, sponsor, year_founded, MANAGER, kit, points, goals, assists, cards
    
    token_stream << "INSERT INTO " << /* teams table name << */ " VALUES FROM (\"" << name;
    token_stream << "\", \"" << city << "\", \"" << sponsor << "\", ";
    token_stream << year_founded << ", \"" << manager << "\", \"" << kit << "\"";
    token_stream << " 0, 0, 0, 0);";
    
    return token_stream.str();
}

std::string create_player(string name, int number, string team, string position) {
    //player -> name, JERSEY_NUM, TEAM, position, goals, assists, cards, starter
    
    std::stringstream token_stream;
    
    token_stream << "INSERT INTO " << /* players table name << */ " VALUES FROM (\"" << name;
    token_stream << "\", " << number << ", \"" << team << "\", \"";
    token_stream << position << "\", 0, 0, 0, \"no\");";    //HOW FORMAT STARTERS??
    
    return token_stream.str();
}

std::string form_roster(string team_name) {
    std::stringstream token_stream;
    
    token_stream << team_name << " <- select (" << /* team header name <<*/ " == \"" << team_name;
    token_stream << "\") "  /* << players table */ << ";";
    
    return token_stream.str();
}

std::string form_league(string league_name) {
    std::stringstream token_stream;
    
    token_stream << league_name << " <- select (" << /* team header name <<*/ " == \"" << team_name;
    token_stream << "\") "  /* << players table */ << ";";
    
    return token_stream.str();
}



