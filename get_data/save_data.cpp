#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <iterator>
#include <thread>
#include <string>
#include "receive_data.h"

#include "save_data.h"

using namespace std;

int save_data(VarClass* dataSource)
{
    ofstream repFile;
    string   time_min;
    string   time_max;
    string   stringLine;
    double   var_value_min(0);
    double   var_value_max(0);
    int ret(0);

    string filename = "rep_" + dataSource->fileName;
    cout << "Open " << filename << " file ... ";

   repFile.open(filename);

    if (repFile.is_open())
    {
        repFile << "Report from " << dataSource->fileName << " file." << endl << endl;

        cout << "done." << endl;
        cout << "Write data ... ";

        for(auto var : dataSource->varList)
        {
            var_value_min = dataSource->get_ValMinMax(var).first;
            var_value_max = dataSource->get_ValMinMax(var).second;
            time_min      = dataSource->get_TimeMinMax(var).first;
            time_max      = dataSource->get_TimeMinMax(var).second;

            // create a sting line for a file
            stringLine = to_string(var) + " ; " + to_string(var_value_min) + " ; " + time_min + " ; "
                + to_string(var_value_max) + " ; " + time_max;
            // write string to a file
            repFile << stringLine << endl;
        }
        repFile.close();

        cout << "done" << endl;

        ret = FILE_CREATED;
    }
    else
    {
        cout << " Can not open a file to save results." << endl;
        ret = FILE_NOT_READY;
    }

    return ret;
}
