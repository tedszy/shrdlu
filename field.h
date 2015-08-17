#include <iostream>

const char quote = '"';
const char comma = ',';
const char newline = '\n';

enum class State {
  start,
    unquoted,
    quoted
    };

class  Field_parser {
 protected:
  State state{State::start};
  std::string field{};
  bool last{false};

 public:
  bool read_field (std::istream&);
  std::string get_field(void);
  bool is_last(void);
};

std::istream& operator>>(std::istream&, Field_parser&);
std::ostream& operator<<(std::ostream&, Field_parser&);
