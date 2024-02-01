#include <iostream>
#include <vector>
//sleep_for
#include <chrono>
//sleep_for
#include <thread>
#include "get_data/parse_data.h"
#include "get_data/receive_data.h"
#include "classes/fileDataClass.h"
#include "get_data/save_data.h"

using namespace std;

VarClass varFromFile;


int main(int argc, char* argv[])
{
    int ret (-1);

    while (ret != EXIT_COMMAND)
    {
        vector<string> linesFromFile;
        string fileName;
        /* read file and get data */
        ret = receive_data(&linesFromFile);

        /* parse data from file */
        if (ret == FILE_READ_OK)
        {
            VarClass varFromFile;

            varFromFile.fileName = fileName;

            ret = parse_string_lines(&linesFromFile, &varFromFile);

            if (ret == PARSE_SUCCESS)
            {
                /* save data to file */
                ret = save_data(&varFromFile);

                cout << endl;
            }
            else
            {
                cout << "Can not parse a file." << endl;
            }
        }
        else
        {
            cout << "Can not read a file." << endl;
        }
    }

    cout << "Goodbye!" << endl;
    // delay to see Goodbye
    this_thread::sleep_for(1000ms);

    return 0;
}
