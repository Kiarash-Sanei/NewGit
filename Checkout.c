#include "Header.h"

int checkout(char* branch_name , HEAD_information* here)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(path , "/.NewGit/Stage");
    DIR* directory = opendir(path);
    dirent* entry = readdir(directory);
    int count = 0;
    while(entry != NULL)
    {
        count++;
        entry = readdir(directory);
    }
    if(count > 2)
    {
        STAGE_IS_NOT_EMPTY_ERROR
        return ERROR;
    }
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/Branches/");
    directory = opendir(path);
    entry = readdir(directory);
    int flag = 0;
    while(entry != NULL)
    {
        if(strcmp(branch_name , entry -> d_name) == 0)
        {
            flag = 1;
            break;
        }
        entry = readdir(directory);
    }
    if(flag == 0)
    {
        BRANCH_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(path , branch_name);
    strcat(path , "/commitHEAD.txt");
    FILE* file = fopen(path , "r");
    commit_information new;
    if(file != NULL)
    {
        if(fread(&new , sizeof(commit_information) , 1 , file) == 1)
        {
            here -> HEAD = new . commit_hash;
        }
    }
    else
    {
        here -> HEAD = -2;
    }
    strcpy(here -> branch_name , branch_name);
    free(path);
    if(here -> HEAD != -2)
    {
        path = NewGit_finder();
        strcat(path , "/.NewGit/Branches/");
        strcat(path , branch_name);
        strcat(path , "/");
        char temporary[MAX_COMMIT_HASH_LENGTH];
        citoa(here -> HEAD , temporary , 10);
        strcat(path , temporary);
        directory = opendir(path);
        entry = readdir(directory);
        char* path_2 = NewGit_finder();
        while(entry != NULL)
        {
            if((entry -> d_type == DT_DIR) && (strcmp(entry -> d_name ,  ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
            {
                char command[MAX_COMMAND_LENGTH];
                strcpy(command , "cp -rf ");
                strcat(command , path);
                strcat(command , "/");
                strcat(command , entry -> d_name);
                strcat(command , " ");
                strcat(command , path_2);
                system(command);
            }
            else if(entry -> d_type == DT_REG)
            {
                char command[MAX_COMMAND_LENGTH];
                strcpy(command , "cp -f ");
                strcat(command , path);
                strcat(command , "/");
                strcat(command , entry -> d_name);
                strcat(command , " ");
                strcat(command , path_2);
                system(command);
            }
            entry = readdir(directory);
        }
        free(path);
        free(path_2);
    }
    path = NewGit_finder();
    strcat(path , "/.NewGit/HEADInformation.txt");
    file = fopen(path , "w");
    here -> read_only = 0;
    fwrite(here , sizeof(HEAD_information) , 1 , file);
    fclose(file);
    free(path);
    SUCCESS_MASSAGE("Checking out")
    return SUCCEED;
}
int checkout_commit_hash(HEAD_information* here)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(path , "/.NewGit/Stage");
    DIR* directory = opendir(path);
    dirent* entry = readdir(directory);
    int count = 0;
    while(entry != NULL)
    {
        count++;
        entry = readdir(directory);
    }
    if(count > 2)
    {
        STAGE_IS_NOT_EMPTY_ERROR
        return ERROR;
    }
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/Branches/");
    strcat(path , here -> branch_name);
    strcat(path , "/");
    char temporary[MAX_COMMIT_HASH_LENGTH];
    citoa(here -> HEAD , temporary , 10);
    strcat(path , temporary);
    directory = opendir(path);
    entry = readdir(directory);
    char* path_2 = NewGit_finder();
    while(entry != NULL)
    {
        if((entry -> d_type == DT_DIR) && (strcmp(entry -> d_name ,  ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
        {
            char command[MAX_COMMAND_LENGTH];
            strcpy(command , "cp -rf ");
            strcat(command , path);
            strcat(command , "/");
            strcat(command , entry -> d_name);
            strcat(command , " ");
            strcat(command , path_2);
            system(command);
        }
        else if(entry -> d_type == DT_REG)
        {
            char command[MAX_COMMAND_LENGTH];
            strcpy(command , "cp -f ");
            strcat(command , path);
            strcat(command , "/");
            strcat(command , entry -> d_name);
            strcat(command , " ");
            strcat(command , path_2);
            system(command);
        }
        entry = readdir(directory);
    }
    free(path);
    free(path_2);
    SUCCESS_MASSAGE("Checking out")
    return SUCCEED;
}