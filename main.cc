#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "shrdlu.h"

#define expect(a,b) {if ((a) == (b)) {                                  \
      std::cout <<"ok: " << #b << std::endl;                            \
    } else {                                                            \
      std::cout << "===> NOT OK: " << #b                                \
      << "... expected: " << a << ", got: " << b << std::endl;}}

void print_record (std::vector<std::string>);

int main ()
{

  Csv_parser p;
  std::stringstream zarf("aaa,bbb,ccc");
  p.read_record(zarf);
  print_record(p.get_record());

  p.reset();

  std::ifstream ifs;
  ifs.open("sample.csv");
  std::stringstream foo;
  foo << ifs.rdbuf();
  while (!foo.eof()) {
    p.read_record(foo);
    print_record(p.get_record());
    p.reset();
  }
  
  /*
  Csv readrec;
  std::ifstream csv_file;
  csv_file.open("sample.csv");  
  stringstream zarf;
  zarf << csv_file.rdbuf();
  while (!zarf.eof()) {
    print_record(readrec(zarf));
  }
  csv_file.close();
  */

  return 0;
}

void print_record (std::vector<std::string> record)
{
  for (auto it = record.begin(); it != record.end(); ++it) {
    std::cout << *it << " | ";
  }
  std::cout << std::endl;
}
