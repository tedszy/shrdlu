#include <iostream>

const char quote = '"';
const char comma = ',';
const char newline = '\n';

enum class State {
  start,
  unquoted,
  quoted,
};

struct  Field_parser {
  State state{State::start};
  std::string field{};
  bool last{false};
  
  bool read_field (std::istream&);
  std::string get_field(void);
  State get_state(void);
  bool is_last(void);
};

std::istream& operator>>(std::istream&, Field_parser&);
std::ostream& operator<<(std::ostream&, Field_parser&);
