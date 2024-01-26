#include "Header.h"

int add_configuration_global(char* option , char* input)
{
    if(strcmp(option , "user.name") == 0)
    {
        FILE* file = fopen("/home/kiarash-sanei/Desktop/NewGit/Configuration/globalName.txt" , "w");
        fprintf(file , "%s\n" , input);
        fclose(file);
        return SUCCEED;
    }
    else if(strcmp(option , "user.email") == 0)
    {
        FILE* file = fopen("/home/kiarash-sanei/Desktop/NewGit/Configuration/globalEmail.txt" , "w");
        fprintf(file , "%s\n" , input);
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
        return ERROR;
    }
}
int add_configuration_loacal(char* option , char* input)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    if(strcmp(option , "user.name") == 0)
    {
        strcat(path , "/.NewGit/Configuration/localName.txt");
        FILE* file = fopen(path , "w");
        fprintf(file , "%s\n" , input);
        fclose(file);
        return SUCCEED;
    }
    else if(strcmp(option , "user.email") == 0)
    {
        strcat(path , "/.NewGit/Configuration/localEmail.txt");
        FILE* file = fopen(path , "w");
        fprintf(file , "%s\n" , input);
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
        return ERROR;
    }
}