#include "Header.h"

int NewGit_maker()
{
    char* path = NewGit_finder();
    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return ERROR;
    }
    if(path == NULL)
    {
        if(mkdir("./.NewGit" , ACCESS) == -1)
        {
            DIRECTORY_CREATING_ERROR
            return ERROR;
        }
        if(chdir("./.NewGit") != 0)
        {
            DIRECTORY_OPENING_ERROR
            return ERROR;
        }
        if(mkdir("./Configuration" , ACCESS) == -1)
        {
            DIRECTORY_CREATING_ERROR
            return ERROR;
        }
        if(mkdir("./Stage" , ACCESS) == -1)
        {
            DIRECTORY_CREATING_ERROR
            return ERROR;
        }
        if(chdir(current_directory) != 0)
        {
            DIRECTORY_OPENING_ERROR
            return ERROR;
        }
        return SUCCEED;
    }
    else if(strcmp(path , current_directory) == 0)
    {
        NewGit_ALREADY_EXIST_IN_CURRENT_DIRECTORY
        return FAILED;
    }
    else if(path != NULL)
    {
        NewGit_ALREADY_EXIST_IN_PARENT_DIRECTORY
        return FAILED;
    }
}
