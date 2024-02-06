#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <ctime>
#include <iomanip>
#include "parse_data.h"
#include "receive_data.h"

using namespace std;

int parse_header_line()
{
    /* SKIP FOR NOW */

    return PARSE_SUCCESS;
}

int parse_variable_line(string &stringLine, VarClass* classForData)
{
    int varName, chName;
    int ret(PARSE_STOP);
    string variable_name;

    char* var_line = &stringLine[0];

    // string starts with @
    if (stringLine[0]=='@')
    {
        sscanf(var_line, "@%d=%d", &chName, &varName);
        classForData->channelVarPairs.insert({chName, varName});
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
    int channel, valueInteger, valueFract, status;
    int t_day, t_month, t_year, t_hour, t_min, t_sec, t_msec;
    vector<int> chAttributs;
    //string attr;
    //pair<time_t, int> timeRes;
    string variable_name;
//    vector<float, int, time_t, float> chAttrGroup;
    int ret(PARSE_STOP);

    char* one_line = &stringLine[0];

    if (stringLine[0]=='@')
    {
        sscanf(one_line, "@%d:%d.%d;%d;%d.%d.%d %d:%d:%d.%d", &channel, &valueInteger, &valueFract, &status, &t_day, &t_month, &t_year, &t_hour, &t_min, &t_sec, &t_msec);

        struct tm record_time = {0};
        record_time.tm_year = (t_year - 1900); // years since 1900
        record_time.tm_mon  = (t_month - 1);   // months since January 0-11
        record_time.tm_mday = t_day;
        record_time.tm_hour = t_hour;
        record_time.tm_min  = t_min;
        record_time.tm_sec  = t_sec;
        time_t record_time_t = mktime(&record_time);

        chAttributs.push_back(valueInteger);
        chAttributs.push_back(valueFract);
        chAttributs.push_back(status);
        chAttributs.push_back(record_time_t);
        chAttributs.push_back(t_msec);

        //timeRes.first = record_time_t;
        //timeRes.second = t_msec;

       // classForData->
        classForData->chInfo.insert({channel, chAttributs});
        //classForData->var_value.insert({channel, valueInteger});
        //classForData->var_time.insert({channel, timeRes});

        ret = PARSE_SUCCESS;
    }

    return ret;
}

int parse_string_lines(vector<string>* lines_in, VarClass* classForData)
{
    int ret(PARSE_STOP);
    int parseDataType (-1);

    classForData->linesNubr = lines_in->size();

    cout << "Start parsing file ...";

    for (auto line : *lines_in)
    {
        if (line.find("HEADER") != string::npos)
        {
            parseDataType = PARSE_HEADER;
            continue; // do not need to parse this line
        }
        else
        {
             if (line.find("VARIABLE") != string::npos)
             {
                 parseDataType = PARSE_VARIABLES;
                 continue; // do not need to parse this line
             }
             else
             {
                  if (line.find("VALUES") != string::npos)
                  {
                        parseDataType = PARSE_VALUES;
                        continue; // do not need to parse this line
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
                ret |= parse_header_line();
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
