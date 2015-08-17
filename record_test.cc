#include <sstream>
#include "testing.h"
#include "record.h"

using std::stringstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;


int main ()
{
  stringstream
    ss{"aaa,bbb,ccc\nddd,eee,fff\n\"gg\"\"g\",\"h,hh\",\"ii\ni\""};
  Record_parser rp;
  ss >> rp;
  cout << rp << endl;
  ss >> rp;
  cout << rp << endl;
  ss >> rp;
  cout << rp << endl;

  return 0;
}
