#include "Header.h"

int branch_maker(char* parent_branch , char* commit_hash , char* branch_name , char* current_directory)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(path , "/.NewGit/Branches");
    DIR* directory = opendir(path);
    dirent* entry = readdir(directory);
    while(entry != NULL)
    {
        if(strcmp(entry -> d_name , branch_name) == 0)
        {
            BRANCH_ALREADY_EXIST
            return FAILED
        }
        entry = readdir(directory);
    }
    chdir(path);
    mkdir(branch_name , ACCESS);
    chdir(current_directory);
    strcat(path , parent_branch);
    strcat(path , "/");
    strcat(path , commit_hash);
    char* path_2 = NewGit_finder();
    strcat(path_2 , "/.NewGit/Branches");
    strcat(path_2 , branch_name);
    copy_directory(path_2 , path);
    free(path);
    free(path_2);
    strcpy(parent_branch , branch_name);
}
int branch_shower()
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(path , "/.NewGit/Branches");
    DIR* directory = opendir(path);
    dirent* entry = readdir(directory);
    while(entry != NULL)
    {
        puts(entry -> d_name);
        entry = readdir(directory);
    }
    closedir(directory);
    free(path);
    return SUCCEED;
}