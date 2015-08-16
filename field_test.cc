#include "field.h"
#include "testing.h"

using std::stringstream;
using std::string;

void test_plain_unquoted ()
{
  stringstream ss{"aaa,bbb,ccc"};
  Field_parser fp;
  ss >> fp;
  check_field("aaa", fp.get_field(), __FUNCTION__);
  check_true(!fp.is_last(), "...");
  ss >> fp;
  check_field("bbb", fp.get_field(), "...");
  check_true(!fp.is_last(), "...");
  ss >> fp;
  check_field("ccc", fp.get_field(), "...");
  check_true(fp.is_last(), "...");
}

void test_plain_quoted ()
{
  stringstream s{"\"aaa\",\"bbb\",\"ccc\""};
  Field_parser fp;
  s >> fp;
  check_field("aaa", fp.get_field(), __FUNCTION__);
  check_true(!fp.is_last(), "...");
  s >> fp;
  check_field("bbb", fp.get_field(), "...");
  check_true(!fp.is_last(), "...");
  s >> fp;
  check_field("ccc", fp.get_field(), "...");
  check_true(fp.is_last(), "...");
}

void test_empty ()
{
  stringstream s1{""};
  stringstream s2{"\n"};
  stringstream s3{"\n\n"};
  Field_parser fp;
  s1 >> fp;
  check_field("", fp.get_field(), __FUNCTION__);
  check_true(fp.is_last(), "...");
  s2 >> fp;
  check_field("", fp.get_field(), "...");
  check_true(fp.is_last(), "...");
  s3 >> fp;
  check_field("", fp.get_field(), "...");
  check_true(fp.is_last(), "...");
  s3 >> fp;
  check_field("", fp.get_field(), "...");
  check_true(fp.is_last(), "...");
}

void test_empty2 ()
{
  stringstream s{",,"};
  Field_parser fp;
  s >> fp;
  check_true(!fp.is_last(), __FUNCTION__);
  s >> fp;
  check_true(!fp.is_last(), "...");
  s >> fp;
  check_true(fp.is_last(), "...");
}

void test_embedded ()
{
  stringstream s{"\"ab\ncd\",\"ab,cd\""};
  Field_parser fp;
  s >> fp;
  check_field("ab\ncd", fp.get_field(), __FUNCTION__);
  check_true(!fp.is_last(), "...");
  s >> fp;
  check_field("ab,cd", fp.get_field(), "...");
  check_true(fp.is_last(), "...");
}

void test_should_fail()
{
  Field_parser fp;
  stringstream s{"ab\"cd"};
  s >> fp;
  check_true(s.fail(), __FUNCTION__);
  s.str("abcd\","); s.clear();
  s >> fp;
  check_true(s.fail(), "...");
  s.str("abcd\"\n"); s.clear();
  s >> fp;
  check_true(s.fail(), "...");
  s.str("ab\"\"cd"); s.clear();
  s >> fp;
  check_true(s.fail(), "...");
  s.str("\"abcd"); s.clear();
  s >> fp;
  check_true(s.fail(), "...");
  s.str("abcd\""); s.clear();
  s >> fp;
  check_true(s.fail(), "...");
  s.str("ab\"cd"); s.clear();
  s >> fp;
  check_true(s.fail(), "...");
  s.str("\"abcd\"e"); s.clear();
  s >> fp;
  check_true(s.fail(), "...");
}

void test_quotequote()
{
  stringstream s1{"\"\"\"abcd\""};
  stringstream s2{"\"ab\"\"cd\""};
  stringstream s3{"\"abcd\"\"\""};
  Field_parser fp;
  s1 >> fp;
  check_field("\"abcd", fp.get_field(), __FUNCTION__);
  s2 >> fp;
  check_field("ab\"cd", fp.get_field(), "...");
  s3 >> fp;
  check_field("abcd\"", fp.get_field(), "...");
}

void test_quotequote2 ()
{
  stringstream s{"\"\"\"abcd\",\"ab\"\"cd\",\"abcd\"\"\""};
  Field_parser fp;
  s >> fp;
  check_field("\"abcd", fp.get_field(), __FUNCTION__);
  check_true(!fp.is_last(), "...");
  s >> fp;
  check_field("ab\"cd", fp.get_field(), "...");
  check_true(!fp.is_last(), "...");
  s >> fp;
  check_field("abcd\"", fp.get_field(), "...");
  check_true(fp.is_last(), "...");
}

int main ()
{
  test_plain_unquoted();
  test_plain_quoted();
  test_empty();
  test_empty2();
  test_embedded();
  test_should_fail();
  test_quotequote();
  test_quotequote2();
  
  return 0;
}
