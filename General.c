#include "Header.h"

char* NewGit_finder()
{
    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
    char* temporary_directory = (char*) malloc(sizeof(char)  * MAX_DIRECTORY_NAME_LENGTH);
    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return NULL;
    }
    if(getcwd(temporary_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return NULL;
    }
    dirent* entry;
    bool exist = false;
    do
    {
        DIR* directory = opendir(".");
        if(directory == NULL)
        {
            DIRECTORY_OPENING_ERROR
            return NULL;
        }
        while((entry = readdir(directory)) != NULL)
        {
            if((entry -> d_type == DT_DIR) && (strcmp(entry -> d_name , ".NewGit") == 0))
            {
                exist = true;
                goto end;
            }
        }
        closedir(directory);
        if(strcmp(temporary_directory , "/") != 0)
        {
            if(chdir("..") != 0)
            {
                DIRECTORY_OPENING_ERROR
                return NULL;
            }
            if(getcwd(temporary_directory  , MAX_DIRECTORY_NAME_LENGTH) == NULL)
            {
                DIRECTORY_OPENING_ERROR
                return NULL;
            }
        }
    }while(strcmp(temporary_directory , "/") != 0);
    end:
        if(chdir(current_directory) != 0)
        {
            DIRECTORY_OPENING_ERROR
            return NULL;
        }
        if(exist == true)
        {
            return temporary_directory;
        }
        else
        {
            return NULL;
        }
}