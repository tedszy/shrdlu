#include <iostream>
#include <vector>
#include "field.h"
#include "testing.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::vector;

void check_record(vector<string> a, vector<string> b, string msg)
{
  if (a == b)
    cout << "ok... " << msg << endl;
  else {
    cout << "NOT OK... " << msg << endl;
    cout << "expected ==>> ";
    for (auto u : a)
      cout << u << " | ";
    cout << endl;
    cout << "got      ==>> ";
    for (auto u : b)
      cout << u << " | ";
    cout << endl;
  }
}

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
