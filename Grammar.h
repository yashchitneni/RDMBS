#ifndef _GRAMMAR
#define _GRAMMAR

#include "Relation.h"
#include <regex>
#include <fstream>

namespace Team_Project_1_Database{
    class Grammar{
    public:
        /*
        Main function that takes in the entire input then decides if it is a command or query
        calls either the command or query function
        */
        static void program(std::string input, std::vector<Relation>& tables);
    private:
        friend class Relation;

        /*
        Command function that takes a command as input and decides which command should be executed
        */
        static void command(
            std::string input,
            std::vector<Relation>& tables);

        /*
        Open function that takes a table name as input and opens the corresponding database file
        */
        static void open_cmd(
            std::string input,
            std::vector<Relation>& tables);

        /*
        Close function that takes a table name as input that saves and closes the corresponding table
        */
        static void close_cmd(
            std::string input,
            std::vector<Relation>& tables);

        /*
        Write function that takes a table name as input and creates the corresponding database file
        */
        static void write_cmd(std::string input);

        /*
        Show function function that takes a reference to a table as input and prints out its content to the console
        */
        static void show_cmd(Relation& table);

        /*
        Create function that takes a table name, keys, and attributes as input and constructes a new table
        keys is a list of all the key names, with each one separated by a ","
        attrs is a list of all the attributes with their type, with each one separated by a ","
        */
        static void create_cmd(
            std::string table_name,
            std::string keys,
            std::string attrs,
            std::vector<Relation>& tables);

        /*
        Update function that takes a table name, attributes to be updated, and conditions as input and 
            updates the values of the corresponding table that meet the condition
        attrs is a list of all the attribute names to be updated and the new value of the form "name == new_value", with each one separated by a ","
        conditions is a list of conditions to be met, with each one separated by a "||"
        */
        static void update_cmd(std::string table_name,
            std::string attrs, std::string conditions,
            std::vector<Relation>& tables);

        /*
        Insert function that takes a two tables as input and inserts the values from the second into the first
        */
        static void insert_cmd(
            Relation& table,
            Relation other_table);

        /*
        Insert function that takes a table and a literals as input and inserts the literals into the table
        literals is a list of the literal of the form int or "string", with each literal separated by a ","
        */
        static void insert_cmd(
            Relation& table,
            std::string literals);

        /*
        Delete function that takes a table and conditions as input and removes the rows that meet the condition
        conditions is a list of conditions to be met, with each one separated by a "||"
        */
        static  void delete_cmd(
            Relation& table,
            std::string condition);

        /*
        Query function that takes the query as input and decides what query to perform
        */
        static void query(
            std::string input,
            std::vector<Relation>& tables);

        /*
        Expr function that takes a expression as input and returns the corresponding table
        input is either a relation algebra statement or a table name
        */
        static Relation& expr(
            std::string input,
            std::vector<Relation>& tables);

        /*
        Atomic Expression function that takes an atomic expression as input and returns the corresponding table
        input is either a table name or an expression, where the expression is in parathesis
        */
        static Relation& atomic_expr(
            std::string input,
            std::vector<Relation>& tables);

        /*
        Find Relation function that takes in a table name as input and returns the table's position in the vector (-1 if not found)
        */
        static int find_relation(
            std::string input,
            std::vector<Relation>& tables);

        /*
        Selection function that takes in conditions and a table as input, performs the selection operation on the table, and returns the new table
        conditions is a list of conditions to be met, with each one separated by a "||"
        */
        static Relation& selection(
            std::string condition,
            Relation& table);

        /*
        Projection function that takes a list of attribute headers and a table as input, performs the projection operation 
            on the table, and returns the new table
        attr_list is a list of attribute header names, each separated by a ","
        */
        static Relation& projection(
            std::string attr_list,
            Relation& table);

        /*
        Renaming function that takes a list of new attributes headers and a table as input, performs the renaming operation
            on the table, returns the new table
        attr_list is a list of attribut header names, each separated by a ","
        */
        static Relation& renaming(
            std::string attr_list,
            Relation& table);

        /*
        Table Union function that takes two tables as input, performs a table union, and returns the new table
        */
        static Relation& table_union(
            Relation& table1,
            Relation& table2);

        /*
        Table Difference function that takes two tables as input, performs a table difference, and returns the new table
        table1 is the original table
        table2 is the table of rows to be removed if present in table1
        */
        static  Relation& difference(
            Relation& table1,
            Relation& table2);

        /*
        Table Product function that takes two tables as input, performs a table cross product, and returns the new table
        */
        static  Relation& product(
            Relation& table1,
            Relation& table2);

        /*
        Natural Join function that takes two tables as input, performs a natural join, and returns the new table
        */
        static Relation& natural_join(
            Relation& table1,
            Relation& table2);

        /*
        Split Attribute function that takes a list of attributes and breaks them up into a vector with each element containing one attribute,
            this vector is then returned
        attrs is a list of attributes (name and type, name and value, or just name) with each separated by a ","
        */
        static std::vector<std::string> split_attr(std::string attrs);
    };
}

#endif