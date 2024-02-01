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


int receive_data(vector<string>* fileData)
{
    /* result of file parsing */
    int ret(-1);
    char fileName[MAX_FILE_NAME];
    string str_quit ("quit");
    string str_fileLine; // string for reading files

    cout << " Type a file name that you want to parse." << endl;
    cout << " For quit the programm type: quit" << endl;
    cout << " File name: ";

    // get a file name from user
    cin.getline(fileName, MAX_FILE_NAME);
    // convert char to string
    string str_fileName(fileName);

    // user decided to exit
    if (str_fileName.compare(str_quit) == 0)
    {
        ret = EXIT_COMMAND;
    }
    else
    {
        ifstream fileStream(fileName);

        if (fileStream.is_open())
        {
            cout << "Start reading " << str_fileName << " file...";

            while (fileStream)
            {
                getline(fileStream, str_fileLine);
                //linesFromFile.push_back(str_fileLine);
                fileData->push_back(str_fileLine);
            }
            //closeFile
            fileStream.close();
            // number of lines in the file
            //classForData->lines = fileData->size();
            cout << " done." << endl;

            ret = FILE_READ_OK;
        }
        else
        {
            cout << "File is not open, try one more time" << endl;
            ret = FILE_NOT_READY;
        }
    }

    return ret;
}
