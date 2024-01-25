#include "Header.h"

char* NewGit_finder()
{
    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
    char* temporary_directory = (char*) malloc(sizeof(char)  * MAX_DIRECTORY_NAME_LENGTH);
    if(getcwd(current_directory  , MAX_DIRECTORY_NAME_LENGTH) == NULL)
    {
        DIRECTORY_OPENING_ERROR
        return NULL;
    }
    if(getcwd(temporary_directory  , MAX_DIRECTORY_NAME_LENGTH) == NULL)
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
        while((entry = readdir(directory)) != NULL)
        {
            if((entry -> d_type == DT_DIR) && (strcmp(entry -> d_name , ".NewGit") == 0))
            {
                exist = true;
                goto end;
            }
        }
        closedir(directory);
        if(getcwd(temporary_directory  , MAX_DIRECTORY_NAME_LENGTH) == NULL)
        {
            DIRECTORY_OPENING_ERROR
            return NULL;
        }
        if(strcmp(temporary_directory , "/") != 0)
        {
            if(chdir("..") != 0)
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
int add_configuration_global(char* option , char* input)
{
    if(strcmp(option , "user.name") == 0)
    {
        FILE* file = fopen("/home/kiarash-sanei/Desktop/NewGit/Configuration/globalName.txt" , "w");
        fprintf(file , "%s" , input);
        fclose(file);
        return SUCCEED;
    }
    else if(strcmp(option , "user.email") == 0)
    {
        FILE* file = fopen("/home/kiarash-sanei/Desktop/NewGit/Configuration/globalEmail.txt" , "w");
        fprintf(file , "%s" , input);
        fclose(file);
        return SUCCEED;
    }
    else if(strncmp(option , "alias." , 6) == 0)
    {
        FILE* file = fopen("/home/kiarash-sanei/Desktop/NewGit/Configuration/globalAlias.txt" , "a");
        strtok(option , ".");
        option = strtok(NULL , ".");
        fprintf(file , "%s %s\n" , option , input);
        fclose(file);
        return SUCCEED;
    }
    else
    {
        INVALID_INPUT_ERROR
        return ERROR;
    }
}
int add_configuration_loacal(char* option , char* input)
{
    if(NewGit_finder() == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    char* path = NewGit_finder();
    if(strcmp(option , "user.name") == 0)
    {
        strcat(path , "/.NewGit/Configuration/localName.txt");
        FILE* file = fopen(path , "w");
        fprintf(file , "%s" , input);
        fclose(file);
        return SUCCEED;
    }
    else if(strcmp(option , "user.email") == 0)
    {
        strcat(path , "/.NewGit/Configuration/localEmail.txt");
        FILE* file = fopen(path , "w");
        fprintf(file , "%s" , input);
        fclose(file);
        return SUCCEED;
    }
    else if(strncmp(option , "alias." , 6) == 0)
    {
        strcat(path , "/.NewGit/Configuration/localAlias.txt");
        FILE* file = fopen(path , "a");
        strtok(option , ".");
        option = strtok(NULL , ".");
        fprintf(file , "%s %s\n" , option , input);
        fclose(file);
        return SUCCEED;
    }
    else
    {
        INVALID_INPUT_ERROR
        return ERROR;
    }
}