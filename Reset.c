#include "Header.h"

int reset_file(char* file_name)
{
    char* stage_path = NewGit_finder();
    if(stage_path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return ERROR;
    }
    if(stage_checker_name(file_name) == SUCCEED)
    {
        delete_file(stage_path , file_name);
    }
    else
    {
        STAGE_EXISTENCE_ERROR_MASSAGE(file_name)
        char massage[strlen(file_name) + 9];
        strcpy(massage , "Unstagging ");
        strcat(massage , file_name);
        FAIL_MASSAGE(massage)
        return ERROR;
        return ERROR;
    }
    strcat(stage_path , "/.NewGit/stageLog.txt");
    FILE* file_log = fopen(stage_path , "r");
    char word[MAX_WORD_LENGTH];
    char all[MAX_UNDO_LENGTH][MAX_WORD_LENGTH];
    int index = 0;
    while(fgets(word , sizeof(word) , file_log)) 
    {
        word[strlen(word) - 1] = '\0';    
        strcpy(all[index] , word);
        index++;
    }
    fclose(file_log);   
    file_log = fopen(stage_path , "w");
    for(int i = 0 ; i < index ; i++)
    {
        if(strcmp(file_name , all[i]) != 0)
        {
            fprintf(file_log , "%s\n" , all[i]);
        }
    }
    fclose(file_log);
    free(stage_path);
    char massage[strlen(file_name) + 9];
    strcpy(massage , "Unstagging ");
    strcat(massage , file_name);
    SUCCESS_MASSAGE(massage)
    return SUCCEED;
}
int reset_directory(char* directory_name)
{
    char* stage_path = NewGit_finder();
    if(stage_path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    DIR* directory = opendir(directory_name);
    if(directory == NULL)
    {
        DIRECTORY_EXISTENCE_ERROR
        EXISTENCE_ERROR_MASSAGE(directory_name)
        return ERROR;
    }
    if(stage_checker_name(directory_name) == SUCCEED)
    {
        delete_directory(stage_path , directory_name);
    }
    else
    {
        STAGE_EXISTENCE_ERROR_MASSAGE(directory_name)
        char massage[strlen(directory_name) + 9];
        strcpy(massage , "Unstagging ");
        strcat(massage , directory_name);
        FAIL_MASSAGE(massage)
        return ERROR;
    }
    closedir(directory);
    strcat(stage_path , "/.NewGit/stageLog.txt");
    FILE* file_log = fopen(stage_path , "r");
    char word[MAX_WORD_LENGTH];
    char all[MAX_UNDO_LENGTH][MAX_WORD_LENGTH];
    int index = 0;
    while(fgets(word , sizeof(word) , file_log)) 
    {
        word[strlen(word) - 1] = '\0';    
        strcpy(all[index] , word);
        index++;
    }
    fclose(file_log);   
    file_log = fopen(stage_path , "w");
    for(int i = 0 ; i < index ; i++)
    {
        if(strcmp(directory_name , all[i]) != 0)
        {
            fprintf(file_log , "%s\n" , all[i]);
        }
    }
    fclose(file_log);
    free(stage_path);
    char massage[strlen(directory_name) + 9];
    strcpy(massage , "Unstagging ");
    strcat(massage , directory_name);
    SUCCESS_MASSAGE(massage)
    return SUCCEED;
}
int undo()
{
    char* stage_path = NewGit_finder();
    if(stage_path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(stage_path , "/.NewGit/stageLog.txt");
    FILE* file_log = fopen(stage_path , "r");
    char word[MAX_WORD_LENGTH];
    char all[MAX_UNDO_LENGTH][MAX_WORD_LENGTH];
    int index = 0;
    while(fgets(word , sizeof(word) , file_log)) 
    {
        word[strlen(word) - 1] = '\0';    
        strcpy(all[index] , word);
        index++;
    }
    fclose(file_log);
    free(stage_path);   
    strcpy(word , all[index - 1]); 
    if(word[0] == '\0')
    {
        LACK_OF_ADD
        return ERROR;
    }
    stage_path = NewGit_finder();
    strcat(stage_path , "/.NewGit/Stage/");
    strcat(stage_path , word);
    DIR* temporary_directory = opendir(stage_path);
    if(temporary_directory == NULL)
    {
        reset_file(word);
    }
    else
    {
        reset_directory(word);
    }
    return SUCCEED;
}