#include "Header.h"

int log_show()
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(path , "/.NewGit/commitLog.txt");
    FILE* file = fopen(path , "r");
    if(file == NULL)
    {
        LACK_OF_COMMIT
        return ERROR;
    }
    commit_information all[MAX_COMMIT_COUNT];
    int index = 0;
    while(fread(&(all[index]) , sizeof(commit_information) , 1 , file) == 1)
    {
        index++;
    } 
    fclose(file);
    for(int i = index -1 ; i > -1 ; i--)
    {
        printf("commit %d:\n" , index - i);
        printf("\tcommit time : %s" , ctime(&(all[i] . commit_time)));
        printf("\tcommit massage : %s\n" , all[i] . commit_massage);
        printf("\tcommit user name : %s\n" , all[i] . commit_user_name);
        printf("\tcommit user email : %s\n" , all[i] . commit_user_email);
        printf("\tcommit hash : %d\n" , all[i] . commit_hash);
        printf("\tcommit branch : %s\n" , all[i] . commit_branch);
        printf("\tcommit action : %d\n" , all[i] . commit_number);
    }
    SUCCESS_MASSAGE("Showing log");
    return SUCCEED;
}
int log_number(int number)
{
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
        index++;
    } 
    fclose(file);
    for(int i = index -1 ; i > -1 ; i--)
    {
        if(number > 0)
        {
            printf("commit %d:\n" , index - i);
            printf("\tcommit time : %s" , ctime(&(all[i] . commit_time)));
            printf("\tcommit massage : %s\n" , all[i] . commit_massage);
            printf("\tcommit user name : %s\n" , all[i] . commit_user_name);
            printf("\tcommit user email : %s\n" , all[i] . commit_user_email);
            printf("\tcommit hash : %d\n" , all[i] . commit_hash);
            printf("\tcommit branch : %s\n" , all[i] . commit_branch);
            printf("\tcommit action : %d\n" , all[i] . commit_number);
            number--;
        }
    }
    SUCCESS_MASSAGE("Showing log");
    return SUCCEED;
}
int log_branch(char* branch_name)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(path , "/.NewGit/Branches");
    DIR* directory = opendir(path);
    dirent* entry = readdir(directory);
    int flag = 0;
    while(entry != NULL)
    {
        if(strcmp(entry -> d_name , branch_name) == 0)
        {
            flag = 1;
            break;
        }
        entry = readdir(directory);    
    }
    if(flag == 0)
    {
        BRANCH_EXISTENCE_ERROR
        return ERROR;
    }
    closedir(directory);
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/commitLog.txt");
    FILE* file = fopen(path , "r");
    commit_information all[MAX_COMMIT_COUNT];
    int index = 0;
    while(fread(&(all[index]) , sizeof(commit_information) , 1 , file) == 1)
    {
        index++;
    } 
    fclose(file);
    int count = 1;
    for(int i = index -1 ; i > -1 ; i--)
    {
        if(strcmp(all[i] . commit_branch , branch_name) == 0)
        {
            printf("commit %d:\n" , count);
            printf("\tcommit time : %s" , ctime(&(all[i] . commit_time)));
            printf("\tcommit massage : %s\n" , all[i] . commit_massage);
            printf("\tcommit user name : %s\n" , all[i] . commit_user_name);
            printf("\tcommit user email : %s\n" , all[i] . commit_user_email);
            printf("\tcommit hash : %d\n" , all[i] . commit_hash);
            printf("\tcommit branch : %s\n" , all[i] . commit_branch);
            printf("\tcommit action : %d\n" , all[i] . commit_number);
            count++;
        }
    }
    SUCCESS_MASSAGE("Showing log");
    return SUCCEED;
}
int log_author(char* user_name)
{
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
        index++;
    } 
    fclose(file);
    int count = 1;
    for(int i = index -1 ; i > -1 ; i--)
    {
        if(strcmp(all[i] . commit_user_name , user_name) == 0)
        {
            printf("commit %d:\n" , count);
            printf("\tcommit time : %s" , ctime(&(all[i] . commit_time)));
            printf("\tcommit massage : %s\n" , all[i] . commit_massage);
            printf("\tcommit user name : %s\n" , all[i] . commit_user_name);
            printf("\tcommit user email : %s\n" , all[i] . commit_user_email);
            printf("\tcommit hash : %d\n" , all[i] . commit_hash);
            printf("\tcommit branch : %s\n" , all[i] . commit_branch);
            printf("\tcommit action : %d\n" , all[i] . commit_number);
            count++;
        }
    }
    SUCCESS_MASSAGE("Showing log");
    return SUCCEED;
}
int log_time_since(time_t since)
{
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
        index++;
    } 
    fclose(file);
    int count = 1;
    for(int i = index -1 ; i > -1 ; i--)
    {
        if(difftime(all[i] . commit_time , since) <= 0)
        {
            printf("commit %d:\n" , count);
            printf("\tcommit time : %s" , ctime(&(all[i] . commit_time)));
            printf("\tcommit massage : %s\n" , all[i] . commit_massage);
            printf("\tcommit user name : %s\n" , all[i] . commit_user_name);
            printf("\tcommit user email : %s\n" , all[i] . commit_user_email);
            printf("\tcommit hash : %d\n" , all[i] . commit_hash);
            printf("\tcommit branch : %s\n" , all[i] . commit_branch);
            printf("\tcommit action : %d\n" , all[i] . commit_number);
            count++;
        }
    }
    SUCCESS_MASSAGE("Showing log");
    return SUCCEED;
}
int log_time_before(time_t before)
{
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
        index++;
    } 
    fclose(file);
    int count = 1;
    for(int i = index -1 ; i > -1 ; i--)
    {
        if(difftime(all[i] . commit_time , before) >= 0)
        {
            printf("commit %d:\n" , count);
            printf("\tcommit time : %s" , ctime(&(all[i] . commit_time)));
            printf("\tcommit massage : %s\n" , all[i] . commit_massage);
            printf("\tcommit user name : %s\n" , all[i] . commit_user_name);
            printf("\tcommit user email : %s\n" , all[i] . commit_user_email);
            printf("\tcommit hash : %d\n" , all[i] . commit_hash);
            printf("\tcommit branch : %s\n" , all[i] . commit_branch);
            printf("\tcommit action : %d\n" , all[i] . commit_number);
            count++;
        }
    }
    SUCCESS_MASSAGE("Showing log");
    return SUCCEED;
}
int log_word(char* word)
{
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
        index++;
    } 
    fclose(file);
    int count = 1;
    for(int i = index -1 ; i > -1 ; i--)
    {
        if(strstr(all[i] . commit_massage , word) != NULL)
        {
            printf("commit %d:\n" , count);
            printf("\tcommit time : %s" , ctime(&(all[i] . commit_time)));
            printf("\tcommit massage : %s\n" , all[i] . commit_massage);
            printf("\tcommit user name : %s\n" , all[i] . commit_user_name);
            printf("\tcommit user email : %s\n" , all[i] . commit_user_email);
            printf("\tcommit hash : %d\n" , all[i] . commit_hash);
            printf("\tcommit branch : %s\n" , all[i] . commit_branch);
            printf("\tcommit action : %d\n" , all[i] . commit_number);
            count++;
        }
    }
    SUCCESS_MASSAGE("Showing log");
    return SUCCEED;
}