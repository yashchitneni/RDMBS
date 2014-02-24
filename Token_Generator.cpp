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
    token_stream << "\" , \"" << team << "\", " << jersey_num;
    token_stream << ", \"" << position << "\", 0, 0, 0, \"no\");";
		return token_stream.str();
}

std::string Token_Generator::update_goals_team(string team_name, int goals){
	std::stringstream token_stream;
	token_stream << "UPDATE _TEAM" << " SET goals = " << goals;
	token_stream << " WHERE  name == \"" << team_name << "\" ;";
	return token_stream.str();
}
std::string Token_Generator::update_goals_player(string team_name, int jersey_num, int goals){
	std::stringstream token_stream;
	token_stream << "UPDATE _PLAYER" << " SET goals = " << goals;
	token_stream << " WHERE  team == \"" << team_name << "\" && jersey_num == " << jersey_num << " ;";

	return token_stream.str();
}

std::string Token_Generator::update_assists_player(string team_name, int jersey_num, int goals){
	std::stringstream token_stream;
	token_stream << "UPDATE _PLAYER" << " SET assists = ++" << goals;
	token_stream << " WHERE  team == \"" << team_name << "\" && jersey_num == " << jersey_num << " ;";

	return token_stream.str();
}

std::string Token_Generator::update_assists_team(string team_name, int assists){
	std::stringstream token_stream;
	token_stream << "UPDATE _TEAM" << " SET assists = ++" << assists;
	token_stream << " WHERE  name == \"" << team_name << "\" ;";

	return token_stream.str();
}

std::string Token_Generator::update_cards_player(string team_name, int jersey_num, int goals){
	std::stringstream token_stream;
	token_stream << "UPDATE _PLAYER" << " SET cards = " << goals;
	token_stream << " WHERE  team == \"" << team_name << "\" && jersey_num == " << jersey_num << " ;";

	return token_stream.str();
}

std::string Token_Generator::update_cards_team(string team_name, int cards){ 
	std::stringstream token_stream;
	token_stream << "UPDATE _PLAYER" << " SET cards = " << cards;
	token_stream << " WHERE  name == \"" << team_name << "\" ;";

	return token_stream.str();
}

std::string Token_Generator::update_points_team(std::string team_name, int points){
	std::stringstream token_stream;
	token_stream << "UPDATE _TEAM SET points = " << points;
	token_stream << " WHERE name == \"" << team_name << "\" ;";
	return token_stream.str();
}

std::string Token_Generator::get_num_goals(string team_name, int jersey_num){
	std::stringstream token_stream;
	token_stream << "Num_goals <- project (goals) (select (team == \"" << team_name;
	token_stream << "\" && jersey_num == " << jersey_num << ") _PLAYER);";
	return token_stream.str();
}
std::string Token_Generator::get_num_assists(string team_name, int jersey_num){
	std::stringstream token_stream;
	token_stream << "Num_assists <- project (assists) (select (team == \"" << team_name;
	token_stream << "\" && jersey_num == " << jersey_num << ") _PLAYER);";
	return token_stream.str();
}
std::string Token_Generator::get_num_cards(string team_name, int jersey_num){
	std::stringstream token_stream;
	token_stream << "Num_cards <- project (cards) (select (team == \"" << team_name;
	token_stream << "\" && jersey_num == " << jersey_num << ") _PLAYER);";
	return token_stream.str();
}
std::string Token_Generator::get_team_goals(string team_name){
	std::stringstream token_stream;
	token_stream << "Team_goals <- project (goals) (select (name == \"" << team_name << "\") _TEAM);";
	return token_stream.str();
}
std::string Token_Generator::get_num_points(string team_name){
	std::stringstream token_stream;
	token_stream << "Num_points <- project (points) (select (name == \"" << team_name << "\") _TEAM);";
	return token_stream.str();
}

std::string Token_Generator::update_num_teams(std::string league_name, int num_teams){
	std::stringstream token_stream;
	token_stream << "UPDATE _LEAGUE" << " SET num_teams = " << num_teams;
	token_stream << " WHERE  name == \"" << league_name << "\" ;";

	return token_stream.str();
}

std::string Token_Generator::view_player_stats(std::string player_name, int jersey_num, string team_name) {
    std::stringstream token_stream;
    
    token_stream << player_name << " <- select (jersey_num == " << jersey_num;
    token_stream << " && team == " << team_name << ") _PLAYER;";
    
    return token_stream.str();
}

std::string Token_Generator::view_team_stats(string team_name) {
    
    std::stringstream token_stream;
    
    token_stream << team_name << " <- select (team_name == \"" << team_name;
    token_stream << "\" ) _TEAM;";
    
    return token_stream.str();
}

std::string Token_Generator::view_league_stats(string league_name) {
    
    std::stringstream token_stream;
    
    token_stream << "SHOW ( select (league_name == \"" << league_name;
    token_stream << "\") _LEAGUE ) ;";
    
    return token_stream.str();
}

std::string Token_Generator::view_team_roster(string team_name) {
    
    std::stringstream token_stream;
    
    token_stream << "SHOW (select ( team == \"" << team_name << "\" ) _PLAYER );";
    
    return token_stream.str();
}

std::string Token_Generator::view_team_starting_roster(string team_name) {
    
    std::stringstream token_stream;
    
    token_stream << "SHOW (project (name, jersey_num) (select ( team == \"" << team_name << "\" && starter == \"yes\" ) _PLAYER ));";
    return token_stream.str();
}

std::string Token_Generator::view_match_lineup(std::string team_name1, std::string team_name2){
	std::stringstream token_stream;
	token_stream << "SHOW ((project (name, team, jersey_num) ";
	token_stream << "(select (team == \"" << team_name1 << "\" ) _PLAYER))";
	token_stream << " + (project (name, team, jersey_num) ";
	token_stream <<	"(select (team == \"" << team_name2 << "\" ) _PLAYER)));";
	return token_stream.str();
}

std::string Token_Generator::view_league_teams(string league_name) {
    
    std::stringstream token_stream;
    
    token_stream << "SHOW (select ( league == \"" << league_name << "\" ) _TEAM );";
    
    return token_stream.str();
}

std::string transfer_player(string player_name, string team_from, string team_to /*data, like player to transfer, from/to, etc.*/) {
    
    //will have to update team AND jersey num...
    
    return "";
}











