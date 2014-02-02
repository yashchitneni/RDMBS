#ifndef _ATTR
#define _ATTR

#include <string>

class attr{
 int value;
public:
  enum attr_type{ATTR, INTEGER, VAR_CHAR};
  attr() : value(0){};
  virtual void set_value(std::string v) = 0;
  virtual std::string get_value() const = 0;
  int get_class() const { return ATTR; }
  virtual bool operator<(const attr& rhs) const = 0;
};

class integer : public attr{
  int value;
public:
  integer() : value(0){ ; }
  integer(int v) : value(v){};
  void set_value(std::string v){ value = atoi(v.c_str()); }
  std::string get_value() const { return std::to_string(value); }
  int get_class() const { return INTEGER; }
  bool operator<(const attr& rhs) const {
	const integer* other = dynamic_cast<const integer*>(&rhs);
	if (other == NULL) return 0;
	return value < atoi(other->get_value().c_str());
  }
};

class var_char : public attr{
  std::string value;
public:
  var_char() : value(""){}
  var_char(std::string v) :value(v){}
  void set_value(std::string v){ value = v;  }
  std::string get_value() const { return value; }
  int get_class() const { return VAR_CHAR; }
  bool operator<(const attr& rhs) const {
	const var_char* other = dynamic_cast<const var_char*>(&rhs);
	if (other == NULL) return 0;
	return value < other->get_value();
  }
};

#endif