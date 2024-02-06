#include "Header.h"

int tag_maker(commit_information commit , char* massage , char* name)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    tag new;
    strcpy(new . tag_massage , massage);
    strcpy(new . commit_massage , commit . commit_massage);
    strcpy(new . tag_name , name);
    strcpy(new . commit_branch , commit . commit_branch);
    strcpy(new . commit_user_email , commit . commit_user_email);
    strcpy(new . commit_user_name , commit . commit_user_name);
    new . commit_time = commit . commit_time;
    new . commit_number = commit . commit_number;
    new . commit_hash = commit . commit_hash;
    strcat(path , "/.NewGit/tagLog.txt");
    FILE* file = fopen(path , "a");
    fwrite(&new , sizeof(tag) , 1 , file);
    fclose(file);
    free(path);
    tag_organizer();
    SUCCESS_MASSAGE("Making tag");
    return SUCCEED;
}
int tag_remaker(commit_information commit , char* massage , char* name)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    tag new;
    strcpy(new . tag_massage , massage);
    strcpy(new . commit_massage , commit . commit_massage);
    strcpy(new . tag_name , name);
    strcpy(new . commit_branch , commit . commit_branch);
    strcpy(new . commit_user_email , commit . commit_user_email);
    strcpy(new . commit_user_name , commit . commit_user_name);
    new . commit_time = commit . commit_time;
    new . commit_number = commit . commit_number;
    new . commit_hash = commit . commit_hash;
    tag all[MAX_TAG_COUNT];
    int index = 0;
    strcat(path , "/.NewGit/tagLog.txt");
    FILE* file = fopen(path , "r");
    while(fread(&(all[index]) , sizeof(tag) , 1 , file) == 1)
    {
        if(strcmp(all[index] . tag_name , name) == 0)
        {
            continue;
        }
        index++;
    }
    fclose(file);
    file = fopen(path , "w");
    for(int i = 0; i < index ; i++)
    {
        fwrite(&(all[i]) , sizeof(tag) , 1 , file);
    }
    fwrite(&new , sizeof(tag) , 1 , file);
    fclose(file);
    free(path);
    tag_organizer();
    SUCCESS_MASSAGE("Making tag");
    return SUCCEED;
}
int tag_organizer()
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    tag all[MAX_TAG_COUNT];
    int index = 0;
    strcat(path , "/.NewGit/tagLog.txt");
    FILE* file = fopen(path , "r");
    while(fread(&(all[index]) , sizeof(tag) , 1 , file) == 1)
    {
        index++;
    }
    for(int i = 0 ; i < index ; i++)
    {
        for(int j = 0 ; j < index ; j++)
        {
            if(i < j)
            {
                if(strcmp(all[i] . tag_name , all[j] . tag_name) > 0)
                {
                    tag temp;
                    strcpy(temp . tag_massage , all[i] . tag_massage);
                    strcpy(temp . commit_massage , all[i] . commit_massage);
                    strcpy(temp . tag_name , all[i] . tag_name);
                    strcpy(temp . commit_branch , all[i] . commit_branch);
                    strcpy(temp . commit_user_email , all[i] . commit_user_email);
                    strcpy(temp . commit_user_name , all[i] . commit_user_name);
                    temp . commit_time = all[i] . commit_time;
                    temp . commit_number = all[i] . commit_number;
                    temp . commit_hash = all[i] . commit_hash;
                    strcpy(all[i] . tag_massage , all[j] . tag_massage);
                    strcpy(all[i] . commit_massage , all[j] . commit_massage);
                    strcpy(all[i] . tag_name , all[j] . tag_name);
                    strcpy(all[i] . commit_branch , all[j] . commit_branch);
                    strcpy(all[i] . commit_user_email , all[j] . commit_user_email);
                    strcpy(all[i] . commit_user_name , all[j] . commit_user_name);
                    all[i] . commit_time = all[j] . commit_time;
                    all[i] . commit_number = all[j] . commit_number;
                    all[i] . commit_hash = all[j] . commit_hash;
                    strcpy(all[j] . tag_massage , temp . tag_massage);
                    strcpy(all[j] . commit_massage , temp . commit_massage);
                    strcpy(all[j] . tag_name , temp . tag_name);
                    strcpy(all[j] . commit_branch , temp . commit_branch);
                    strcpy(all[j] . commit_user_email , temp . commit_user_email);
                    strcpy(all[j] . commit_user_name , temp . commit_user_name);
                    all[j] . commit_time = temp . commit_time;
                    all[j] . commit_number = temp . commit_number;
                    all[j] . commit_hash = temp . commit_hash;
                }
            }
        }
    }
}
int all_tag_shower()
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    tag all[MAX_TAG_COUNT];
    int index = 0;
    strcat(path , "/.NewGit/tagLog.txt");
    FILE* file = fopen(path , "r");
    while(fread(&(all[index]) , sizeof(tag) , 1 , file) == 1)
    {
        index++;
    }
    for(int i = 0 ; i < index ; i++)
    {
        puts(all[i] . tag_name);
    }
}
int tag_shower(char* tag_name)
{
    char* path = NewGit_finder();
    if(path == NULL)
    {
        NewGit_EXISTENCE_ERROR
        return ERROR;
    }
    tag find;
    strcat(path , "/.NewGit/tagLog.txt");
    FILE* file = fopen(path , "r");
    int flag = 0;
    while(fread(&(find) , sizeof(tag) , 1 , file) == 1)
    {
        if(strcmp(find . tag_name , tag_name) == 0)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0)
    {
        TAG_EXISTENCE_ERROR
        return ERROR;
    }
    printf("TAG :\n");
    printf("\ttag name : %s\n" , find . tag_name);
    printf("\ttag massage : %s\n" , find . tag_massage);
    printf("\tcommit hash : %d\n" , find . commit_hash);
    printf("\tcommit branch : %s\n" , find . commit_branch);
    printf("\tcommit massage : %s\n" , find . commit_massage);
    printf("\tcommit user name : %s\n" , find . commit_user_name);
    printf("\tcommit user email : %s\n" , find . commit_user_email);
    printf("\tcommit number : %d\n" , find . commit_number);
    printf("\tcommit time : %s" , ctime(&(find . commit_time)));
}