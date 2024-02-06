#include "Header.h"

int main(int argc , char** argv)
{
    //Default branch:
    HEAD_information* here = (HEAD_information*) malloc(sizeof(HEAD_information));
    strcpy(here -> branch_name , "master");
    here -> HEAD = -2;
    here -> read_only = 0;
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
                here -> HEAD = new . HEAD;
                here -> read_only = new . read_only;
                strcpy(here -> branch_name , new . branch_name);
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
            if(here -> read_only == -1)
            {
                READ_ONLY_ERROR
                return ERROR;
            }
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
        else if(argc == 3)
        {
            if(here -> read_only == -1)
            {
                READ_ONLY_ERROR
                return ERROR;
            }
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
            if(branch_maker(here -> branch_name , here -> HEAD , argv[2] , current_direcotry) == ERROR)
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
                    if(add_commit(here -> branch_name , argv[3] , &(here -> HEAD)) == SUCCEED)
                    {
                        char* path = NewGit_finder();
                        strcat(path , "/.NewGit/HEADInformation.txt");
                        FILE* file = fopen(path , "w");
                        fwrite(here , sizeof(HEAD_information) , 1 , file);
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
                    if(add_commit(here -> branch_name , current_shortcut . massage , &(here -> HEAD)) == SUCCEED)
                    {
                        char* path = NewGit_finder();
                        strcat(path , "/.NewGit/HEADInformation.txt");
                        FILE* file = fopen(path , "w");
                        fwrite(here , sizeof(HEAD_information) , 1 , file);
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
        else if(strcmp(argv[2] , "-search") == 0)
        {
            if(argc == 4)
            {
                if(log_word(argv[3]) == ERROR)
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
    else if(strcmp(argv[1] , "checkout") == 0)
    {
        if(argc == 3)
        {
            if(('0' <= argv[2][0]) && ('9' >= argv[2][0]))
            {
                HEAD_information temporary;
                int commit_hash = atoi(argv[2]);
                char* path = NewGit_finder();
                if(path == NULL)
                {
                    NewGit_EXISTENCE_ERROR
                    return ERROR;
                }
                strcat(path , "/.NewGit/");
                strcat(path , "commitLog.txt");
                FILE* file = fopen(path , "r");
                commit_information current_commit;
                free(path);
                if(file == NULL)
                {
                    LACK_OF_COMMIT
                    return ERROR;
                }
                else
                {
                    int flag = 0;
                    while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                    {
                        if(current_commit . commit_hash == commit_hash)
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0)
                    {
                        COMMIT_EXISTENCE_ERROR
                        return ERROR;
                    }
                    else
                    {
                        temporary . HEAD = current_commit . commit_hash;
                        strcpy(temporary . branch_name , current_commit . commit_branch);
                    }
                }
                fclose(file);
                here -> read_only = -1;
                path = NewGit_finder();
                strcat(path , "/.NewGit/HEADInformation.txt");
                file = fopen(path , "w");
                fwrite(here , sizeof(HEAD_information) , 1 , file);
                fclose(file);
                free(path);
                if(checkout_commit_hash(&temporary) != SUCCEED)
                {
                    here -> read_only = 0;
                    path = NewGit_finder();
                    strcat(path , "/.NewGit/HEADInformation.txt");
                    file = fopen(path , "w");
                    fwrite(here , sizeof(HEAD_information) , 1 , file);
                    fclose(file);
                    free(path);
                    FAIL_MASSAGE("Checking out")
                    return ERROR;
                }
                return SUCCEED;
            }
            else if(strcmp(argv[2] , "HEAD") == 0)
            {
                if(checkout(here -> branch_name , here) != SUCCEED)
                {
                    FAIL_MASSAGE("Checking out")
                    return ERROR;
                }
                return SUCCEED;
            }
            else
            {
                if(checkout(argv[2] , here) != SUCCEED)
                {
                    FAIL_MASSAGE("Checking out")
                    return ERROR;
                }
                return SUCCEED;
            }
        }
        else if(argc ==5)
        {
            if(strcmp(argv[2] , "HEAD") == 0)
            {
                if(strcmp(argv[3] , "-n") == 0)
                {
                    int n = atoi(argv[4]);
                    n++;
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/commitLog.txt");
                    FILE* file = fopen(path , "r");
                    commit_information all[MAX_COMMIT_COUNT];
                    int index = 0;
                    while(fread(&(all[index]) , sizeof(commit_information) , 1 , file) == 1)
                    {
                        if(strcmp(here -> branch_name , all[index] . commit_branch) == 0)
                        {
                            index++;
                        }
                    } 
                    fclose(file);
                    index -= n;
                    HEAD_information temporary;
                    temporary . HEAD = all[index] . commit_hash;
                    strcpy(temporary . branch_name , all[index] . commit_branch);
                    here -> read_only = -1;
                    path = NewGit_finder();
                    strcat(path , "/.NewGit/HEADInformation.txt");
                    file = fopen(path , "w");
                    fwrite(here , sizeof(HEAD_information) , 1 , file);
                    fclose(file);
                    free(path);
                    if(checkout_commit_hash(&temporary) != SUCCEED)
                    {
                        here -> read_only = 0;
                        path = NewGit_finder();
                        strcat(path , "/.NewGit/HEADInformation.txt");
                        file = fopen(path , "w");
                        fwrite(here , sizeof(HEAD_information) , 1 , file);
                        fclose(file);
                        free(path);
                        FAIL_MASSAGE("Checking out")
                        return ERROR;
                    }
                    return SUCCEED;
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
    else if(strcmp(argv[1] , "revert") == 0)
    {
        if(strcmp(argv[2] , "-m") == 0)
        {
            if(strncmp(argv[4] , "HEAD-" , 5) == 0)
            {
                char temporary[MAX_WORD_LENGTH];
                strcpy(temporary , argv[4]);
                strtok(temporary , "-");
                strcpy(temporary , strtok(NULL , "-"));
                int n = atoi(temporary);
                n++;
                char* path = NewGit_finder();
                if(path == NULL)
                {
                    NewGit_EXISTENCE_ERROR
                    return ERROR;
                }
                strcat(path , "/.NewGit/commitLog.txt");
                FILE* file = fopen(path , "r");
                commit_information all[MAX_COMMIT_COUNT];
                int index = 0;
                while(fread(&(all[index]) , sizeof(commit_information) , 1 , file) == 1)
                {
                    if(strcmp(here -> branch_name , all[index] . commit_branch) == 0)
                    {
                        index++;
                    }
                } 
                fclose(file);
                index -= n;
                HEAD_information temp;
                temp . HEAD = all[index] . commit_hash;
                strcpy(temp . branch_name , all[index] . commit_branch);
                if(strchr(temp . branch_name , '+') != NULL)
                {
                    MERGE_EXISTENCE_ERROR
                    return ERROR;
                }
                if(checkout_commit_hash(&temp) != SUCCEED)
                {
                    FAIL_MASSAGE("Checking out")
                    return ERROR;
                }
                free(path);
                path = NewGit_finder();
                char command[MAX_COMMAND_LENGTH];
                strcpy(command , path);
                strcat(command , "/.NewGit/Branches/");
                strcat(command , temp . branch_name);
                strcat(command , "/");
                char a[MAX_WORD_LENGTH];
                citoa(temp . HEAD , a , 10);
                strcat(command , a);
                char current_directory[MAX_DIRECTORY_NAME_LENGTH];
                getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH);
                chdir(command);
                char* stage = NewGit_finder();
                strcat(stage , "/.NewGit/Stage");
                DIR* directrory = opendir(command);
                dirent* entry = readdir(directrory);
                while(entry != NULL)
                {
                    if(entry -> d_type == DT_REG)
                    {
                        copy_file(stage , entry -> d_name);
                    }
                    else if((strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
                    {
                        copy_directory(stage , entry -> d_name);
                    }
                    entry = readdir(directrory);
                }
                chdir(current_directory);
                free(path);
                if(add_commit(here -> branch_name , argv[3] , &(here -> HEAD)) == SUCCEED)
                {
                    char* path = NewGit_finder();
                    strcat(path , "/.NewGit/HEADInformation.txt");
                    FILE* file = fopen(path , "w");
                    fwrite(here , sizeof(HEAD_information) , 1 , file);
                    return SUCCEED;
                }
            }
            else
            {
                HEAD_information temporary;
                int commit_hash = atoi(argv[4]);
                char* path = NewGit_finder();
                if(path == NULL)
                {
                    NewGit_EXISTENCE_ERROR
                    return ERROR;
                }
                strcat(path , "/.NewGit/");
                strcat(path , "commitLog.txt");
                FILE* file = fopen(path , "r");
                commit_information current_commit;
                free(path);
                if(file == NULL)
                {
                    LACK_OF_COMMIT
                    return ERROR;
                }
                else
                {
                    int flag = 0;
                    while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                    {
                        if(current_commit . commit_hash == commit_hash)
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0)
                    {
                        COMMIT_EXISTENCE_ERROR
                        return ERROR;
                    }
                    else
                    {
                        temporary . HEAD = current_commit . commit_hash;
                        strcpy(temporary . branch_name , current_commit . commit_branch);
                    }
                }
                fclose(file);
                if(strchr(temporary . branch_name , '+') != NULL)
                {
                    MERGE_EXISTENCE_ERROR
                    return ERROR;
                }
                if(checkout_commit_hash(&temporary) != SUCCEED)
                {
                    return ERROR;
                }
                strcpy(here -> branch_name , temporary . branch_name);
                path = NewGit_finder();
                char command[MAX_COMMAND_LENGTH];
                strcpy(command , path);
                strcat(command , "/.NewGit/Branches/");
                strcat(command , temporary . branch_name);
                strcat(command , "/");
                char a[MAX_WORD_LENGTH];
                citoa(temporary . HEAD , a , 10);
                strcat(command , a);
                char current_directory[MAX_DIRECTORY_NAME_LENGTH];
                getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH);
                chdir(command);
                char* stage = NewGit_finder();
                strcat(stage , "/.NewGit/Stage");
                DIR* directrory = opendir(command);
                dirent* entry = readdir(directrory);
                while(entry != NULL)
                {
                    if(entry -> d_type == DT_REG)
                    {
                        copy_file(stage , entry -> d_name);
                    }
                    else if((strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
                    {
                        copy_directory(stage , entry -> d_name);
                    }
                    entry = readdir(directrory);
                }
                chdir(current_directory);
                free(path);
                if(add_commit(here -> branch_name , argv[3] , &(here -> HEAD)) == SUCCEED)
                {
                    char* path = NewGit_finder();
                    strcat(path , "/.NewGit/HEADInformation.txt");
                    FILE* file = fopen(path , "w");
                    fwrite(here , sizeof(HEAD_information) , 1 , file);
                    return SUCCEED;
                }
            }
        }
        if(strncmp(argv[2] , "HEAD-" , 5) == 0)
        {
            char temporary[MAX_WORD_LENGTH];
            strcpy(temporary , argv[2]);
            strtok(temporary , "-");
            strcpy(temporary , strtok(NULL , "-"));
            int n = atoi(temporary);
            n++;
            char* path = NewGit_finder();
            if(path == NULL)
            {
                NewGit_EXISTENCE_ERROR
                return ERROR;
            }
            strcat(path , "/.NewGit/commitLog.txt");
            FILE* file = fopen(path , "r");
            commit_information all[MAX_COMMIT_COUNT];
            int index = 0;
            while(fread(&(all[index]) , sizeof(commit_information) , 1 , file) == 1)
            {
                if(strcmp(here -> branch_name , all[index] . commit_branch) == 0)
                {
                    index++;
                }
            } 
            fclose(file);
            index -= n;
            HEAD_information temp;
            temp . HEAD = all[index] . commit_hash;
            strcpy(temp . branch_name , all[index] . commit_branch);
            if(checkout_commit_hash(&temp) != SUCCEED)
            {
                FAIL_MASSAGE("Checking out")
                return ERROR;
            }
            free(path);
            path = NewGit_finder();
            char command[MAX_COMMAND_LENGTH];
            strcpy(command , path);
            strcat(command , "/.NewGit/Branches/");
            strcat(command , temp . branch_name);
            strcat(command , "/");
            char a[MAX_WORD_LENGTH];
            citoa(temp . HEAD , a , 10);
            strcat(command , a);
            char current_directory[MAX_DIRECTORY_NAME_LENGTH];
            getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH);
            chdir(command);
            char* stage = NewGit_finder();
            strcat(stage , "/.NewGit/Stage");
            DIR* directrory = opendir(command);
            dirent* entry = readdir(directrory);
            while(entry != NULL)
            {
                if(entry -> d_type == DT_REG)
                {
                    copy_file(stage , entry -> d_name);
                }
                else if((strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
                {
                    copy_directory(stage , entry -> d_name);
                }
                entry = readdir(directrory);
            }
            chdir(current_directory);
            free(path);
            if(add_commit(here -> branch_name , all[index] . commit_massage , &(here -> HEAD)) == SUCCEED)
            {
                char* path = NewGit_finder();
                strcat(path , "/.NewGit/HEADInformation.txt");
                FILE* file = fopen(path , "w");
                fwrite(here , sizeof(HEAD_information) , 1 , file);
                return SUCCEED;
            }
        }
        else if(strcmp(argv[2] , "-n") == 0)
        {
            if(argc == 3)
            {
                if(checkout_commit_hash(here) == ERROR)
                {
                    return ERROR;
                }
            }
            else if(argc == 4)
            {
                HEAD_information temporary;
                int commit_hash = atoi(argv[3]);
                char* path = NewGit_finder();
                if(path == NULL)
                {
                    NewGit_EXISTENCE_ERROR
                    return ERROR;
                }
                strcat(path , "/.NewGit/");
                strcat(path , "commitLog.txt");
                FILE* file = fopen(path , "r");
                commit_information current_commit;
                free(path);
                if(file == NULL)
                {
                    LACK_OF_COMMIT
                    return ERROR;
                }
                else
                {
                    int flag = 0;
                    while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                    {
                        if(current_commit . commit_hash == commit_hash)
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0)
                    {
                        COMMIT_EXISTENCE_ERROR
                        return ERROR;
                    }
                    else
                    {
                        temporary . HEAD = current_commit . commit_hash;
                        strcpy(temporary . branch_name , current_commit . commit_branch);
                    }
                }
                fclose(file);
                if(checkout_commit_hash(&temporary) == ERROR)
                {
                    return ERROR;
                }
            }
        }
        else
        {
            HEAD_information temporary;
            int commit_hash = atoi(argv[2]);
            char* path = NewGit_finder();
            if(path == NULL)
            {
                NewGit_EXISTENCE_ERROR
                return ERROR;
            }
            strcat(path , "/.NewGit/");
            strcat(path , "commitLog.txt");
            FILE* file = fopen(path , "r");
            commit_information current_commit;
            free(path);
            if(file == NULL)
            {
                LACK_OF_COMMIT
                return ERROR;
            }
            else
            {
                int flag = 0;
                while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                {
                    if(current_commit . commit_hash == commit_hash)
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    COMMIT_EXISTENCE_ERROR
                    return ERROR;
                }
                else
                {
                    temporary . HEAD = current_commit . commit_hash;
                    strcpy(temporary . branch_name , current_commit . commit_branch);
                }
            }
            fclose(file);
            if(checkout_commit_hash(&temporary) != SUCCEED)
            {
                return ERROR;
            }
            strcpy(here -> branch_name , temporary . branch_name); 
            path = NewGit_finder();
            char command[MAX_COMMAND_LENGTH];
            strcpy(command , path);
            strcat(command , "/.NewGit/Branches/");
            strcat(command , temporary . branch_name);
            strcat(command , "/");
            char a[MAX_WORD_LENGTH];
            citoa(temporary . HEAD , a , 10);
            strcat(command , a);
            char current_directory[MAX_DIRECTORY_NAME_LENGTH];
            getcwd(current_directory , MAX_DIRECTORY_NAME_LENGTH);
            chdir(command);
            char* stage = NewGit_finder();
            strcat(stage , "/.NewGit/Stage");
            DIR* directrory = opendir(command);
            dirent* entry = readdir(directrory);
            while(entry != NULL)
            {
                if(entry -> d_type == DT_REG)
                {
                    copy_file(stage , entry -> d_name);
                }
                else if((strcmp(entry -> d_name , ".") != 0) && (strcmp(entry -> d_name , "..") != 0))
                {
                    copy_directory(stage , entry -> d_name);
                }
                entry = readdir(directrory);
            }
            chdir(current_directory);
            free(path);
            if(add_commit(here -> branch_name , current_commit . commit_massage , &(here -> HEAD)) == SUCCEED)
            {
                char* path = NewGit_finder();
                strcat(path , "/.NewGit/HEADInformation.txt");
                FILE* file = fopen(path , "w");
                fwrite(here , sizeof(HEAD_information) , 1 , file);
                return SUCCEED;
            }
        }
    }
    else if(strcmp(argv[1] , "tag") == 0)
    {
        if(argc == 2)
        {
            all_tag_shower();
            return SUCCEED;
        }
        else if(strcmp(argv[2] , "show") == 0)
        {
            if(argc == 4)
            {
                tag_shower(argv[3]);
                return SUCCEED;
            }
            else
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
        }
        else if(strcmp(argv[2] , "-a") == 0)
        {
            if(argc == 4)
            {
                char* path = NewGit_finder();
                if(path == NULL)
                {
                    NewGit_EXISTENCE_ERROR
                    return ERROR;
                }
                strcat(path , "/.NewGit/");
                strcat(path , "commitLog.txt");
                FILE* file = fopen(path , "r");
                commit_information current_commit;
                free(path);
                if(file == NULL)
                {
                    LACK_OF_COMMIT
                    return ERROR;
                }
                else
                {
                    while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                    {
                        if(current_commit . commit_hash == here -> HEAD)
                        {
                            break;
                        }
                    }
                }
                tag_maker(current_commit , "" , argv[3]);
                return SUCCEED;
            }
            else if(argc == 6)
            {
                if(strcmp(argv[4] , "-m") == 0)
                {
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/");
                    strcat(path , "commitLog.txt");
                    FILE* file = fopen(path , "r");
                    commit_information current_commit;
                    free(path);
                    if(file == NULL)
                    {
                        LACK_OF_COMMIT
                        return ERROR;
                    }
                    else
                    {
                        while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                        {
                            if(current_commit . commit_hash == here -> HEAD)
                            {
                                break;
                            }
                        }
                    }
                    tag_maker(current_commit , argv[5] , argv[3]);
                    return SUCCEED;
                }
                else if(strcmp(argv[4] , "-c") == 0)
                {
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/");
                    strcat(path , "commitLog.txt");
                    FILE* file = fopen(path , "r");
                    commit_information current_commit;
                    free(path);
                    if(file == NULL)
                    {
                        LACK_OF_COMMIT
                        return ERROR;
                    }
                    else
                    {
                        while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                        {
                            if(current_commit . commit_hash == atoi(argv[5]))
                            {
                                break;
                            }
                        }
                    }
                    tag_maker(current_commit , "" , argv[3]);
                    return SUCCEED;
                }
                else
                {
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
            }
            else if(argc == 8)
            {
                if((strcmp(argv[4] , "-m") == 0) && (strcmp(argv[6] , "-c") == 0))
                {
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/");
                    strcat(path , "commitLog.txt");
                    FILE* file = fopen(path , "r");
                    commit_information current_commit;
                    free(path);
                    if(file == NULL)
                    {
                        LACK_OF_COMMIT
                        return ERROR;
                    }
                    else
                    {
                        while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                        {
                            if(current_commit . commit_hash == atoi(argv[7]))
                            {
                                break;
                            }
                        }
                    }
                    tag_maker(current_commit , argv[5] , argv[3]);
                    return SUCCEED;
                }
                else if((strcmp(argv[4] , "-c") == 0) && (strcmp(argv[6] , "-m") == 0))
                {
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/");
                    strcat(path , "commitLog.txt");
                    FILE* file = fopen(path , "r");
                    commit_information current_commit;
                    free(path);
                    if(file == NULL)
                    {
                        LACK_OF_COMMIT
                        return ERROR;
                    }
                    else
                    {
                        while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                        {
                            if(current_commit . commit_hash == atoi(argv[5]))
                            {
                                break;
                            }
                        }
                    }
                    tag_maker(current_commit , argv[7] , argv[3]);
                    return SUCCEED;
                }
                else
                {
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
            }
            else if(argc == 5)
            {
                if(strcmp(argv[4] , "-f") == 0)
                {
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/");
                    strcat(path , "commitLog.txt");
                    FILE* file = fopen(path , "r");
                    commit_information current_commit;
                    free(path);
                    if(file == NULL)
                    {
                        LACK_OF_COMMIT
                        return ERROR;
                    }
                    else
                    {
                        while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                        {
                            if(current_commit . commit_hash == here -> HEAD)
                            {
                                break;
                            }
                        }
                    }
                    tag_remaker(current_commit , "" , argv[3]);
                    return SUCCEED;
                }
                else
                {
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
            }
            else if(argc == 7)
            {
                if((strcmp(argv[4] , "-m") == 0) && (strcmp(argv[6] , "-f") == 0))
                {
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/");
                    strcat(path , "commitLog.txt");
                    FILE* file = fopen(path , "r");
                    commit_information current_commit;
                    free(path);
                    if(file == NULL)
                    {
                        LACK_OF_COMMIT
                        return ERROR;
                    }
                    else
                    {
                        while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                        {
                            if(current_commit . commit_hash == here -> HEAD)
                            {
                                break;
                            }
                        }
                    }
                    tag_remaker(current_commit , argv[5] , argv[3]);
                    return SUCCEED;
                }
                else if((strcmp(argv[4] , "-c") == 0) && (strcmp(argv[6] , "-f") == 0))
                {
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/");
                    strcat(path , "commitLog.txt");
                    FILE* file = fopen(path , "r");
                    commit_information current_commit;
                    free(path);
                    if(file == NULL)
                    {
                        LACK_OF_COMMIT
                        return ERROR;
                    }
                    else
                    {
                        while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                        {
                            if(current_commit . commit_hash == atoi(argv[5]))
                            {
                                break;
                            }
                        }
                    }
                    tag_remaker(current_commit , "" , argv[3]);
                    return SUCCEED;
                }
                else
                {
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
            }
            else if(argc == 9)
            {
                if((strcmp(argv[4] , "-m") == 0) && (strcmp(argv[6] , "-c") == 0) && (strcmp(argv[8] , "-f") == 0))
                {
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/");
                    strcat(path , "commitLog.txt");
                    FILE* file = fopen(path , "r");
                    commit_information current_commit;
                    free(path);
                    if(file == NULL)
                    {
                        LACK_OF_COMMIT
                        return ERROR;
                    }
                    else
                    {
                        while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                        {
                            if(current_commit . commit_hash == atoi(argv[7]))
                            {
                                break;
                            }
                        }
                    }
                    tag_remaker(current_commit , argv[5] , argv[3]);
                    return SUCCEED;
                }
                else if((strcmp(argv[4] , "-c") == 0) && (strcmp(argv[6] , "-m") == 0) && (strcmp(argv[8] , "-f") == 0))
                {
                    char* path = NewGit_finder();
                    if(path == NULL)
                    {
                        NewGit_EXISTENCE_ERROR
                        return ERROR;
                    }
                    strcat(path , "/.NewGit/");
                    strcat(path , "commitLog.txt");
                    FILE* file = fopen(path , "r");
                    commit_information current_commit;
                    free(path);
                    if(file == NULL)
                    {
                        LACK_OF_COMMIT
                        return ERROR;
                    }
                    else
                    {
                        while(fread(&current_commit , sizeof(commit_information) , 1 , file) == 1)
                        {
                            if(current_commit . commit_hash == atoi(argv[5]))
                            {
                                break;
                            }
                        }
                    }
                    tag_remaker(current_commit , argv[7] , argv[3]);
                    return SUCCEED;
                }
                else
                {
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
            }
        }
    }
    else if(strcmp(argv[1] , "diff") == 0)
    {
        if(strcmp(argv[2] , "-f") == 0)
        {
            if(argc == 9)
            {
                if((strcmp(argv[5] , "-line1") == 0) && (strcmp(argv[7] , "-line2") == 0))
                {
                    int line_begin_1 = atoi(strtok(argv[6] , "-"));
                    int line_end_1 = atoi(strtok(NULL , "-"));
                    int line_begin_2 = atoi(strtok(argv[8] , "-"));
                    int line_end_2 = atoi(strtok(NULL , "-"));
                    diff_file(argv[3] , argv[4] , line_begin_1 , line_end_1 , line_begin_2 , line_end_2);
                    return SUCCEED;
                }
                else
                {
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
            }
            else if(argc == 7)
            {
                if(strcmp(argv[5] , "-line1") == 0)
                {
                    int line_begin_1 = atoi(strtok(argv[6] , "-"));
                    int line_end_1 = atoi(strtok(NULL , "-"));
                    diff_file(argv[3] , argv[4] , line_begin_1 , line_end_1 , 1 , 100);
                    return SUCCEED;
                }
                else if(strcmp(argv[5] , "-line2") == 0)
                {
                    int line_begin_2 = atoi(strtok(argv[6] , "-"));
                    int line_end_2 = atoi(strtok(NULL , "-"));
                    diff_file(argv[3] , argv[4] , 1 , 100 , line_begin_2 , line_end_2);
                    return SUCCEED;
                }
                else
                {
                    INVALID_INPUT_ERROR
                    return ERROR;
                }
            }
            else if(argc == 5)
            {
                diff_file(argv[3] , argv[4] , 1 , 100 , 1 , 100);
                return SUCCEED;
            }
            else
            {
                INVALID_INPUT_ERROR
                return ERROR;
            }
        }
        else if(strcmp(argv[2] , "-c") == 0)
        {
            if(argc == 5)
            {
                char* path = NewGit_finder();
                if(path == NULL)
                {
                    NewGit_EXISTENCE_ERROR
                    return ERROR;
                }
                strcat(path , "/.NewGit/commitLog.txt");
                FILE* file = fopen(path , "r");
                int flag_1 = 0;
                int flag_2 = 0;
                commit_information commit_1;
                commit_information commit_2;
                commit_information temporary;
                while(fread(&temporary , sizeof(commit_information) , 1 , file) == 1)
                {
                    if(temporary . commit_hash == atoi(argv[3]))
                    {
                        strcpy(commit_1 . commit_massage , temporary . commit_massage);
                        strcpy(commit_1 . commit_branch , temporary . commit_branch);
                        strcpy(commit_1 . commit_user_email , temporary . commit_user_email);
                        strcpy(commit_1 . commit_user_name , temporary . commit_user_name);
                        commit_1 . commit_time = temporary . commit_time;
                        commit_1 . commit_number = temporary . commit_number;
                        commit_1 . commit_hash = temporary . commit_hash;
                        flag_1 = 1;
                    }
                    else if(temporary . commit_hash == atoi(argv[4]))
                    {
                        strcpy(commit_1 . commit_massage , temporary . commit_massage);
                        strcpy(commit_2 . commit_branch , temporary . commit_branch);
                        strcpy(commit_2 . commit_user_email , temporary . commit_user_email);
                        strcpy(commit_2 . commit_user_name , temporary . commit_user_name);
                        commit_2 . commit_time = temporary . commit_time;
                        commit_2 . commit_number = temporary . commit_number;
                        commit_2 . commit_hash = temporary . commit_hash;
                        flag_2 = 1;
                    }
                }
                if(flag_1 + flag_2 != 2)
                {
                    COMMIT_EXISTENCE_ERROR
                    return ERROR;
                }
                diff_commit(commit_1 , commit_2);
                return SUCCEED;
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
    else if(strcmp(argv[1] , "merge") == 0)
    {
        if(strcmp(argv[2] , "-b") == 0)
        {
            if(argc == 5)
            {
                merge(argv[3] , argv[4]);
                return SUCCEED;
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
    else
    {
        if(argc == 2)
        {
            char* path = NewGit_finder();
            if(path == NULL)
            {
                NewGit_EXISTENCE_ERROR
                return ERROR;
            }
            strcat(path , "/.NewGit/Configuration/localAlias.txt");
            FILE* file_alias_global = fopen("/home/kiarash-sanei/Desktop/NewGit/Configuration/globalAlias.txt" , "r");
            FILE* file_alias_local = fopen(path , "r");
            alias current;
            int flag = 0;
            while(fread(&current , sizeof(alias) , 1 , file_alias_global) == 1)
            {
                if(strcmp(current . shortcut , argv[1]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            fclose(file_alias_global);
            if(flag == 0)
            {
                while(fread(&current , sizeof(alias) , 1 , file_alias_local) == 1)
                {
                    if(strcmp(current . shortcut , argv[1]) == 0)
                    {
                        flag = 1;
                        break;
                    }
                }
                fclose(file_alias_local);
            }
            if(flag == 0)
            {
                goto there;
            }
            else
            {
                char command[MAX_COMMAND_LENGTH];
                strcpy(command , current . command);
                system(command);
                return SUCCEED;
            }
        }
        else
        {
            goto there;
        }
    }
    there:
        INVALID_COMMAND_ERROR
        return ERROR;
}