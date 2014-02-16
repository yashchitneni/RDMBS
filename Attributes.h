/*
class: attr
Abstract class with inheriting subclasses integer and var_char
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
		virtual std::string get_value() const = 0;
		virtual int get_class() const = 0;
		virtual bool operator<(const Attribute& rhs) const= 0;
		virtual bool operator==(const Attribute& rhs) const = 0;
		virtual bool operator!=(const Attribute& rhs) const = 0;
	};

	class Integer : public Attribute{
		int value;
	public:
		Integer() : value(0){ ; }
		Integer(int v) : value(v){};
		Integer(const Integer& other);
		void set_value(std::string v);
		std::string Integer::get_value() const;
		int get_class() const;
		bool operator<(const Attribute& rhs) const;
		bool operator==(const Attribute& rhs) const;
		bool operator!=(const Attribute& rhs) const;
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
		bool operator<(const Attribute& rhs) const;
		bool operator==(const Attribute& rhs) const;
		bool operator!=(const Attribute& rhs) const;
	};
}
#endif