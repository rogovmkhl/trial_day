#ifndef PARSE_DATA_H_INCLUDED
#define PARSE_DATA_H_INCLUDED

#include <memory>
#include "../classes/fileDataClass.h"

using namespace std;

#define PARSE_STOP      0
#define PARSE_HEADER    1
#define PARSE_VARIABLES 2
#define PARSE_VALUES    3

#define PARSE_SUCCESS 20U
#define PARSE_EXIT    30U
#define PARSE_HEADER_ISSUE    40U
#define PARSE_VARIABLES_ISSUE 50U
#define PARSE_VALUES_ISSUE    60U

#define PARSE_FILE_NAME_START 6

#define PARSE_VAR_ATTR_NUM 3

// sscanf(Linux) -> sscanf_s(Windows)
#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#endif

int parse_string_lines(vector<string>*, VarClass*);

#endif // PARSE_DATA_H_INCLUDED
