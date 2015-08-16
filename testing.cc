#include <iostream>
#include <sstream>
#include "field.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

void check_field(string a, string b, string func)
{
  if (a == b)
    cout << "ok... " << func << endl;
  else {
    cout << "NOT OK... " << func << endl;
    cout << "expected ==>> " << a << endl;
    cout << "got      ==>> " << b << endl;
  }
}

void check_fail(stringstream& s, string func)
{
  Field_parser f;
  if (!f.read_field(s))
    cout << "ok... " << func << endl;
  else {
    cout << "NOT OK... " << func << endl;
    cout << "expected failure " << endl;
    cout << "got pass    ==>> " << f.get_field() << endl;
  }
}

void check_pass(stringstream& s, string func)
{
  Field_parser f;
  if (f.read_field(s))
    cout << "ok... " << func << endl;
  else {
    cout << "NOT OK... " << func << endl;
    cout << "expected pass " << endl;
    cout << "got failure  ==>> " << f.get_field() << endl;
  }
}
