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
    token_stream << "none" << "\", 0);";   /* current champ to null -> " " */
    
    return token_stream.str();
}

std::string Token_Generator::create_team(string name, string league, string city, string sponsor, int year_founded, string manager, string kit) {
    std::stringstream token_stream;
    
    //team -> NAME, city, sponsor, year_founded, MANAGER, kit, points, goals, assists, cards
    
    token_stream << "INSERT INTO _TEAM VALUES FROM (\"" << name << "\", \"" << league;
    token_stream << "\", \"" << city << "\", \"" << sponsor << "\", ";
    token_stream << year_founded << ", \"" << manager << "\", \"" << kit << "\" ,";
    token_stream << " 0, 0, 0, 0);";
    return token_stream.str();
}

std::string Token_Generator::create_player(string name, int jersey_num, string team, string position) {
    //player -> name, TEAM, JERSEY_NUM, position, goals, assists, cards, starter
    
    std::stringstream token_stream;
    
    token_stream << "INSERT INTO _PLAYER VALUES FROM (\"" << name;
    token_stream << ", \"" << team << "\", \"" << "\", " << jersey_num;
    token_stream << position << "\", 0, 0, 0, \"no\");";    //HOW FORMAT STARTERS??
                                                                    //"no" and "yes"
    return token_stream.str();
}

std::string Token_Generator::update_goals_team(string team_name, int goals){
	std::stringstream token_stream;
	token_stream << "UPDATE _TEAM" << " SET goals = ++" << goals;
	token_stream << " WHERE  name == \"" << team_name << "\" ;";

	return token_stream.str();
}
std::string Token_Generator::update_goals_player(string team_name, int jersey_num){
	std::stringstream token_stream;
	token_stream << "UPDATE _PLAYER" << " SET goals = ++" << 1;
	token_stream << " WHERE  team == \"" << team_name << "\" && jersey_num == " << jersey_num << " ;";

	return token_stream.str();
}

std::string Token_Generator::update_assists_player(string team_name, int jersey_num){
	std::stringstream token_stream;
	token_stream << "UPDATE _PLAYER" << " SET assists = ++" << 1;
	token_stream << " WHERE  team == \"" << team_name << "\" && jersey_num == " << jersey_num << " ;";

	return token_stream.str();
}

std::string Token_Generator::update_assists_team(string team_name, int assists){
	std::stringstream token_stream;
	token_stream << "UPDATE _PLAYER" << " SET assists = ++" << assists;
	token_stream << " WHERE  name == \"" << team_name << "\" ;";

	return token_stream.str();
}

std::string Token_Generator::update_cards_player(string team_name, int jersey_num){
	std::stringstream token_stream;
	token_stream << "UPDATE _PLAYER" << " SET cards = ++" << 1;
	token_stream << " WHERE  team == \"" << team_name << "\" && jersey_num == " << jersey_num << " ;";

	return token_stream.str();
}

std::string Token_Generator::update_cards_team(string team_name, int cards){ 
	std::stringstream token_stream;
	token_stream << "UPDATE _PLAYER" << " SET cards = ++" << cards;
	token_stream << " WHERE  name == \"" << team_name << "\" ;";

	return token_stream.str();
}

std::string Token_Generator::update_points_team(std::string team_name, int points){return "";}

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











