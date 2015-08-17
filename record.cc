#include "record.h"

using std::vector;
using std::string;
using std::istream;
using std::ostream;

vector<string> Record_parser::get_record()
{
  return record;
}

bool Record_parser::read_record(istream& is)
{
  record.clear();
  last = false;
  while (!last && !is.fail()) {
    bool ok = read_field(is);
    record.push_back(field);
  }
}

istream& operator>>(istream& is, Record_parser& r)
{
  r.read_record(is);
  return is;
}

ostream& operator<<(ostream& os, Record_parser& r)
{
  for (auto f : r.get_record())
    os << f << " | ";
  return os;
}
