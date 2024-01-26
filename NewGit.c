#include "Header.h"

int main(int argc , char** argv)
{
    if(strcmp(argv[1] , "config") == 0)
    {
        if(argc < 4)
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
        if(strcmp(argv[2] , "-global") == 0)
        {
            if(argc < 5)
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
            if(add_configuration_global(argv[3] , argv[4]) == ERROR)
            {
                return ERROR;
            }
            else
            {
                return SUCCEED;
            }
        }
        if(argc != 4)
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
        if(add_configuration_loacal(argv[2] , argv[3]) == ERROR)
        {
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "init") == 0)
    {
        if(argc != 2)
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
        if(NewGit_maker() != SUCCEED)
        {
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "add") == 0)
    {
        if(strcmp(argv[2] , "-f") == 0)
        {
            for(int i = 0 ; i < argc - 3 ; i++)
            {
                if(opendir(argv[i + 3]) == NULL)
                {
                    stage_file(argv[i + 3]);
                }
                else
                {
                    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
                    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                    {
                        DIRECTORY_OPENING_ERROR
                        return ERROR;
                    }
                    char main_directory[MAX_DIRECTORY_NAME_LENGTH];
                    if(getcwd(main_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                    {
                        DIRECTORY_OPENING_ERROR
                        return ERROR;
                    }
                    stage_directory(argv[i + 3] , current_directory , main_directory);
                }
            }
        }
        if(strcmp(argv[2] , "-n") == 0)
        {
            char current_directory[MAX_DIRECTORY_NAME_LENGTH];
            if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
            {
                DIRECTORY_OPENING_ERROR
                return ERROR;
            }
            puts("FILE NAME ---- STATUS");
            show(atoi(argv[3]) , current_directory);
        }
        if(strcmp(argv[2] , "-redo") == 0)
        {
            char current_directory[MAX_DIRECTORY_NAME_LENGTH];
            if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
            {
                DIRECTORY_OPENING_ERROR
                return ERROR;
            }
            char main_directory[MAX_DIRECTORY_NAME_LENGTH];
            if(getcwd(main_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
            {
                DIRECTORY_OPENING_ERROR
                return ERROR;
            }
            char directory_name[MAX_DIRECTORY_NAME_LENGTH]; 
            strcpy(directory_name , strrchr(main_directory , '/') + 1);
            redo(directory_name , current_directory , main_directory);
        }
        if(argc == 3)
        {
            if(opendir(argv[2]) == NULL)
            {
                stage_file(argv[2]);
            }
            else
            {
                char current_directory[MAX_DIRECTORY_NAME_LENGTH];
                if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                {
                    DIRECTORY_OPENING_ERROR
                    return ERROR;
                }
                char main_directory[MAX_DIRECTORY_NAME_LENGTH];
                if(getcwd(main_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                {
                    DIRECTORY_OPENING_ERROR
                    return ERROR;
                }
                stage_directory(argv[2] , current_directory , main_directory);
            }
        }
    }
}