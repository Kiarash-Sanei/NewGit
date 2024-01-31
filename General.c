#include "Header.h"

char* NewGit_finder()
{
    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
    char* temporary_directory = (char*) malloc(sizeof(char)  * MAX_DIRECTORY_NAME_LENGTH);
    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return NULL;
    }
    if(getcwd(temporary_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return NULL;
    }
    dirent* entry;
    bool exist = false;
    do
    {
        DIR* directory = opendir(".");
        if(directory == NULL)
        {
            DIRECTORY_OPENING_ERROR
            return NULL;
        }
        entry = readdir(directory);
        while(entry != NULL)
        {
            if((entry -> d_type == DT_DIR) && (strcmp(entry -> d_name , ".NewGit") == 0))
            {
                exist = true;
                goto end;
            }
            entry = readdir(directory);
        }
        closedir(directory);
        if(strcmp(temporary_directory , "/") != 0)
        {
            if(chdir("..") != 0)
            {
                DIRECTORY_OPENING_ERROR
                return NULL;
            }
            if(getcwd(temporary_directory  , MAX_DIRECTORY_NAME_LENGTH) == NULL)
            {
                DIRECTORY_OPENING_ERROR
                return NULL;
            }
        }
    }while(strcmp(temporary_directory , "/") != 0);
    end:
        if(chdir(current_directory) != 0)
        {
            DIRECTORY_OPENING_ERROR
            return NULL;
        }
        if(exist == true)
        {
            return temporary_directory;
        }
        else
        {
            return NULL;
        }
}
int copy_file(char* destination , char* source)
{
    char command[MAX_COMMAND_LENGTH];
    strcpy(command , "cp ");
    strcat(command , source);
    strcat(command , " ");
    strcat(command , destination);
    if(system(command) !=0)
    {
        return ERROR;
    }
    return SUCCEED;
}
int copy_directory(char* destenation , char* source)
{
    char command[MAX_COMMAND_LENGTH];
    strcpy(command , "cp -r ");
    strcat(command , source);
    strcat(command , " ");
    strcat(command , destenation);
    system(command);
}
int file_content_checker(char* file_name1 , char* file_name2)
{
    FILE* file1 = fopen(file_name1 , "r");
    if(file1 == NULL)
    {
        FILE_OPENING_ERROR
        return ERROR;
    }
    FILE* file2 = fopen(file_name2 , "r");
    if(file2 == NULL)
    {
        FILE_OPENING_ERROR
        return ERROR;
    }
    char c1 = fgetc(file1);
    char c2 = fgetc(file2);
    while(1)
    {
        if(c1 != c2)
        {
            return FAILED;
        }
        else if((c1 == EOF) && (c2 == EOF))
        {
            return SUCCEED;
        }
        c1 = fgetc(file1);
        c2 = fgetc(file2);
    }
}
int stage_checker_complete(char* file_name , char* current_directory)
{
    char* stage_path = NewGit_finder();
    strcat(stage_path , "/.NewGit/Stage");
    DIR* directory = opendir(stage_path);
    if(directory == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    dirent* entry = readdir(directory);
    while(entry != NULL)
    {
        if((entry -> d_type == DT_REG) && (strcmp(entry -> d_name , file_name) == 0))
        {
            char file_name1[MAX_DIRECTORY_NAME_LENGTH];
            strcpy(file_name1 , current_directory);
            strcat(file_name1 , "/");
            strcat(file_name1 , file_name);
            char file_name2[MAX_DIRECTORY_NAME_LENGTH];
            strcpy(file_name2 , stage_path);
            strcat(file_name2 , "/");
            strcat(file_name2 , file_name);
            if(file_content_checker(file_name1 , file_name2) == SUCCEED)
            {
                return SUCCEED;
            }
            return MODIFIED;
        }
        entry = readdir(directory);
    }
    closedir(directory);
    free(stage_path);
    return FAILED;
}
int stage_checker_name(char* file_name)
{
    char* stage_path = NewGit_finder();
    strcat(stage_path , "/.NewGit/Stage");
    DIR* directory = opendir(stage_path);
    if(directory == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    dirent* entry = readdir(directory);
    while(entry != NULL)
    {
        if(strcmp(entry -> d_name , file_name) == 0)
        {
            return SUCCEED;
        }
        entry = readdir(directory);
    }
    closedir(directory);
    free(stage_path);
    return FAILED;
}
int delete_file(char* file_name_destenation , char* file_name)
{
    char destination_path[MAX_DIRECTORY_NAME_LENGTH];
    strcpy(destination_path , file_name_destenation);
    strcat(destination_path , "/.NewGit/Stage/");
    strcat(destination_path , file_name);
    char command[MAX_COMMAND_LENGTH];
    strcpy(command , "rm ");
    strcat(command , destination_path);
    if(system(command) !=0)
    {
        return ERROR;
    }
    return SUCCEED;
}
int delete_directory(char* directory_destenation , char* directory)
{
    char destination_path[MAX_DIRECTORY_NAME_LENGTH];
    strcpy(destination_path , directory_destenation);
    strcat(destination_path , "/.NewGit/Stage/");
    strcat(destination_path , directory);
    char command[MAX_COMMAND_LENGTH];
    strcpy(command , "rm -rf ");
    strcat(command , destination_path);
    if(system(command) !=0)
    {
        return ERROR;
    }
    return SUCCEED;
}