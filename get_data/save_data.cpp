#include <iostream>
#include <map>
#include <fstream>
#include <iterator>
#include <string>
#include "receive_data.h"

#include "save_data.h"

using namespace std;

int save_data(VarClass* dataSource)
{
    ofstream repFile;
    pair<pair<time_t, int>, pair<time_t, int>> time_min_max;
    pair<float,float>  var_value_min_max;
    string   stringLine;
    int ret(0);

    string filename = "rep_" + dataSource->fileName + ".txt";
    cout << "Open " << filename << " file ... ";

   repFile.open(filename);

    if (repFile.is_open())
    {
        repFile << "Report from " << dataSource->fileName << " file." << endl << endl;

        cout << "done." << endl;
        cout << "Write data ... ";

        for(auto var : dataSource->varList)
        {
            var_value_min_max = dataSource->get_ValMinMax(var);
            time_min_max = dataSource->get_TimeMinMax(var);

            char time_buf_min[80];
            char time_buf_max[80];

            struct tm *temp_tm_min;
            struct tm *temp_tm_max;
            temp_tm_min = localtime(&time_min_max.first.first);
            temp_tm_max = localtime(&time_min_max.second.first);
            strftime (time_buf_min,80,"%d.%m.%Y %X",temp_tm_min);
            strftime (time_buf_max,80,"%d.%m.%Y %X",temp_tm_max);

            // create a sting line for a file
            stringLine = to_string(var) + " ; " +
                         to_string(var_value_min_max.first) + " ; " +
                         time_buf_min + "." + to_string(time_min_max.first.second) + " ; " +
                         to_string(var_value_min_max.second) + " ; " +
                         time_buf_max + "." + to_string(time_min_max.second.second);

            // write string to a file
            repFile << stringLine << endl;
        }
        repFile.close();

        cout << "done" << endl;

        ret = SAVE_DATA_SUCCESS;
    }
    else
    {
        cout << " Can not open a file to save results." << endl;
        ret = FILE_NOT_READY;
    }

    return ret;
}
