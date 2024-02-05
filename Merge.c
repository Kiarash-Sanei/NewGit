#include "Header.h"

int merge(char* branch_name_1 , char* branch_name_2)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(path , "/.NewGit/Branches/");
    int flag_1 = 0;
    int flag_2 = 0;
    DIR* directory = opendir(path);
    dirent* entry = readdir(directory);
    while(entry != NULL)
    {
        if(strcmp(entry -> d_name , branch_name_1) == 0)
        {
            flag_1 = 1;
        }
        else if(strcmp(entry -> d_name , branch_name_2) == 0)
        {
            flag_2 = 1;
        }
        entry = readdir(directory);
    }
    if(flag_1 + flag_2 != 2)
    {
        BRANCH_EXISTENCE_ERROR
        return ERROR;
    }
    char path_1[MAX_DIRECTORY_NAME_LENGTH];
    char path_2[MAX_DIRECTORY_NAME_LENGTH];
    strcpy(path_1 , path);
    strcpy(path_2 , path);
    strcat(path_1 , branch_name_1);
    strcat(path_2 , branch_name_2);
    DIR* directory_1 = opendir(path_1);
    DIR* directory_2 = opendir(path_2);
    char list_1[MAX_FILE_COUNT][MAX_FILE_NAME_LENGTH];
    int index_1 = 0;
    char list_2[MAX_FILE_COUNT][MAX_FILE_NAME_LENGTH];
    int index_2 = 0;
    entry = readdir(directory_1);
    while(entry != NULL)
    {
        if((strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
        {
            strcpy(list_1[index_1] , entry -> d_name);
            index_1++;
        }
        entry = readdir(directory_1);
    }
    entry = readdir(directory_2);
    while(entry != NULL)
    {
        if((strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
        {
            strcpy(list_2[index_2] , entry -> d_name);
            index_2++;
        }
        entry = readdir(directory_2);
    }
    strcat(path , branch_name_1);
    strcat(path , "+");
    strcat(path , branch_name_2);
    mkdir(path , ACCESS);
    for(int i = 0 ; i < index_1 ; i++)
    {
        int flag = 0;
        for(int j = 0 ; j < index_2 ; j++)
        {
            if(strcmp(list_1[i] , list_2[j]) == 0)
            {
                char temporary_1[MAX_DIRECTORY_NAME_LENGTH];
                char temporary_2[MAX_DIRECTORY_NAME_LENGTH];
                strcpy(temporary_1 , path_1);
                strcat(temporary_1 , list_1[i]);
                strcpy(temporary_2 , path_2);
                strcat(temporary_2 , list_2[j]);
                diff_file(temporary_1 , temporary_2 , 1 , 100 , 1 , 100);
                flag = 1;
            }
        }
        if(flag == 0)
        {
            char temporary_1[MAX_DIRECTORY_NAME_LENGTH];
            strcpy(temporary_1 , path_1);
            strcat(temporary_1 , list_1[i]);
            copy_file(path , temporary_1);
        }
    }
    for(int i = 0 ; i < index_2 ; i++)
    {
        int flag = 0;
        for(int j = 0 ; j < index_1 ; j++)
        {
            if(strcmp(list_2[i] , list_1[j]) == 0)
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            char temporary_2[MAX_DIRECTORY_NAME_LENGTH];
            strcpy(temporary_2 , path_2);
            strcat(temporary_2 , list_2[i]);
            copy_file(path , temporary_2);
        }
    }
    return SUCCEED;
}