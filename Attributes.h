/*
class: Attributes
Abstract class with inheriting subclasses Integer and Var_Char that
act as containers for ints and strings respectively
*/

#ifndef _ATTR
#define _ATTR

#include <string>

namespace Team_Project_1_Database{
    class Attribute{
    public:
        enum attr_type{INTEGER, VAR_CHAR};
        Attribute() {};
        virtual void set_value(std::string v) = 0;
        
        //Returns the value of the attribute as a string
        virtual std::string get_value() const = 0;
        
        //Returns the enum class of an attribute as an integer
        virtual int get_class() const = 0;
        virtual bool operator<(const Attribute& rhs) const= 0;
        virtual bool operator==(const Attribute& rhs) const = 0;
        virtual bool operator!=(const Attribute& rhs) const = 0;
				virtual Attribute& operator+(const std::string rhs) = 0;
				virtual void operator+=(const std::string rhs) = 0;
				virtual void operator++() = 0;
				virtual void operator--() = 0;
    };

    class Integer : public Attribute{
        int value;
    public:
        Integer() : value(0){ ; }
        Integer(int v) : value(v){};
        Integer(const Integer& other);
        void set_value(std::string v);
        std::string get_value() const;
        int get_class() const;
        
        //Compares are made to be the same as ints
        bool operator<(const Attribute& rhs) const;
        bool operator==(const Attribute& rhs) const;
        bool operator!=(const Attribute& rhs) const;
				Attribute& operator+(const std::string rhs);
				void operator+=(const std::string rhs);
				void operator++();
				void operator--();
    };

    class Var_Char : public Attribute{
        std::string value;
    public:
        Var_Char() : value(""){}
        Var_Char(std::string v) :value(v){}
        Var_Char(const Var_Char& other);
        void set_value(std::string v);
        std::string get_value() const;
        int get_class() const;
        
        //Compares are made to be the same as strings
        bool operator<(const Attribute& rhs) const;
        bool operator==(const Attribute& rhs) const;
        bool operator!=(const Attribute& rhs) const;
				Attribute& operator+(const std::string rhs);
				void operator+=(const std::string rhs);
				void operator++();
				void operator--();
    };
}
#endif