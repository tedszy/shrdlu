#include <vector>
#include <sstream>
#include "field.h"

class Record_parser 
{
  std::vector<std::string> record{};
  Field_parser fp{};

 public:
  bool read_record (std::stringstream&);
  std::vector<std::string> get_record(void);
};
