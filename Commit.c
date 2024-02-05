#include "Header.h"

int add_commit(char* current_branch , char* massage , int* HEAD)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    commit_information* current_commit = (commit_information*) malloc(sizeof(commit_information));
    current_commit -> commit_time = time(NULL);
    strcpy(current_commit -> commit_massage , massage);
    strcat(path , "/.NewGit/Configuration/localUser.txt");
    FILE* global_user = fopen("/home/kiarash-sanei/Desktop/NewGit/Configuration/globalUser.txt" , "r");
    FILE* local_user = fopen(path , "r");
    user* prior_user = (user*) malloc(sizeof(user));
    if(fread(prior_user , sizeof(user) , 1 , local_user) == 1)
    {
        strcpy(current_commit -> commit_user_name , prior_user -> name);
        strcpy(current_commit -> commit_user_email , prior_user -> email);
    }
    else if(fread(prior_user , sizeof(user) , 1 , global_user) == 1)
    {
        strcpy(current_commit -> commit_user_name , prior_user -> name);
        strcpy(current_commit -> commit_user_email , prior_user -> email);
    }
    else
    {
        LACK_OF_CONFIGURATION
        return FAILED;
    }
    fclose(global_user);
    fclose(local_user);
    free(prior_user);
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/Stage");
    DIR* stage = opendir(path);
    dirent* entry = readdir(stage);
    int count = 0;
    while(entry != NULL)
    {
        count++;
        entry = readdir(stage);
    }
    if(count == 2)
    {
        LACK_OF_ADD
        return ERROR;
    }
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/");
    strcat(path , current_branch);
    strcat(path , "/commitLog.txt");
    FILE* file = fopen(path , "r");
    commit_information new;
    if(file != NULL)
    {
        fread(&new , sizeof(commit_information) , 1 , file);
        if(new . commit_hash != *HEAD)
        {
            READ_ONLY_ERROR
            return ERROR;
        }
        fclose(file);
    }
    free(path);
    srand((unsigned int) current_commit -> commit_time);
    current_commit -> commit_hash = abs(rand() % (2147483647));
    *HEAD = current_commit -> commit_hash;
    path = NewGit_finder();
    strcat(path , "/.NewGit/Branches/");
    strcat(path , current_branch);
    strcat(path , "/");
    char commit_hash_string[MAX_COMMIT_HASH_LENGTH];
    strcat(path , citoa(current_commit -> commit_hash , commit_hash_string , 10));
    strcpy(current_commit -> commit_branch , current_branch);
    char* stage_path = NewGit_finder();
    strcat(stage_path , "/.NewGit/Stage");
    copy_directory(path , stage_path);
    free(stage_path);
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/Stage");
    stage = opendir(path);
    entry = readdir(stage);
    count = -2;
    while(entry != NULL)
    {
        count++;
        entry = readdir(stage);
    }
    current_commit -> commit_number = count;
    closedir(stage);
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/stageLog.txt");
    remove(path);
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/commitLog.txt");
    file = fopen(path , "a");
    fwrite(current_commit , sizeof(commit_information) , 1 , file);
    fclose(file);
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/Branches/");
    strcat(path , current_branch);
    strcat(path , "/commitHEAD.txt");
    file = fopen(path , "w");
    fwrite(current_commit , sizeof(commit_information) , 1 , file);
    fclose(file);
    free(current_commit);
    free(path);
    path = NewGit_finder();
    delete_directory(path , "");
    strcat(path , "/.NewGit/Stage");
    mkdir(path , ACCESS);
    free(path);
    SUCCESS_MASSAGE("Committing")
    return SUCCEED;
}
int set(char* massage , char* shortcut)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    massage_information new;
    strcpy(new . massage , massage);
    strcpy(new . shortcut , shortcut);
    strcat(path , "/.NewGit/setting.txt");
    FILE* file = fopen(path , "a");
    fwrite(&new , sizeof(massage_information) , 1 , file);
    fclose(file);
    free(path);
    SUCCESS_MASSAGE("Setting")
    return SUCCEED;
}
int replace(char* new_massage , char* shortcut)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(path , "/.NewGit/setting.txt");
    FILE* file = fopen(path , "r");
    if(file == NULL)
    {
        LACK_OF_SETTING
        return ERROR;
    }
    massage_information current_massage[MAX_SETTING_COUNT];
    int index = 0;
    int flag = 0;
    while(fread(&(current_massage[index]) , sizeof(massage_information) , 1 , file) == 1)
    {
        if(strcmp(current_massage[index] . shortcut , shortcut) == 0)
        {
            flag = 1;
            strcpy(current_massage[index] . massage , new_massage);
        }
        index++;
    }
    fclose(file);
    if(flag == 0)
    {
        SHORTCUT_EXISTENCE_ERROR
        return ERROR;
    }
    file = fopen(path , "w");
    for(int i = 0 ; i < index ; i++)
    {
        fwrite(&(current_massage[i]) , sizeof(massage_information) , 1 , file);
    }
    fclose(file);
    SUCCESS_MASSAGE("Replacing")
    return SUCCEED;
}
int remove_shortcut(char* shortcut)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    strcat(path , "/.NewGit/setting.txt");
    FILE* file = fopen(path , "r");
    if(file == NULL)
    {
        LACK_OF_SETTING
        return ERROR;
    }
    massage_information current_massage[MAX_SETTING_COUNT];
    int index = 0;
    int flag = 0;
    while(fread(&(current_massage[index]) , sizeof(massage_information) , 1 , file) == 1)
    {
        if(strcmp(current_massage[index] . shortcut , shortcut) == 0)
        {
            flag = 1;
            index--;
        }
        index++;
    }
    fclose(file);
    if(flag == 0)
    {
        SHORTCUT_EXISTENCE_ERROR
        return ERROR;
    }
    file = fopen(path , "w");
    for(int i = 0 ; i < index ; i++)
    {
        fwrite(&(current_massage[i]) , sizeof(massage_information) , 1 , file);
    }
    fclose(file);
    SUCCESS_MASSAGE("Removing")
    return SUCCEED;
}