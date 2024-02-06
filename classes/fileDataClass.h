#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include <map>
#include <vector>
#include <chrono>
#include <iterator>

using namespace std;

class VarClass
{

public:
    string        fileName;  // File name
    unsigned int  linesNubr; // Period for measurement
    vector<int>   varList;   // List of variables
    map<int,int>  channelVarPairs;
    vector<int>   chList;   // List of channels
    multimap<int, vector<int>> chInfo;
    multimap<int,int>   var_status; //Map with variable-status pairs
    multimap<int,float> var_value;  //Map with variable-value pairs
    multimap<int,pair<time_t,int>> var_time; // Map with variable-time pairs

    int get_ChMinMaxValTime(int arg_variable, pair<string, string> *chMinMaxRes)
    {
        time_t chDateMin;
        time_t chDateMax;
        char time_buf_min[80];
        char time_buf_max[80];
        struct tm *temp_tm_min;
        struct tm *temp_tm_max;
        int chValMin, chValMinFract, chDateMsecMin;
        int chValMax, chValMaxFract, chDateMsecMax;

        multimap<int, vector<int>>::iterator chListFirstItem = this->chInfo.find(arg_variable);

        chValMin = chValMax           = chListFirstItem->second.at(0);
        chValMinFract = chValMaxFract = chListFirstItem->second.at(1);
        //chStatusMin = chStatusMax   = chListFirstItem->second.at(2);
        chDateMin = chDateMax         = chListFirstItem->second.at(3);
        chDateMsecMin = chDateMsecMax = chListFirstItem->second.at(4);

        /* Iterate through the map and print the elements */
        multimap<int, vector<int>>::iterator chListNextChItem = this->chInfo.upper_bound(arg_variable);

        while (chListFirstItem != chListNextChItem)
        {
            // Min
            if (chValMin > chListFirstItem->second.at(0))
            {
                chValMin      = chListFirstItem->second.at(0);
                chValMinFract = chListFirstItem->second.at(1);

                if (chDateMin > chListFirstItem->second.at(3))
                {
                    chDateMin   = chListFirstItem->second.at(3);
                    chDateMsecMin = chListFirstItem->second.at(4);
                }
                else
                {
                    if ( (chDateMin == chListFirstItem->second.at(3)) &&
                         (chDateMsecMin > chListFirstItem->second.at(4)) )
                    {
                        chDateMsecMin = chListFirstItem->second.at(4);
                    }
                    else
                    {
                        /* NOTHING TO DO */
                    }
                }
            }
            else
            {
                if ( (chValMin == chListFirstItem->second.at(0)) &&
                     (chValMinFract > chListFirstItem->second.at(1)) )
                {
                    chValMinFract = chListFirstItem->second.at(1);
                    if (chDateMin > chListFirstItem->second.at(3))
                    {
                        chDateMin   = chListFirstItem->second.at(3);
                        chDateMsecMin = chListFirstItem->second.at(4);
                    }
                    else
                    {
                        if ( (chDateMin == chListFirstItem->second.at(3)) &&
                             (chDateMsecMin > chListFirstItem->second.at(4)) )
                        {
                            chDateMsecMin = chListFirstItem->second.at(4);
                        }
                        else
                        {
                            /* NOTHING TO DO */
                        }
                    }
                }
                else
                {
                    /* NOTHING TO DO */
                }
            }

            // Max
            if (chValMax < chListFirstItem->second.at(0))
            {
                chValMax      = chListFirstItem->second.at(0);
                chValMaxFract = chListFirstItem->second.at(1);

                if (chDateMax < chListFirstItem->second.at(3))
                {
                    chDateMax   = chListFirstItem->second.at(3);
                    chDateMsecMax = chListFirstItem->second.at(4);
                }
                else
                {
                    if ( (chDateMax == chListFirstItem->second.at(3)) &&
                         (chDateMsecMax < chListFirstItem->second.at(4)) )
                    {
                        chDateMsecMax = chListFirstItem->second.at(4);
                    }
                    else
                    {
                        /* NOTHING TO DO */
                    }
                }
            }
            else
            {
                if ( (chValMax == chListFirstItem->second.at(0)) &&
                     (chValMaxFract < chListFirstItem->second.at(1)) )
                {
                    chValMaxFract = chListFirstItem->second.at(1);
                    if (chDateMax > chListFirstItem->second.at(3))
                    {
                        chDateMax   = chListFirstItem->second.at(3);
                        chDateMsecMax = chListFirstItem->second.at(4);
                    }
                    else
                    {
                        if ( (chDateMin == chListFirstItem->second.at(3)) &&
                             (chDateMsecMax < chListFirstItem->second.at(4)) )
                        {
                            chDateMsecMax = chListFirstItem->second.at(4);
                        }
                        else
                        {
                            /* NOTHING TO DO */
                        }
                    }
                }
                else
                {
                    /* NOTHING TO DO */
                }
            }

            ++chListFirstItem;
        }

        temp_tm_min = localtime(&chDateMin);
        temp_tm_max = localtime(&chDateMax);
        strftime (time_buf_min,80,"%d.%m.%Y %X",temp_tm_min);
        strftime (time_buf_max,80,"%d.%m.%Y %X",temp_tm_max);

        char msec_form[4];
        sprintf(msec_form, "%03d", chDateMsecMin);
        string str_msec_min(msec_form);
        string ChMinValTime = to_string(chValMin) + "." + to_string(chValMinFract) + " ; " +
                              time_buf_min + "." + msec_form;

        sprintf(msec_form, "%03d", chDateMsecMax);
        string str_msec_max(msec_form);
        string ChMaxValTime = to_string(chValMax) + "." + to_string(chValMaxFract) + " ; " +
                              time_buf_max + "." + msec_form;

        chMinMaxRes->first = ChMinValTime;
        chMinMaxRes->second = ChMaxValTime;

        return 0;
    }

};

#endif // VARIABLES_H_INCLUDED
