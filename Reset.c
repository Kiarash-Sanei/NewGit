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
    if(delete_file(stage_path , file_name) == ERROR)
    {
        FILE_EXISTENCE_ERROR_IN_STAGE
        return ERROR;
    }
    strcat(stage_path , "/.NewGit/stageLog.txt");
    FILE* file_log = fopen(stage_path , "r");
    char word[MAX_WORD_LENGTH];
    char all[MAX_UNDO_LENGTH];
    while(fgets(word , sizeof(word) , file_log)) 
    {
        word[strlen(word) - 1] = '\0';    
        strcat(all , " ");
        strcat(all , word);
    }
    fclose(file_log);
    char* end = strrchr(all , ' '); 
    strcpy(word , end + 1);
    file_log = fopen(stage_path , "w");
    for(int i = 0 ; all + i != end ; i++)
    {
        if((all[i] == ' ') && (i != 0))
        {
            fprintf(file_log , "\n");
        }
        else if(all[i] != ' ')
        {
            fprintf(file_log , "%c" , all[i]);
        }
    }
    fprintf(file_log , "\n");
    fclose(file_log);
    free(stage_path);
    char massage[strlen(file_name) + 9];
    strcpy(massage , "Unstagging ");
    strcat(massage , file_name);
    SUCCESS_MASSAGE(massage)
    return SUCCEED;
}
int reset_directory(char* directory_name , char* current_directory , char* main_directory)
{
    char* stage_path = NewGit_finder();
    if(stage_path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    chdir(current_directory);
    strcat(current_directory , "/");
    strcat(current_directory , directory_name);
    DIR* directory = opendir(directory_name);
    if(directory == NULL)
    {
        DIRECTORY_EXISTENCE_ERROR
        EXISTENCE_ERROR_MASSAGE(directory_name)
        return ERROR;
    }
    dirent* entry = readdir(directory);
    while(entry != NULL)
    {
        if(entry -> d_type == DT_REG)
        {
            if(delete_file(stage_path , entry -> d_name) == ERROR)
            {
                FILE_EXISTENCE_ERROR_IN_STAGE
            }
            char path[MAX_DIRECTORY_NAME_LENGTH];
            strcpy(path , stage_path);
            strcat(path , "/.NewGit/stageLog.txt");
            FILE* file_log = fopen(path , "r");
            char word[MAX_WORD_LENGTH];
            char all[MAX_UNDO_LENGTH];
            while(fgets(word , sizeof(word) , file_log)) 
            {
                word[strlen(word) - 1] = '\0';    
                strcat(all , " ");
                strcat(all , word);
            }
            fclose(file_log);
            char* end = strrchr(all , ' '); 
            strcpy(word , end + 1);
            file_log = fopen(path , "w");
            for(int i = 0 ; all + i != end ; i++)
            {
                if((all[i] == ' ') && (i != 0))
                {
                    fprintf(file_log , "\n");
                }
                else if(all[i] != ' ')
                {
                    fprintf(file_log , "%c" , all[i]);
                }
            }
            fprintf(file_log , "\n");
            fclose(file_log);
            char massage[strlen(entry -> d_name) + 9];
            strcpy(massage , "Unstagging ");
            strcat(massage , entry -> d_name);
            SUCCESS_MASSAGE(massage)
        }
        else if((entry -> d_type == DT_DIR) && (strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
        {
            reset_directory(entry -> d_name , current_directory , main_directory);
        }
        entry = readdir(directory);
    }
    closedir(directory);
    free(stage_path);
    chdir(main_directory);
    char massage[strlen(directory_name) + 9];
    strcpy(massage , "Unstagging ");
    strcat(massage , directory_name);
    SUCCESS_MASSAGE(massage)
    return SUCCEED;
}
int undo()
{
    char* path = NewGit_finder();
    strcat(path , "/.NewGit/stageLog.txt");
    FILE* file_log = fopen(path , "r");
    char word[MAX_WORD_LENGTH];
    char all[MAX_UNDO_LENGTH];
    while(fgets(word , sizeof(word) , file_log)) 
    {
        word[strlen(word) - 1] = '\0';    
        strcat(all , " ");
        strcat(all , word);
    }
    fclose(file_log);
    char* end = strrchr(all , ' '); 
    strcpy(word , end + 1);
    file_log = fopen(path , "w");
    for(int i = 0 ; all + i != end ; i++)
    {
        if((all[i] == ' ') && (i != 0))
        {
            fprintf(file_log , "\n");
        }
        else if(all[i] != ' ')
        {
            fprintf(file_log , "%c" , all[i]);
        }
    }
    fprintf(file_log , "\n");
    fclose(file_log);
    if(word[0] == '\0')
    {
        LACK_OF_ADD
        return ERROR;
    }
    if(reset_file(word) == ERROR)
    {
        FAIL_MASSAGE("Unstagging")
        return ERROR;
    }
    return SUCCEED;
}