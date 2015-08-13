#include <vector>
#include <sstream>

enum class State {
  start,
    quoted,
    unquoted,
    ready,
    end
    };

enum class Event {
  data,
    quote,
    comma,
    newline,
    eof
    };

enum class Action {
  add,
    next,
    emit_field,
    emit_field_end_record,
    end_record,
    report_error
    };

struct Transition {
  State state;
  Action action;
};

struct Token {
  Event event;
  char ch;
};

class Csv_parser {
 private:
  State state{State::start};
  int position{0};
  std::vector<std::string> record{};
  Token get_token(std::stringstream&);
  
 public:
  int read_record (std::stringstream&);
  int get_position (void);
  const std::vector<std::string>& get_record(void);
};

Transition transition(const State&, const Event&);
