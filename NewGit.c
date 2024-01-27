#include "Header.h"

//Default brach:
char branch_name[MAX_BRANCH_NAME] = "main";

int main(int argc , char** argv)
{
    if(strcmp(argv[1] , "config") == 0)
    {
        if(strcmp(argv[2] , "-global") == 0)
        {
            if(argc != 5)
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
            else if(add_configuration_global(argv[3] , argv[4]) == ERROR)
            {
                FAIL_MASSAGE("Adding global configuration")
                return ERROR;
            }
            else
            {
                SUCCESS_MASSAGE("Adding global configuration")
                return SUCCEED;
            }
        }
        else if(argc == 4)
        {
            if(add_configuration_loacal(argv[2] , argv[3]) == ERROR)
            {
                FAIL_MASSAGE("Adding local configuration")
                return ERROR;
            }
            else
            {
                SUCCESS_MASSAGE("Adding local configuration")
                return SUCCEED;
            }
        }
        else
        {
            INVALID_INPUT_ERROR
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
        else if(NewGit_maker() != SUCCEED)
        {
            FAIL_MASSAGE("Initializing")
            return ERROR;
        }
        else
        {
            SUCCESS_MASSAGE("Initializing")
            return SUCCEED;
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
                    stage_file(argv[i + 3]);//Error handeling cann't be done 
                }
                else
                {
                    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
                    char main_directory[MAX_DIRECTORY_NAME_LENGTH];
                    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                    {
                        DIRECTORY_OPENING_ERROR
                        return ERROR;
                    }
                    else if(getcwd(main_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                    {
                        DIRECTORY_OPENING_ERROR
                        return ERROR;
                    }
                    stage_directory(argv[i + 3] , current_directory , main_directory);//Error handeling cann't be done 
                }
            }
            return SUCCEED;
        }
        else if(strcmp(argv[2] , "-n") == 0)
        {
            char current_directory[MAX_DIRECTORY_NAME_LENGTH];
            if(argc != 4)
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
            else if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
            {
                DIRECTORY_OPENING_ERROR
                return ERROR;
            }
            else if(show(atoi(argv[3]) , current_directory) == ERROR)
            {
                FAIL_MASSAGE("Showing stagging status")
                return ERROR;
            }
            else
            {
                SUCCESS_MASSAGE("Showing stagging status")
                return SUCCEED;
            }
        }
        else if(strcmp(argv[2] , "-redo") == 0)
        {
            
        }
        else if(argc == 3)
        {
            if(opendir(argv[2]) == NULL)
            {
                if(stage_file(argv[2]) == ERROR)
                {
                    return ERROR;
                }
                else
                {
                    return SUCCEED;
                }
            }
            else
            {
                char current_directory[MAX_DIRECTORY_NAME_LENGTH];
                char main_directory[MAX_DIRECTORY_NAME_LENGTH];
                if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                {
                    DIRECTORY_OPENING_ERROR
                    return ERROR;
                }
                else if(getcwd(main_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                {
                    DIRECTORY_OPENING_ERROR
                    return ERROR;
                }
                else if(stage_directory(argv[2] , current_directory , main_directory) == ERROR)
                {
                    return ERROR;
                }
                else
                {
                    return SUCCEED;
                }
            }
        }
        else
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "reset") == 0)
    {
        if(strcmp(argv[2] , "-undo") == 0)
        {
            if(argc != 3)
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
            else if(undo() == ERROR)
            {
                return ERROR;
            }
            else
            {
                return SUCCEED;
            }
        }
        else if(strcmp(argv[2] , "-f") == 0)
        {
            for(int i = 0 ; i < argc - 3 ; i++)
            {
                if(opendir(argv[i + 3]) == NULL)
                {
                    reset_file(argv[i + 3]);//Error handeling cann't be done 
                }
                else
                {
                    char current_directory[MAX_DIRECTORY_NAME_LENGTH];
                    char main_directory[MAX_DIRECTORY_NAME_LENGTH];
                    if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                    {
                        DIRECTORY_OPENING_ERROR
                        return ERROR;
                    }
                    else if(getcwd(main_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                    {
                        DIRECTORY_OPENING_ERROR
                        return ERROR;
                    }
                    reset_directory(argv[i + 3] , current_directory , main_directory);//Error handeling cann't be done 
                }
            }
            return SUCCEED;
        }
        else if(argc == 3)
        {
            if(opendir(argv[2]) == NULL)
            {
                if(reset_file(argv[2]) == ERROR)
                {
                    return ERROR;
                }
                else
                {
                    return SUCCEED;
                }
            }
            else
            {
                char current_directory[MAX_DIRECTORY_NAME_LENGTH];
                char main_directory[MAX_DIRECTORY_NAME_LENGTH];
                if(getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                {
                    DIRECTORY_OPENING_ERROR
                    return ERROR;
                }
                else if(getcwd(main_directory , MAX_DIRECTORY_NAME_LENGTH) == NULL)
                {
                    DIRECTORY_OPENING_ERROR
                    return ERROR;
                }
                else if(reset_directory(argv[2] , current_directory , main_directory) == ERROR)
                {
                    return ERROR;
                }
                else
                {
                    return SUCCEED;
                }
            }
        }
        else
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "status") == 0)
    {
        if(argc != 2)
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
        else
        {
            char current_direcotry[MAX_DIRECTORY_NAME_LENGTH];
            if(getcwd(current_direcotry , MAX_DIRECTORY_NAME_LENGTH) == NULL)
            {
                DIRECTORY_OPENING_ERROR
                return ERROR;
            }
            else if(status(current_direcotry) == ERROR)
            {
                return ERROR;
            }
            else
            {
                return SUCCEED;
            }
        }
    }
}