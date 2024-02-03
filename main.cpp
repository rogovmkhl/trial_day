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

int main(int argc, char* argv[])
{
    int ret (-1);

    while (ret != EXIT_COMMAND)
    {
        vector<string> linesFromFile;

        /* read file and get data */
        ret = receive_data(&linesFromFile);

        /* parse data from file */
        if (ret == FILE_READ_OK)
        {
            unique_ptr<VarClass> varDataFromFile(new VarClass);

            ret = parse_string_lines(&linesFromFile, varDataFromFile.get());

            if (ret == PARSE_SUCCESS)
            {
                /* save data to file */
                ret = save_data(varDataFromFile.get());

                if (ret == SAVE_DATA_SUCCESS)
                {
                    /* NOTHING TO DO */
                }
                else
                {
                    cout << "Can not save data to file." << endl;
                }
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
