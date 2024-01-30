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
    char all[MAX_FILE_COUNT][MAX_FILE_NAME_LENGTH];
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
                strcpy(all[index] , entry -> d_name);
                index ++;
            }
            else
            {
                printf("%s ---- Unstagged Was added recently\n", entry -> d_name);
            }
        }
        entry = readdir(directory);
    }
    FILE* file_log = fopen(stage_path , "r");
    char word[MAX_WORD_LENGTH];
    char all_2[MAX_UNDO_LENGTH][MAX_WORD_LENGTH];
    int index_2 = 0;
    char* stage_path_2 = NewGit_finder();
    strcat(stage_path_2 , "/Stage");
    chdir(stage_path_2);
    while(fgets(word , sizeof(word) , file_log)) 
    {
        word[strlen(word) - 1] = '\0';  
        DIR* temp = opendir(word);  
        if(temp != NULL)
        {
            continue;
        }
        strcpy(all_2[index_2] , word);
        index_2++;
    }
    chdir(current_directory);
    fclose(file_log);  
    for(int i = 0 ; i < index_2 ; i++)
    {
        int flag = 0;
        for(int j = 0 ; j < index ; j++)
        {
            if(strcmp(all[j] , all_2[i]) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag != 1)
        {
            printf("%s ---- Stagged Deleted from the project\n", all_2[i]);
        }
    }
    free(stage_path);
    return SUCCEED;
}