#include <sstream>
#include <ios>
#include "field.h"

using std::stringstream;
using std::string;
using std::istream;
using std::ostream;
using std::cout;
using std::endl;
using std::ios;

bool Field_parser::is_last()
{
  return last;
}

string Field_parser::get_field(void)
{
  return field;
}

bool Field_parser::read_field (istream& ss)
{
  last = false;
  state = State::start;
  field.clear();
  while (true) {
    char c = ss.get();
    switch (state) {
    case State::start:
      if (ss.eof()) {
        last = true;
        return true;
      }
      switch (c) {
      case quote:
        state = State::quoted;
        break;
      case comma: return true;
      case newline:
        last = true;
	return true;
      default:
        state = State::unquoted;
        field.push_back(c);
        break;
      }
      break;
    case State::unquoted:
      if (ss.eof()) {
        last = true;
        return true;
      }
      switch (c) {
      case quote: return false;
      case comma:
        return true;
      case newline:
        last = true; 
	return true;
      default:
        field.push_back(c);
        break;
      }
      break;
    case State::quoted:
      if (ss.eof()) return false;
      if (c == quote) {
        char cnext = ss.get();
        if (ss.eof()) {
          last = true;
          return true;
        } else if (cnext == comma) {
          return true;
        } else if (cnext == newline) {
          last = true;
          return true;
        } else if (cnext == quote) {
          field.push_back(quote);
        } else {
          ss.unget();
          return false;
        }
      } else {
        field.push_back(c);
      }
      break;        
    }
  }
}


istream& operator>>(istream& is, Field_parser& f)
{
  if (f.read_field(is))
    return is;
  else {
    is.setstate(ios::failbit);
    return is;
  } 
}

ostream& operator<<(ostream& os, Field_parser& f)
{
  os << f.get_field();
  return os;
}


