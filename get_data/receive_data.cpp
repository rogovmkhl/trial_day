/* File name: receive_data.cpp
 * Purpose: Read file data and parse its data.
 * Functions: receive_data
 */

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "receive_data.h"

using namespace std;


int receive_data(vector<string>* fileData, char* ch_fileName)
{
    int      ret(ERROR);
    string   linesFromFile;
    ifstream fileStream(ch_fileName);

    if (fileStream.is_open())
    {
        cout << "Start reading " << ch_fileName << " file...";

        while (fileStream)
        {
            getline(fileStream, linesFromFile);
            fileData->push_back(linesFromFile);
        }
        fileStream.close();
        cout << " done." << endl;

        ret = FILE_READ_OK;
    }
    else
    {
        cout << "File is not open, try one more time" << endl;
        ret = FILE_NOT_READY;
    }

    return ret;
}
