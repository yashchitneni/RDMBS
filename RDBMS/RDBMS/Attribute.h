#ifndef _ATTRIBUTE
#define _ATTRIBUTE

#include <string>

class Attribute{
	int i_value;
	int s_value;
public:
	enum attr_type{ INTEGER, VAR_CHAR };
	Attribute() {};
	virtual void set_value(std::string v) = 0;
	virtual std::string get_value() const = 0;
	virtual int get_class() const = 0;
	virtual bool operator<(const Attribute& rhs) const = 0;
	virtual bool operator==(const Attribute& rhs) const = 0;
};

class Integer : public Attribute{
	int value;
public:
	Integer() : value(0){ ; }
	Integer(int v) : value(v){};
	void set_value(std::string v){ value = atoi(v.c_str()); }
	std::string get_value() const { return std::to_string(value); }
	int get_class() const { return INTEGER; }
	bool operator<(const Attribute& rhs) const {
		const Integer* other = static_cast<const Integer*>(&rhs);
		if (other == NULL) return 0;
		return value < atoi(other->get_value().c_str());
	}
	bool operator==(const Attribute& rhs) const{
		const Integer* other = static_cast<const Integer*>(&rhs);
		if (other == NULL) return 0;
		return value == atoi(other->get_value().c_str());
	}
};

class Var_Char : public Attribute{
	std::string value;
public:
	Var_Char() : value(""){}
	Var_Char(std::string v) :value(v){}
	void set_value(std::string v){ value = v; }
	std::string get_value() const { return value; }
	int get_class() const { return VAR_CHAR; }
	bool operator<(const Attribute& rhs) const {
		const Var_Char* other = static_cast<const Var_Char*>(&rhs);
		if (other == NULL) return 0;
		return value < other->get_value();
	}
	bool operator==(const Attribute& rhs) const {
		const Var_Char* other = static_cast<const Var_Char*>(&rhs);
		if (other == NULL) return 0;
		return value == other->get_value();
	}
};

#endif