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
        if(argc != 4)
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
        if(add_configuration_loacal(argv[2] , argv[3]) == ERROR)
        {
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "init") == 0)
    {
        if(argc != 2)
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
        if(NewGit_maker() != SUCCEED)
        {
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "add") == 0)
    {
        if(strcmp(argv[2] , "-f") == 0)
        {
            puts("0");
        }
        if(strcmp(argv[2] , "-n") == 0)
        {
            puts("1");
        }
        if(strcmp(argv[2] , "-redo") == 0)
        {
            puts("2");
        }
        if(argc == 3)
        {
            if(opendir(argv[2]) == NULL)
            {
                stage_file(argv[2]);
            }
            else
            {
                stage_directory(argv[2]);
            }
        }
    }
}