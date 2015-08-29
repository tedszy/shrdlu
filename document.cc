#include "document.h"

using std::vector;
using std::string;
using std::istream;
using std::ostream;
using std::cout;
using std::endl;

vector<vector<string>> Document_parser::get_document()
{
  return document;
}

bool Document_parser::read_document(istream& is)
{
  document.clear();
  last = false;
  while (!is.eof() && !is.fail()) {
    bool ok = read_record(is);
    document.push_back(record);
  }
}

istream& operator>>(istream& is, Document_parser& d)
{
  d.read_document(is);
  return is;
}

ostream& operator<<(ostream& os, Document_parser& d)
{
  for (auto r: d.get_document()) {
    for (auto f: r)
      cout << f << " ";
    cout << endl;
  }
  return os;
}




