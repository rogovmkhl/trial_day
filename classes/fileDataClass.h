#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED
#include <map>
#include <vector>
#include <chrono>

using namespace std;

class VarClass {
public:
    string                fileName; // File name
    unsigned int          lines;    // Period for measurement
    vector<unsigned int>  varList;  // List of variables
    vector<string>        chList;   // List of channels
    multimap<int, vector<int>>     var_time; // Map with variable-time pairs
    multimap<string, unsigned int> var_status; //Map with variable-status pairs
    multimap<int, double>          var_value;  //Map with variable-value pairs

    pair<double,double> get_ValMinMax(int arg_variable)
    {
        pair<double, double> min_max_val(0,0);
        /* create iterator */
        multimap<int, double>::iterator iter = this->var_value.find(arg_variable);

        /* initialize pair with the first element in multimap */
        min_max_val.first = min_max_val.second = iter->second;

        /* Iterate through the map and print the elements */
        while (iter != this->var_value.upper_bound(arg_variable))
        {
            if (min_max_val.first > iter->second)
                min_max_val.first = iter->second;
            if (min_max_val.second < iter->second)
                min_max_val.second = iter->second;

            //cout << "Key: " << arg_variable << "Min Value: " << min_max_val.first << "Max_value " << min_max_val.second << endl;
            ++iter;
        }

        return min_max_val;
    }

    pair<string,string> get_TimeMinMax(int arg_variable)
    {
        pair<string, string> min_max_time;
        vector<int> time_min;
        vector<int> time_max;
        char tmpStr[30];
        char tmpStr2[30];

        /* create iterator */
        multimap<int, vector<int>>::iterator iter_time = this->var_time.find(arg_variable);

        /* initialize pair with the first element in multimap */
        time_min = time_max = iter_time->second;

        /* Iterate through the map and print the elements */
        while (iter_time != this->var_time.upper_bound(arg_variable))
        {
            // looking for min date
            for (int i=0; i < 6 ; i++)
            {
                if (time_min.at(i) > iter_time->second.at(i))
                {
                    time_min = iter_time->second;
                }
            }

            //for (int i=0; i< iter_time->second.size(); i++)
            for (int b=0; b< 6; b++)
            {
                if (time_max.at(b) < iter_time->second.at(b))
                {
                    time_max = iter_time->second;
                }
            }
            ++iter_time;
        }

        sprintf(tmpStr,"%02d.%02d.%04d %02d:%02d:%02d.%03d", time_min.at(0), time_min.at(1),
                time_min.at(2),time_min.at(3),time_min.at(4),time_min.at(5),time_min.at(6));
        sprintf(tmpStr2,"%02d.%02d.%04d %02d:%02d:%02d.%03d", time_max.at(0), time_max.at(1),
                time_max.at(2),time_max.at(3),time_max.at(4),time_max.at(5),time_max.at(6));

        min_max_time.first = tmpStr;
        min_max_time.second = tmpStr2;

        return min_max_time;
    }

};

#endif // VARIABLES_H_INCLUDED
