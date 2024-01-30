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
    chdir(path);
    mkdir(branch_name , ACCESS);
    char command[MAX_COMMAND_LENGTH];
    strcpy(command , "cp -r ");
    strcat(command , "./");
    strcat(command , parent_branch);
    strcat(command , "/");
    strcat(command , commit_hash);
    strcat(command , " ./");
    strcat(command , branch_name);
    system(command);
    chdir(current_directory);
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
    free(directory);
    free(entry);
    free(path);
    return SUCCEED;
}