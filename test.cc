#include <sstream>
#include <vector>
#include "field.h"
#include "record.h"

using std::stringstream;
using std::string;
using std::cout;
using std::endl;
using std::vector;

void check_true(bool x, string msg)
{
  if (x)
    cout << "ok... " << msg << endl;
  else {
    cout << "NOT OK... " << msg << endl;
  }
}

void check_field(string a, string b, string msg)
{
  if (a == b)
    cout << "ok... " << msg << endl;
  else {
    cout << "NOT OK... " << msg << endl;
    cout << "expected ==>> " << a << endl;
    cout << "got      ==>> " << b << endl;
  }
}

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

void test_plain_unquoted(void);
void test_plain_quoted(void);
void test_empty1(void);
void test_empty2(void);
void test_embedded(void);
void test_should_fail(void);
void test_quotequote1(void);
void test_quotequote2(void);
void test_record(void);

int main (void)
{
  cout << "----- Field parser tests -----" << endl;
  test_plain_unquoted();
  cout << endl;
  test_plain_quoted();
  cout << endl;
  test_empty1();
  cout << endl;
  test_empty2();
  cout << endl;
  test_embedded();
  cout << endl;
  test_should_fail();
  cout << endl;
  test_quotequote1();
  cout << endl;
  test_quotequote2();
  cout << endl;
  cout << "----- Record parser tests -----" << endl;
  test_record();
  return 0;
}

void test_plain_unquoted()
{
  string msg{"plain unquoted fields"};
  stringstream ss{"aaa,bbb,ccc"};
  Field_parser fp;
  ss >> fp;
  check_field("aaa", fp.get_field(), msg);
  check_true(!fp.is_last(), "*");
  ss >> fp;
  check_field("bbb", fp.get_field(), "**");
  check_true(!fp.is_last(), "***");
  ss >> fp;
  check_field("ccc", fp.get_field(), "****");
  check_true(fp.is_last(), "*****");
}

void test_plain_quoted ()
{
  string msg{"plain quoted fields"};
  stringstream s{"\"aaa\",\"bbb\",\"ccc\""};
  Field_parser fp;
  s >> fp;
  check_field("aaa", fp.get_field(), msg);
  check_true(!fp.is_last(), "*");
  s >> fp;
  check_field("bbb", fp.get_field(), "**");
  check_true(!fp.is_last(), "***");
  s >> fp;
  check_field("ccc", fp.get_field(), "****");
  check_true(fp.is_last(), "*****");
}

void test_empty1 ()
{
  string msg{"ways of getting empty fields: nulls and newlines"};
  stringstream s1{""};
  stringstream s2{"\n"};
  stringstream s3{"\n\n"};
  Field_parser fp;
  s1 >> fp;
  check_field("", fp.get_field(), msg);
  check_true(fp.is_last(), "*");
  s2 >> fp;
  check_field("", fp.get_field(), "**");
  check_true(fp.is_last(), "***");
  s3 >> fp;
  check_field("", fp.get_field(), "****");
  check_true(fp.is_last(), "*****");
  s3 >> fp;
  check_field("", fp.get_field(), "******");
  check_true(fp.is_last(), "*******");
}

void test_empty2 ()
{
  string msg{"ways of getting empty fields: nulls and commas"};
  stringstream s{",,"};
  Field_parser fp;
  s >> fp;
  check_true(!fp.is_last(), msg);
  s >> fp;
  check_true(!fp.is_last(), "*");
  s >> fp;
  check_true(fp.is_last(), "**");
}

void test_embedded ()
{
  string msg{"embedded commas and newlines in quoted fields"};
  stringstream s{"\"ab\ncd\",\"ab,cd\""};
  Field_parser fp;
  s >> fp;
  check_field("ab\ncd", fp.get_field(), msg);
  check_true(!fp.is_last(), "*");
  s >> fp;
  check_field("ab,cd", fp.get_field(), "**");
  check_true(fp.is_last(), "***");
}

void test_should_fail()
{
  string msg{"stream should fail on parse errors"};
  Field_parser fp;
  stringstream s{"ab\"cd"};
  s >> fp;
  check_true(s.fail(), msg);
  s.str("abcd\","); s.clear();
  s >> fp;
  check_true(s.fail(), "*");
  s.str("abcd\"\n"); s.clear();
  s >> fp;
  check_true(s.fail(), "**");
  s.str("ab\"\"cd"); s.clear();
  s >> fp;
  check_true(s.fail(), "***");
  s.str("\"abcd"); s.clear();
  s >> fp;
  check_true(s.fail(), "****");
  s.str("abcd\""); s.clear();
  s >> fp;
  check_true(s.fail(), "*****");
  s.str("ab\"cd"); s.clear();
  s >> fp;
  check_true(s.fail(), "******");
  s.str("\"abcd\"e"); s.clear();
  s >> fp;
  check_true(s.fail(), "******");
}

void test_quotequote1()
{
  string msg{"double quote in quoted field"};
  stringstream s1{"\"\"\"abcd\""};
  stringstream s2{"\"ab\"\"cd\""};
  stringstream s3{"\"abcd\"\"\""};
  Field_parser fp;
  s1 >> fp;
  check_field("\"abcd", fp.get_field(), msg);
  s2 >> fp;
  check_field("ab\"cd", fp.get_field(), "*");
  s3 >> fp;
  check_field("abcd\"", fp.get_field(), "**");
}

void test_quotequote2 ()
{
  string msg{"double quote in record, multiple reads"};
  stringstream s{"\"\"\"abcd\",\"ab\"\"cd\",\"abcd\"\"\""};
  Field_parser fp;
  s >> fp;
  check_field("\"abcd", fp.get_field(), msg);
  check_true(!fp.is_last(), "*");
  s >> fp;
  check_field("ab\"cd", fp.get_field(), "**");
  check_true(!fp.is_last(), "***");
  s >> fp;
  check_field("abcd\"", fp.get_field(), "****");
  check_true(fp.is_last(), "*****");
}

void test_record ()
{
  string msg{"Read several records from stream"};
  stringstream ss{"aaa,bbb,ccc\nddd,eee,fff\n\"gg\"\"g\",\"h,hh\",\"ii\ni\""};
  vector<string> r1{"aaa","bbb","ccc"};
  vector<string> r2{"ddd","eee","fff"};
  vector<string> r3{"gg\"g","h,hh", "ii\ni"};
  Record_parser rp;
  ss >> rp;
  check_record(r1, rp.get_record(), msg);
  ss >> rp;
  check_record(r2, rp.get_record(), "*");
  ss >> rp;
  check_record(r3, rp.get_record(), "**");
  check_true(rp.is_last(), "***");
}
  
