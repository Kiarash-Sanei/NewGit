#include "Header.h"

int main(int argc , char** argv)
{
    if(strcmp(argv[1] , "config") == 0)
    {
        if(argc < 4)
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
        if(strcmp(argv[2] , "-global") == 0)
        {
            if(argc < 5)
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
            if(add_configuration_global(argv[3] , argv[4]) == ERROR)
            {
                return ERROR;
            }
            else
            {
                return SUCCEED;
            }
        }
        if(add_configuration_loacal(argv[2] , argv[3]) == ERROR)
        {
            return ERROR;
        }
    }
}