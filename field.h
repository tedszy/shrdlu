#include <sstream>

const char quote = '"';
const char comma = ',';
const char newline = '\n';

enum class State {
  start,
  unquoted,
  quoted,
};

class Field_parser {
  State state{State::start};
  std::string field{};
  
public:
  bool read_field (std::stringstream&);
  std::string get_field(void);
  State get_state(void);
};

