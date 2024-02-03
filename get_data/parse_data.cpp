#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "parse_data.h"
#include "receive_data.h"

using namespace std;

int parse_header_line(string &stringLine, VarClass* classForData)
{
    int ret(PARSE_STOP);

    //input from sscanf
    char* name_line = &stringLine[0];
    // output from sscanf
    char variab_name[MAX_FILE_NAME];
    char *variable_name = &variab_name[0];

    if (stringLine.find("Name") != string::npos)
    {
        sscanf(name_line, "Name :%s", &variable_name[0]);
        string str(variable_name);
        classForData->fileName = str;
    }
    else
    {
        /* NOTHING TO DO*/
    }

    ret = PARSE_SUCCESS;

    return ret;
}

int parse_variable_line(string &stringLine, VarClass* classForData)
{
    int varName(0);
    int chName(0);
    int ret(PARSE_STOP);
    string variable_name;

    char* var_line = &stringLine[0];

    // string starts with @
    if (stringLine[0]=='@')
    {
        sscanf(var_line, "@%d=%d", &varName, &chName);

        classForData->varList.push_back(varName);
        classForData->chList.push_back(chName);
    }
    else
    {
        /* NOTHING TO DO */
    }

    ret = PARSE_SUCCESS;

    return ret;
}

int parse_value_line(string &stringLine, VarClass* classForData)
{
    int variable(0);
    float value(0.0);
    int status(0);
    int t_day(0);
    int t_month(0);
    int t_year(0);
    int t_hour(0);
    int t_min(0);
    int t_sec(0);
    int t_msec(0);
    string attr;
    vector<int> timeRes;
    string variable_name;
    int ret(PARSE_STOP);

    char* one_line = &stringLine[0];

    if (stringLine[0]=='@')
    {
        sscanf(one_line, "@%d:%f;%d;%d.%d.%d %d:%d:%d.%d", &variable, &value, &status, &t_day, &t_month, &t_year, &t_hour, &t_min, &t_sec, &t_msec);

        /*Get time*/
        timeRes.push_back(t_day);
        timeRes.push_back(t_month);
        timeRes.push_back(t_year);
        timeRes.push_back(t_hour);
        timeRes.push_back(t_min);
        timeRes.push_back(t_sec);
        timeRes.push_back(t_msec);
        /**********/

        classForData->var_value.insert({variable, value});
        classForData->var_status.insert({variable, status});
        classForData->var_time.insert({variable, timeRes});

        ret = PARSE_SUCCESS;
    }

    return ret;
}

int parse_string_lines(vector<string>* lines_in, VarClass* classForData)
{
    int ret(PARSE_STOP);
    int vector_line(0); //help to go through vector
    int parseDataType (-1);
    vector<int> var_time {};
    string variable_str {};
    vector<string> variable_attr {};

    pair<vector<int>, string> parseTime;

    // File size
    classForData->lines = lines_in->size();

    cout << "Start parsing file ...";

    // Get list of variables
    for (auto line : *lines_in)
    {
        ++vector_line;
        if (line.find("HEADER") != string::npos)
        {
            parseDataType = PARSE_HEADER;
        }
        else
        {
             if (line.find("VARIABLE") != string::npos)
             {
                 parseDataType = PARSE_VARIABLES;
             }
             else
             {
                  if (line.find("VALUES") != string::npos)
                  {
                        parseDataType = PARSE_VALUES;
                  }
                  else
                  {
                      /* NOTHING TO DO */
                  }
             }
        }

        switch (parseDataType)
        {
             case PARSE_HEADER:
                ret |= parse_header_line(line, classForData);
                break;

            case PARSE_VARIABLES:
                ret |= parse_variable_line(line, classForData);
                break;

            case PARSE_VALUES:
                ret |= parse_value_line(line, classForData);
                break;

            default:
                break;
        }
    }

    parseDataType = PARSE_STOP;
    // Parsing finished
    cout << " done." << endl;

    return ret;
}
