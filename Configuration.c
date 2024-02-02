#include "Header.h"

int add_configuration_global(char* option , char* input)
{
    if((strcmp(option , "user.name") == 0) || (strcmp(option , "user.email") == 0))
    {
        FILE* file = fopen("/home/kiarash-sanei/Desktop/NewGit/Configuration/globalUser.txt" , "r");
        user* old_user = (user*) malloc(sizeof(user));
        fread(old_user , sizeof(user) , 1 , file);
        if(option[5] == 'n')
        {
            strcpy(old_user -> name , input);
        }
        else
        {
            strcpy(old_user -> email , input);
        }
        fclose(file);
        file = fopen("/home/kiarash-sanei/Desktop/NewGit/Configuration/globalUser.txt" , "w");
        fwrite(old_user , sizeof(user) , 1 , file);
        fclose(file);
        free(old_user);
        return SUCCEED;
    }
    else if(strncmp(option , "alias." , 6) == 0)
    {
        FILE* file = fopen("/home/kiarash-sanei/Desktop/NewGit/Configuration/globalAlias.txt" , "a");
        strtok(option , ".");
        option = strtok(NULL , ".");
        alias* current_alias = (alias*) malloc(sizeof(alias));
        strcpy(current_alias -> shortcut , option);
        strcpy(current_alias -> command , input);
        if(strchr(input , ' ') == NULL)
        {
            INVALID_COMMAND_ERROR
            return ERROR;
        }
        if(strncmp("NewGit" , input , 6) != 0)
        {
            INVALID_COMMAND_ERROR
            return ERROR;
        }
        char word[MAX_WORD_LENGTH];
        strtok(input , " ");
        strcpy(word , strtok(NULL , " "));
        FILE* file_command = fopen("/home/kiarash-sanei/Desktop/NewGit/commands.txt" , "r");
        char command[MAX_WORD_LENGTH];
        int flag = 0;
        while(fgets(command , MAX_WORD_LENGTH , file_command))
        {
            command[strlen(command) - 1] = '\0';
            if(strcmp(word , command) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            INVALID_COMMAND_ERROR
            return ERROR;
        }
        fwrite(current_alias , sizeof(alias) , 1 , file);
        fclose(file);
        free(current_alias);
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
    if((strcmp(option , "user.name") == 0) || (strcmp(option , "user.email") == 0))
    {
        strcat(path , "/.NewGit/Configuration/localUser.txt");
        FILE* file = fopen(path , "r");
        user* old_user = (user*) malloc(sizeof(user));
        fread(old_user , sizeof(user) , 1 , file);
        if(option[5] == 'n')
        {
            strcpy(old_user -> name , input);
        }
        else
        {
            strcpy(old_user -> email , input);
        }
        fclose(file);
        file = fopen(path , "w");
        fwrite(old_user , sizeof(user) , 1 , file);
        fclose(file);
        free(old_user);
        return SUCCEED;
    }
    else if(strncmp(option , "alias." , 6) == 0)
    {
        strcat(path , "/.NewGit/Configuration/localAlias.txt");
        FILE* file = fopen(path , "a");
        strtok(option , ".");
        option = strtok(NULL , ".");
        alias* current_alias = (alias*) malloc(sizeof(alias));
        strcpy(current_alias -> shortcut , option);
        strcpy(current_alias -> command , input);
        if(strchr(input , ' ') == NULL)
        {
            INVALID_COMMAND_ERROR
            return ERROR;
        }
        if(strncmp("NewGit" , input , 6) != 0)
        {
            INVALID_COMMAND_ERROR
            return ERROR;
        }
        char word[MAX_WORD_LENGTH];
        strtok(input , " ");
        strcpy(word , strtok(NULL , " "));
        FILE* file_command = fopen("/home/kiarash-sanei/Desktop/NewGit/commands.txt" , "r");
        char command[MAX_WORD_LENGTH];
        int flag = 0;
        while(fgets(command , MAX_WORD_LENGTH , file_command))
        {
            command[strlen(command) - 1] = '\0';
            if(strcmp(word , command) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            INVALID_COMMAND_ERROR
            return ERROR;
        }
        fwrite(current_alias , sizeof(alias) , 1 , file);
        fclose(file);
        free(current_alias);
        return SUCCEED;
    }
    else
    {
        return ERROR;
    }
}