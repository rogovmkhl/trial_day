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
    string   stringLine;
    int ret, variable;

    string filename = "rep_" + dataSource->fileName + ".txt";
    cout << "Open " << filename << " file ... ";

    ret = FILE_NOT_READY;

    repFile.open(filename);

    if (repFile.is_open())
    {
        repFile << "Report from " << dataSource->fileName << " file." << endl << endl;

        cout << "done." << endl;
        cout << "Write data ... ";

        for(auto channel : dataSource->chList)
        {
            pair<string,string> ChMinMalValues;
            variable = dataSource->channelVarPairs.find(channel)->second;
            dataSource->get_ChMinMaxValTime(channel, &ChMinMalValues);

            stringLine = to_string(variable) + " ; " + ChMinMalValues.first + " ; " + ChMinMalValues.second;
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
