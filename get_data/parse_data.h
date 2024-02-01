#ifndef PARSE_DATA_H_INCLUDED
#define PARSE_DATA_H_INCLUDED

#include <memory>
#include "parse_data.h"
#include "../classes/fileDataClass.h"

using namespace std;

#define PARSE_STOP      0
#define PARSE_HEADER    1
#define PARSE_VARIABLES 2
#define PARSE_VALUES    3

#define PARSE_SUCCESS    20U
#define PARSE_EXIT       30U

#define PARSE_FILE_NAME_START 6

#define PARSE_VAR_ATTR_NUM 3

string parse_variable_line(string &stringLine);
vector<int> parse_time_line(string  &time_string);
int parse_string_lines(vector<string>*, VarClass*);
vector<string> parse_value_line(string &stringLine);

#endif // PARSE_DATA_H_INCLUDED
