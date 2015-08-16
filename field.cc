#include <sstream>
#include "field.h"

using std::stringstream;
using std::string;

State Field_parser::get_state(void)
{
  return state;
}

string Field_parser::get_field(void)
{
  return field;
}

bool Field_parser::read_field (stringstream& ss)
{
  state = State::start;
  field.clear();
  while (true) {
    char c = ss.get();
    switch (state) {
    case State::start:
      if (ss.eof()) return true;
      switch (c) {
      case quote:
        state = State::quoted;
        break;
      case comma: return true;
      case newline:
	ss.unget(); 
	return true;
      default:
        state = State::unquoted;
        field.push_back(c);
        break;
      }
      break;
    case State::unquoted:
      if (ss.eof()) return true;
      switch (c) {
      case quote: return false;
      case comma: return false;
      case newline:
	ss.unget(); 
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
          return true;
        } else if (cnext == quote) {
          field.push_back(quote);
        } else {
          ss.unget();
          return true;
        }
      } else {
        field.push_back(c);
      }
      break;        
    }
  }
};

