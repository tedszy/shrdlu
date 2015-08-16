#include <sstream>
#include <vector>

void check_record(std::vector<std::string> a, std::vector<std::string> b, std::string msg);
void check_field(std::string, std::string, std::string);
void check_fail(std::stringstream&, std::string);
void check_pass(std::stringstream&, std::string);
