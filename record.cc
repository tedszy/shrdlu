#include <vector>
#include <iostream>
#include <sstream>
//#include "field.h"
#include "record.h"
#include "testing.h"

using std::stringstream;
using std::vector;
using std::string;

vector<string> Record_parser::get_record()
{
  return record;
}

bool Record_parser::read_record(stringstream& ss)
{
  record.clear();

  while (true) {
    bool ok = fp.read_field(ss);
    State state = fp.get_state();
    char c = ss.get();

    if (ss.eof()) {
      record.push_back(fp.get_field());
      return true;
    }

    if (c == newline) {
      record.push_back(fp.get_field());
      return true;
    }

    if ((state == State::quoted) && (c != comma)) {
      record.push_back(fp.get_field());
      return false;
    }

    if (c != comma) ss.unget();
    record.push_back(fp.get_field());
  }
}
