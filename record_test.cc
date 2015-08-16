#include "testing.h"
#include "record.h"

using std::stringstream;
using std::vector;
using std::string;

void test_record1()
{
  stringstream ss("aaa,bbb,ccc");
  Record_parser rp;
  rp.read_record(ss);
  check_record(vector<string>{"aaa","bbb","ccc"}, rp.get_record(), __FUNCTION__);
  ss.str("\"aaa\",\"bbb\",\"ccc\""); ss.clear();
  check_record(vector<string>{"aaa","bbb","ccc"}, rp.get_record(), "...");
}

void test_record2()
{
  stringstream ss("aaa,bbb,ccc\nddd,eee,fff");
  Record_parser rp;
  rp.read_record(ss);
  check_record(vector<string>{"aaa","bbb","ccc"}, rp.get_record(), __FUNCTION__);
  ss.str("\"aaa\",\"bbb\",\"ccc\"\n\"ddd\",\"eee\",\"fff\""); ss.clear();
  check_record(vector<string>{"aaa","bbb","ccc"}, rp.get_record(), "...");
}
          
int main()
{
  test_record1();
  test_record2();
  
  return 0;
}
