#include "Header.h"

int stage_file(char* file_name)
{
    char* stage_file_name = NewGit_finder();
    if(stage_file_name == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(stage_file_name , "/.NewGit/Stage/");
    strcat(stage_file_name , file_name);
    if(copy(stage_file_name , file_name) == ERROR)
    {
        FILE_EXISTENCE_ERROR
        return ERROR;
    }
    char massage[strlen(file_name) + 9];
    strcpy(massage , "Stagging ");
    strcat(massage , file_name);
    SUCCESS_MASSAGE(massage)
    return SUCCEED;
}
int stage_directory(char* directory_name)
{
    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return ERROR;
    }
    DIR* directory = opendir(directory_name);
    if(directory == NULL)
    {
        DIRECTORY_EXISTENCE_ERROR
        return ERROR;
    }
    dirent* entry = readdir(directory);
    while(entry != NULL)
    {
        if(entry -> d_type == DT_REG)
        {
            DIR* temp = directory;
            chdir(directory_name);
            if(stage_file(entry -> d_name) == ERROR)
            {
                FAIL_MASSAGE("Stagging process")
                return ERROR;
            }
            chdir(current_directory);
            directory = temp;
        }
        else if((entry -> d_type == DT_DIR) && (strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
        {
            DIR* temp = directory;
            chdir(directory_name);
            stage_directory(entry -> d_name);
            chdir(current_directory);
            directory = temp;
        }
        entry = readdir(directory);
    }
    closedir(directory);
    char massage[strlen(directory_name) + 9];
    strcpy(massage , "Stagging ");
    strcat(massage , directory_name);
    SUCCESS_MASSAGE(massage)
    return SUCCEED;
}