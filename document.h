#include <vector>
#include <iostream>
#include "record.h"

class Document_parser : public Record_parser
{
  std::vector<std::vector<std::string>> document{};

 public:
  bool read_document (std::istream&);
  std::vector<std::vector<std::string>> get_document(void);
};

std::istream& operator>>(std::istream&, Document_parser&);
std::ostream& operator<<(std::ostream&, Document_parser&);


