#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "parse_data.h"

using namespace std;

string parse_variable_line(string &stringLine)
{
    int varNameBegin(0);
    int varNameEnd(0);
    const int strLen = stringLine.length();
    char symb;
    string ret;
    string variable_name;

    for(auto i=0; i<strLen; i++)
    {
        symb = stringLine[i];
        if (symb == '@')
        {
            varNameBegin = i + 1; // Variable name starts after @
        }
        else
        {
            if (symb == '=')
            {
                varNameEnd = i;
            }
            else
            {
                /* NOTHING TO DO */
            }
        }

        if (varNameEnd > varNameBegin)
        {
            variable_name = stringLine.substr(varNameBegin, varNameEnd - varNameBegin);
            ret = variable_name;
            // variable has been found
            break;
        }
    }

    return ret;
}

vector<string> parse_value_line(string &stringLine)
{
    int varNameReady(0);
    int varNameBegin(0);
    int varNameEnd(0);
    string attr;
    vector<int> varAttrBegin;
    vector<int> varAttrEnd;
    vector<string> strParseRes;
    const int strLen = stringLine.length();
    string variable_name;
    char symb;

    map<string,double> mapVarVal();
    for(auto i=0; i<strLen; i++)
    {
        symb = stringLine[i];
        if (symb == '@')
        {
            varNameBegin = i + 1; // Variable name starts after @
        }
        else
        {
            if ((symb == ':') && (varNameEnd == 0))
            {
                varNameEnd = i;
                varAttrBegin.push_back(i + 1);
            }
            else
            {
                if (symb == ';')
                {
                    varAttrBegin.push_back(i + 1);
                    varAttrEnd.push_back(i);

                }
                else
                {
                    /* NOTHING TO DO */
                }
            }
        }

        if (i == strLen - 1)
        {
            // end of final value's attribute
            varAttrEnd.push_back(i);
        }
    }

    // get value's name
    if (varNameEnd > varNameBegin)
    {
        variable_name = stringLine.substr(varNameBegin, varNameEnd - varNameBegin);
        varNameReady = 1;
        strParseRes.push_back(variable_name);
    }

    // get attributes for the value name in the line
    if (varNameReady)
    {
        for(int i = 0; i < (int)varAttrBegin.size(); i++)
        {
            attr = stringLine.substr(varAttrBegin.at(i), (varAttrEnd.at(i) - varAttrBegin.at(i)) );
            strParseRes.push_back(attr);
        }
    }

    return strParseRes;
}

vector<int> parse_time_line(string &time_string)
{
    vector<int> time;
    string tmp_strtime {};

    // save time in a way year->month->day->hour->min->sec->msec
    time.push_back(stod(time_string.substr(0,2))); // year
    time.push_back(stod(time_string.substr(3,2))); // monthr
    time.push_back(stod(time_string.substr(6,4))); // day

    time.push_back(stod(time_string.substr(11,2))); // hour
    time.push_back(stod(time_string.substr(14,2))); // min
    time.push_back(stod(time_string.substr(17,2))); // sec
    time.push_back(stod(time_string.substr(20,4))); // msec

    return time;
}

int parse_string_lines(vector<string>* lines_in, VarClass* classForData)
{
    int ret(PARSE_STOP);
    int vector_line(0); //help to go through vector
    int parseDataType (-1);
    int variable_int(0);
    double var_value(0.0);
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
                 // skip this line, parsing does not require
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
                if (line.find("Name") != string::npos)
                {
                    int fileNameStrSize = line.length();
                    classForData->fileName = line.substr(PARSE_FILE_NAME_START ,fileNameStrSize - PARSE_FILE_NAME_START - 1) + ".txt";
                }
                break;

            case PARSE_VARIABLES:
                variable_str = parse_variable_line(line);
                if (variable_str.size() > 0)
                {
                    classForData->varList.push_back(stod(variable_str));
                }
                break;

            case PARSE_VALUES:
                variable_attr = parse_value_line(line);
                if (variable_attr.size() == (1 + PARSE_VAR_ATTR_NUM))// Variable + number of attributs
                {
                    variable_int = stoi(variable_attr.at(0)); // variable name
                    var_value = stoi(variable_attr.at(1));    // value of the variable
                    var_time = parse_time_line(variable_attr.at(3));
                    classForData->var_value.insert({variable_int,var_value});
                    classForData->var_time.insert({variable_int,var_time});
                }
                break;

            default:
                break;
        }
    }

    parseDataType = PARSE_STOP;
    // Parsing finished
    cout << " done." << endl;

    ret = PARSE_SUCCESS;

    return ret;
}
