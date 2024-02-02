#include "Header.h"

int branch_maker(char* parent_branch , int commit_hash , char* branch_name , char* current_directory)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR 
        return ERROR;
    }
    strcat(path , "/.NewGit/Branches/");
    DIR* directory = opendir(path);
    dirent* entry = readdir(directory);
    while(entry != NULL)
    {
        if(strcmp(entry -> d_name , branch_name) == 0)
        {
            BRANCH_ALREADY_EXIST
            return ERROR;
        }
        entry = readdir(directory);
    }
    closedir(directory);
    chdir(path);
    mkdir(branch_name , ACCESS);
    chdir(current_directory);
    strcat(path , parent_branch);
    strcat(path , "/");
    char commit_hash_string[MAX_COMMIT_HASH_LENGTH];
    strcat(path , citoa(commit_hash , commit_hash_string , 10));
    char* path_2 = NewGit_finder();
    strcat(path_2 , "/.NewGit/Branches/");
    strcat(path_2 , branch_name);
    copy_directory(path_2 , path);
    free(path);
    free(path_2);
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
        if((strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
        {
            puts(entry -> d_name);
        }
        entry = readdir(directory);
    }
    closedir(directory);
    free(path);
    return SUCCEED;
}