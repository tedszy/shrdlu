#include <sstream>
#include <iostream>
#include "field.h"

using std::stringstream;
using std::endl;
using std::cout;
using std::string;

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

void test_quotequote()
{
  stringstream s1{"\"\"\"abcd\""};
  stringstream s2{"\"ab\"\"cd\""};
  stringstream s3{"\"abcd\"\"\""};
  Field_parser f;
  f.read_field(s1);
  check_field("\"abcd", f.get_field(), __FUNCTION__);
  f.read_field(s2);
  check_field("ab\"cd", f.get_field(), "...");
  f.read_field(s3);
  check_field("abcd\"", f.get_field(), "...");
}
  
void test_quoted()
{
  stringstream s{"\"abcd\""};
  Field_parser f;
  f.read_field(s);
  check_field("abcd", f.get_field(), __FUNCTION__);
}

void test_embedded ()
{
  stringstream s1{"\"ab\ncd\""};
  stringstream s2{"\"ab,cd\""};
  Field_parser f;
  f.read_field(s1);
  check_field("ab\ncd", f.get_field(), __FUNCTION__);
  f.read_field(s2);
  check_field("ab,cd", f.get_field(), "...");
}

void test_eject ()
{
  stringstream ss1{"abc\n"};
  stringstream ss2("abc,");
  Field_parser f;
  f.read_field(ss1);
  check_field("abc", f.get_field(), __FUNCTION__);
  f.read_field(ss2);
  check_field("abc", f.get_field(), "...");
}
    
void test_comma ()
{
  stringstream ss{"abc,def"};
  Field_parser f;
  f.read_field(ss);
  check_field("abc", f.get_field(), __FUNCTION__);
}

void test_unquoted ()
{
  stringstream ss{"abc"};
  Field_parser f;
  f.read_field(ss);
  check_field("abc", f.get_field(), __FUNCTION__);
}

void test_empty ()
{
  stringstream s1{""};
  stringstream s2{"\n"};
  Field_parser f;
  f.read_field(s1);
  check_field("", f.get_field(), __FUNCTION__);
  f.read_field(s2);
  check_field("", f.get_field(), "...");
}

int main ()
{
  test_empty();
  test_unquoted();
  test_quoted();
  test_comma();
  test_eject();
  test_embedded();
  test_quotequote();
  
  return 0;
}
