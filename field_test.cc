#include "field.h"
#include "testing.h"

using std::stringstream;
using std::string;

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

void test_fail_unquoted()
{
  stringstream s{"ab\"cd"};
  check_fail(s, __FUNCTION__);
  s.str("abcd\","); s.clear();
  check_fail(s, "...");
  s.str("abcd\"\n"); s.clear();
  check_fail(s, "...");
  s.str("ab\"\"cd"); s.clear();
  check_fail(s, "...");
  s.str("\"abcd"); s.clear();
  check_fail(s, "...");
  s.str("abcd\""); s.clear();
  check_fail(s, "...");
}

void test_pass_quoted()
{
  // Once the field parser reads an endquote,
  // it knows that it is at the end of a quoted
  // field, so it returns true. It is up to
  // a higher routine (such as one parsing a
  // complete record or file) to determine if the
  // characters that follow are legal. For example:
  // a non-comma character after the endquote would
  // be illegal. But the field parser cannot (and should not)
  // know this.
  stringstream s{"\"abcd\""};
  check_pass(s, __FUNCTION__);
  s.str("\"abcd\"\n"); s.clear();
  check_pass(s, "...");
  s.str("\"abcd\","); s.clear();
  check_pass(s, "...");
  s.str("\"abcd\"abcd"); s.clear();
  check_pass(s, "...");
}

int main ()
{
  test_pass_quoted();
  test_fail_unquoted();
  test_empty();
  test_unquoted();
  test_quoted();
  test_comma();
  test_eject();
  test_embedded();
  test_quotequote();
  
  return 0;
}
