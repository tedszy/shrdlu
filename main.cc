#include <sstream>
#include <fstream>
#include <vector>
#include "shrdlu.h"

using namespace std;

void print_vector(vector<string>);
void check_equal(vector<string>, vector<string>, string);

void test_unquoted(void);
void test_quoted(void);
void test_embedded_comma(void);
void test_embedded_newline(void);
void test_triple_quote(void);
void test_empty_fields1(void);
void test_empty_fields2(void);
void test_terminal_newline1(void);
void test_terminal_newline2(void);
void test_embedded_quotes(void);
void test_embedded_quotes2(void);

int main ()
{
  test_unquoted();
  test_quoted();
  test_embedded_comma();
  test_embedded_newline();
  test_triple_quote();
  test_empty_fields1();
  test_empty_fields2();
  test_terminal_newline1();
  test_terminal_newline2();
  test_embedded_quotes();

  // this should give parse error.
  // test_embedded_quotes2();
  
  return 0;
}

void print_vector (vector<string> record)
{
  int k = 1;
  for (auto it = record.begin(); it != record.end(); ++it, k++) {
    cout << k << " " << *it << " | ";
  }
}

void check_equal(vector<string> a, vector<string> b, string func)
{
  if (a == b)
    cout << "ok... " << func << endl;
  else {
    cout << "NOT OK... " << func << endl;
    cout << "expected ==>> ";
    print_vector(a);
    cout << endl << "got      ==>> ";
    print_vector(b);
    cout << endl;
  }
}

// this should give a parse error.
void test_embedded_quotes2(void)
{
  stringstream ss{"aaa,b""bb,ccc"};
  vector<string> r{"aaa","b\"bb","ccc"};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}

void test_embedded_quotes(void)
{
  stringstream ss{"\"aa\"\"a\",bbb,ccc"};
  vector<string> r{"aa\"a","bbb","ccc"};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}

void test_terminal_newline2(void)
{
  stringstream ss{"aaa,bbb,\"ccc\"\n"};
  vector<string> r{"aaa","bbb","ccc"};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}

void test_terminal_newline1(void)
{
  stringstream ss{"aaa,bbb,ccc\n"};
  vector<string> r{"aaa","bbb","ccc"};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}

void test_empty_fields2(void)
{
  stringstream ss{",,"};
  vector<string> r{"","",""};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}

void test_empty_fields1(void)
{
  stringstream ss{",,\n"};
  vector<string> r{"","",""};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}

void test_triple_quote(void)
{
  stringstream ss{"\"\"\"aaa\"\"\",\"\"\"bbb\"\"\",\"\"\"ccc\"\"\""};
  vector<string> r{"\"aaa\"", "\"bbb\"", "\"ccc\""};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}

void test_embedded_newline(void)
{
  stringstream ss{"\"\naaa\",\"bb\nb\",\"ccc\n\""};
  vector<string> r{"\naaa","bb\nb","ccc\n"};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}

void test_embedded_comma(void)
{
  stringstream ss{"\",aaa\",\"b,bb\",\"ccc,\""};
  vector<string> r{",aaa","b,bb","ccc,"};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}

void test_unquoted(void)
{  
  stringstream ss{"aaa,bbb,ccc"};
  vector<string> r{"aaa","bbb","ccc"};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}

void test_quoted(void)
{
  stringstream ss{"\"aaa\",\"bbb\",\"ccc\""};
  vector<string> r{"aaa","bbb","ccc"};
  Csv_parser p;
  p.read_record(ss);
  check_equal(r, p.get_record(), __FUNCTION__);
}
