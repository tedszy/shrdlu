#include <fstream>
#include "document.h"

int main ()
{
  std::ifstream my_file;
  Document_parser dp;
  my_file.open("sample.csv");
  my_file >> dp;
  my_file.close();
  std::cout << dp << std::endl;

  return 0;
}
