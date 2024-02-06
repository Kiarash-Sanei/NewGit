#include "Header.h"

int stage_file(char* file_name)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    FILE* file = fopen(file_name , "r");
    if(file == NULL)
    {
        FILE_EXISTENCE_ERROR
        EXISTENCE_ERROR_MASSAGE(file_name)
        return ERROR;
    }
    fclose(file);
    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return ERROR;
    }
    strcat(current_directory , "/");
    strcat(current_directory , file_name);
    strcat(path , "/.NewGit/Stage");
    if(copy_file(path , current_directory) == ERROR)
    {
        char massage[strlen(file_name) + 9];
        strcpy(massage , "Stagging ");
        strcat(massage , file_name);
        FAIL_MASSAGE(massage)
        return ERROR;
    }
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/stageLog.txt");
    file = fopen(path , "a");
    fprintf(file , "%s\n" , file_name);
    fclose(file);
    free(path);
    char massage[strlen(file_name) + 9];
    strcpy(massage , "Stagging ");
    strcat(massage , file_name);
    SUCCESS_MASSAGE(massage)
    return SUCCEED;
}
int stage_directory(char* directory_name)
{
    char* path = NewGit_finder();
    if(path == NULL)
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
    closedir(directory);
    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return ERROR;
    }
    strcat(current_directory , "/");
    strcat(current_directory , directory_name);
    strcat(path , "/.NewGit/Stage");
    if(copy_directory(path , current_directory) == ERROR)
    {
        char massage[strlen(directory_name) + 9];
        strcpy(massage , "Stagging ");
        strcat(massage , directory_name);
        FAIL_MASSAGE(massage)
        return ERROR;
    }
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/stageLog.txt");
    FILE* file = fopen(path , "a");
    fprintf(file , "%s\n" , directory_name);
    fclose(file);
    free(path);
    char massage[strlen(directory_name) + 9];
    strcpy(massage , "Stagging ");
    strcat(massage , directory_name);
    SUCCESS_MASSAGE(massage)
    return SUCCEED;
}
int show(int depth , char* current_directory)
{
    char* stage_path = NewGit_finder();
    if(stage_path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    free(stage_path);
    DIR* directory = opendir(current_directory);
    if(directory == NULL)
    {
        DIRECTORY_EXISTENCE_ERROR
        EXISTENCE_ERROR_MASSAGE(current_directory)
        return ERROR;
    }
    dirent* entry = readdir(directory);
    while((entry != NULL) && (depth > 0))
    {
        if(entry -> d_type == DT_REG)
        {
            if(stage_checker_name(entry -> d_name) == SUCCEED)
            {
                printf("%s ---- Stagged\n", entry -> d_name);
            }
            else
            {
                printf("%s ---- Unstagged\n", entry -> d_name);
            }
        }
        else if((entry -> d_type == DT_DIR) && (strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0) && (strcmp(entry -> d_name , ".NewGit") != 0))
        {
            if(stage_checker_name(entry -> d_name) == SUCCEED)
            {
                printf("directory %s ---- Stagged\n", entry -> d_name);
            }
            else
            {
                char temporary_directory[MAX_DIRECTORY_NAME_LENGTH];
                strcpy(temporary_directory , current_directory);
                strcat(temporary_directory , "/");
                strcat(temporary_directory , entry -> d_name);
                show(depth - 1 , temporary_directory);
            }
        }
        entry = readdir(directory);
    }
    closedir(directory);
    return SUCCEED;
}