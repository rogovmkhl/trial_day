#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include <map>
#include <vector>
#include <chrono>
#include <iterator>

using namespace std;

class VarClass {
public:
    string        fileName; // File name
    unsigned int  lines;    // Period for measurement
    vector<int>   varList;  // List of variables
    vector<int>   chList;   // List of channels
    multimap<int,int>   var_status; //Map with variable-status pairs
    multimap<int,float> var_value;  //Map with variable-value pairs
    multimap<int,pair<time_t,int>> var_time; // Map with variable-time pairs

    pair<float,float> get_ValMinMax(int arg_variable)
    {
        pair<float,float> min_max_val(0,0);
        /* create iterator */
        multimap<int,float>::iterator iter = this->var_value.find(arg_variable);

        /* initialize pair with the first element in multimap */
        min_max_val.first = min_max_val.second = iter->second;

        /* Iterate through the map and print the elements */
        while (iter != this->var_value.upper_bound(arg_variable))
        {
            if (min_max_val.first > iter->second)
            {
                min_max_val.first = iter->second;
            }
            if (min_max_val.second < iter->second)
            {
                min_max_val.second = iter->second;
            }
            ++iter;
        }

        return min_max_val;
    }

    pair<pair<time_t,int>, pair<time_t, int>> get_TimeMinMax(int arg_variable)
    {
        pair<pair<time_t, int>, pair<time_t, int>> min_max_time;
        pair<time_t, int> time_min;
        pair<time_t, int> time_max;
        time_t date_min;
        time_t date_max;
        int time_ms_min;
        int time_ms_max;

        /* create iterator */
        multimap<int, pair<time_t, int>>::iterator iter_time = this->var_time.find(arg_variable);

        /* initialize pair with the first element in multimap */
        date_min = date_max = iter_time->second.first;
        time_ms_min = time_ms_max = iter_time->second.second;

        /* Iterate through the map and print the elements */
        while (iter_time != this->var_time.upper_bound(arg_variable))
        {
            if (date_min > iter_time->second.first)
            {
                date_min    = iter_time->second.first;
                time_ms_min = iter_time->second.second;
            }
            else
            {
                if ( (date_min == iter_time->second.first) &&
                     (time_ms_min > iter_time->second.second) )
                {
                    time_ms_min = iter_time->second.second;
                }
                else
                {
                    /* NOTHING TO DO */
                }
            }

            if (date_max < iter_time->second.first)
            {
                date_max    = iter_time->second.first;
                time_ms_max = iter_time->second.second;
            }
            else
            {
                if ( (date_max == iter_time->second.first) &&
                     (time_ms_max < iter_time->second.second) )
                {
                    time_ms_max = iter_time->second.second;
                }
                else
                {
                    /* NOTHING TO DO */
                }
            }

            ++iter_time;
        }

        min_max_time.first.first  = date_min;
        min_max_time.first.second = time_ms_min;

        min_max_time.second.first  = date_max;
        min_max_time.second.second = time_ms_max;

        return min_max_time;
    }
};

#endif // VARIABLES_H_INCLUDED
