#include <vector>
#include <string>
#include <cstring>
#include <typeinfo>
using namespace std;

// for all string thing I may need in the future

typedef vector<string> str_vec;

str_vec str_split_by_space(string input);

bool str_is_in(string main_str, string sub_str);

bool str_equal(string str_1, string str_2);