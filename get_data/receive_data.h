#ifndef RECEIVE_DATA_H_INCLUDED
#define RECEIVE_DATA_H_INCLUDED
#include <vector>

#define MAX_FILE_NAME    40U
#define FILE_NO_FILE     11U
#define FILE_WRONG_NAME  12U
#define FILE_NOT_READY   13U
#define FILE_READ_OK     14U
#define FILE_CREATED     40U
#define ERROR            101U


#include "../classes/fileDataClass.h"
/* Function: receive_data()
 * @arg_in
 * @ret    code number
 */
int receive_data(vector<string>*, char*);

#endif // RECEIVE_DATA_H_INCLUDED
