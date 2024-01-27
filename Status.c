#include "Header.h"

int status(char* current_directory)
{
    char* stage_path = NewGit_finder();
    if(stage_path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(stage_path , "/.NewGit/stageLog.txt");
    char** all = (char**) malloc(sizeof(char) * MAX_FILE_COUNT);
    int index = 0;
    DIR* directory = opendir(current_directory);
    dirent* entry = readdir(directory);
    while(entry != NULL)
    {
        if(entry -> d_type == DT_REG)
        {
            if(stage_checker_name(entry -> d_name) == SUCCEED)
            {
                printf("%s ---- Stagged", entry -> d_name);
                if(stage_checker_complete(entry -> d_name , current_directory) == MODIFIED)
                {
                    printf(" Modified\n");
                }
                else
                {
                    printf("\n");
                }
                *(all + index) = (char*) malloc(sizeof(char) * MAX_FILE_NAME_LENGTH);
                strcpy(*(all + index) , entry -> d_name);
                index++;
            }
            else
            {
                printf("%s ---- Unstagged Was added recently\n", entry -> d_name);
            }
        }
        else if((entry -> d_type == DT_DIR) && (strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
        {
            char temporary_directory[MAX_DIRECTORY_NAME_LENGTH];
            strcpy(temporary_directory , current_directory);
            strcat(temporary_directory , "/");
            strcat(temporary_directory , entry -> d_name);
            if(status(temporary_directory) == ERROR)
            {
                return ERROR;
            }
        }
        entry = readdir(directory);
    }
    for(int i = 0 ; i < index ; i++)
    {
        printf("%d:", i);
        puts(all[i]);
    }
    char** remain = (char**) malloc(sizeof(char) * MAX_FILE_COUNT);
    int index1 = 0;
    FILE* file_log = fopen(stage_path , "r");
    char word[MAX_WORD_LENGTH];
    while(fgets(word , sizeof(word) , file_log)) 
    {
        word[strlen(word) - 1] = '\0';    
        int flag = 1;
        for(int i = 0 ; i < index1 ; i++)
        {
            if(strcmp(word , *(remain + i)) == 0)
            {
                flag = 0;
            }
        }
        if(flag == 1)
        {
            *(remain + index1) = (char*) malloc(sizeof(char) * MAX_FILE_NAME_LENGTH);
            strcpy(*(remain + index1) , word);
            index1++;
        }
    }
    fclose(file_log);
    for(int i = 0 ; i < index1 ; i++)
    {
        int flag = 0;
        for(int j = 0 ; j < index ; j++)
        {
            if(strcmp(all[j] , remain[i]) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
        {
            continue;
        }
        else
        {
            printf("%s ---- Stagged Deleted from the project\n", remain[i]);
        }
    }
    free(stage_path);
    for(int i = 0 ; i < index ; i++)
    {
        free(*(all + i));
    }
    free(all);
    for(int i = 0 ; i < index1 ; i++)
    {
        free(*(remain + i));
    }
    free(remain);
    return SUCCEED;
}