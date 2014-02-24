#ifndef _RELATION
#define _RELATION

#include "Attributes.h"
#include <map>
#include <array>
#include <vector>
#include <regex>
#include <fstream>

namespace Team_Project_1_Database{
    
    struct less_attr_pt{
        bool operator() (std::vector<Attribute*> lhs, std::vector<Attribute*> rhs) const;
    };
    
    class Relation{
        typedef std::vector<Attribute*> tuple;
        typedef std::map<tuple, tuple, less_attr_pt> table;
        
        int n_keys;
        int n_attr;
        std::string table_name;
        std::vector<std::string> header;
        table t;
        
        //Checks if an individual row satisfies a given condition
        //Input: string of type "condition", row of a table
        //Return: truth value for condition met
        bool meets_condition(
                             std::string condition,
                             std::pair<tuple, tuple> row);
        
        //Checks if an individual row satisfies a given conjunction
        //Input: string of type "conjunction", row of a table
        //Return: truth value for conjunction met
        bool meets_conjunction(
                               std::string conjunction,
                               std::pair<tuple, tuple> row);
        
        //Input: name of an attribute
        //Return: position of attribute in row
        int header_pos(std::string name);
        
        //Input: position of an attribute in a row
        //Return: truth value for if attribute is a key.
        bool is_key(int pos);
        
        //Input: attribute and keys to a given row
        //Return: position of the key in the map's key values for that row
        int find_key(Attribute* attribute, tuple keys);
        
        static std::vector<std::string> split_condition(std::string condition);
        static std::vector<std::string> split_conjunction(std::string conjunction);
        
        friend class Relation;
        friend class Grammar;
        
    public:
        Relation() : n_keys(0), n_attr(0), table_name(""){}
        
        Relation(
                 std::string name,
                 std::vector<std::string> key_header,
                 std::vector<std::string> attr_header);
        
        Relation(const Relation& other_table);
        
        Relation& operator=(const Relation& rhs);
        
        ~Relation();
        
        void set_name(std::string name);
        
        void insert(std::pair<tuple, tuple> row);
        
        std::vector<std::string> get_header() const;
        
        Attribute* get_attribute(
                                 std::string conjunction,
                                 std::string column);
        
        table get_table() const;
        
        int get_size() const;
        
        void save();
        void show() const;
        
        //Comparators that check if two relations' headers and attributes in their tables are the same.
        bool operator== (const Relation& rhs) const;
        bool operator!= (const Relation& rhs) const;
        
        //Input: vector of strings of the form "literal"
        //Return: truth value of the success of insertion
        bool insert_into(std::vector<std::string> literals);
        
        //Input: Relation whose table you will insert from
        //Return: truth value of the success of insertion
        bool insert_into(Relation other_table);
        
        //Updates attributes in the relation that meet conditions
        //Input: vector of strings of type "attr_name = literal", vector of strings of conjunction type.
        //Updates attributes in the relation that meet conditions
        bool update(
                    std::vector<std::string> attr_list,
                    std::vector<std::string> conjunctions);
        
        //Deletes rows from relation that satisfies the conditions
        //Input: vector of conjunctions, which consist of conditions
        //Return: truth value of deletion success
        bool delete_from(std::vector<std::string> conjunctions);
        
        //Creates a new relation with only rows that satisfy the conditions
        //Input: vector of conjunctions, which consist of conditions
        //Return: pointer to selection of relation
        Relation* selection(std::vector<std::string> conjunctions);
        
        //Creates a new relation with only columns that match given attribute names
        //Input: vector of attribute names to project into new relation
        //Return: pointer to projection of relation
        Relation* projection(std::vector<std::string> attr_list);
        
        //Creates a new relation with header titles changed to those found in attr_list
        //Input: vector of new header titles
        //Return: pointer to new relation with changed header titles
        Relation* renaming(std::vector<std::string> attr_list);
        
        //Computes the union of two sets and creates a new relation
        //Input: reference to existing relation
        //Return: pointer to new relation that represents union
        Relation* set_union(Relation& other_table);
        
        //Computes the difference of two sets and creates a new relation
        //Input: reference to existing relation
        //Return: pointer to new relation that represents difference
        Relation* set_difference(Relation& other_table);
        
        //Creates a new relation that is the relational cross-product
        //of the relation passed in and the relation this is called on
        //Input:  reference to existing relation
        //Return: pointer to new relation with new tuple combinations
        Relation* cross_product(Relation& other_table);
        
        /*
         Creates a new relation that is the relational natural join
         of the relation passed in and the relation this is called on
         Input:  reference to existing relation
         Return: pointer to new relation with condensed attributes
         (or the cross_product if there are no matching attributes)
         */
        Relation* natural_join(Relation& other_table);
    };
}

#endif