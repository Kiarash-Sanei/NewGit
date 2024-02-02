#include "Header.h"

//Default branch:
char branch_name[MAX_BRANCH_NAME] = "master";
int HEAD;

int main(int argc , char** argv)
{
    char* path = NewGit_finder();
    if(path != NULL)
    {
        strcat(path , "/.NewGit/HEADInformation.txt");
        FILE* file_HEAD = fopen(path , "r");
        if(file_HEAD != NULL)
        {
            HEAD_information new;
            if(fread(&new , sizeof(HEAD_information) , 1 , file_HEAD) == 1)
            {
                HEAD = new . HEAD;
                strcpy(branch_name , new . branch_name);
            }
        }
    }
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
                    stage_directory(argv[i + 3]);//Error handeling cann't be done 
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
                if(stage_directory(argv[2]) == ERROR)
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
                    reset_directory(argv[i + 3]);//Error handeling cann't be done 
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
                reset_directory(argv[2]);
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
            if(status(current_direcotry) == ERROR)
            {
                return ERROR;
            }
            else
            {
                return SUCCEED;
            }
        }
    }
    else if(strcmp(argv[1] , "branch") == 0)
    {
        if(argc == 2)
        {
            if(branch_shower() == ERROR)
            {
                FAIL_MASSAGE("Showing branches")
                return ERROR;
            }
            else
            {
                SUCCESS_MASSAGE("Showing branches")
                return SUCCEED;
            }
        }
        else if(argc == 3)
        {
            char current_direcotry[MAX_DIRECTORY_NAME_LENGTH];
            if(getcwd(current_direcotry , MAX_DIRECTORY_NAME_LENGTH) == NULL)
            {
                DIRECTORY_OPENING_ERROR
                return ERROR;
            }
            if(branch_maker(branch_name , HEAD , argv[2] , current_direcotry) == ERROR)
            {
                FAIL_MASSAGE("Making branch")
                return ERROR;
            }
            else
            {
                SUCCESS_MASSAGE("Making branch")
                return SUCCEED;
            }
        }
        else
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "commit") == 0)
    {
        if(strcmp(argv[2] , "-m") == 0)
        {
            if(argc == 4)
            {
                if(strlen(argv[3]) > MAX_COMMIT_MESSAGE_LENGTH)
                {
                    MASSAGE_IS_TOO_LONG
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
                else
                {
                    if(add_commit(branch_name , argv[3] , &HEAD) == SUCCEED)
                    {
                        char* path = NewGit_finder();
                        strcat(path , "/.NewGit/HEADInformation.txt");
                        FILE* file = fopen(path , "w");
                        HEAD_information new;
                        new . HEAD = HEAD;
                        strcpy(new . branch_name , branch_name);
                        fwrite(&new , sizeof(HEAD_information) , 1 , file);
                        return SUCCEED;
                    }
                    else
                    {
                        FAIL_MASSAGE("Committing")
                        return ERROR;
                    }
                }
            }
            else
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
        }
        if(strcmp(argv[2] , "-s") == 0)
        {
            if(argc == 4)
            {
                if(strlen(argv[3]) > MAX_ALIAS_LENGHT)
                {
                    SHORTCUT_IS_TOO_LONG
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
                else
                {
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/setting.txt");
                    FILE* file_setting = fopen(path , "r");
                    massage_information current_shortcut;
                    int flag = 0;
                    while(fread(&current_shortcut , sizeof(massage_information) , 1 , file_setting) == 1)
                    {
                        if(strcmp(current_shortcut . shortcut , argv[3]) == 0)
                        {
                            flag = 1;
                            break; 
                        }
                    }
                    if(flag == 0)
                    {
                        SHORTCUT_EXISTENCE_ERROR
                        return ERROR;
                    }
                    if(add_commit(branch_name , current_shortcut . massage , &HEAD) == SUCCEED)
                    {
                        char* path = NewGit_finder();
                        strcat(path , "/.NewGit/HEADInformation.txt");
                        FILE* file = fopen(path , "w");
                        HEAD_information new;
                        new . HEAD = HEAD;
                        strcpy(new . branch_name , branch_name);
                        fwrite(&new , sizeof(HEAD_information) , 1 , file);
                        return SUCCEED;
                    }
                    else
                    {
                        FAIL_MASSAGE("Committing")
                        return ERROR;
                    }
                }
            }
            else
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
        }
        else
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "set") == 0)
    {
        if((strcmp(argv[2] , "-m") == 0) && (strcmp(argv[4] , "-s") == 0))
        {
            if(argc == 6)
            {
                if(strlen(argv[3]) > MAX_COMMIT_MESSAGE_LENGTH)
                {
                    MASSAGE_IS_TOO_LONG
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
                if(strlen(argv[5]) > MAX_ALIAS_LENGHT)
                {
                    SHORTCUT_IS_TOO_LONG
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
                else
                {
                    if(set(argv[3] , argv[5]) == SUCCEED)
                    {
                        return SUCCEED;
                    }
                    else
                    {
                        FAIL_MASSAGE("Setting")
                        return ERROR;
                    }
                }
            }
            else
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
        }
        else
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "replace") == 0)
    {
        if((strcmp(argv[2] , "-m") == 0) && (strcmp(argv[4] , "-s") == 0))
        {
            if(argc == 6)
            {
                if(strlen(argv[3]) > MAX_COMMIT_MESSAGE_LENGTH)
                {
                    MASSAGE_IS_TOO_LONG
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
                if(strlen(argv[5]) > MAX_ALIAS_LENGHT)
                {
                    SHORTCUT_IS_TOO_LONG
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
                else
                {
                    if(replace(argv[3] , argv[5]) == SUCCEED)
                    {
                        return SUCCEED;
                    }
                    else
                    {
                        FAIL_MASSAGE("Replacing")
                        return ERROR;
                    }
                }
            }
            else
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
        }
        else
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "remove") == 0)
    {
        if(strcmp(argv[2] , "-s") == 0)
        {
            if(argc == 4)
            {
                if(strlen(argv[3]) > MAX_ALIAS_LENGHT)
                {
                    SHORTCUT_IS_TOO_LONG
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
                else
                {
                    if(remove_shortcut(argv[3]) == SUCCEED)
                    {
                        return SUCCEED;
                    }
                    else
                    {
                        FAIL_MASSAGE("Removing")
                        return ERROR;
                    }
                }
            }
            else
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
        }
        else
        {
            INVALID_INPUT_ERROR
            return ERROR;
        }
    }
    else if(strcmp(argv[1] , "log") == 0)
    {
        if(argc == 2)
        {
            if(log_show() == ERROR)
            {
                FAIL_MASSAGE("Showing log")
                return ERROR;
            }
            else
            {
                return SUCCEED;
            }
        }
        else if(strcmp(argv[2] , "-n") == 0)
        {
            if(argc == 4)
            {
                if(log_number(atoi(argv[3])) == ERROR)
                {
                    FAIL_MASSAGE("Showing log")
                    return ERROR;
                }
                else
                {
                    return SUCCEED;
                }
            }
        }
        else if(strcmp(argv[2] , "-branch") == 0)
        {
            if(argc == 4)
            {
                if(log_branch(argv[3]) == ERROR)
                {
                    FAIL_MASSAGE("Showing log")
                    return ERROR;
                }
                else
                {
                    return SUCCEED;
                }
            }    
        }
        else if(strcmp(argv[2] , "-author") == 0)
        {
            if(argc == 4)
            {
                if(log_author(argv[3]) == ERROR)
                {
                    FAIL_MASSAGE("Showing log")
                    return ERROR;
                }
                else
                {
                    return SUCCEED;
                }
            }    
        }
        else if(strcmp(argv[2] , "-since") == 0)
        {
            if(argc == 4)
            {
                tm temporary;
                int year;
                int month;
                int day;
                sscanf(argv[3] , "%d/%d/%d" , &year, &month, &day);
                temporary . tm_year = year - 1900;
                temporary . tm_mon = month - 1;
                temporary . tm_mday = day;                
                if(log_time_since(mktime(&temporary)) == ERROR)
                {
                    FAIL_MASSAGE("Showing log")
                    return ERROR;
                }
                else
                {
                    return SUCCEED;
                }
            }    
        }
        else if(strcmp(argv[2] , "-before") == 0)
        {
            if(argc == 4)
            {
                tm temporary;
                int year;
                int month;
                int day;
                sscanf(argv[3] , "%d/%d/%d" , &year, &month, &day);
                temporary . tm_year = year - 1900;
                temporary . tm_mon = month - 1;
                temporary . tm_mday = day;
                if(log_time_before(mktime(&temporary)) == ERROR)
                {
                    FAIL_MASSAGE("Showing log")
                    return ERROR;
                }
                else
                {
                    return SUCCEED;
                }
            }    
        }
    }
}