#include "Header.h"

int diff_file(char* file_name_1 , char* file_name_2 , int line_begin_1 , int line_end_1 , int line_begin_2 , int line_end_2)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    char command[MAX_COMMAND_LENGTH];
    strcpy(command , "sed -n '");
    char a[MAX_WORD_LENGTH];
    char b[MAX_WORD_LENGTH];
    citoa(line_begin_1 , a , 10);
    citoa(line_end_1 , b , 10);
    strcat(command , a);
    strcat(command , ",");
    strcat(command , b);
    strcat(command , "p' ");
    strcat(command , file_name_1);
    strcat(command , " > 1");
    system(command);
    strcpy(command , "sed -n '");
    char c[MAX_WORD_LENGTH];
    char d[MAX_WORD_LENGTH];
    citoa(line_begin_2 , c , 10);
    citoa(line_end_2 , d , 10);
    strcat(command , c);
    strcat(command , ",");
    strcat(command , d);
    strcat(command , "p' ");
    strcat(command , file_name_2);
    strcat(command , " > 2");
    system(command);
    strcpy(command , "diff -w -c 1 2");
    system(command);
    remove("1");
    remove("2");
    return SUCCEED;
}
int diff_commit(commit_information commit_1 , commit_information commit_2)
{
    char* path_1 = NewGit_finder();
    if(path_1 == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    char* path_2 = NewGit_finder();
    strcat(path_1 , "/.NewGit/Branches/");
    strcat(path_1 , commit_1 . commit_branch);
    strcat(path_1 , "/");
    char a[MAX_WORD_LENGTH];
    citoa(commit_1 . commit_hash , a , 10);
    strcat(path_1 , a);
    strcat(path_2 , "/.NewGit/Branches/");
    strcat(path_2 , commit_2 . commit_branch);
    strcat(path_2 , "/");
    char b[MAX_WORD_LENGTH];
    citoa(commit_2 . commit_hash , b , 10);
    strcat(path_2 , b);
    DIR* directory_1 = opendir(path_1);
    dirent* all_1[MAX_FILE_COUNT];
    int index_1 = 0;
    all_1[index_1] = readdir(directory_1);
    while(all_1[index_1] != NULL)
    {
        index_1++;
        all_1[index_1] = readdir(directory_1);
    }
    closedir(directory_1);
    DIR* directory_2 = opendir(path_2);
    dirent* all_2[MAX_FILE_COUNT];
    int index_2 = 0;
    all_2[index_2] = readdir(directory_2);
    while(all_2[index_2] != NULL)
    {
        index_2++;
        all_2[index_2] = readdir(directory_2);
    }
    closedir(directory_2);
    for(int i = 0 ; i < index_1 ; i++)
    {
        int flag = 0;
        for(int  j = 0 ; j < index_2 ; j++)
        {
            if((strcmp(all_1[i] -> d_name , all_2[j] -> d_name) == 0))
            {
                if((all_1[i] -> d_type == DT_REG)  && (strcmp(all_1[i] -> d_name , ".") != 0) && (strcmp(all_1[i] -> d_name , "..") != 0) && (strcmp("." , all_2[j] -> d_name) != 0) && (strcmp(".." , all_2[j] -> d_name) != 0))
                {
                    char temporary_1[MAX_DIRECTORY_NAME_LENGTH];
                    strcpy(temporary_1 , path_1);
                    strcat(temporary_1 , "/");
                    strcat(temporary_1 , all_1[i] -> d_name);
                    char temporary_2[MAX_DIRECTORY_NAME_LENGTH];
                    strcpy(temporary_2 , path_2);
                    strcat(temporary_2 , "/");
                    strcat(temporary_2 , all_2[j] -> d_name);
                    diff_file(temporary_1 , temporary_2 , 1 , 100 , 1 , 100);
                }
                flag = 1;
            }
        }
        if(flag == 0)
        {
            puts(all_1[i] -> d_name);
        }
    }
    for(int i = 0 ; i < index_2 ; i++)
    {
        int flag = 0;
        for(int  j = 0 ; j < index_1 ; j++)
        {
            if(strcmp(all_2[i] -> d_name , all_1[j] -> d_name) == 0)
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            puts(all_2[i] -> d_name);
        }
    }
    return SUCCEED;
}