#include "Header.h"

int add_commit(char* current_branch , char* massage)
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
    if((fread(prior_user , sizeof(user) , 1 , global_user) == sizeof(user)) && (strcmp(prior_user -> name , "") != 0) && (strcmp(prior_user -> email , "") != 0))
    {
        strcpy(current_commit -> commit_user_name , prior_user -> name);
        strcpy(current_commit -> commit_user_email , prior_user -> email);
    }
    else if((fread(prior_user , sizeof(user) , 1 , local_user) == sizeof(user)) && (strcmp(prior_user -> name , "") != 0) && (strcmp(prior_user -> email , "") != 0))
    {
        strcpy(current_commit -> commit_user_name , prior_user -> name);
        strcpy(current_commit -> commit_user_email , prior_user -> email);
    }
    else
    {
        LACK_OF_CONFIGURATION
        return FAILED
    }
    fclose(global_user);
    fclose(local_user);
    free(prior_user);
    srand((unsigned int) current_commit -> commit_time);
    current_commit -> commit_hash = abs(rand() % (2147483647));
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/Branches/");
    strcat(path , current_branch);
    strcat(path , itoa(current_commit -> commit_hash));
    char* stage_path = NewGit_finder();
    strcat(stage_path , "/.NewGit/Stage");
    copy_directory(path , stage_path);
    free(stage_path);
    free(path);
    path = NewGit_finder();
    strcat(path , "/.NewGit/Branches/");
    strcat(path , current_branch);
    strcat(path , "/");
    strcat(path , "commitLog.txt");
    FILE* file = fopen(path , "a");
    fwrite(current_commit , sizeof(commit_information) , 1 , file);
    fclose(file);
    free(current_commit);
    free(path);
    SUCCESS_MASSAGE("Committing")
    return SUCCEED;
}