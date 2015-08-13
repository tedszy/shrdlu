#include <iostream>
#include <sstream>
#include <vector>
#include "shrdlu.h"

using std::stringstream;
using std::vector;
using std::string;
using std::cerr;
using std::endl;

Transition get_transition(const State& s, const Event& e) {
  switch (s) {
  case State::start:
    switch (e) {
    case Event::data: return Transition{State::unquoted, Action::add};
    case Event::quote: return Transition{State::quoted, Action::next};
    case Event::comma: return Transition{State::start, Action::emit_field};
    case Event::newline: return Transition{State::start, Action::emit_field_end_record}; 
    case Event::eof: return Transition{State::end, Action::end_record};
    }
  case State::quoted:
    switch (e) {
    case Event::data: return Transition{State::quoted, Action::add};
    case Event::quote: return Transition{State::ready, Action::next};
    case Event::comma: return Transition{State::quoted, Action::add};
    case Event::newline: return Transition{State::quoted, Action::add};
    case Event::eof: return Transition{State::end, Action::report_error};
    }
  case State::unquoted:
    switch (e) {
    case Event::data: return Transition{State::unquoted, Action::add};
    case Event::quote: return Transition{State::end, Action::report_error};
    case Event::comma: return Transition{State::start, Action::emit_field};
    case Event::newline: return Transition{State::start, Action::emit_field_end_record};
    case Event::eof: return Transition{State::end, Action::emit_field_end_record};
    }
  case State::ready:
    switch (e) {
    case Event::data: return Transition{State::end, Action::report_error};
    case Event::quote: return Transition{State::end, Action::report_error};
    case Event::comma: return Transition{State::start, Action::emit_field};
    case Event::newline: return Transition{State::start, Action::emit_field_end_record};
    case Event::eof: return Transition{State::end, Action::emit_field_end_record};
    }
  }
}

int Csv_parser::get_position(void)
{
  return position;
}

void Csv_parser::reset(void)
{
  position = 0;
  record.clear();
  state = State::start;
}

Token Csv_parser::get_token(stringstream& ss)
{
  char c;
  char cnext;
  c = ss.get();

  if (ss.eof())
    return Token{Event::eof, '\0'};
  
  switch (c) {
  case ',': return Token{Event::comma, c};
  case '\n': return Token{Event::newline, c};
  case '"':
    if (state == State::start)
      return Token{Event::quote, '\0'};
    cnext = ss.get();
    if (ss.eof()) {
      ss.clear();
      return Token{Event::quote, '\0'};
    } else if (cnext == '"') {
      return Token{Event::data, '"'};
    } else {
      ss.unget();
      return Token{Event::quote, '\0'};
    }
  default:
    return Token{Event::data, c};
  }
}

int Csv_parser::read_record(stringstream& ss)
{
  position = 0;
  record.clear();
  state = State::start;
  string field;
  Token tok;
  Transition trans;

  while (true) {
    tok = get_token(ss);
    position++;
    trans = get_transition(state, tok.event);
    state = trans.state;
    switch (trans.action) {
    case Action::add:
      field.push_back(tok.ch);
      break;
    case Action::next:
      break;
    case Action::emit_field:
      record.push_back(field);
      field.clear();
      break;
    case Action::emit_field_end_record:
      record.push_back(field);
      return 0;
    case Action::end_record:
      if (record.empty())
        return 2;
      else
        return 0;
    case Action::report_error:
      cerr << "parse error at position:" << position << endl;
      return 1;
    }
  }
}

const std::vector<std::string>& Csv_parser::get_record(void)
{
  return record;
}
