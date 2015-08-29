#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <iostream>
#include "field.h"

class Record_parser : public Field_parser
{
 protected:
  std::vector<std::string> record{};

 public:
  bool read_record (std::istream&);
  std::vector<std::string> get_record(void);
};

std::istream& operator>>(std::istream&, Record_parser&);
std::ostream& operator<<(std::ostream&, Record_parser&);

#endif
