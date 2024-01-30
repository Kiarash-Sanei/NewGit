#include "Header.h"

int stage_file(char* file_name)
{
    char* stage_path = NewGit_finder();
    if(stage_path == NULL)
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
    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return ERROR;
    }
    if(copy_file(stage_path , current_directory , file_name) == ERROR)
    {
        char massage[strlen(file_name) + 9];
        strcpy(massage , "Stagging ");
        strcat(massage , file_name);
        FAIL_MASSAGE(massage)
        return ERROR;
    }
    fclose(file);
    strcat(stage_path , "/.NewGit/stageLog.txt");
    file = fopen(stage_path , "a");
    fprintf(file , "%s\n" , file_name);
    fclose(file);
    free(stage_path);
    char massage[strlen(file_name) + 9];
    strcpy(massage , "Stagging ");
    strcat(massage , file_name);
    SUCCESS_MASSAGE(massage)
    return SUCCEED;
}
int stage_directory(char* directory_name , char* current_directory , char* main_directory)
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
    closedir(directory);
    char command[MAX_COMMAND_LENGTH];
    strcpy(command , "cp -r ");
    strcat(command , directory_name);
    strcat(command , " ");
    strcat(command , stage_path);
    strcat(command , "/.NewGit/Stage");
    system(command);
    strcat(stage_path , "/.NewGit/stageLog.txt");
    FILE* file = fopen(stage_path , "a");
    fprintf(file , "%s\n" , directory_name);
    fclose(file);
    free(stage_path);
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
                strcat(current_directory , "/");
                strcat(current_directory , entry -> d_name);
                show(depth - 1 , current_directory);
                strcpy(current_directory , temporary_directory);
            }
        }
        entry = readdir(directory);
    }
    closedir(directory);
    return SUCCEED;
}
int redo()
{

}